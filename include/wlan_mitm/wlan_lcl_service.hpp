#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "logging.hpp"
#include "dlog_config.hpp"
#include "interfaces/ilclservice.hpp"
#include "wlan_lcl_shim.hpp"

namespace ams::mitm::wlan
{

    class WlanLclMitmService : public sf::MitmServiceImplBase
    {
    private:
        DLogConfig *m_config = ams::mitm::GetConfigInstance();

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            DEBUG_LOG("should_mitm pid: %" PRIu64 " tid: 0%" PRIx64, client_info.process_id, client_info.program_id);
            if (!ams::mitm::GetConfigInstance()->wlan_lcl.enable_mitm)
            {
                return false;
            }
            return client_info.program_id == ncm::SystemProgramId::Ldn;
        }

    public:
        /* Overridden commands. */
        Result OpenMode(Mode mode);
        Result CloseMode(Mode mode);
        Result GetMacAddress(sf::Out<LdnMacAddress> out);
        Result CreateBss(Bss in);
        Result DestroyBss();
        Result StartScan(const sf::InMapAliasArray<ams::mitm::wlan::ScanRequest> &request);
        Result StopScan();
        Result Connect(ams::mitm::wlan::ConnectParam in);
        Result CancelConnect();
        Result Join(ams::mitm::wlan::ConnectParam in);
        Result CancelJoin();
        Result Disconnect(DisconnectData in);
        Result SetBeaconLostCount(u32 beaconLostCount);
        Result GetSystemEvent(u32 systemEventType, sf::Out<sf::CopyHandle> eventHandle);
        Result GetConnectionStatus(sf::Out<ConnectionStatus> status);
        Result GetClientStatus(sf::OutMapAliasArray<ams::mitm::wlan::ClientStatus> status);
        Result GetBssIndicationEvent(sf::Out<sf::CopyHandle> eventHandle);
        Result GetBssIndicationInfo(sf::OutMapAliasBuffer data);
        Result GetState(sf::Out<ams::mitm::wlan::State> state);
        Result GetAllowedChannels(sf::Out<u32> allowedChannelsCount, sf::OutPointerBuffer out_data);
        Result AddIe(u32 managementFrameType, sf::Out<u32> ie, const sf::InBuffer &in_buffer);
        Result DeleteIe(u32 ie);
        Result PutFrameRaw(const sf::InBuffer &in_buffer);
        Result CancelGetFrame(u32 rxId);
        Result CreateRxEntry(u32 capacity, sf::Out<u32> rxId, const sf::InPointerBuffer &in_array);
        Result DeleteRxEntry(u32 rxId);
        Result AddEthertypeToRxEntry(u32 rxId, u32 protocol);
        Result DeleteEthertypeFromRxEntry(u16 protocol, sf::Out<u32> out);
        Result AddMatchingDataToRxEntry(u32 rxId, const sf::InPointerBuffer &in_buffer);
        Result RemoveMatchingDataFromRxEntry(u32 rxId, const sf::InPointerBuffer &in_buffer);
        Result GetScanResult(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasArray<ams::mitm::wlan::ScanResult> result);
        Result PutActionFrameOneShot(PutActionFrameOneShotData in, const sf::InMapAliasBuffer &in_array);
        Result SetActionFrameWithBeacon(const sf::InMapAliasBuffer &in_buffer);
        Result CancelActionFrameWithBeacon();
        Result CreateRxEntryForActionFrame(u32 capacity, sf::Out<u32> rxId, const sf::InPointerBuffer &in_buffer);
        Result DeleteRxEntryForActionFrame(u32 rxId);
        Result AddSubtypeToRxEntryForActionFrame(u32 rxId, u32 subType);
        Result DeleteSubtypeFromRxEntryForActionFrame(u32 subType, sf::Out<u32> out);
        Result CancelGetActionFrame(u32 rxId);
        Result GetRssi(sf::Out<u32> rssi);
        Result SetMaxAssociationNumber(u32 maxAssociationNumber);
        Result Cmd41(sf::Out<u32> out, sf::OutPointerBuffer out_buffer);
        Result Cmd42(u8 in);
        Result Cmd43(Cmd43Data in);
        Result Cmd44(Bss in);
        Result Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer);
        Result Cmd46(u8 in);
        Result Cmd47(Cmd47Data in, sf::Out<u32> out);
        Result Cmd48(u32 in);
        Result Cmd49(u32 in);
        Result Cmd50();
        Result Cmd51(sf::Out<u32> out);
    };
    static_assert(ams::mitm::wlan::IsIWlanLclMitmInterface<WlanLclMitmService>);

}
