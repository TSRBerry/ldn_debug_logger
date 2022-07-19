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
        Result OpenMode(u32 in);
        Result CloseMode(u32 in);
        Result GetMacAddress(sf::Out<GetMacAddressData> out);
        Result CreateBss(UnknownNetworkData in);
        Result DestroyBss();
        Result StartScan(const sf::InMapAliasArray<u8> &data);
        Result StopScan();
        Result Connect(UnknownNetworkData in);
        Result CancelConnect();
        Result Join(UnknownNetworkData in);
        Result CancelJoin();
        Result Disconnect(DisconnectData in);
        Result SetBeaconLostCount(u32 in);
        Result GetSystemEvent(u32 in, sf::Out<sf::CopyHandle> out_handle);
        Result GetConnectionStatus(sf::Out<GetConnectionStatusData> out);
        Result GetClientStatus(sf::OutMapAliasBuffer data);
        Result GetBssIndicationEvent(sf::Out<sf::CopyHandle> out_handle);
        Result GetBssIndicationInfo(sf::OutMapAliasBuffer data);
        Result GetState(sf::Out<u32> out);
        Result GetAllowedChannels(sf::Out<u32> out, sf::OutPointerBuffer out_data);
        Result AddIe(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer);
        Result DeleteIe(u32 in);
        Result PutFrameRaw(const sf::InBuffer &in_buffer);
        Result CancelGetFrame(u32 in);
        Result CreateRxEntry(u32 in, sf::Out<u32> out, const sf::InPointerBuffer &in_array);
        Result DeleteRxEntry(u32 in);
        Result AddEthertypeToRxEntry(u64 in);
        Result DeleteEthertypeFromRxEntry(u16 in, sf::Out<u32> out);
        Result AddMatchingDataToRxEntry(u32 in, const sf::InPointerBuffer &in_buffer);
        Result RemoveMatchingDataFromRxEntry(u32 in, const sf::InPointerBuffer &in_buffer);
        Result GetScanResult(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasBuffer out_buffer);
        Result PutActionFrameOneShot(PutActionFrameOneShotData in, const sf::InMapAliasBuffer &in_array);
        Result SetActionFrameWithBeacon(const sf::InMapAliasBuffer &in_buffer);
        Result CancelActionFrameWithBeacon();
        Result CreateRxEntryForActionFrame(u32 in, sf::Out<u32> out, const sf::InPointerBuffer &in_buffer);
        Result DeleteRxEntryForActionFrame(u32 in);
        Result AddSubtypeToRxEntryForActionFrame(u64 in);
        Result DeleteSubtypeFromRxEntryForActionFrame(u32 in, sf::Out<u32> out);
        Result CancelGetActionFrame(u32 in);
        Result GetRssi(sf::Out<u32> out);
        Result SetMaxAssociationNumber(u32 in);
        Result Cmd41(sf::Out<u32> out, sf::OutPointerBuffer out_buffer);
        Result Cmd42(u8 in);
        Result Cmd43(Cmd43Data in);
        Result Cmd44(UnknownNetworkData in);
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
