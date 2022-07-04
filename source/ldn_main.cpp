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

#include "ldn_service.hpp"

namespace ams
{
    namespace
    {
        constexpr size_t MallocBufferSize = 1_MB;
        alignas(os::MemoryPageSize) constinit u8 g_malloc_buffer[MallocBufferSize];
    }

    namespace mitm
    {
        namespace
        {

            struct LdnMitmManagerOptions
            {
                static constexpr size_t PointerBufferSize = 0x1000;
                static constexpr size_t MaxDomains = 0x10;
                static constexpr size_t MaxDomainObjects = 0x100;
                static constexpr bool CanDeferInvokeRequest = false;
                static constexpr bool CanManageMitmServers = true;
            };

            class ServerManager final : public sf::hipc::ServerManager<1, LdnMitmManagerOptions, 3>
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
                return this->AcceptMitmImpl(server, sf::CreateSharedObjectEmplaced<mitm::ldn::ILdnMitMService, mitm::ldn::LdnMitMService>(decltype(fsrv)(fsrv), client_info), fsrv);
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
            fs::SetEnabledAutoAbort(false);

            /* Mount the SD card. */
            R_ABORT_UNLESS(fsdevMountSdmc());
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
        LogFormat("Main");
        constexpr sm::ServiceName MitmServiceName = sm::ServiceName::Encode("ldn:u");
        // sf::hipc::ServerManager<2, LdnMitmManagerOptions, 3> server_manager;
        R_ABORT_UNLESS((mitm::g_server_manager.RegisterMitmServer<mitm::ldn::LdnMitMService>(0, MitmServiceName)));
        LogFormat("Registered");

        mitm::g_server_manager.LoopProcess();
    }
}
