/*
 * Copyright (c) TSRBerry
 *  -> removed socket initialization
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

#include "ldn_mitm/ldn_module.hpp"
#include "ldn_mitm/ldn_service.hpp"

namespace ams::mitm::ldn
{
    const s32 ThreadPriority = 6;
    const size_t TotalThreads = 2;
    const size_t NumExtraThreads = TotalThreads - 1;
    const size_t ThreadStackSize = 0x4000;

    alignas(os::MemoryPageSize) u8 g_thread_stack[ThreadStackSize];
    os::ThreadType g_thread;

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

        constexpr size_t MaxSessions = 3;

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
            return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::ldn::ILdnUMitmInterface, mitm::ldn::LdnUMitmService>(decltype(fsrv)(fsrv), client_info), fsrv);
        }

        alignas(os::MemoryPageSize) u8 g_extra_thread_stacks[NumExtraThreads][ThreadStackSize];
        os::ThreadType g_extra_threads[NumExtraThreads];

        void LoopServerThread(void *)
        {
            g_server_manager.LoopProcess();
        }

        void ProcessForServerOnAllThreads(void *)
        {
            /* Initialize threads. */
            if constexpr (NumExtraThreads > 0)
            {
                const s32 priority = os::GetThreadCurrentPriority(os::GetCurrentThread());
                for (size_t i = 0; i < NumExtraThreads; i++)
                {
                    R_ABORT_UNLESS(os::CreateThread(g_extra_threads + i, LoopServerThread, nullptr, g_extra_thread_stacks[i], ThreadStackSize, priority));
                    os::SetThreadNamePointer(g_extra_threads + i, "ldn::UMitmThread");
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

    }

    Result Launch()
    {
        constexpr sm::ServiceName MitmServiceName = sm::ServiceName::Encode("ldn:u");
        R_ABORT_UNLESS((g_server_manager.RegisterMitmServer<mitm::ldn::LdnUMitmService>(0, MitmServiceName)));
        log::DEBUG_LOG("Registered mitm server");

        R_TRY(os::CreateThread(
            &g_thread,
            ProcessForServerOnAllThreads,
            nullptr,
            g_thread_stack,
            ThreadStackSize,
            ThreadPriority));

        os::SetThreadNamePointer(&g_thread, "ldn::UMitmMainThread");
        os::StartThread(&g_thread);

        R_SUCCEED();
    }

    void WaitFinished()
    {
        os::WaitThread(&g_thread);
    }
}
