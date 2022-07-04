/*
 * Copyright (c) 2022 TSRBerry
 *  -> added wlan forward service
 *  -> adapted for wlan sysmodule
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

#include <switch.h>

#include "debug.hpp"
#include "wlan_lcl_service.hpp"

namespace ams::mitm::wlan
{
    using ObjectFactory = ams::sf::ObjectFactory<ams::sf::StdAllocationPolicy<std::allocator>>;

    WlanLclMitMService::WlanLclMitMService(std::shared_ptr<::Service> &&s, const sm::MitmProcessInfo &c) : sf::MitmServiceImplBase(std::forward<std::shared_ptr<::Service>>(s), c)
    {
        LogFormat("wlan:lcl Created");
    }

    Result WlanLclMitMService::OpenMasterMode(u32 in)
    {
        LogFormat("OpenMasterMode in value: %x", in);
    }

    Result WlanLclMitMService::CloseMasterMode(u32 in)
    {
        LogFormat("CloseMasterMode in value: %x", in);
    }

    Result WlanLclMitMService::OpenClientMode(sf::Out<OpenClientModeData> out)
    {
        LogFormat("OpenClientMode OpenClientModeData ptr: %p", out.GetPointer());
    }

    Result WlanLclMitMService::CloseClientMode(UnknownNetworkData in)
    {
        LogFormat("CloseClientMode UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
    }

    Result WlanLclMitMService::OpenSpectatorMode()
    {
        LogFormat("OpenSpectatorMode");
    }

    Result WlanLclMitMService::CloseSpectatorMode(const sf::InMapAliasArray<SpectatorModeData> &data)
    {
        LogFormat("CloseSpectatorMode SpectatorModeData ptr: %p", data.GetPointer());
        LogFormat("CloseSpectatorMode SpectatorModeData:");
        LogHex(data.GetPointer(), data.GetSize());
    }

    Result WlanLclMitMService::GetMacAddress()
    {
        LogFormat("GetMacAddress");
    }

    Result WlanLclMitMService::CreateBss(UnknownNetworkData in)
    {
        LogFormat("CreateBss UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
    }

    Result WlanLclMitMService::DestroyBss()
    {
        LogFormat("DestroyBss");
    }

    Result WlanLclMitMService::StartScan(UnknownNetworkData in)
    {
        LogFormat("StartScan UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
    }

    Result WlanLclMitMService::StopScan()
    {
        LogFormat("StopScan");
    }

    Result WlanLclMitMService::Connect(ConnectData in)
    {
        LogFormat("Connect ConnectData:");
        LogHex(&in, sizeof(ConnectData));
    }

    Result WlanLclMitMService::CancelConnect(u32 in)
    {
        LogFormat("CancelConnect in value: %x", in);
    }

    Result WlanLclMitMService::Join(u32 in, sf::Out<sf::CopyHandle> handle)
    {
        LogFormat("Join in value: %x handle ptr: %p", in, handle.GetPointer());
    }

    Result WlanLclMitMService::CancelJoin(sf::Out<CancelJoinData> out)
    {
        LogFormat("CancelJoin CancelJoinData:");
        LogHex(out.GetPointer(), sizeof(CancelJoinData));
    }

    Result WlanLclMitMService::Disconnect(sf::OutMapAliasBuffer data)
    {
        LogFormat("Disconnect data ptr: %p", data.GetPointer());
    }

    Result WlanLclMitMService::SetBeaconLostCount(sf::Out<sf::CopyHandle> handle)
    {
        LogFormat("SetBeaconLostCount handle ptr: %p", handle.GetPointer());
    }

    Result WlanLclMitMService::GetSystemEvent(sf::OutMapAliasBuffer data)
    {
        LogFormat("GetSystemEvent data ptr: %p", data.GetPointer());
    }

    Result WlanLclMitMService::GetConnectionStatus(sf::Out<u32> out)
    {
        LogFormat("GetConnectionStatus out ptr: %p", out.GetPointer());
    }

    Result WlanLclMitMService::GetClientStatus(sf::Out<u32> out, sf::OutPointerArray<ClientStatusData> out_data)
    {
        LogFormat("GetClientStatus out ptr: %p out_data ptr: %p", out.GetPointer(), out_data.GetPointer());
    }

    Result WlanLclMitMService::GetBssIndicationEvent(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer)
    {
        LogFormat("GetBssIndicationEvent in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetBssIndicationEvent in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
    }

    Result WlanLclMitMService::GetBssIndicationInfo(u32 in)
    {
        LogFormat("GetBssIndicationInfo in value: %x", in);
    }

    Result WlanLclMitMService::GetState(const sf::InBuffer &in_buffer)
    {
        LogFormat("GetState in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
    }

    Result WlanLclMitMService::GetAllowedChannels(u32 in)
    {
        LogFormat("GetAllowedChannels in value: %x", in);
    }

    Result WlanLclMitMService::AddIe(u32 in, sf::Out<u32> out)
    {
        LogFormat("AddIe in value: %x out ptr: %p", in, out.GetPointer());
    }

    Result WlanLclMitMService::DeleteIe(u32 in)
    {
        LogFormat("DeleteIe in value: %x", in);
    }

    Result WlanLclMitMService::PutFrameRaw(u64 in)
    {
        LogFormat("PutFrameRaw in value: %x", in);
    }

    Result WlanLclMitMService::CancelGetFrame(u16 in, sf::Out<u32> out)
    {
        LogFormat("CancelGetFrame in value: %x out ptr: %p", in, out.GetPointer());
    }

    Result WlanLclMitMService::CreateRxEntry(u32 in, const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer)
    {
        LogFormat("CreateRxEntry in value: %x", in);
        LogFormat("CreateRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
    }

    Result WlanLclMitMService::DeleteRxEntry(u32 in, const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer)
    {
        LogFormat("DeleteRxEntry in value: %x", in);
        LogFormat("DeleteRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
    }

    Result WlanLclMitMService::AddEthertypeToRxEntry(const sf::InPointerBuffer<RxEntryDataBuffer> &in_buffer, sf::InMapAliasBuffer &in_array)
    {
        LogFormat("AddEthertypeToRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), sizeof(RxEntryDataBuffer));
        LogFormat("AddEthertypeToRxEntry in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
    }

    Result WlanLclMitMService::DeleteEthertypeFromRxEntry(DeleteEthertypeFromRxEntryData in, const sf::InMapAliasBuffer &in_array)
    {
        LogFormat("DeleteEthertypeFromRxEntry DeleteEthertypeFromRxEntryData:");
        LogHex(&in, sizeof(DeleteEthertypeFromRxEntryData));
        LogFormat("DeleteEthertypeFromRxEntry in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
    }

    Result WlanLclMitMService::GetScanResult(u32 in, sf::Out<u32> out, const sf::InPointerBuffer<ScanResultDataBuffer> &in_buffer)
    {
        LogFormat("GetScanResult in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetScanResult in_buffer:");
        LogHex(in_buffer.GetPointer(), sizeof(ScanResultDataBuffer));
    }

    Result WlanLclMitMService::PutActionFrameOneShot(u32 in)
    {
        LogFormat("PutActionFrameOneShot in value: %x", in);
    }

    Result WlanLclMitMService::SetActionFrameWithBeacon(u64 in)
    {
        LogFormat("SetActionFrameWithBeacon in value: %ld", in);
    }

    Result WlanLclMitMService::CancelActionFrameWithBeacon(u32 in, sf::Out<u32> out)
    {
        LogFormat("CancelActionFrameWithBeacon in value: %x, out ptr: %p", in, out.GetPointer());
    }

    Result WlanLclMitMService::CreateRxEntryForActionFrame(u32 in)
    {
        LogFormat("CreateRxEntryForActionFrame in value: %x", in);
    }

    Result WlanLclMitMService::DeleteRxEntryForActionFrame(sf::Out<u32> out)
    {
        LogFormat("DeleteRxEntryForActionFrame out ptr:", out.GetPointer());
    }

    Result WlanLclMitMService::AddSubtypeToRxEntryForActionFrame(u32 in)
    {
        LogFormat("AddSubtypeToRxEntryForActionFrame in value: %x", in);
    }

    Result WlanLclMitMService::DeleteSubtypeFromRxEntryForActionFrame(sf::Out<u32> out, sf::OutPointerBuffer<DeleteSubtypeFromRxEntryForActionFrameDataBuffer> out_buffer)
    {
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out ptr: %p", out.GetPointer());
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out_buffer:");
        LogHex(out_buffer.GetPointer(), sizeof(DeleteSubtypeFromRxEntryForActionFrameDataBuffer));
    }

    Result WlanLclMitMService::CancelGetActionFrame(u8 in)
    {
        LogFormat("CancelGetActionFrame in value: %x", in);
    }

    Result WlanLclMitMService::GetRssi(GetRssiData in)
    {
        LogFormat("GetRssi GetRssiData:");
        LogHex(&in, sizeof(GetRssiData));
    }

    Result WlanLclMitMService::SetMaxAssociationNumber(UnknownNetworkData in)
    {
        LogFormat("SetMaxAssociationNumber UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
    }

    Result WlanLclMitMService::Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer)
    {
        LogFormat("Cmd45 data:");
        LogHex(&in, sizeof(Cmd45Data));
        LogFormat("Cmd45 in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
    }

    Result WlanLclMitMService::Cmd46(u8 in)
    {
        LogFormat("Cmd46 in value: %x", in);
    }

    Result WlanLclMitMService::Cmd47(Cmd47Data in, sf::Out<u32> out)
    {
        LogFormat("Cmd47 data:");
        LogHex(&in, sizeof(Cmd47Data));
        LogFormat("Cmd47 out ptr: %p", out.GetPointer());
    }

    Result WlanLclMitMService::Cmd48(u32 in)
    {
        LogFormat("Cmd48 in value: %x", in);
    }

    Result WlanLclMitMService::Cmd49(u32 in)
    {
        LogFormat("Cmd49 in value: %x", in);
    }

    Result WlanLclMitMService::Cmd50()
    {
        LogFormat("Cmd50");
    }

    Result WlanLclMitMService::Cmd51(sf::Out<u32> out)
    {
        LogFormat("Cmd51 out ptr: %p", out.GetPointer());
    }
}
