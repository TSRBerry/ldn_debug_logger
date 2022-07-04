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
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CloseMasterMode(u32 in)
    {
        LogFormat("CloseMasterMode in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::OpenClientMode(sf::Out<OpenClientModeData> out)
    {
        LogFormat("OpenClientMode OpenClientModeData ptr: %p", out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CloseClientMode(UnknownNetworkData in)
    {
        LogFormat("CloseClientMode UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::OpenSpectatorMode()
    {
        LogFormat("OpenSpectatorMode");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CloseSpectatorMode(const sf::InMapAliasArray<SpectatorModeData> &data)
    {
        LogFormat("CloseSpectatorMode SpectatorModeData ptr: %p", data.GetPointer());
        LogFormat("CloseSpectatorMode SpectatorModeData:");
        LogHex(data.GetPointer(), data.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetMacAddress()
    {
        LogFormat("GetMacAddress");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CreateBss(UnknownNetworkData in)
    {
        LogFormat("CreateBss UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DestroyBss()
    {
        LogFormat("DestroyBss");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::StartScan(UnknownNetworkData in)
    {
        LogFormat("StartScan UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::StopScan()
    {
        LogFormat("StopScan");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Connect(ConnectData in)
    {
        LogFormat("Connect ConnectData:");
        LogHex(&in, sizeof(ConnectData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CancelConnect(u32 in)
    {
        LogFormat("CancelConnect in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Join(u32 in, sf::Out<sf::CopyHandle> handle)
    {
        LogFormat("Join in value: %x handle ptr: %p", in, &handle);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CancelJoin(sf::Out<CancelJoinData> out)
    {
        LogFormat("CancelJoin CancelJoinData:");
        LogHex(out.GetPointer(), sizeof(CancelJoinData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Disconnect(sf::OutMapAliasBuffer data)
    {
        LogFormat("Disconnect data ptr: %p", data.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::SetBeaconLostCount(sf::Out<sf::CopyHandle> handle)
    {
        LogFormat("SetBeaconLostCount handle ptr: %p", &handle);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetSystemEvent(sf::OutMapAliasBuffer data)
    {
        LogFormat("GetSystemEvent data ptr: %p", data.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetConnectionStatus(sf::Out<u32> out)
    {
        LogFormat("GetConnectionStatus out ptr: %p", out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetClientStatus(sf::Out<u32> out, sf::OutPointerArray<ClientStatusData> out_data)
    {
        LogFormat("GetClientStatus out ptr: %p out_data ptr: %p", out.GetPointer(), out_data.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetBssIndicationEvent(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer)
    {
        LogFormat("GetBssIndicationEvent in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetBssIndicationEvent in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetBssIndicationInfo(u32 in)
    {
        LogFormat("GetBssIndicationInfo in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetState(const sf::InBuffer &in_buffer)
    {
        LogFormat("GetState in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetAllowedChannels(u32 in)
    {
        LogFormat("GetAllowedChannels in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::AddIe(u32 in, sf::Out<u32> out, const sf::InPointerArray<IeData> &in_array)
    {
        LogFormat("AddIe in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("AddIe in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DeleteIe(u32 in)
    {
        LogFormat("DeleteIe in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::PutFrameRaw(u64 in)
    {
        LogFormat("PutFrameRaw in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CancelGetFrame(u16 in, sf::Out<u32> out)
    {
        LogFormat("CancelGetFrame in value: %x out ptr: %p", in, out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CreateRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("CreateRxEntry in value: %x", in);
        LogFormat("CreateRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DeleteRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("DeleteRxEntry in value: %x", in);
        LogFormat("DeleteRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::AddEthertypeToRxEntry(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasBuffer out_buffer)
    {
        LogFormat("AddEthertypeToRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("AddEthertypeToRxEntry out_buffer:");
        LogHex(out_buffer.GetPointer(), out_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DeleteEthertypeFromRxEntry(DeleteEthertypeFromRxEntryData in, const sf::InMapAliasBuffer &in_array)
    {
        LogFormat("DeleteEthertypeFromRxEntry DeleteEthertypeFromRxEntryData:");
        LogHex(&in, sizeof(DeleteEthertypeFromRxEntryData));
        LogFormat("DeleteEthertypeFromRxEntry in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::AddMatchingDataToRxEntry(const sf::InMapAliasBuffer &in_buffer)
    {
        LogFormat("AddMatchingDataToRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::RemoveMatchingDataFromRxEntry()
    {
        LogFormat("RemoveMatchingDataFromRxEntry");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetScanResult(u32 in, sf::Out<u32> out, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("GetScanResult in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetScanResult in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::PutActionFrameOneShot(u32 in)
    {
        LogFormat("PutActionFrameOneShot in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::SetActionFrameWithBeacon(u64 in)
    {
        LogFormat("SetActionFrameWithBeacon in value: %ld", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CancelActionFrameWithBeacon(u32 in, sf::Out<u32> out)
    {
        LogFormat("CancelActionFrameWithBeacon in value: %x, out ptr: %p", in, out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CreateRxEntryForActionFrame(u32 in)
    {
        LogFormat("CreateRxEntryForActionFrame in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DeleteRxEntryForActionFrame(sf::Out<u32> out)
    {
        LogFormat("DeleteRxEntryForActionFrame out ptr:", out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::AddSubtypeToRxEntryForActionFrame(u32 in)
    {
        LogFormat("AddSubtypeToRxEntryForActionFrame in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::DeleteSubtypeFromRxEntryForActionFrame(sf::Out<u32> out, sf::OutPointerBuffer out_buffer)
    {
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out ptr: %p", out.GetPointer());
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out_buffer:");
        LogHex(out_buffer.GetPointer(), out_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::CancelGetActionFrame(u8 in)
    {
        LogFormat("CancelGetActionFrame in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::GetRssi(GetRssiData in)
    {
        LogFormat("GetRssi GetRssiData:");
        LogHex(&in, sizeof(GetRssiData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::SetMaxAssociationNumber(UnknownNetworkData in)
    {
        LogFormat("SetMaxAssociationNumber UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer)
    {
        LogFormat("Cmd45 data:");
        LogHex(&in, sizeof(Cmd45Data));
        LogFormat("Cmd45 in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd46(u8 in)
    {
        LogFormat("Cmd46 in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd47(Cmd47Data in, sf::Out<u32> out)
    {
        LogFormat("Cmd47 data:");
        LogHex(&in, sizeof(Cmd47Data));
        LogFormat("Cmd47 out ptr: %p", out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd48(u32 in)
    {
        LogFormat("Cmd48 in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd49(u32 in)
    {
        LogFormat("Cmd49 in value: %x", in);
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd50()
    {
        LogFormat("Cmd50");
        return sm::mitm::ResultShouldForwardToSession();
    }

    Result WlanLclMitMService::Cmd51(sf::Out<u32> out)
    {
        LogFormat("Cmd51 out ptr: %p", out.GetPointer());
        return sm::mitm::ResultShouldForwardToSession();
    }
}
