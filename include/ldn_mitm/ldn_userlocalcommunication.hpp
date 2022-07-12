/*
 * Copyright (c) 2022 TSRBerry
 *  -> added LDN forward service
 *  -> added missing arguments for IPC commands
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

#include "logging.hpp"
#include "ldn_types.hpp"
#include "interfaces/icommunication.hpp"
#include "ldn_shim.hpp"

namespace ams::mitm::ldn
{
    class UserLocalCommunicationService
    {
    private:
        std::unique_ptr<LdnUserLocalCommunicationInterface> m_srv;

    public:
        UserLocalCommunicationService(std::unique_ptr<LdnUserLocalCommunicationInterface> s) : m_srv(std::move(s))
        {
            log::DEBUG_LOG("UserLocalCommunicationService");
            /* ... */
        };

        ~UserLocalCommunicationService()
        {
            log::DEBUG_LOG("~UserLocalCommunicationService");
            ldnUserLocalCommunicationInterfaceClose(m_srv.get());
        };

    public:
        Result GetState(sf::Out<u32> state);
        Result GetNetworkInfo(sf::Out<NetworkInfo> buffer);
        Result GetIpv4Address(sf::Out<Ipv4Address> address, sf::Out<SubnetMask> mask);
        Result GetDisconnectReason(sf::Out<s16> reason);
        Result GetSecurityParameter(sf::Out<SecurityParameter> out);
        Result GetNetworkConfig(sf::Out<NetworkConfig> out);
        Result AttachStateChangeEvent(sf::Out<sf::CopyHandle> handle);
        Result GetNetworkInfoLatestUpdate(sf::Out<NetworkInfo> buffer, sf::OutArray<NodeLatestUpdate> pUpdates);
        Result Scan(sf::OutAutoSelectArray<NetworkInfo> buffer, sf::Out<s16> count, LdnScanFilter filter, s16 channel);
        Result ScanPrivate(sf::OutAutoSelectArray<NetworkInfo> buffer, sf::Out<s16> outCount, LdnScanFilter filter, s16 channel);
        Result SetWirelessControllerRestriction(WirelessControllerRestriction in);
        Result SetBluetoothAudioDeviceConnectableMode(u32 in);
        Result OpenAccessPoint();
        Result CloseAccessPoint();
        Result CreateNetwork(CreateNetworkConfig data);
        Result CreateNetworkPrivate(CreateNetworkPrivateConfig data, const sf::InPointerArray<AddressEntry> &entries);
        Result DestroyNetwork();
        Result Reject(LdnIpv4Address addr);
        Result SetAdvertiseData(sf::InAutoSelectBuffer data);
        Result SetStationAcceptPolicy(LdnAcceptPolicy policy);
        Result AddAcceptFilterEntry(LdnMacAddress mac);
        Result ClearAcceptFilter();
        Result OpenStation();
        Result CloseStation();
        Result Connect(ConnectNetworkData param, const LdnNetworkInfo &data);
        Result ConnectPrivate(ConnectNetworkPrivateData param);
        Result Disconnect();
        Result Initialize(const sf::ClientProcessId &client_process_id);
        Result Finalize();
        Result Initialize2(u32 unk, const sf::ClientProcessId &client_process_id);
    };
    static_assert(ams::mitm::ldn::IsIUserLocalCommunicationInterface<UserLocalCommunicationService>);
}
