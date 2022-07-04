#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "debug.hpp"
#include "interfaces/ilclservice.hpp"
#include "wlan_lcl_shim.hpp"

namespace ams::mitm::wlan
{

    class WlanLclMitMService : public sf::MitmServiceImplBase
    {
    private:
        using RedirectOnlyLocationResolverFactory = sf::ObjectFactory<sf::StdAllocationPolicy<std::allocator>>;

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        WlanLclMitMService(std::shared_ptr<::Service> &&s, const sm::MitmProcessInfo &c);

        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            LogFormat("should_mitm pid: %" PRIu64 " tid: %" PRIx64, client_info.process_id, client_info.program_id);
            return true;
        }

    public:
        /* Overridden commands. */
        Result OpenMasterMode(u32 in);
        Result CloseMasterMode(u32 in);
        Result OpenClientMode(sf::Out<OpenClientModeData> out);
        Result CloseClientMode(UnknownNetworkData in);
        Result OpenSpectatorMode();
        Result CloseSpectatorMode(const sf::InMapAliasArray<SpectatorModeData> &data);
        Result GetMacAddress();
        Result CreateBss(UnknownNetworkData in);
        Result DestroyBss();
        Result StartScan(UnknownNetworkData in);
        Result StopScan();
        Result Connect(ConnectData in);
        Result CancelConnect(u32 in);
        Result Join(u32 in, sf::Out<sf::CopyHandle> handle);
        Result CancelJoin(sf::Out<CancelJoinData> out);
        Result Disconnect(sf::OutMapAliasBuffer data);
        Result SetBeaconLostCount(sf::Out<sf::CopyHandle> handle);
        Result GetSystemEvent(sf::OutMapAliasBuffer data);
        Result GetConnectionStatus(sf::Out<u32> out);
        Result GetClientStatus(sf::Out<u32> out, sf::OutPointerArray<ClientStatusData> out_data);
        Result GetBssIndicationEvent(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer);
        Result GetBssIndicationInfo(u32 in);
        Result GetState(const sf::InBuffer &in_buffer);
        Result GetAllowedChannels(u32 in);
        Result AddIe(u32 in, sf::Out<u32> out);
        Result DeleteIe(u32 in);
        Result PutFrameRaw(u64 in);
        Result CancelGetFrame(u16 in, sf::Out<u32> out);
        Result CreateRxEntry(u32 in, const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer);
        Result DeleteRxEntry(u32 in, const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer);
        Result AddEthertypeToRxEntry(const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer, sf::InMapAliasBuffer &in_array);
        Result DeleteEthertypeFromRxEntry(DeleteEthertypeFromRxEntryData in, const sf::InMapAliasBuffer &in_array);
        Result GetScanResult(u32 in, sf::Out<u32> out, const sf::InPointerBuffer<ScanResultDataBuffer> &in_buffer);
        Result PutActionFrameOneShot(u32 in);
        Result SetActionFrameWithBeacon(u64 in);
        Result CancelActionFrameWithBeacon(u32 in, sf::Out<u32> out);
        Result CreateRxEntryForActionFrame(u32 in);
        Result DeleteRxEntryForActionFrame(sf::Out<u32> out);
        Result AddSubtypeToRxEntryForActionFrame(u32 in);
        Result DeleteSubtypeFromRxEntryForActionFrame(sf::Out<u32> out, sf::OutPointerBuffer<DeleteSubtypeFromRxEntryForActionFrameDataBuffer> out_buffer);
        Result CancelGetActionFrame(u8 in);
        Result GetRssi(GetRssiData in);
        Result SetMaxAssociationNumber(UnknownNetworkData in);
        Result Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer);
        Result Cmd46(u8 in);
        Result Cmd47(Cmd47Data in, sf::Out<u32> out);
        Result Cmd48(u32 in);
        Result Cmd49(u32 in);
        Result Cmd50();
        Result Cmd51(sf::Out<u32> out);
    };
    static_assert(ams::mitm::wlan::IsIWlanLclMitMService<WlanLclMitMService>);

}
