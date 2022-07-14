#include "ldn_mitm/ldn_userlocalcommunication.hpp"

namespace ams::mitm::ldn
{
    Result UserLocalCommunicationService::GetState(sf::Out<u32> state)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetState ptr: %p", state.GetPointer());
        if (m_config->ldn_u.commands.disable_getstate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetState(m_srv.get(), state.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetState rc: %#x", rc);
        log::DEBUG_LOG("UserLocalCommunicationService::GetState value: %d", state.GetValue());
        return rc;
    }

    Result UserLocalCommunicationService::GetNetworkInfo(sf::Out<NetworkInfo> buffer)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkInfo ptr: %p", buffer.GetPointer());
        if (m_config->ldn_u.commands.disable_getnetworkinfo)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetNetworkInfo(m_srv.get(), buffer.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkInfo rc: %#x", rc);
        log::DEBUG_DATA_DUMP(buffer.GetPointer(), sizeof(NetworkInfo), "UserLocalCommunicationService::GetNetworkInfo NetworkInfo");
        return rc;
    }

    Result UserLocalCommunicationService::GetIpv4Address(sf::Out<LdnIpv4Address> address, sf::Out<LdnSubnetMask> netmask)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetIpv4Address addr ptr: %p netmask ptr: %p", address.GetPointer(), netmask.GetPointer());
        if (m_config->ldn_u.commands.disable_getipv4address)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetIpv4Address(m_srv.get(), address.GetPointer(), netmask.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetIpv4Address rc: %#x", rc);
        log::DEBUG_DATA_DUMP(address.GetPointer(), sizeof(LdnIpv4Address), "UserLocalCommunicationService::GetIpv4Address addr");
        log::DEBUG_DATA_DUMP(netmask.GetPointer(), sizeof(LdnSubnetMask), "UserLocalCommunicationService::GetIpv4Address netmask");
        return rc;
    }

    Result UserLocalCommunicationService::GetDisconnectReason(sf::Out<s16> reason)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetDisconnectReason ptr: %p", reason.GetPointer());
        if (m_config->ldn_u.commands.disable_getdisconnectreason)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetDisconnectReason(m_srv.get(), reason.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetDisconnectReason rc: %#x", rc);
        log::DEBUG_LOG("UserLocalCommunicationService::GetDisconnectReason value: %x", reason.GetValue());
        return rc;
    }

    Result UserLocalCommunicationService::GetSecurityParameter(sf::Out<LdnSecurityParameter> out)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetSecurityParameter ptr: %p", out.GetPointer());
        if (m_config->ldn_u.commands.disable_getsecurityparameter)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetSecurityParameter(m_srv.get(), out.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetSecurityParameter rc: %#x", rc);
        log::DEBUG_DATA_DUMP(out.GetPointer(), sizeof(LdnSecurityParameter), "UserLocalCommunicationService::GetSecurityParameter SecurityParameter");
        return rc;
    }

    Result UserLocalCommunicationService::GetNetworkConfig(sf::Out<LdnNetworkConfig> out)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkConfig ptr: %p", out.GetPointer());
        if (m_config->ldn_u.commands.disable_getnetworkconfig)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetNetworkConfig(m_srv.get(), out.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkConfig rc: %#x", rc);
        log::DEBUG_DATA_DUMP(out.GetPointer(), sizeof(LdnNetworkConfig), "UserLocalCommunicationService::GetNetworkConfig NetworkConfig");
        return rc;
    }

    Result UserLocalCommunicationService::AttachStateChangeEvent(sf::Out<sf::CopyHandle> out_handle)
    {
        os::NativeHandle handle;
        log::DEBUG_LOG("UserLocalCommunicationService::AttachStateChangeEvent");
        if (m_config->ldn_u.commands.disable_attachstatechangeevent)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationAttachStateChangeEvent(m_srv.get(), &handle);
        log::DEBUG_LOG("UserLocalCommunicationService::AttachStateChangeEvent rc: %x", rc);
        out_handle.SetValue(handle, false);
        return rc;
    }

    Result UserLocalCommunicationService::GetNetworkInfoLatestUpdate(sf::Out<NetworkInfo> buffer, sf::OutArray<LdnNodeLatestUpdate> pUpdates)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkInfoLatestUpdate buffer ptr: %p", buffer.GetPointer());
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkInfoLatestUpdate pUpdates ptr: %p size: %" PRIu64, pUpdates.GetPointer(), pUpdates.GetSize());
        if (m_config->ldn_u.commands.disable_getnetworkinfolatestupdate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationGetNetworkInfoLatestUpdate(m_srv.get(), buffer.GetPointer(), pUpdates.GetPointer(), pUpdates.GetSize());
        log::DEBUG_LOG("UserLocalCommunicationService::GetNetworkInfoLatestUpdate rc: %#x", rc);
        log::DEBUG_DATA_DUMP(buffer.GetPointer(), sizeof(NetworkInfo), "UserLocalCommunicationService::GetNetworkInfoLatestUpdate NetworkInfo");
        log::DEBUG_DATA_DUMP(pUpdates.GetPointer(), pUpdates.GetSize(), "UserLocalCommunicationService::GetNetworkInfoLatestUpdate NodeLatestUpdate");
        return rc;
    }

    Result UserLocalCommunicationService::Scan(sf::OutAutoSelectArray<NetworkInfo> buffer, sf::Out<s16> outCount, LdnScanFilter filter, s16 channel)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Scan outCount ptr: %p buffer ptr: %p size: %x", outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize());
        log::DEBUG_LOG("UserLocalCommunicationService::Scan channel value: %x filter ptr: %p", channel, &filter);
        log::DEBUG_DATA_DUMP(&filter, sizeof(LdnScanFilter), "UserLocalCommunicationService::Scan filter");
        if (m_config->ldn_u.commands.disable_scan)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationScan(m_srv.get(), outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize(), channel, filter);
        log::DEBUG_LOG("UserLocalCommunicationService::Scan rc: %#x", rc);
        log::DEBUG_DATA_DUMP(buffer.GetPointer(), buffer.GetSize(), "UserLocalCommunicationService::Scan NetworkInfo");
        return rc;
    }

    Result UserLocalCommunicationService::ScanPrivate(sf::OutAutoSelectArray<NetworkInfo> buffer, sf::Out<s16> outCount, LdnScanFilter filter, s16 channel)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::ScanPrivate outCount ptr: %p buffer ptr: %p size: %x", outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize());
        log::DEBUG_LOG("UserLocalCommunicationService::ScanPrivate channel value: %x filter ptr: %x", channel, &filter);
        log::DEBUG_DATA_DUMP(&filter, sizeof(LdnScanFilter), "UserLocalCommunicationService::ScanPrivate filter");
        if (m_config->ldn_u.commands.disable_scanprivate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationScanPrivate(m_srv.get(), outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize(), channel, filter);
        log::DEBUG_LOG("UserLocalCommunicationService::ScanPrivate rc: %#x", rc);
        log::DEBUG_DATA_DUMP(buffer.GetPointer(), buffer.GetSize(), "UserLocalCommunicationService::ScanPrivate NetworkInfo");
        return rc;
    }

    // HOS: 5.0.0+
    Result UserLocalCommunicationService::SetWirelessControllerRestriction(WirelessControllerRestriction in)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::SetWirelessControllerRestriction value: %d", in);
        if (m_config->ldn_u.commands.disable_setwirelesscontrollerrestriction)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationSetWirelessControllerRestriction(m_srv.get(), in);
        log::DEBUG_LOG("UserLocalCommunicationService::SetWirelessControllerRestriction rc: %#x", rc);
        return rc;
    }

    // HOS: 13.1.0+
    Result UserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode(u32 in)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode value: %d", in);
        if (m_config->ldn_u.commands.disable_setbluetoothaudiodeviceconnectablemode)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(m_srv.get(), in);
        log::DEBUG_LOG("UserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::OpenAccessPoint()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::OpenAccessPoint");
        if (m_config->ldn_u.commands.disable_openaccesspoint)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationOpenAccessPoint(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::OpenAccessPoint rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::CloseAccessPoint()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::CloseAccessPoint");
        if (m_config->ldn_u.commands.disable_closeaccesspoint)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationCloseAccessPoint(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::CloseAccessPoint rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::CreateNetwork(CreateNetworkConfig data)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::CreateNetwork ptr: %p size: %d", &data, sizeof(CreateNetworkConfig));
        log::DEBUG_DATA_DUMP(&data, sizeof(CreateNetworkConfig), "UserLocalCommunicationService::CreateNetwork");
        if (m_config->ldn_u.commands.disable_createnetwork)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationCreateNetwork(m_srv.get(), data);
        log::DEBUG_LOG("UserLocalCommunicationService::CreateNetwork rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::CreateNetworkPrivate(CreateNetworkPrivateConfig data, const sf::InPointerArray<LdnAddressEntry> &entries)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::CreateNetworkPrivate config ptr: %p size: %d", &data, sizeof(CreateNetworkPrivateConfig));
        log::DEBUG_DATA_DUMP(&data, sizeof(CreateNetworkConfig), "UserLocalCommunicationService::CreateNetworkPrivate config");
        log::DEBUG_LOG("UserLocalCommunicationService::CreateNetworkPrivate entries ptr: %p size: %d", entries.GetPointer(), entries.GetSize());
        log::DEBUG_DATA_DUMP(entries.GetPointer(), entries.GetSize(), "UserLocalCommunicationService::CreateNetworkPrivate entries");
        if (m_config->ldn_u.commands.disable_createnetworkprivate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationCreateNetworkPrivate(m_srv.get(), data, entries.GetPointer(), entries.GetSize());
        log::DEBUG_LOG("UserLocalCommunicationService::CreateNetworkPrivate rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::DestroyNetwork()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::DestroyNetwork");
        if (m_config->ldn_u.commands.disable_destroynetwork)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationDestroyNetwork(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::DestroyNetwork rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Reject(LdnIpv4Address addr)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Reject addr: %x", addr);
        if (m_config->ldn_u.commands.disable_reject)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationReject(m_srv.get(), &addr);
        log::DEBUG_LOG("UserLocalCommunicationService::Reject rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::SetAdvertiseData(sf::InAutoSelectBuffer data)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::SetAdvertiseData ptr: %p size: %d", data.GetPointer(), data.GetSize());
        log::DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "UserLocalCommunicationService::SetAdvertiseData data");
        if (m_config->ldn_u.commands.disable_setadvertisedata)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationSetAdvertiseData(m_srv.get(), data.GetPointer(), data.GetSize());
        log::DEBUG_LOG("UserLocalCommunicationService::SetAdvertiseData rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::SetStationAcceptPolicy(LdnAcceptPolicy policy)
    {
        log::DEBUG_DATA_DUMP(&policy, sizeof(LdnAcceptPolicy), "UserLocalCommunicationService::SetStationAcceptPolicy policy");
        if (m_config->ldn_u.commands.disable_setstationacceptpolicy)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationSetStationAcceptPolicy(m_srv.get(), &policy);
        log::DEBUG_LOG("UserLocalCommunicationService::SetStationAcceptPolicy rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::AddAcceptFilterEntry(LdnMacAddress mac)
    {
        log::DEBUG_DATA_DUMP(&mac, sizeof(LdnMacAddress), "UserLocalCommunicationService::AddAcceptFilterEntry mac");
        if (m_config->ldn_u.commands.disable_addacceptfilterentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationAddAcceptFilterEntry(m_srv.get(), &mac);
        log::DEBUG_LOG("UserLocalCommunicationService::AddAcceptFilterEntry rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::ClearAcceptFilter()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::ClearAcceptFilter");
        if (m_config->ldn_u.commands.disable_clearacceptfilter)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationClearAcceptFilter(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::ClearAcceptFilter rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::OpenStation()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::OpenStation");
        if (m_config->ldn_u.commands.disable_openstation)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationOpenStation(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::OpenStation rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::CloseStation()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::CloseStation");
        if (m_config->ldn_u.commands.disable_closestation)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationCloseStation(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::CloseStation rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Connect(ConnectNetworkData param, const LdnNetworkInfo &data)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Connect param ptr: %p networkInfo ptr: %p", &param, data);
        log::DEBUG_DATA_DUMP(&param, sizeof(ConnectNetworkData), "UserLocalCommunicationService::Connect param");
        log::DEBUG_DATA_DUMP(&data, sizeof(LdnNetworkInfo), "UserLocalCommunicationService::Connect networkInfo");
        if (m_config->ldn_u.commands.disable_connect)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationConnect(m_srv.get(), &param, &data);
        log::DEBUG_LOG("UserLocalCommunicationService::Connect rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::ConnectPrivate(ConnectNetworkPrivateData param)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::ConnectPrivate param ptr: %p", &param);
        log::DEBUG_DATA_DUMP(&param, sizeof(ConnectNetworkData), "UserLocalCommunicationService::ConnectPrivate param");
        if (m_config->ldn_u.commands.disable_connectprivate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationConnectPrivate(m_srv.get(), &param);
        log::DEBUG_LOG("UserLocalCommunicationService::ConnectPrivate rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Disconnect()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Disconnect");
        if (m_config->ldn_u.commands.disable_disconnect)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationDisconnect(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::Disconnect rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Initialize(const sf::ClientProcessId &client_process_id)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Initialize pid: %" PRIu64, client_process_id);
        if (m_config->ldn_u.commands.disable_initialize)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationInitialize(m_srv.get(), static_cast<u64>(client_process_id.GetValue()));
        log::DEBUG_LOG("UserLocalCommunicationService::Initialize rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Finalize()
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Finalize");
        if (m_config->ldn_u.commands.disable_finalize)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationFinalize(m_srv.get());
        log::DEBUG_LOG("UserLocalCommunicationService::Finalize rc: %#x", rc);
        return rc;
    }

    Result UserLocalCommunicationService::Initialize2(u32 unk, const sf::ClientProcessId &client_process_id)
    {
        log::DEBUG_LOG("UserLocalCommunicationService::Initialize2 unk: %d pid: %" PRIu64, unk, client_process_id);
        if (m_config->ldn_u.commands.disable_initialize2)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = ldnUserCommunicationInitialize2(m_srv.get(), unk, static_cast<u64>(client_process_id.GetValue()));
        log::DEBUG_LOG("UserLocalCommunicationService::Initialize rc: %#x", rc);
        return rc;
    }
}
