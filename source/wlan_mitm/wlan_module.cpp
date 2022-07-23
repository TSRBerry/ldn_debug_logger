/*
 * Copyright (c) TSRBerry
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

#include "wlan_mitm/wlan_module.hpp"
#include "wlan_mitm/wlan_lcl_service.hpp"
#include "wlan_mitm/wlan_lg_service.hpp"
#include "wlan_mitm/wlan_lga_service.hpp"

namespace ams::mitm::wlan
{
    const s32 ThreadPriority = 3;
    const size_t TotalThreads = 4;
    const size_t NumExtraThreads = TotalThreads - 1;
    const size_t ThreadStackSize = 0x4000;

    alignas(os::MemoryPageSize) u8 g_thread_stack[ThreadStackSize];
    os::ThreadType g_thread;

    namespace
    {
        enum PortIndex
        {
            PortIndex_WlanLcl,
            PortIndex_WlanLg,
            PortIndex_WlanLga,

            PortIndex_Count
        };

        struct ServerOptions
        {
            static constexpr size_t PointerBufferSize = 0x1000;
            static constexpr size_t MaxDomains = 0x10;
            static constexpr size_t MaxDomainObjects = 0x100;
            static constexpr bool CanDeferInvokeRequest = false;
            static constexpr bool CanManageMitmServers = true;
        };

        constexpr size_t MaxSessions = 61;

        class ServerManager final : public sf::hipc::ServerManager<PortIndex_Count, ServerOptions, MaxSessions>
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

            switch (port_index)
            {
            case PortIndex_WlanLcl:
                return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::wlan::IWlanLclMitmInterface, mitm::wlan::WlanLclMitmService>(decltype(fsrv)(fsrv), client_info), fsrv);
            case PortIndex_WlanLg:
                return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::wlan::IWlanLgMitmInterface, mitm::wlan::WlanLgMitmService>(decltype(fsrv)(fsrv), client_info), fsrv);
            case PortIndex_WlanLga:
                return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::wlan::IWlanLgaMitmInterface, mitm::wlan::WlanLgaMitmService>(decltype(fsrv)(fsrv), client_info), fsrv);

                AMS_UNREACHABLE_DEFAULT_CASE();
            }
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
                    os::SetThreadNamePointer(g_extra_threads + i, "wlan::MitmThread");
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
        constexpr sm::ServiceName WlanLclServiceName = sm::ServiceName::Encode("wlan:lcl");
        constexpr sm::ServiceName WlanLgServiceName = sm::ServiceName::Encode("wlan:lg");
        constexpr sm::ServiceName WlanLgaServiceName = sm::ServiceName::Encode("wlan:lga");
        R_ABORT_UNLESS((g_server_manager.RegisterMitmServer<mitm::wlan::WlanLclMitmService>(PortIndex_WlanLcl, WlanLclServiceName)));
        R_ABORT_UNLESS((g_server_manager.RegisterMitmServer<mitm::wlan::WlanLgMitmService>(PortIndex_WlanLg, WlanLgServiceName)));
        R_ABORT_UNLESS((g_server_manager.RegisterMitmServer<mitm::wlan::WlanLgaMitmService>(PortIndex_WlanLga, WlanLgaServiceName)));
        DEBUG_LOG("Registered mitm server");

        R_TRY(os::CreateThread(
            &g_thread,
            ProcessForServerOnAllThreads,
            nullptr,
            g_thread_stack,
            ThreadStackSize,
            ThreadPriority));

        os::SetThreadNamePointer(&g_thread, "wlan::MitmMainThread");
        os::StartThread(&g_thread);

        R_SUCCEED();
    }

    void WaitFinished()
    {
        os::WaitThread(&g_thread);
    }
}
