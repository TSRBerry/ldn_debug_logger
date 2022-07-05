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

#include "logging.hpp"
#include "wlan_lcl_service.hpp"

namespace ams::mitm::wlan
{
    Result WlanLclMitmService::OpenMasterMode(u32 in)
    {
        log::DEBUG_LOG("OpenMasterMode in value: %x", in);
        Result rc = wlanLocalManagerOpenMasterMode(m_forward_service.get(), in);
        log::DEBUG_LOG("OpenMasterMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseMasterMode(u32 in)
    {
        log::DEBUG_LOG("CloseMasterMode in value: %x", in);
        Result rc = wlanLocalManagerCloseMasterMode(m_forward_service.get(), in);
        log::DEBUG_LOG("CloseMasterMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::OpenClientMode(sf::Out<OpenClientModeData> out)
    {
        log::DEBUG_LOG("OpenClientMode OpenClientModeData ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerOpenClientMode(m_forward_service.get(), out.GetPointer());
        log::DEBUG_DATA_DUMP(out.GetPointer(), sizeof(OpenClientModeData), "OpenClientMode OpenClientModeData");
        log::DEBUG_LOG("OpenClientMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseClientMode(UnknownNetworkData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(UnknownNetworkData), "CloseClientMode UnknownNetworkData");
        Result rc = wlanLocalManagerCloseClientMode(m_forward_service.get(), in);
        log::DEBUG_LOG("CloseClientMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::OpenSpectatorMode()
    {
        log::DEBUG_LOG("OpenSpectatorMode");
        Result rc = wlanLocalManagerOpenSpectatorMode(m_forward_service.get());
        log::DEBUG_LOG("OpenSpectatorMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseSpectatorMode(const sf::InMapAliasArray<SpectatorModeData> &data)
    {
        log::DEBUG_LOG("CloseSpectatorMode SpectatorModeData ptr: %p", data.GetPointer());
        log::DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "CloseSpectatorMode SpectatorModeData");
        Result rc = wlanLocalManagerCloseSpectatorMode(m_forward_service.get(), data.GetPointer());
        log::DEBUG_LOG("CloseSpectatorMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetMacAddress()
    {
        log::DEBUG_LOG("GetMacAddress");
        Result rc = wlanLocalManagerGetMacAddress(m_forward_service.get());
        log::DEBUG_LOG("GetMacAddress rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateBss(UnknownNetworkData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(UnknownNetworkData), "CreateBss UnknownNetworkData");
        Result rc = wlanLocalManagerCreateBss(m_forward_service.get(), in);
        log::DEBUG_LOG("CreateBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DestroyBss()
    {
        log::DEBUG_LOG("DestroyBss");
        Result rc = wlanLocalManagerDestroyBss(m_forward_service.get());
        log::DEBUG_LOG("DestroyBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StartScan(UnknownNetworkData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(UnknownNetworkData), "StartScan UnknownNetworkData");
        Result rc = wlanLocalManagerStartScan(m_forward_service.get(), in);
        log::DEBUG_LOG("StartScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StopScan()
    {
        log::DEBUG_LOG("StopScan");
        Result rc = wlanLocalManagerStopScan(m_forward_service.get());
        log::DEBUG_LOG("StopScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Connect(ConnectData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(ConnectData), "Connect ConnectData");
        Result rc = wlanLocalManagerConnect(m_forward_service.get(), in);
        log::DEBUG_LOG("Connect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelConnect(u32 in)
    {
        log::DEBUG_LOG("CancelConnect in value: %x", in);
        Result rc = wlanLocalManagerCancelConnect(m_forward_service.get(), in);
        log::DEBUG_LOG("CancelConnect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Join(u32 in, sf::Out<sf::CopyHandle> out_handle)
    {
        os::NativeHandle handle;
        log::DEBUG_LOG("Join in value: %x handle ptr: %p", in, &out_handle);
        Result rc = wlanLocalManagerJoin(m_forward_service.get(), in, &handle);
        log::DEBUG_LOG("Join rc: %#x", rc);
        out_handle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::CancelJoin(sf::Out<CancelJoinData> out)
    {
        log::DEBUG_DATA_DUMP(out.GetPointer(), sizeof(CancelJoinData), "CancelJoin CancelJoinData");
        Result rc = wlanLocalManagerCancelJoin(m_forward_service.get(), out.GetPointer());
        log::DEBUG_LOG("CancelJoin rc: %#x", rc);
        log::DEBUG_DATA_DUMP(out.GetPointer(), sizeof(CancelJoinData), "CancelJoin data");
        return rc;
    }

    Result WlanLclMitmService::Disconnect(sf::OutMapAliasBuffer data)
    {
        log::DEBUG_LOG("Disconnect data ptr: %p", data.GetPointer());
        Result rc = wlanLocalManagerDisconnect(m_forward_service.get(), data.GetPointer(), data.GetSize());
        log::DEBUG_LOG("Disconnect rc: %#x", rc);
        log::DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "Disconnect data");
        return rc;
    }

    Result WlanLclMitmService::SetBeaconLostCount(sf::Out<sf::CopyHandle> out_handle)
    {
        os::NativeHandle handle;
        log::DEBUG_LOG("SetBeaconLostCount handle ptr: %p", &out_handle);
        Result rc = wlanLocalManagerSetBeaconLostCount(m_forward_service.get(), &handle);
        log::DEBUG_LOG("SetBeaconLostCount rc: %#x", rc);
        out_handle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::GetSystemEvent(sf::OutMapAliasBuffer data)
    {
        log::DEBUG_LOG("GetSystemEvent data ptr: %p", data.GetPointer());
        Result rc = wlanLocalManagerGetSystemEvent(m_forward_service.get(), data.GetPointer(), data.GetSize());
        log::DEBUG_LOG("GetSystemEvent rc: %#x", rc);
        log::DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "GetSystemEvent data");
        return rc;
    }

    Result WlanLclMitmService::GetConnectionStatus(sf::Out<u32> out)
    {
        log::DEBUG_LOG("GetConnectionStatus out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerGetConnectionStatus(m_forward_service.get(), out.GetPointer());
        log::DEBUG_LOG("GetConnectionStatus rc: %#x", rc);
        log::DEBUG_LOG("GetConnectionStatus out value: %x", out);
        return rc;
    }

    Result WlanLclMitmService::GetClientStatus(sf::Out<u32> out, sf::OutPointerArray<ClientStatusData> out_data)
    {
        log::DEBUG_LOG("GetClientStatus out ptr: %p out_data ptr: %p", out.GetPointer(), out_data.GetPointer());
        Result rc = wlanLocalManagerGetClientStatus(m_forward_service.get(), out.GetPointer(), out_data.GetPointer());
        log::DEBUG_LOG("GetClientStatus rc: %#x", rc);
        log::DEBUG_LOG("GetClientStatus out value: %x", out);
        log::DEBUG_DATA_DUMP(out_data.GetPointer(), sizeof(ClientStatusData), "GetClientStatus out_data[%d]", out_data.GetSize());
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationEvent(u32 in, sf::Out<u32> out, const sf::InBuffer &in_buffer)
    {
        log::DEBUG_LOG("GetBssIndicationEvent in value: %x out ptr: %p", in, out.GetPointer());
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "GetBssIndicationEvent in_buffer");
        Result rc = wlanLocalManagerGetBssIndicationEvent(m_forward_service.get(), in, out.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("GetBssIndicationEvent rc: %#x", rc);
        log::DEBUG_LOG("GetBssIndicationEvent out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationInfo(u32 in)
    {
        log::DEBUG_LOG("GetBssIndicationInfo in value: %x", in);
        Result rc = wlanLocalManagerGetBssIndicationInfo(m_forward_service.get(), in);
        log::DEBUG_LOG("GetBssIndicationInfo rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetState(const sf::InBuffer &in_buffer)
    {
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "GetState in_buffer");
        Result rc = wlanLocalManagerGetState(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("GetState rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetAllowedChannels(u32 in)
    {
        log::DEBUG_LOG("GetAllowedChannels in value: %x", in);
        Result rc = wlanLocalManagerGetAllowedChannels(m_forward_service.get(), in);
        log::DEBUG_LOG("GetAllowedChannels rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddIe(u32 in, sf::Out<u32> out, const sf::InPointerArray<IeData> &in_array)
    {
        log::DEBUG_LOG("AddIe in value: %x out ptr: %p", in, out.GetPointer());
        log::DEBUG_DATA_DUMP(in_array.GetPointer(), in_array.GetSize(), "AddIe in_array");
        Result rc = wlanLocalManagerAddIe(m_forward_service.get(), in, out.GetPointer(), in_array.GetPointer(), in_array.GetSize());
        log::DEBUG_LOG("AddIe out value: %x", out.GetValue());
        log::DEBUG_LOG("AddIe rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteIe(u32 in)
    {
        log::DEBUG_LOG("DeleteIe in value: %x", in);
        Result rc = wlanLocalManagerDeleteIe(m_forward_service.get(), in);
        log::DEBUG_LOG("DeleteIe rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::PutFrameRaw(u64 in)
    {
        log::DEBUG_LOG("PutFrameRaw in value: %x", in);
        Result rc = wlanLocalManagerPutFrameRaw(m_forward_service.get(), in);
        log::DEBUG_LOG("PutFrameRaw rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelGetFrame(u16 in, sf::Out<u32> out)
    {
        log::DEBUG_LOG("CancelGetFrame in value: %x out ptr: %p", in, out.GetPointer());
        Result rc = wlanLocalManagerCancelGetFrame(m_forward_service.get(), in, out.GetPointer());
        log::DEBUG_LOG("CancelGetFrame rc: %#x", rc);
        log::DEBUG_LOG("CancelGetFrame out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        log::DEBUG_LOG("CreateRxEntry in value: %x", in);
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "CreateRxEntry in_buffer");
        Result rc = wlanLocalManagerCreateRxEntry(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("CreateRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntry(u32 in, const sf::InPointerBuffer &in_buffer)
    {
        log::DEBUG_LOG("DeleteRxEntry in value: %x", in);
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "DeleteRxEntry in_buffer");
        Result rc = wlanLocalManagerDeleteRxEntry(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("DeleteRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddEthertypeToRxEntry(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasBuffer out_buffer)
    {
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "AddEthertypeToRxEntry in_buffer");
        Result rc = wlanLocalManagerAddEthertypeToRxEntry(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize(), out_buffer.GetPointer(), out_buffer.GetSize());
        log::DEBUG_LOG("AddEthertypeToRxEntry rc: %#x", rc);
        log::DEBUG_DATA_DUMP(out_buffer.GetPointer(), out_buffer.GetSize(), "AddEthertypeToRxEntry out_buffer");
        return rc;
    }

    Result WlanLclMitmService::DeleteEthertypeFromRxEntry(DeleteEthertypeFromRxEntryData in, const sf::InMapAliasBuffer &in_array)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(DeleteEthertypeFromRxEntryData), "DeleteEthertypeFromRxEntry DeleteEthertypeFromRxEntryData");
        log::DEBUG_DATA_DUMP(in_array.GetPointer(), in_array.GetSize(), "DeleteEthertypeFromRxEntry in_array");
        Result rc = wlanLocalManagerDeleteEthertypeFromRxEntry(m_forward_service.get(), in, in_array.GetPointer(), in_array.GetSize());
        log::DEBUG_LOG("DeleteEthertypeFromRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddMatchingDataToRxEntry(const sf::InMapAliasBuffer &in_buffer)
    {
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "AddMatchingDataToRxEntry in_buffer");
        Result rc = wlanLocalManagerAddMatchingDataToRxEntry(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("AddMatchingDataToRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::RemoveMatchingDataFromRxEntry()
    {
        log::DEBUG_LOG("RemoveMatchingDataFromRxEntry");
        Result rc = wlanLocalManagerRemoveMatchingDataFromRxEntry(m_forward_service.get());
        log::DEBUG_LOG("RemoveMatchingDataFromRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetScanResult(u32 in, sf::Out<u32> out, const sf::InPointerBuffer &in_buffer)
    {
        log::DEBUG_LOG("GetScanResult in value: %x out ptr: %p", in, out.GetPointer());
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "GetScanResult in_buffer");
        Result rc = wlanLocalManagerGetScanResult(m_forward_service.get(), in, out.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("GetScanResult rc: %#x", rc);
        log::DEBUG_LOG("GetScanResult out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::PutActionFrameOneShot(u32 in)
    {
        log::DEBUG_LOG("PutActionFrameOneShot in value: %x", in);
        Result rc = wlanLocalManagerPutActionFrameOneShot(m_forward_service.get(), in);
        log::DEBUG_LOG("PutActionFrameOneShot rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetActionFrameWithBeacon(u64 in)
    {
        log::DEBUG_LOG("SetActionFrameWithBeacon in value: %ld", in);
        Result rc = wlanLocalManagerSetActionFrameWithBeacon(m_forward_service.get(), in);
        log::DEBUG_LOG("SetActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelActionFrameWithBeacon(u32 in, sf::Out<u32> out)
    {
        log::DEBUG_LOG("CancelActionFrameWithBeacon in value: %x, out ptr: %p", in, out.GetPointer());
        Result rc = wlanLocalManagerCancelActionFrameWithBeacon(m_forward_service.get(), in, out.GetPointer());
        log::DEBUG_LOG("CancelActionFrameWithBeacon out value: %x", out.GetValue());
        log::DEBUG_LOG("CancelActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntryForActionFrame(u32 in)
    {
        log::DEBUG_LOG("CreateRxEntryForActionFrame in value: %x", in);
        Result rc = wlanLocalManagerCreateRxEntryForActionFrame(m_forward_service.get(), in);
        log::DEBUG_LOG("CreateRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntryForActionFrame(sf::Out<u32> out)
    {
        log::DEBUG_LOG("DeleteRxEntryForActionFrame out ptr:", out.GetPointer());
        Result rc = wlanLocalManagerDeleteRxEntryForActionFrame(m_forward_service.get(), out.GetPointer());
        log::DEBUG_LOG("DeleteRxEntryForActionFrame rc: %#x", rc);
        log::DEBUG_LOG("DeleteRxEntryForActionFrame out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::AddSubtypeToRxEntryForActionFrame(u32 in)
    {
        log::DEBUG_LOG("AddSubtypeToRxEntryForActionFrame in value: %x", in);
        Result rc = wlanLocalManagerAddSubtypeToRxEntryForActionFrame(m_forward_service.get(), in);
        log::DEBUG_LOG("AddSubtypeToRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteSubtypeFromRxEntryForActionFrame(sf::Out<u32> out, sf::OutPointerBuffer out_buffer)
    {
        log::DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(m_forward_service.get(), out.GetPointer(), out_buffer.GetPointer(), out_buffer.GetSize());
        log::DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame rc: %#x", rc);
        log::DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame out value: %x", out);
        log::DEBUG_DATA_DUMP(out_buffer.GetPointer(), out_buffer.GetSize(), "DeleteSubtypeFromRxEntryForActionFrame out_buffer");
        return rc;
    }

    Result WlanLclMitmService::CancelGetActionFrame(u8 in)
    {
        log::DEBUG_LOG("CancelGetActionFrame in value: %x", in);
        Result rc = wlanLocalManagerCancelGetActionFrame(m_forward_service.get(), in);
        log::DEBUG_LOG("CancelGetActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetRssi(GetRssiData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(GetRssiData), "GetRssi GetRssiData");
        Result rc = wlanLocalManagerGetRssi(m_forward_service.get(), in);
        log::DEBUG_LOG("GetRssi rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetMaxAssociationNumber(UnknownNetworkData in)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(UnknownNetworkData), "SetMaxAssociationNumber UnknownNetworkData");
        Result rc = wlanLocalManagerSetMaxAssociationNumber(m_forward_service.get(), in);
        log::DEBUG_LOG("SetMaxAssociationNumber rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(Cmd45Data), "Cmd45 data");
        log::DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "Cmd45 in_buffer");
        Result rc = wlanLocalManagerCmd45(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        log::DEBUG_LOG("Cmd45 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd46(u8 in)
    {
        log::DEBUG_LOG("Cmd46 in value: %x", in);
        Result rc = wlanLocalManagerCmd46(m_forward_service.get(), in);
        log::DEBUG_LOG("Cmd46 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd47(Cmd47Data in, sf::Out<u32> out)
    {
        log::DEBUG_DATA_DUMP(&in, sizeof(Cmd47Data), "Cmd47 data");
        log::DEBUG_LOG("Cmd47 out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerCmd47(m_forward_service.get(), in, out.GetPointer());
        log::DEBUG_LOG("Cmd47 rc: %#x", rc);
        log::DEBUG_LOG("Cmd47 out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::Cmd48(u32 in)
    {
        log::DEBUG_LOG("Cmd48 in value: %x", in);
        Result rc = wlanLocalManagerCmd48(m_forward_service.get(), in);
        log::DEBUG_LOG("Cmd48 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd49(u32 in)
    {
        log::DEBUG_LOG("Cmd49 in value: %x", in);
        Result rc = wlanLocalManagerCmd49(m_forward_service.get(), in);
        log::DEBUG_LOG("Cmd49 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd50()
    {
        log::DEBUG_LOG("Cmd50");
        Result rc = wlanLocalManagerCmd50(m_forward_service.get());
        log::DEBUG_LOG("Cmd50 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd51(sf::Out<u32> out)
    {
        log::DEBUG_LOG("Cmd51 out ptr: %p", out.GetPointer());
        Result rc = wlanLocalManagerCmd51(m_forward_service.get(), out.GetPointer());
        log::DEBUG_LOG("Cmd51 rc: %#x", rc);
        log::DEBUG_LOG("Cmd51 out value: %x", out.GetValue());
        return rc;
    }
}
