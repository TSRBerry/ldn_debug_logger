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
    Result WlanLclMitmService::OpenMasterMode(u32 in)
    {
        LogFormat("OpenMasterMode in value: %x", in);
        Result rc = wlanLocalManagerOpenMasterMode(m_forward_service.get(), in);
        LogFormat("OpenMasterMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseMasterMode(u32 in)
    {
        LogFormat("CloseMasterMode in value: %x", in);
        Result rc = wlanLocalManagerCloseMasterMode(m_forward_service.get(), in);
        LogFormat("CloseMasterMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::OpenClientMode(sf::Out<OpenClientModeData> out)
    {
        LogFormat("OpenClientMode OpenClientModeData ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerOpenClientMode(m_forward_service.get(), out.GetPointer());
        LogFormat("OpenClientMode OpenClientModeData:");
        LogHex(out.GetPointer(), sizeof(OpenClientModeData));
        LogFormat("OpenClientMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseClientMode(UnknownNetworkData in)
    {
        LogFormat("CloseClientMode UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        Result rc = wlanLocalManagerCloseClientMode(m_forward_service.get(), in);
        LogFormat("CloseClientMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::OpenSpectatorMode()
    {
        LogFormat("OpenSpectatorMode");
        Result rc = wlanLocalManagerOpenSpectatorMode(m_forward_service.get());
        LogFormat("OpenSpectatorMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseSpectatorMode(const sf::InMapAliasArray<SpectatorModeData> &data)
    {
        LogFormat("CloseSpectatorMode SpectatorModeData ptr: %p", data.GetPointer());
        LogFormat("CloseSpectatorMode SpectatorModeData:");
        LogHex(data.GetPointer(), data.GetSize());
        Result rc = wlanLocalManagerCloseSpectatorMode(m_forward_service.get(), data.GetPointer());
        LogFormat("CloseSpectatorMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetMacAddress()
    {
        LogFormat("GetMacAddress");
        Result rc = wlanLocalManagerGetMacAddress(m_forward_service.get());
        LogFormat("GetMacAddress rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateBss(UnknownNetworkData in)
    {
        LogFormat("CreateBss UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        Result rc = wlanLocalManagerCreateBss(m_forward_service.get(), in);
        LogFormat("CreateBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DestroyBss()
    {
        LogFormat("DestroyBss");
        Result rc = wlanLocalManagerDestroyBss(m_forward_service.get());
        LogFormat("DestroyBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StartScan(UnknownNetworkData in)
    {
        LogFormat("StartScan UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        Result rc = wlanLocalManagerStartScan(m_forward_service.get(), in);
        LogFormat("StartScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StopScan()
    {
        LogFormat("StopScan");
        Result rc = wlanLocalManagerStopScan(m_forward_service.get());
        LogFormat("StopScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Connect(ConnectData in)
    {
        LogFormat("Connect ConnectData:");
        LogHex(&in, sizeof(ConnectData));
        Result rc = wlanLocalManagerConnect(m_forward_service.get(), in);
        LogFormat("Connect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelConnect(u32 in)
    {
        LogFormat("CancelConnect in value: %x", in);
        Result rc = wlanLocalManagerCancelConnect(m_forward_service.get(), in);
        LogFormat("CancelConnect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Join(u32 in, sf::Out<sf::CopyHandle> out_handle)
    {
        os::NativeHandle handle;
        LogFormat("Join in value: %x handle ptr: %p", in, &out_handle);
        Result rc = wlanLocalManagerJoin(m_forward_service.get(), in, &handle);
        LogFormat("Join rc: %#x", rc);
        out_handle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::CancelJoin(sf::Out<CancelJoinData> out)
    {
        LogFormat("CancelJoin CancelJoinData:");
        LogHex(out.GetPointer(), sizeof(CancelJoinData));
        Result rc = wlanLocalManagerCancelJoin(m_forward_service.get(), out.GetPointer());
        LogFormat("CancelJoin rc: %#x", rc);
        LogFormat("CancelJoin data:");
        LogHex(out.GetPointer(), sizeof(CancelJoinData));
        return rc;
    }

    Result WlanLclMitmService::Disconnect(sf::OutMapAliasBuffer data)
    {
        LogFormat("Disconnect data ptr: %p", data.GetPointer());
        Result rc = wlanLocalManagerDisconnect(m_forward_service.get(), data.GetPointer(), data.GetSize());
        LogFormat("Disconnect rc: %#x", rc);
        LogFormat("Disconnect data:");
        LogHex(data.GetPointer(), data.GetSize());
        return rc;
    }

    Result WlanLclMitmService::SetBeaconLostCount(sf::Out<sf::CopyHandle> out_handle)
    {
        os::NativeHandle handle;
        LogFormat("SetBeaconLostCount handle ptr: %p", &out_handle);
        Result rc = wlanLocalManagerSetBeaconLostCount(m_forward_service.get(), &handle);
        LogFormat("SetBeaconLostCount rc: %#x", rc);
        out_handle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::GetSystemEvent(sf::OutMapAliasBuffer data)
    {
        LogFormat("GetSystemEvent data ptr: %p", data.GetPointer());
        Result rc = wlanLocalManagerGetSystemEvent(m_forward_service.get(), data.GetPointer(), data.GetSize());
        LogFormat("GetSystemEvent rc: %#x", rc);
        LogFormat("GetSystemEvent data:");
        LogHex(data.GetPointer(), data.GetSize());
        return rc;
    }

    Result WlanLclMitmService::GetConnectionStatus(sf::Out<u32> out)
    {
        LogFormat("GetConnectionStatus out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerGetConnectionStatus(m_forward_service.get(), out.GetPointer());
        LogFormat("GetConnectionStatus rc: %#x", rc);
        LogFormat("GetConnectionStatus out value: %x", out);
        return rc;
    }

    Result WlanLclMitmService::GetClientStatus(sf::Out<u32> out, sf::OutPointerArray<ClientStatusData> out_data)
    {
        LogFormat("GetClientStatus out ptr: %p out_data ptr: %p", out.GetPointer(), out_data.GetPointer());
        Result rc = wlanLocalManagerGetClientStatus(m_forward_service.get(), out.GetPointer(), out_data.GetPointer());
        LogFormat("GetClientStatus rc: %#x", rc);
        LogFormat("GetClientStatus out value: %x", out);
        LogFormat("GetClientStatus out_data[%d]:", out_data.GetSize());
        LogHex(out_data.GetPointer(), sizeof(ClientStatusData));
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationEvent(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer)
    {
        LogFormat("GetBssIndicationEvent in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetBssIndicationEvent in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerGetBssIndicationEvent(m_forward_service.get(), in, out.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("GetBssIndicationEvent rc: %#x", rc);
        LogFormat("GetBssIndicationEvent out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationInfo(u32 in)
    {
        LogFormat("GetBssIndicationInfo in value: %x", in);
        Result rc = wlanLocalManagerGetBssIndicationInfo(m_forward_service.get(), in);
        LogFormat("GetBssIndicationInfo rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetState(const sf::InBuffer &in_buffer)
    {
        LogFormat("GetState in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerGetState(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("GetState rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetAllowedChannels(u32 in)
    {
        LogFormat("GetAllowedChannels in value: %x", in);
        Result rc = wlanLocalManagerGetAllowedChannels(m_forward_service.get(), in);
        LogFormat("GetAllowedChannels rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddIe(u32 in, sf::Out<u32> out, const sf::InPointerArray<IeData> &in_array)
    {
        LogFormat("AddIe in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("AddIe in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
        Result rc = wlanLocalManagerAddIe(m_forward_service.get(), in, out.GetPointer(), in_array.GetPointer(), in_array.GetSize());
        LogFormat("AddIe out value: %x", out.GetValue());
        LogFormat("AddIe rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteIe(u32 in)
    {
        LogFormat("DeleteIe in value: %x", in);
        Result rc = wlanLocalManagerDeleteIe(m_forward_service.get(), in);
        LogFormat("DeleteIe rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::PutFrameRaw(u64 in)
    {
        LogFormat("PutFrameRaw in value: %x", in);
        Result rc = wlanLocalManagerPutFrameRaw(m_forward_service.get(), in);
        LogFormat("PutFrameRaw rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelGetFrame(u16 in, sf::Out<u32> out)
    {
        LogFormat("CancelGetFrame in value: %x out ptr: %p", in, out.GetPointer());
        Result rc = wlanLocalManagerCancelGetFrame(m_forward_service.get(), in, out.GetPointer());
        LogFormat("CancelGetFrame rc: %#x", rc);
        LogFormat("CancelGetFrame out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("CreateRxEntry in value: %x", in);
        LogFormat("CreateRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerCreateRxEntry(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("CreateRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("DeleteRxEntry in value: %x", in);
        LogFormat("DeleteRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerDeleteRxEntry(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("DeleteRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddEthertypeToRxEntry(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasBuffer out_buffer)
    {
        LogFormat("AddEthertypeToRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("AddEthertypeToRxEntry out_buffer:");
        LogHex(out_buffer.GetPointer(), out_buffer.GetSize());
        Result rc = wlanLocalManagerAddEthertypeToRxEntry(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize(), out_buffer.GetPointer(), out_buffer.GetSize());
        LogFormat("AddEthertypeToRxEntry rc: %#x", rc);
        LogFormat("AddEthertypeToRxEntry out_buffer:");
        LogHex(out_buffer.GetPointer(), out_buffer.GetSize());
        return rc;
    }

    Result WlanLclMitmService::DeleteEthertypeFromRxEntry(DeleteEthertypeFromRxEntryData in, const sf::InMapAliasBuffer &in_array)
    {
        LogFormat("DeleteEthertypeFromRxEntry DeleteEthertypeFromRxEntryData:");
        LogHex(&in, sizeof(DeleteEthertypeFromRxEntryData));
        LogFormat("DeleteEthertypeFromRxEntry in_array:");
        LogHex(in_array.GetPointer(), in_array.GetSize());
        Result rc = wlanLocalManagerDeleteEthertypeFromRxEntry(m_forward_service.get(), in, in_array.GetPointer(), in_array.GetSize());
        LogFormat("DeleteEthertypeFromRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddMatchingDataToRxEntry(const sf::InMapAliasBuffer &in_buffer)
    {
        LogFormat("AddMatchingDataToRxEntry in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerAddMatchingDataToRxEntry(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("AddMatchingDataToRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::RemoveMatchingDataFromRxEntry()
    {
        LogFormat("RemoveMatchingDataFromRxEntry");
        Result rc = wlanLocalManagerRemoveMatchingDataFromRxEntry(m_forward_service.get());
        LogFormat("RemoveMatchingDataFromRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetScanResult(u32 in, sf::Out<u32> out, const sf::InPointerBuffer &in_buffer)
    {
        LogFormat("GetScanResult in value: %x out ptr: %p", in, out.GetPointer());
        LogFormat("GetScanResult in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerGetScanResult(m_forward_service.get(), in, out.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("GetScanResult rc: %#x", rc);
        LogFormat("GetScanResult out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::PutActionFrameOneShot(u32 in)
    {
        LogFormat("PutActionFrameOneShot in value: %x", in);
        Result rc = wlanLocalManagerPutActionFrameOneShot(m_forward_service.get(), in);
        LogFormat("PutActionFrameOneShot rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetActionFrameWithBeacon(u64 in)
    {
        LogFormat("SetActionFrameWithBeacon in value: %ld", in);
        Result rc = wlanLocalManagerSetActionFrameWithBeacon(m_forward_service.get(), in);
        LogFormat("SetActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelActionFrameWithBeacon(u32 in, sf::Out<u32> out)
    {
        LogFormat("CancelActionFrameWithBeacon in value: %x, out ptr: %p", in, out.GetPointer());
        Result rc = wlanLocalManagerCancelActionFrameWithBeacon(m_forward_service.get(), in, out.GetPointer());
        LogFormat("CancelActionFrameWithBeacon out value: %x", out.GetValue());
        LogFormat("CancelActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntryForActionFrame(u32 in)
    {
        LogFormat("CreateRxEntryForActionFrame in value: %x", in);
        Result rc = wlanLocalManagerCreateRxEntryForActionFrame(m_forward_service.get(), in);
        LogFormat("CreateRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntryForActionFrame(sf::Out<u32> out)
    {
        LogFormat("DeleteRxEntryForActionFrame out ptr:", out.GetPointer());
        Result rc = wlanLocalManagerDeleteRxEntryForActionFrame(m_forward_service.get(), out.GetPointer());
        LogFormat("DeleteRxEntryForActionFrame rc: %#x", rc);
        LogFormat("DeleteRxEntryForActionFrame out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::AddSubtypeToRxEntryForActionFrame(u32 in)
    {
        LogFormat("AddSubtypeToRxEntryForActionFrame in value: %x", in);
        Result rc = wlanLocalManagerAddSubtypeToRxEntryForActionFrame(m_forward_service.get(), in);
        LogFormat("AddSubtypeToRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteSubtypeFromRxEntryForActionFrame(sf::Out<u32> out, sf::OutPointerBuffer out_buffer)
    {
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(m_forward_service.get(), out.GetPointer(), out_buffer.GetPointer(), out_buffer.GetSize());
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame rc: %#x", rc);
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out value: %x", out);
        LogFormat("DeleteSubtypeFromRxEntryForActionFrame out_buffer:");
        LogHex(out_buffer.GetPointer(), out_buffer.GetSize());
        return rc;
    }

    Result WlanLclMitmService::CancelGetActionFrame(u8 in)
    {
        LogFormat("CancelGetActionFrame in value: %x", in);
        Result rc = wlanLocalManagerCancelGetActionFrame(m_forward_service.get(), in);
        LogFormat("CancelGetActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetRssi(GetRssiData in)
    {
        LogFormat("GetRssi GetRssiData:");
        LogHex(&in, sizeof(GetRssiData));
        Result rc = wlanLocalManagerGetRssi(m_forward_service.get(), in);
        LogFormat("GetRssi rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetMaxAssociationNumber(UnknownNetworkData in)
    {
        LogFormat("SetMaxAssociationNumber UnknownNetworkData:");
        LogHex(&in, sizeof(UnknownNetworkData));
        Result rc = wlanLocalManagerSetMaxAssociationNumber(m_forward_service.get(), in);
        LogFormat("SetMaxAssociationNumber rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer)
    {
        LogFormat("Cmd45 data:");
        LogHex(&in, sizeof(Cmd45Data));
        LogFormat("Cmd45 in_buffer:");
        LogHex(in_buffer.GetPointer(), in_buffer.GetSize());
        Result rc = wlanLocalManagerCmd45(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        LogFormat("Cmd45 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd46(u8 in)
    {
        LogFormat("Cmd46 in value: %x", in);
        Result rc = wlanLocalManagerCmd46(m_forward_service.get(), in);
        LogFormat("Cmd46 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd47(Cmd47Data in, sf::Out<u32> out)
    {
        LogFormat("Cmd47 data:");
        LogHex(&in, sizeof(Cmd47Data));
        LogFormat("Cmd47 out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerCmd47(m_forward_service.get(), in, out.GetPointer());
        LogFormat("Cmd47 rc: %#x", rc);
        LogFormat("Cmd47 out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::Cmd48(u32 in)
    {
        LogFormat("Cmd48 in value: %x", in);
        Result rc = wlanLocalManagerCmd48(m_forward_service.get(), in);
        LogFormat("Cmd48 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd49(u32 in)
    {
        LogFormat("Cmd49 in value: %x", in);
        Result rc = wlanLocalManagerCmd49(m_forward_service.get(), in);
        LogFormat("Cmd49 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd50()
    {
        LogFormat("Cmd50");
        Result rc = wlanLocalManagerCmd50(m_forward_service.get());
        LogFormat("Cmd50 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd51(sf::Out<u32> out)
    {
        LogFormat("Cmd51 out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerCmd51(m_forward_service.get(), out.GetPointer());
        LogFormat("Cmd51 rc: %#x", rc);
        LogFormat("Cmd51 out value: %x", out.GetValue());
        return rc;
    }
}
