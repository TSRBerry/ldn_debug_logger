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
#include "wlan_mitm/wlan_lcl_service.hpp"

namespace ams::mitm::wlan
{
    Result WlanLclMitmService::OpenMode(Mode mode)
    {
        DEBUG_LOG("OpenMode mode: %d", mode);
        if (m_config->wlan_lcl.commands.disable_openmode)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerOpenMode(m_forward_service.get(), mode);
        DEBUG_LOG("OpenMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CloseMode(Mode mode)
    {
        DEBUG_LOG("CloseMode in value: %d", mode);
        if (m_config->wlan_lcl.commands.disable_closemode)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCloseMode(m_forward_service.get(), mode);
        DEBUG_LOG("CloseMode rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetMacAddress(sf::Out<LdnMacAddress> out)
    {
        DEBUG_LOG("GetMacAddress MacAddress ptr: %p", out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getmacaddress)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetMacAddress(m_forward_service.get(), out.GetPointer());
        DEBUG_DATA_DUMP(out.GetPointer(), sizeof(LdnMacAddress), "GetMacAddress MacAddressData");
        DEBUG_LOG("GetMacAddress rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateBss(Bss in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(Bss), "CreateBss Bss");
        if (m_config->wlan_lcl.commands.disable_createbss)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCreateBss(m_forward_service.get(), in);
        DEBUG_LOG("CreateBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DestroyBss()
    {
        DEBUG_LOG("DestroyBss");
        if (m_config->wlan_lcl.commands.disable_destroybss)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDestroyBss(m_forward_service.get());
        DEBUG_LOG("DestroyBss rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StartScan(const sf::InMapAliasArray<ams::mitm::wlan::ScanRequest> &request)
    {
        DEBUG_LOG("StartScan ScanRequest ptr: %p", request.GetPointer());
        DEBUG_DATA_DUMP(&request, sizeof(ams::mitm::wlan::ScanRequest), "StartScan ScanRequest");
        if (m_config->wlan_lcl.commands.disable_startscan)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerStartScan(m_forward_service.get(), request.GetPointer());
        DEBUG_LOG("StartScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::StopScan()
    {
        DEBUG_LOG("StopScan");
        if (m_config->wlan_lcl.commands.disable_stopscan)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerStopScan(m_forward_service.get());
        DEBUG_LOG("StopScan rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Connect(ConnectParam in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(ConnectParam), "Connect ConnectParam");
        if (m_config->wlan_lcl.commands.disable_connect)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerConnect(m_forward_service.get(), in);
        DEBUG_LOG("Connect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelConnect()
    {
        DEBUG_LOG("CancelConnect");
        if (m_config->wlan_lcl.commands.disable_cancelconnect)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCancelConnect(m_forward_service.get());
        DEBUG_LOG("CancelConnect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Join(ConnectParam in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(ConnectParam), "Join ConnectParam");
        if (m_config->wlan_lcl.commands.disable_join)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerJoin(m_forward_service.get(), in);
        DEBUG_LOG("Join rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelJoin()
    {
        DEBUG_LOG("CancelJoin");
        if (m_config->wlan_lcl.commands.disable_canceljoin)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCancelJoin(m_forward_service.get());
        DEBUG_LOG("CancelJoin rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Disconnect(DisconnectData in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(DisconnectData), "Disconnect DisconnectData");
        if (m_config->wlan_lcl.commands.disable_disconnect)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDisconnect(m_forward_service.get(), in);
        DEBUG_LOG("Disconnect rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetBeaconLostCount(u32 beaconLostCount)
    {
        DEBUG_LOG("SetBeaconLostCount beaconLostCount value: %x", beaconLostCount);
        if (m_config->wlan_lcl.commands.disable_setbeaconlostcount)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerSetBeaconLostCount(m_forward_service.get(), beaconLostCount);
        DEBUG_LOG("SetBeaconLostCount rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetSystemEvent(u32 systemEventType, sf::Out<sf::CopyHandle> eventHandle)
    {
        os::NativeHandle handle;
        DEBUG_LOG("GetSystemEvent systemEventType value: %x eventHandle ptr: %p", systemEventType, &eventHandle);
        if (m_config->wlan_lcl.commands.disable_getsystemevent)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetSystemEvent(m_forward_service.get(), systemEventType, &handle);
        DEBUG_LOG("GetSystemEvent rc: %#x", rc);
        eventHandle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::GetConnectionStatus(sf::Out<ConnectionStatus> status)
    {
        DEBUG_LOG("GetConnectionStatus ConnectionStatus ptr: %p", status.GetPointer());
        DEBUG_DATA_DUMP(status.GetPointer(), sizeof(ConnectionStatus), "GetConnectionStatus ConnectionStatus");
        if (m_config->wlan_lcl.commands.disable_getconnectionstatus)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetConnectionStatus(m_forward_service.get(), status.GetPointer());
        DEBUG_LOG("GetConnectionStatus rc: %#x", rc);
        DEBUG_DATA_DUMP(status.GetPointer(), sizeof(ConnectionStatus), "GetConnectionStatus ConnectionStatus");
        return rc;
    }

    Result WlanLclMitmService::GetClientStatus(sf::OutMapAliasArray<ClientStatus> status)
    {
        DEBUG_LOG("GetClientStatus status ptr: %p", status.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getclientstatus)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetClientStatus(m_forward_service.get(), status.GetPointer(), status.GetSize());
        DEBUG_LOG("GetClientStatus rc: %#x", rc);
        DEBUG_LOG("GetClientStatus ClientStatus value: %d", status);
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationEvent(sf::Out<sf::CopyHandle> eventHandle)
    {
        os::NativeHandle handle;
        DEBUG_LOG("GetBssIndicationEvent handle ptr: %p", &eventHandle);
        if (m_config->wlan_lcl.commands.disable_getbssindicationevent)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetBssIndicationEvent(m_forward_service.get(), &handle);
        DEBUG_LOG("GetBssIndicationEvent rc: %#x", rc);
        eventHandle.SetValue(handle, false);
        return rc;
    }

    Result WlanLclMitmService::GetBssIndicationInfo(sf::OutMapAliasBuffer data)
    {
        DEBUG_LOG("GetBssIndicationInfo data ptr: %p", data.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getbssindicationinfo)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetBssIndicationInfo(m_forward_service.get(), data.GetPointer(), data.GetSize());
        DEBUG_LOG("GetBssIndicationInfo rc: %#x", rc);
        DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "GetBssIndicationInfo data");
        return rc;
    }

    Result WlanLclMitmService::GetState(sf::Out<State> state)
    {
        DEBUG_LOG("GetState state ptr: %p", state.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getstate)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetState(m_forward_service.get(), state.GetPointer());
        DEBUG_LOG("GetState rc: %#x", rc);
        DEBUG_LOG("GetState state value: %d", state.GetValue());
        return rc;
    }

    Result WlanLclMitmService::GetAllowedChannels(sf::Out<u32> allowedChannelsCount, sf::OutPointerBuffer out_data)
    {
        DEBUG_LOG("GetAllowedChannels allowedChannelsCount ptr: %p out_data ptr: %p", allowedChannelsCount.GetPointer(), out_data.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getallowedchannels)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetAllowedChannels(m_forward_service.get(), allowedChannelsCount.GetPointer(), out_data.GetPointer(), out_data.GetSize());
        DEBUG_LOG("GetAllowedChannels rc: %#x", rc);
        DEBUG_LOG("GetAllowedChannels allowedChannelsCount value: %d", allowedChannelsCount.GetValue());
        DEBUG_DATA_DUMP(out_data.GetPointer(), out_data.GetSize(), "GetAllowedChannels out_data[%d]", out_data.GetSize());
        return rc;
    }

    Result WlanLclMitmService::AddIe(u32 managementFrameType, sf::Out<u32> ie, const sf::InBuffer &in_buffer)
    {
        DEBUG_LOG("AddIe managementFrameType value: %d out ptr: %p", managementFrameType, ie.GetPointer());
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "AddIe in_buffer");
        if (m_config->wlan_lcl.commands.disable_addie)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerAddIe(m_forward_service.get(), managementFrameType, ie.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("AddIe rc: %#x", rc);
        DEBUG_LOG("AddIe ie value: %d", ie.GetValue());
        return rc;
    }

    Result WlanLclMitmService::DeleteIe(u32 ie)
    {
        DEBUG_LOG("DeleteIe in value: %d", ie);
        if (m_config->wlan_lcl.commands.disable_deleteie)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDeleteIe(m_forward_service.get(), ie);
        DEBUG_LOG("DeleteIe rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::PutFrameRaw(const sf::InBuffer &in_buffer)
    {
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "PutFrameRaw in_buffer");
        if (m_config->wlan_lcl.commands.disable_putframeraw)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerPutFrameRaw(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("PutFrameRaw rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelGetFrame(u32 rxId)
    {
        DEBUG_LOG("CancelGetFrame rxId value: %x", rxId);
        if (m_config->wlan_lcl.commands.disable_cancelgetframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCancelGetFrame(m_forward_service.get(), rxId);
        DEBUG_LOG("CancelGetFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntry(u32 capacity, sf::Out<u32> rxId, const sf::InPointerBuffer &in_array)
    {
        DEBUG_LOG("CreateRxEntry capacity value: %x rxId ptr: %p", capacity, rxId.GetPointer());
        DEBUG_DATA_DUMP(in_array.GetPointer(), in_array.GetSize(), "CreateRxEntry in_array");
        if (m_config->wlan_lcl.commands.disable_createrxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCreateRxEntry(m_forward_service.get(), capacity, rxId.GetPointer(), in_array.GetPointer(), in_array.GetSize());
        DEBUG_LOG("CreateRxEntry rc: %#x", rc);
        DEBUG_LOG("CreateRxEntry rxId value: %x", rxId.GetValue());
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntry(u32 rxId)
    {
        DEBUG_LOG("DeleteRxEntry rxId value: %x", rxId);
        if (m_config->wlan_lcl.commands.disable_deleterxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDeleteRxEntry(m_forward_service.get(), rxId);
        DEBUG_LOG("DeleteRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddEthertypeToRxEntry(u32 rxId, u32 protocol)
    {
        DEBUG_LOG("AddEthertypeToRxEntry rxId value: %d protocol value: %d", rxId, protocol);
        if (m_config->wlan_lcl.commands.disable_addethertypetorxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerAddEthertypeToRxEntry(m_forward_service.get(), rxId, protocol);
        DEBUG_LOG("AddEthertypeToRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteEthertypeFromRxEntry(u16 protocol, sf::Out<u32> out)
    {
        DEBUG_LOG("DeleteEthertypeFromRxEntry protocol value: %x out ptr: %p", protocol, out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_deleteethertypefromrxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDeleteEthertypeFromRxEntry(m_forward_service.get(), protocol, out.GetPointer());
        DEBUG_LOG("DeleteEthertypeFromRxEntry rc: %#x", rc);
        DEBUG_LOG("DeleteEthertypeFromRxEntry out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::AddMatchingDataToRxEntry(u32 rxId, const sf::InPointerBuffer &in_buffer)
    {
        DEBUG_LOG("AddMatchingDataToRxEntry rxId value: %d", rxId);
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "AddMatchingDataToRxEntry in_buffer");
        if (m_config->wlan_lcl.commands.disable_addmatchingdatatorxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerAddMatchingDataToRxEntry(m_forward_service.get(), rxId, in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("AddMatchingDataToRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::RemoveMatchingDataFromRxEntry(u32 rxId, const sf::InPointerBuffer &in_buffer)
    {
        DEBUG_LOG("RemoveMatchingDataFromRxEntry rxId value: %d", rxId);
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "RemoveMatchingDataFromRxEntry in_buffer");
        if (m_config->wlan_lcl.commands.disable_removematchingdatafromrxentry)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerRemoveMatchingDataFromRxEntry(m_forward_service.get(), rxId, in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("RemoveMatchingDataFromRxEntry rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetScanResult(const sf::InPointerBuffer &in_buffer, sf::OutMapAliasArray<ams::mitm::wlan::ScanResult> result)
    {
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "GetScanResult in_buffer");
        if (m_config->wlan_lcl.commands.disable_getscanresult)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetScanResult(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize(), result.GetPointer(), result.GetSize());
        DEBUG_LOG("GetScanResult rc: %#x", rc);
        DEBUG_DATA_DUMP(result.GetPointer(), result.GetSize(), "GetScanResult ScanResult");
        return rc;
    }

    Result WlanLclMitmService::PutActionFrameOneShot(PutActionFrameOneShotData in, const sf::InMapAliasBuffer &in_array)
    {
        DEBUG_DATA_DUMP(&in, sizeof(PutActionFrameOneShotData), "PutActionFrameOneShot PutActionFrameOneShotData");
        DEBUG_DATA_DUMP(in_array.GetPointer(), in_array.GetSize(), "PutActionFrameOneShot in_array");
        if (m_config->wlan_lcl.commands.disable_putactionframeoneshot)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerPutActionFrameOneShot(m_forward_service.get(), in, in_array.GetPointer(), in_array.GetSize());
        DEBUG_LOG("PutActionFrameOneShot rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::SetActionFrameWithBeacon(const sf::InMapAliasBuffer &in_buffer)
    {
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "SetActionFrameWithBeacon in_buffer");
        if (m_config->wlan_lcl.commands.disable_setactionframewithbeacon)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerSetActionFrameWithBeacon(m_forward_service.get(), in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("SetActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelActionFrameWithBeacon()
    {
        DEBUG_LOG("CancelActionFrameWithBeacon");
        if (m_config->wlan_lcl.commands.disable_cancelactionframewithbeacon)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCancelActionFrameWithBeacon(m_forward_service.get());
        DEBUG_LOG("CancelActionFrameWithBeacon rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CreateRxEntryForActionFrame(u32 capacity, sf::Out<u32> rxId, const sf::InPointerBuffer &in_buffer)
    {
        DEBUG_LOG("CreateRxEntryForActionFrame capacity value: %d rxId ptr: %p", capacity, rxId.GetPointer());
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "CreateRxEntryForActionFrame in_buffer");
        if (m_config->wlan_lcl.commands.disable_createrxentryforactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCreateRxEntryForActionFrame(m_forward_service.get(), capacity, rxId.GetPointer(), in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("CreateRxEntryForActionFrame rc: %#x", rc);
        DEBUG_LOG("CreateRxEntryForActionFrame rxId value: %d", rxId.GetValue());
        return rc;
    }

    Result WlanLclMitmService::DeleteRxEntryForActionFrame(u32 rxId)
    {
        DEBUG_LOG("DeleteRxEntryForActionFrame rxId value: %d", rxId);
        if (m_config->wlan_lcl.commands.disable_deleterxentryforactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDeleteRxEntryForActionFrame(m_forward_service.get(), rxId);
        DEBUG_LOG("DeleteRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::AddSubtypeToRxEntryForActionFrame(u32 rxId, u32 subType)
    {
        DEBUG_LOG("AddSubtypeToRxEntryForActionFrame rxId value: %d subType value: %d", rxId, subType);
        if (m_config->wlan_lcl.commands.disable_addsubtypetorxentryforactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerAddSubtypeToRxEntryForActionFrame(m_forward_service.get(), rxId, subType);
        DEBUG_LOG("AddSubtypeToRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::DeleteSubtypeFromRxEntryForActionFrame(u32 subType, sf::Out<u32> out)
    {
        DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame subType value: %x, out ptr: %p", subType, out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_deletesubtypefromrxentryforactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(m_forward_service.get(), subType, out.GetPointer());
        DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame out value: %x", out.GetValue());
        DEBUG_LOG("DeleteSubtypeFromRxEntryForActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::CancelGetActionFrame(u32 rxId)
    {
        DEBUG_LOG("CancelGetActionFrame rxId value: %x", rxId);
        if (m_config->wlan_lcl.commands.disable_cancelgetactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCancelGetActionFrame(m_forward_service.get(), rxId);
        DEBUG_LOG("CancelGetActionFrame rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::GetRssi(sf::Out<u32> rssi)
    {
        DEBUG_LOG("GetRssi rssi ptr:", rssi.GetPointer());
        if (m_config->wlan_lcl.commands.disable_getrssi)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerGetRssi(m_forward_service.get(), rssi.GetPointer());
        DEBUG_LOG("GetRssi rc: %#x", rc);
        DEBUG_LOG("GetRssi rssi value: %x", rssi.GetValue());
        return rc;
    }

    Result WlanLclMitmService::SetMaxAssociationNumber(u32 maxAssociationNumber)
    {
        DEBUG_LOG("SetMaxAssociationNumber maxAssociationNumber value: %d", maxAssociationNumber);
        if (m_config->wlan_lcl.commands.disable_setmaxassociationnumber)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerSetMaxAssociationNumber(m_forward_service.get(), maxAssociationNumber);
        DEBUG_LOG("SetMaxAssociationNumber rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd41(sf::Out<u32> out, sf::OutPointerBuffer out_buffer)
    {
        DEBUG_LOG("Cmd41 out ptr: %p", out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_cmd41)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd41(m_forward_service.get(), out.GetPointer(), out_buffer.GetPointer(), out_buffer.GetSize());
        DEBUG_LOG("Cmd41 rc: %#x", rc);
        DEBUG_LOG("Cmd41 out value: %x", out);
        DEBUG_DATA_DUMP(out_buffer.GetPointer(), out_buffer.GetSize(), "Cmd41 out_buffer");
        return rc;
    }

    Result WlanLclMitmService::Cmd42(u8 in)
    {
        DEBUG_LOG("Cmd42 in value: %x", in);
        if (m_config->wlan_lcl.commands.disable_cmd42)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd42(m_forward_service.get(), in);
        DEBUG_LOG("Cmd42 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd43(Cmd43Data in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(Cmd43Data), "Cmd43 Cmd43Data");
        if (m_config->wlan_lcl.commands.disable_cmd43)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd43(m_forward_service.get(), in);
        DEBUG_LOG("Cmd43 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd44(Bss in)
    {
        DEBUG_DATA_DUMP(&in, sizeof(Bss), "Cmd44 Bss");
        if (m_config->wlan_lcl.commands.disable_cmd44)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd44(m_forward_service.get(), in);
        DEBUG_LOG("Cmd44 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd45(Cmd45Data in, const sf::InMapAliasBuffer &in_buffer)
    {
        DEBUG_DATA_DUMP(&in, sizeof(Cmd45Data), "Cmd45 data");
        DEBUG_DATA_DUMP(in_buffer.GetPointer(), in_buffer.GetSize(), "Cmd45 in_buffer");
        if (m_config->wlan_lcl.commands.disable_cmd45)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd45(m_forward_service.get(), in, in_buffer.GetPointer(), in_buffer.GetSize());
        DEBUG_LOG("Cmd45 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd46(u8 in)
    {
        DEBUG_LOG("Cmd46 in value: %x", in);
        if (m_config->wlan_lcl.commands.disable_cmd46)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd46(m_forward_service.get(), in);
        DEBUG_LOG("Cmd46 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd47(Cmd47Data in, sf::Out<u32> out)
    {
        DEBUG_DATA_DUMP(&in, sizeof(Cmd47Data), "Cmd47 data");
        DEBUG_LOG("Cmd47 out ptr: %p", out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_cmd47)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd47(m_forward_service.get(), in, out.GetPointer());
        DEBUG_LOG("Cmd47 rc: %#x", rc);
        DEBUG_LOG("Cmd47 out value: %x", out.GetValue());
        return rc;
    }

    Result WlanLclMitmService::Cmd48(u32 in)
    {
        DEBUG_LOG("Cmd48 in value: %x", in);
        if (m_config->wlan_lcl.commands.disable_cmd48)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd48(m_forward_service.get(), in);
        DEBUG_LOG("Cmd48 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd49(u32 in)
    {
        DEBUG_LOG("Cmd49 in value: %x", in);
        if (m_config->wlan_lcl.commands.disable_cmd49)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd49(m_forward_service.get(), in);
        DEBUG_LOG("Cmd49 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd50()
    {
        DEBUG_LOG("Cmd50");
        if (m_config->wlan_lcl.commands.disable_cmd50)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd50(m_forward_service.get());
        DEBUG_LOG("Cmd50 rc: %#x", rc);
        return rc;
    }

    Result WlanLclMitmService::Cmd51(sf::Out<u32> out)
    {
        DEBUG_LOG("Cmd51 out ptr: %p", out.GetPointer());
        if (m_config->wlan_lcl.commands.disable_cmd51)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalManagerCmd51(m_forward_service.get(), out.GetPointer());
        DEBUG_LOG("Cmd51 rc: %#x", rc);
        DEBUG_LOG("Cmd51 out value: %x", out.GetValue());
        return rc;
    }
}
