#include "ldn_icommunication.hpp"

namespace ams::mitm::ldn
{
    static_assert(sizeof(NetworkInfo) == 0x480, "sizeof(NetworkInfo) should be 0x480");
    static_assert(sizeof(ConnectNetworkData) == 0x7C, "sizeof(ConnectNetworkData) should be 0x7C");
    static_assert(sizeof(ScanFilter) == 0x60, "sizeof(ScanFilter) should be 0x60");

    Result IUserLocalCommunicationService::GetState(sf::Out<u32> state)
    {
        LogFormat("IUserLocalCommunicationService::GetState ptr: %p value: %d", state.GetPointer(), state.GetValue());
        Result rc = ldnUserCommunicationGetState(m_srv.get(), state.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetState rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::GetNetworkInfo(sf::Out<NetworkInfo> buffer)
    {
        LogFormat("IUserLocalCommunicationService::GetNetworkInfo ptr: %p", buffer.GetPointer());
        Result rc = ldnUserCommunicationGetNetworkInfo(m_srv.get(), buffer.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetNetworkInfo rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::GetIpv4Address(sf::Out<LdnIpv4Address> address, sf::Out<LdnSubnetMask> netmask)
    {
        LogFormat("IUserLocalCommunicationService::GetIpv4Address addr ptr: %p netmask ptr: %p", address.GetPointer(), netmask.GetPointer());
        Result rc = ldnUserCommunicationGetIpv4Address(m_srv.get(), address.GetPointer(), netmask.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetIpv4Address rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetIpv4Address addr: %x netmask: %x", address.GetValue().addr, netmask.GetValue().mask);
        return rc;
    }

    Result IUserLocalCommunicationService::GetDisconnectReason(sf::Out<s16> reason)
    {
        LogFormat("IUserLocalCommunicationService::GetDisconnectReason ptr: %p", reason.GetPointer());
        Result rc = ldnUserCommunicationGetDisconnectReason(m_srv.get(), reason.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetDisconnectReason rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetDisconnectReason value: %x", reason.GetValue());
        return rc;
    }

    Result IUserLocalCommunicationService::GetSecurityParameter(sf::Out<SecurityParameter> out)
    {
        LogFormat("IUserLocalCommunicationService::GetSecurityParameter ptr: %p", out.GetPointer());
        Result rc = ldnUserCommunicationGetSecurityParameter(m_srv.get(), out.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetSecurityParameter rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetSecurityParameter SecurityParameter:");
        LogHex(out.GetPointer(), sizeof(SecurityParameter));
        return rc;
    }

    Result IUserLocalCommunicationService::GetNetworkConfig(sf::Out<LdnNetworkConfig> out)
    {
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig ptr: %p", out.GetPointer());
        Result rc = ldnUserCommunicationGetNetworkConfig(m_srv.get(), out.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig NetworkConfig:");
        LogHex(out.GetPointer(), sizeof(LdnNetworkConfig));
        return rc;
    }

    Result IUserLocalCommunicationService::AttachStateChangeEvent(sf::Out<sf::CopyHandle> handle)
    {
        LogFormat("IUserLocalCommunicationService::AttachStateChangeEvent");
        Result rc = ldnUserCommunicationAttachStateChangeEvent(m_srv.get(), this->state_event);
        LogFormat("IUserLocalCommunicationService::AttachStateChangeEvent rc: %x", rc);
        handle.SetValue(this->state_event->GetReadableHandle(), true);
        return rc;
    }

    Result IUserLocalCommunicationService::GetNetworkInfoLatestUpdate(sf::Out<NetworkInfo> buffer, sf::OutArray<NodeLatestUpdate> pUpdates)
    {
        LogFormat("IUserLocalCommunicationService::GetNetworkInfoLatestUpdate buffer ptr: %p", buffer.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetNetworkInfoLatestUpdate pUpdates ptr: %p size: %" PRIu64, pUpdates.GetPointer(), pUpdates.GetSize());
        Result rc = ldnUserCommunicationGetNetworkInfoLatestUpdate(m_srv.get(), buffer.GetPointer(), pUpdates.GetPointer(), pUpdates.GetSize());
        LogFormat("IUserLocalCommunicationService::GetNetworkInfoLatestUpdate rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetNetworkInfoLatestUpdate NetworkInfo:");
        LogHex(buffer.GetPointer(), sizeof(NetworkInfo));
        LogFormat("IUserLocalCommunicationService::GetNetworkInfoLatestUpdate NodeLatestUpdate[%d]:", pUpdates.GetSize());
        LogHex(pUpdates.GetPointer(), pUpdates.GetSize());
        return rc;
    }

    Result IUserLocalCommunicationService::Scan(sf::Out<s16> outCount, sf::OutAutoSelectArray<NetworkInfo> buffer, s16 channel, ScanFilter filter)
    {
        LogFormat("IUserLocalCommunicationService::Scan outCount ptr: %p buffer ptr: %p", outCount.GetPointer(), buffer.GetPointer());
        LogFormat("IUserLocalCommunicationService::Scan channel value: %x filter value: %x", channel, filter);
        Result rc = ldnUserCommunicationScan(m_srv.get(), outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize(), channel, filter);
        LogFormat("IUserLocalCommunicationService::Scan rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::Scan NetworkInfo[%d]:", outCount.GetValue());
        LogHex(buffer.GetPointer(), buffer.GetSize());
        return rc;
    }

    Result IUserLocalCommunicationService::ScanPrivate(sf::Out<s16> outCount, sf::OutAutoSelectArray<NetworkInfo> buffer, s16 channel, ScanFilter filter)
    {
        LogFormat("IUserLocalCommunicationService::ScanPrivate outCount ptr: %p buffer ptr: %p", outCount.GetPointer(), buffer.GetPointer());
        LogFormat("IUserLocalCommunicationService::ScanPrivate channel value: %x filter value: %x", channel, filter);
        Result rc = ldnUserCommunicationScanPrivate(m_srv.get(), outCount.GetPointer(), buffer.GetPointer(), buffer.GetSize(), channel, filter);
        LogFormat("IUserLocalCommunicationService::ScanPrivate rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::ScanPrivate NetworkInfo[%d]:", outCount.GetValue());
        LogHex(buffer.GetPointer(), buffer.GetSize());
        return rc;
    }

    // HOS: 5.0.0+
    Result IUserLocalCommunicationService::SetWirelessControllerRestriction(WirelessControllerRestriction in)
    {
        LogFormat("IUserLocalCommunicationService::SetWirelessControllerRestriction value: %d", in);
        Result rc = ldnUserCommunicationSetWirelessControllerRestriction(m_srv.get(), in);
        LogFormat("IUserLocalCommunicationService::SetWirelessControllerRestriction rc: %#x", rc);
        return rc;
    }

    // HOS: 13.1.0+
    Result IUserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode(u32 in)
    {
        LogFormat("IUserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode value: %d", in);
        Result rc = ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(m_srv.get(), in);
        LogFormat("IUserLocalCommunicationService::SetBluetoothAudioDeviceConnectableMode rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::OpenAccessPoint()
    {
        LogFormat("IUserLocalCommunicationService::OpenAccessPoint");
        Result rc = ldnUserCommunicationOpenAccessPoint(m_srv.get());
        LogFormat("IUserLocalCommunicationService::OpenAccessPoint rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::CloseAccessPoint()
    {
        LogFormat("IUserLocalCommunicationService::CloseAccessPoint");
        Result rc = ldnUserCommunicationCloseAccessPoint(m_srv.get());
        LogFormat("IUserLocalCommunicationService::CloseAccessPoint rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::CreateNetwork(CreateNetworkConfig data)
    {
        LogFormat("IUserLocalCommunicationService::CreateNetwork ptr: %p size: %d", &data, sizeof(CreateNetworkConfig));
        LogFormat("IUserLocalCommunicationService::CreateNetwork");
        LogHex(&data, sizeof(CreateNetworkConfig));
        Result rc = ldnUserCommunicationCreateNetwork(m_srv.get(), data);
        LogFormat("IUserLocalCommunicationService::CreateNetwork rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::CreateNetworkPrivate(CreateNetworkPrivateConfig data, const sf::InPointerArray<AddressEntry> &entries)
    {
        LogFormat("IUserLocalCommunicationService::CreateNetworkPrivate config ptr: %p size: %d", &data, sizeof(CreateNetworkPrivateConfig));
        LogFormat("IUserLocalCommunicationService::CreateNetworkPrivate entries ptr: %p size: %d", entries.GetPointer(), entries.GetSize());
        Result rc = ldnUserCommunicationCreateNetworkPrivate(m_srv.get(), data, entries.GetPointer(), entries.GetSize());
        LogFormat("IUserLocalCommunicationService::CreateNetworkPrivate rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::DestroyNetwork()
    {
        LogFormat("IUserLocalCommunicationService::DestroyNetwork");
        Result rc = ldnUserCommunicationDestroyNetwork(m_srv.get());
        LogFormat("IUserLocalCommunicationService::DestroyNetwork rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::Reject(LdnIpv4Address addr)
    {
        LogFormat("IUserLocalCommunicationService::Reject addr: %x", addr);
        Result rc = ldnUserCommunicationReject(m_srv.get(), &addr);
        LogFormat("IUserLocalCommunicationService::Reject rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::SetAdvertiseData(sf::InAutoSelectBuffer data)
    {
        LogFormat("IUserLocalCommunicationService::SetAdvertiseData ptr: %p size: %d", data.GetPointer(), data.GetSize());
        Result rc = ldnUserCommunicationSetAdvertiseData(m_srv.get(), data.GetPointer(), data.GetSize());
        LogFormat("IUserLocalCommunicationService::SetAdvertiseData rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::SetStationAcceptPolicy(LdnAcceptPolicy policy)
    {
        LogFormat("IUserLocalCommunicationService::SetStationAcceptPolicy value: %x", policy);
        Result rc = ldnUserCommunicationSetStationAcceptPolicy(m_srv.get(), &policy);
        LogFormat("IUserLocalCommunicationService::SetStationAcceptPolicy rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::AddAcceptFilterEntry(LdnMacAddress mac)
    {
        LogFormat("IUserLocalCommunicationService::AddAcceptFilterEntry value: %x", mac);
        Result rc = ldnUserCommunicationAddAcceptFilterEntry(m_srv.get(), &mac);
        LogFormat("IUserLocalCommunicationService::AddAcceptFilterEntry rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::ClearAcceptFilter()
    {
        LogFormat("IUserLocalCommunicationService::ClearAcceptFilter");
        Result rc = ldnUserCommunicationClearAcceptFilter(m_srv.get());
        LogFormat("IUserLocalCommunicationService::ClearAcceptFilter rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::OpenStation()
    {
        LogFormat("IUserLocalCommunicationService::OpenStation");
        Result rc = ldnUserCommunicationOpenStation(m_srv.get());
        LogFormat("IUserLocalCommunicationService::OpenStation rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::CloseStation()
    {
        LogFormat("IUserLocalCommunicationService::CloseStation");
        Result rc = ldnUserCommunicationCloseStation(m_srv.get());
        LogFormat("IUserLocalCommunicationService::CloseStation rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::Connect(ConnectNetworkData param, const NetworkInfo &data)
    {
        LogFormat("IUserLocalCommunicationService::Connect param ptr: %p networkInfo ptr: %p", &param, data);
        // LogHex(&data, sizeof(NetworkInfo));
        // LogHex(&param, sizeof(param));
        Result rc = ldnUserCommunicationConnect(m_srv.get(), &param, &data);
        LogFormat("IUserLocalCommunicationService::Connect rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::ConnectPrivate(ConnectNetworkPrivateData param)
    {
        LogFormat("IUserLocalCommunicationService::ConnectPrivate param ptr: %p", &param);
        Result rc = ldnUserCommunicationConnectPrivate(m_srv.get(), &param);
        LogFormat("IUserLocalCommunicationService::ConnectPrivate rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::Disconnect()
    {
        LogFormat("IUserLocalCommunicationService::Disconnect");
        Result rc = ldnUserCommunicationDisconnect(m_srv.get());
        LogFormat("IUserLocalCommunicationService::Disconnect rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::Initialize(const sf::ClientProcessId &client_process_id)
    {
        LogFormat("IUserLocalCommunicationService::Initialize pid: %" PRIu64, client_process_id);
        if (this->state_event == nullptr)
        {
            // ClearMode, inter_process
            this->state_event = new os::SystemEvent(::ams::os::EventClearMode_AutoClear, true);
        }
        Result rc = ldnUserCommunicationInitialize(m_srv.get(), static_cast<u64>(client_process_id.GetValue()));
        LogFormat("IUserLocalCommunicationService::Initialize rc: %#x", rc);
        return rc;
    }

    Result IUserLocalCommunicationService::InitializeSystem2(u64 unk, const sf::ClientProcessId &client_process_id)
    {
        LogFormat("IUserLocalCommunicationService::InitializeSystem2 unk: %d pid: %" PRIu64, unk, client_process_id);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::Finalize()
    {
        LogFormat("IUserLocalCommunicationService::Finalize");
        Result rc = ldnUserCommunicationFinalize(m_srv.get());
        LogFormat("IUserLocalCommunicationService::Finalize rc: %#x", rc);
        return rc;
    }
}
