/*
 * Copyright (c) TSRBerry
 *  -> removed socket initialization
 *  -> adapted for wlan sysmodule
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>

#include "wlan_lcl_service.hpp"

namespace ams
{
    namespace
    {
        constexpr size_t MallocBufferSize = 32_KB;
        alignas(os::MemoryPageSize) constinit u8 g_malloc_buffer[MallocBufferSize];
    }

    namespace mitm
    {
        namespace
        {
            struct ServerOptions
            {
                static constexpr size_t PointerBufferSize = 0x1000;
                static constexpr size_t MaxDomains = 0x10;
                static constexpr size_t MaxDomainObjects = 0x100;
                static constexpr bool CanDeferInvokeRequest = false;
                static constexpr bool CanManageMitmServers = true;
            };

            constexpr size_t MaxSessions = 61;

            class ServerManager final : public sf::hipc::ServerManager<1, ServerOptions, MaxSessions>
            {
            private:
                virtual ams::Result OnNeedsToAccept(int port_index, Server *server) override;
            };

            ServerManager g_server_manager;

            Result ServerManager::OnNeedsToAccept(int port_index, Server *server)
            {
                AMS_UNUSED(port_index);
                /* Acknowledge the mitm session. */
                std::shared_ptr<::Service> fsrv;
                sm::MitmProcessInfo client_info;
                server->AcknowledgeMitmSession(std::addressof(fsrv), std::addressof(client_info));
                return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::wlan::IWlanLclMitmInterface, mitm::wlan::WlanLclMitmService>(decltype(fsrv)(fsrv), client_info), fsrv);
            }

            const s32 ThreadPriority = 3;
            const size_t TotalThreads = 4;
            const size_t NumExtraThreads = TotalThreads - 1;
            const size_t ThreadStackSize = 0x4000;

            alignas(os::MemoryPageSize) u8 g_extra_thread_stacks[NumExtraThreads][ThreadStackSize];
            os::ThreadType g_extra_threads[NumExtraThreads];

            void LoopServerThread(void *)
            {
                g_server_manager.LoopProcess();
            }

            void ProcessForServerOnAllThreads()
            {
                /* Initialize threads. */
                if constexpr (NumExtraThreads > 0)
                {
                    const s32 priority = os::GetThreadCurrentPriority(os::GetCurrentThread());
                    for (size_t i = 0; i < NumExtraThreads; i++)
                    {
                        R_ABORT_UNLESS(os::CreateThread(g_extra_threads + i, LoopServerThread, nullptr, g_extra_thread_stacks[i], ThreadStackSize, priority));
                        os::SetThreadNamePointer(g_extra_threads + i, "wlan::LclMitmThread");
                    }
                }

                /* Start extra threads. */
                if constexpr (NumExtraThreads > 0)
                {
                    for (size_t i = 0; i < NumExtraThreads; i++)
                    {
                        os::StartThread(g_extra_threads + i);
                    }
                }

                /* Loop this thread. */
                LoopServerThread(nullptr);

                /* Wait for extra threads to finish. */
                if constexpr (NumExtraThreads > 0)
                {
                    for (size_t i = 0; i < NumExtraThreads; i++)
                    {
                        os::WaitThread(g_extra_threads + i);
                    }
                }
            }

            alignas(0x40) constinit u8 g_heap_memory[128_KB];
            constinit lmem::HeapHandle g_heap_handle;
            constinit bool g_heap_initialized;
            constinit os::SdkMutex g_heap_init_mutex;

            lmem::HeapHandle GetHeapHandle()
            {
                if (AMS_UNLIKELY(!g_heap_initialized))
                {
                    std::scoped_lock lk(g_heap_init_mutex);

                    if (AMS_LIKELY(!g_heap_initialized))
                    {
                        g_heap_handle = lmem::CreateExpHeap(g_heap_memory, sizeof(g_heap_memory), lmem::CreateOption_ThreadSafe);
                        g_heap_initialized = true;
                    }
                }

                return g_heap_handle;
            }

            void *Allocate(size_t size)
            {
                return lmem::AllocateFromExpHeap(GetHeapHandle(), size);
            }

            void Deallocate(void *p, size_t size)
            {
                AMS_UNUSED(size);
                return lmem::FreeToExpHeap(GetHeapHandle(), p);
            }
        }

    }

    namespace init
    {

        void InitializeSystemModule()
        {
            /* Initialize our connection to sm. */
            R_ABORT_UNLESS(sm::Initialize());

            /* Initialize fs. */
            fs::InitializeForSystem();
            fs::SetAllocator(mitm::Allocate, mitm::Deallocate);
            fs::SetEnabledAutoAbort(false);

            /* Mount the SD card. */
            R_ABORT_UNLESS(fs::MountSdCard("sdmc"));
        }

        void FinalizeSystemModule()
        {
            /* ... */
        }

        void Startup()
        {
            /* Initialize the global malloc allocator. */
            init::InitializeAllocator(g_malloc_buffer, sizeof(g_malloc_buffer));
        }

    }

    void NORETURN Exit(int rc)
    {
        AMS_UNUSED(rc);
        AMS_ABORT("Exit called by immortal process");
    }

    void Main()
    {
        R_ABORT_UNLESS(log::Initialize());
        log::DEBUG_LOG("Main");
        constexpr sm::ServiceName MitmServiceName = sm::ServiceName::Encode("wlan:lcl");
        R_ABORT_UNLESS((mitm::g_server_manager.RegisterMitmServer<mitm::wlan::WlanLclMitmService>(0, MitmServiceName)));
        log::DEBUG_LOG("Registered");

        mitm::ProcessForServerOnAllThreads();
    }
}

void *operator new(size_t size)
{
    return ams::mitm::Allocate(size);
}

void *operator new(size_t size, const std::nothrow_t &)
{
    return ams::mitm::Allocate(size);
}

void operator delete(void *p)
{
    return ams::mitm::Deallocate(p, 0);
}

void operator delete(void *p, size_t size)
{
    return ams::mitm::Deallocate(p, size);
}

void *operator new[](size_t size)
{
    return ams::mitm::Allocate(size);
}

void *operator new[](size_t size, const std::nothrow_t &)
{
    return ams::mitm::Allocate(size);
}

void operator delete[](void *p)
{
    return ams::mitm::Deallocate(p, 0);
}

void operator delete[](void *p, size_t size)
{
    return ams::mitm::Deallocate(p, size);
}
