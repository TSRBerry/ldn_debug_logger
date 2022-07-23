/*
 * Copyright (c) TSRBerry
 *  -> adapted for wlan:lcl
 * Copyright (c) Atmosphère-NX
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

#include <string.h>
#include <stratosphere/sf/sf_mitm_dispatch.h>
#include <switch.h>
#include "wlan_mitm/wlan_lcl_shim.hpp"

/* Command forwarders. */
Result wlanLocalManagerOpenMode(Service *s, ams::mitm::wlan::Mode mode)
{
    return serviceMitmDispatchIn(s, 0, mode);
}

Result wlanLocalManagerCloseMode(Service *s, ams::mitm::wlan::Mode mode)
{
    return serviceMitmDispatchIn(s, 1, mode);
}

Result wlanLocalManagerGetMacAddress(Service *s, LdnMacAddress *out)
{
    return serviceMitmDispatchOut(s, 2, *out);
}

Result wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::Bss in)
{
    return serviceMitmDispatchIn(s, 3, in);
}

Result wlanLocalManagerDestroyBss(Service *s)
{
    return serviceMitmDispatch(s, 4);
}

Result wlanLocalManagerStartScan(Service *s, const ams::mitm::wlan::ScanRequest *request)
{
    return serviceMitmDispatch(s, 5,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {request, sizeof(ams::mitm::wlan::ScanRequest)},
                               }, );
}

Result wlanLocalManagerStopScan(Service *s)
{
    return serviceMitmDispatch(s, 6);
}

Result wlanLocalManagerConnect(Service *s, ams::mitm::wlan::ConnectParam in)
{
    return serviceMitmDispatchIn(s, 7, in);
}

Result wlanLocalManagerCancelConnect(Service *s)
{
    return serviceMitmDispatch(s, 8);
}

Result wlanLocalManagerJoin(Service *s, ams::mitm::wlan::ConnectParam in)
{
    return serviceMitmDispatchIn(s, 9, in);
}

Result wlanLocalManagerCancelJoin(Service *s)
{
    return serviceMitmDispatch(s, 10);
}

Result wlanLocalManagerDisconnect(Service *s, ams::mitm::wlan::DisconnectData in)
{
    return serviceMitmDispatchIn(s, 11, in);
}

Result wlanLocalManagerSetBeaconLostCount(Service *s, u32 beaconLostCount)
{
    return serviceMitmDispatchIn(s, 12, beaconLostCount);
}

Result wlanLocalManagerGetSystemEvent(Service *s, u32 systemEventType, Handle *eventHandle)
{
    return serviceMitmDispatchIn(s, 13, systemEventType,
                                 .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                                 .out_handles = eventHandle, );
}

Result wlanLocalManagerGetConnectionStatus(Service *s, ams::mitm::wlan::ConnectionStatus *status)
{
    return serviceMitmDispatchOut(s, 14, *status);
}

Result wlanLocalManagerGetClientStatus(Service *s, ams::mitm::wlan::ClientStatus *status, size_t status_size)
{
    return serviceMitmDispatch(s, 15,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {status, status_size},
                               }, );
}

Result wlanLocalManagerGetBssIndicationEvent(Service *s, Handle *eventHandle)
{
    return serviceMitmDispatch(s, 16,
                               .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                               .out_handles = eventHandle, );
}

Result wlanLocalManagerGetBssIndicationInfo(Service *s, void *data, size_t data_size)
{
    return serviceMitmDispatch(s, 17,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

Result wlanLocalManagerGetState(Service *s, ams::mitm::wlan::State *state)
{
    return serviceMitmDispatchOut(s, 18, *state);
}

Result wlanLocalManagerGetAllowedChannels(Service *s, u32 *allowedChannelsCount, void *out_data, size_t out_data_size)
{
    return serviceMitmDispatchOut(s, 19, *allowedChannelsCount,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_data, out_data_size},
                                  }, );
}

Result wlanLocalManagerAddIe(Service *s, u32 managementFrameType, u32 *ie, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 20, managementFrameType, *ie,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

Result wlanLocalManagerDeleteIe(Service *s, u32 ie)
{
    return serviceMitmDispatchIn(s, 21, ie);
}

Result wlanLocalManagerPutFrameRaw(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 22,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

Result wlanLocalManagerCancelGetFrame(Service *s, u32 rxId)
{
    return serviceMitmDispatchIn(s, 23, rxId);
}

Result wlanLocalManagerCreateRxEntry(Service *s, u32 capacity, u32 *rxId, const void *in_array, size_t in_array_size)
{
    return serviceMitmDispatchInOut(s, 24, capacity, *rxId,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {
                                        {in_array, in_array_size},
                                    }, );
}

Result wlanLocalManagerDeleteRxEntry(Service *s, u32 rxId)
{
    return serviceMitmDispatchIn(s, 25, rxId);
}

Result wlanLocalManagerAddEthertypeToRxEntry(Service *s, u32 rxId, u32 protocol)
{
    const struct
    {
        u32 rxId;
        u32 protocol;
    } in = {rxId, protocol};
    return serviceMitmDispatchIn(s, 26, in);
}

Result wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, u16 protocol, u32 *out)
{
    return serviceMitmDispatchInOut(s, 27, protocol, *out);
}

Result wlanLocalManagerAddMatchingDataToRxEntry(Service *s, u32 rxId, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 28, rxId,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

Result wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s, u32 rxId, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 29, rxId,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

Result wlanLocalManagerGetScanResult(Service *s, const void *in_buffer, size_t in_buffer_size, ams::mitm::wlan::ScanResult *result, size_t result_size)
{
    return serviceMitmDispatch(s, 30,
                               .buffer_attrs = {
                                   SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize,
                                   SfBufferAttr_Out | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                                   {result, result_size},
                               }, );
}

Result wlanLocalManagerPutActionFrameOneShot(Service *s, ams::mitm::wlan::PutActionFrameOneShotData in, const void *in_array, size_t in_array_size)
{
    return serviceMitmDispatchIn(s, 31, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                 .buffers = {
                                     {in_array, in_array_size},
                                 }, );
}

Result wlanLocalManagerSetActionFrameWithBeacon(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 32,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

Result wlanLocalManagerCancelActionFrameWithBeacon(Service *s)
{
    return serviceMitmDispatch(s, 33);
}

Result wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 capacity, u32 *rxId, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 34, capacity, *rxId,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

Result wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 rxId)
{
    return serviceMitmDispatchIn(s, 35, rxId);
}

Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u32 rxId, u32 subType)
{
    const struct
    {
        u32 rxId;
        u32 subType;
    } in = {rxId, subType};
    return serviceMitmDispatchIn(s, 36, in);
}

Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 subType, u32 *out)
{
    return serviceMitmDispatchInOut(s, 37, subType, *out);
}

Result wlanLocalManagerCancelGetActionFrame(Service *s, u32 rxId)
{
    return serviceMitmDispatchIn(s, 38, rxId);
}

Result wlanLocalManagerGetRssi(Service *s, u32 *rssi)
{
    return serviceMitmDispatchOut(s, 39, *rssi);
}

Result wlanLocalManagerSetMaxAssociationNumber(Service *s, u32 maxAssociationNumber)
{
    return serviceMitmDispatchIn(s, 40, maxAssociationNumber);
}

Result wlanLocalManagerCmd41(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatchOut(s, 41, *out,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_buffer, out_buffer_size},
                                  }, );
}

Result wlanLocalManagerCmd42(Service *s, u8 in)
{
    return serviceMitmDispatchIn(s, 42, in);
}

Result wlanLocalManagerCmd43(Service *s, ams::mitm::wlan::Cmd43Data in)
{
    return serviceMitmDispatchIn(s, 43, in);
}

Result wlanLocalManagerCmd44(Service *s, ams::mitm::wlan::Bss in)
{
    return serviceMitmDispatchIn(s, 44, in);
}

Result wlanLocalManagerCmd45(Service *s, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 45, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

Result wlanLocalManagerCmd46(Service *s, u8 in)
{
    return serviceMitmDispatchIn(s, 46, in);
}

Result wlanLocalManagerCmd47(Service *s, ams::mitm::wlan::Cmd47Data in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 47, in, *out);
}

Result wlanLocalManagerCmd48(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 48, in);
}

Result wlanLocalManagerCmd49(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 49, in);
}

Result wlanLocalManagerCmd50(Service *s)
{
    return serviceMitmDispatch(s, 50);
}

Result wlanLocalManagerCmd51(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 51, *out);
}
