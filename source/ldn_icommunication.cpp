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

    Result IUserLocalCommunicationService::GetNetworkConfig(sf::Out<NetworkConfig> out)
    {
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig ptr: %p", out.GetPointer());
        Result rc = ldnUserCommunicationGetNetworkConfig(m_srv.get(), out.GetPointer());
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig rc: %#x", rc);
        LogFormat("IUserLocalCommunicationService::GetNetworkConfig NetworkConfig:");
        LogHex(out.GetPointer(), sizeof(NetworkConfig));
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

    Result IUserLocalCommunicationService::SetWirelessControllerRestriction(WirelessControllerRestriction in)
    {
        LogFormat("IUserLocalCommunicationService::SetWirelessControllerRestriction value: %d", in);
        Result rc = ldnUserCommunicationSetWirelessControllerRestriction(m_srv.get(), in);
        LogFormat("IUserLocalCommunicationService::SetWirelessControllerRestriction rc: %#x", rc);
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

    Result IUserLocalCommunicationService::OpenAccessPoint()
    {
        LogFormat("IUserLocalCommunicationService::OpenAccessPoint");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::CloseAccessPoint()
    {
        LogFormat("IUserLocalCommunicationService::CloseAccessPoint");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::DestroyNetwork()
    {
        LogFormat("IUserLocalCommunicationService::DestroyNetwork");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::OpenStation()
    {
        LogFormat("IUserLocalCommunicationService::OpenStation");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::CloseStation()
    {
        LogFormat("IUserLocalCommunicationService::CloseStation");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::Disconnect()
    {
        LogFormat("IUserLocalCommunicationService::Disconnect");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::CreateNetwork(CreateNetworkConfig data)
    {
        LogFormat("IUserLocalCommunicationService::CreateNetwork ptr: %p size: %d", &data, sizeof(data));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::SetAdvertiseData(sf::InAutoSelectBuffer data)
    {
        LogFormat("IUserLocalCommunicationService::SetAdvertiseData ptr: %p size: %d", data.GetPointer(), data.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::Connect(ConnectNetworkData param, const NetworkInfo &data)
    {
        LogFormat("IUserLocalCommunicationService::Connect param ptr: %p networkInfo ptr: %p", &param, data);
        // LogHex(&data, sizeof(NetworkInfo));
        // LogHex(&param, sizeof(param));
        return sm::mitm::ResultShouldForwardToSession();
    }

    /*nyi*/
    Result IUserLocalCommunicationService::SetStationAcceptPolicy(u8 policy)
    {
        LogFormat("IUserLocalCommunicationService::SetStationAcceptPolicy value: %x", policy);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::CreateNetworkPrivate()
    {
        LogFormat("IUserLocalCommunicationService::CreateNetworkPrivate");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::Reject()
    {
        LogFormat("IUserLocalCommunicationService::Reject");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::AddAcceptFilterEntry()
    {
        LogFormat("IUserLocalCommunicationService::AddAcceptFilterEntry");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::ClearAcceptFilter()
    {
        LogFormat("IUserLocalCommunicationService::ClearAcceptFilter");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result IUserLocalCommunicationService::ConnectPrivate()
    {
        LogFormat("IUserLocalCommunicationService::ConnectPrivate");
        return sm::mitm::ResultShouldForwardToSession();
    }
}