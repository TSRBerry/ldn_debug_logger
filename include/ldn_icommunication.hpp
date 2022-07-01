/*
 * Copyright (c) 2018 Atmosphère-NX
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

#pragma once
#include <stratosphere.hpp>
#include <switch.h>

#include "debug.hpp"
#include "ldn_types.hpp"
#include "interfaces/icommunication.hpp"
#include "ldn_shim.hpp"

namespace ams::mitm::ldn
{
    class IUserLocalCommunicationService
    {
    private:
        std::unique_ptr<::LdnIUserLocalCommunicationInterface> m_srv;
        os::SystemEvent *state_event;

    public:
        IUserLocalCommunicationService(std::unique_ptr<::LdnIUserLocalCommunicationInterface> s) : m_srv(std::move(s)), state_event(nullptr)
        {
            LogFormat("IUserLocalCommunicationService");
            /* ... */
        };

        ~IUserLocalCommunicationService()
        {
            LogFormat("~IUserLocalCommunicationService");
            if (this->state_event != nullptr)
            {
                delete this->state_event;
                this->state_event = nullptr;
            }
            ldnIUserLocalCommunicationInterfaceClose(m_srv.get());
        };

    public:
        Result GetState(sf::Out<u32> state);
        Result GetNetworkInfo(sf::Out<NetworkInfo> buffer);
        Result GetIpv4Address(sf::Out<LdnIpv4Address> address, sf::Out<LdnSubnetMask> mask);
        Result GetDisconnectReason(sf::Out<s16> reason);
        Result GetSecurityParameter(sf::Out<SecurityParameter> out);
        Result GetNetworkConfig(sf::Out<NetworkConfig> out);
        Result AttachStateChangeEvent(sf::Out<sf::CopyHandle> handle);
        Result GetNetworkInfoLatestUpdate(sf::Out<NetworkInfo> buffer, sf::OutArray<NodeLatestUpdate> pUpdates);
        Result Scan(sf::Out<s16> count, sf::OutAutoSelectArray<NetworkInfo> buffer, s16 channel, ScanFilter filter);
        Result ScanPrivate(sf::Out<s16> outCount, sf::OutAutoSelectArray<NetworkInfo> buffer, s16 channel, ScanFilter filter);
        Result SetWirelessControllerRestriction(WirelessControllerRestriction in);
        Result SetBluetoothAudioDeviceConnectableMode(u32 in);
        Result OpenAccessPoint();
        Result CloseAccessPoint();
        Result CreateNetwork(CreateNetworkConfig data);
        Result CreateNetworkPrivate(CreateNetworkPrivateConfig data, const sf::InPointerArray<AddressEntry> &entries);
        Result Initialize(const sf::ClientProcessId &client_process_id);
        Result Finalize();
        Result DestroyNetwork();
        Result OpenStation();
        Result CloseStation();
        Result Disconnect();
        Result SetAdvertiseData(sf::InAutoSelectBuffer data);
        Result Connect(ConnectNetworkData dat, const NetworkInfo &data);

        /*nyi----------------------------------------------------------------------------*/
        Result Reject();
        Result AddAcceptFilterEntry();
        Result ClearAcceptFilter();
        Result ConnectPrivate();
        Result SetStationAcceptPolicy(u8 policy);
        Result InitializeSystem2(u64 unk, const sf::ClientProcessId &client_process_id);
        /*-------------------------------------------------------------------------------*/
    };
    static_assert(ams::mitm::ldn::IsIUserLocalCommunicationInterface<IUserLocalCommunicationService>);
}
