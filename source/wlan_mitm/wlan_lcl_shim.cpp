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
Result wlanLocalManagerOpenMasterMode(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 0, in);
}

Result wlanLocalManagerCloseMasterMode(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 1, in);
}

Result wlanLocalManagerOpenClientMode(Service *s, ams::mitm::wlan::OpenClientModeData *out)
{
    return serviceMitmDispatchOut(s, 2, *out);
}

Result wlanLocalManagerCloseClientMode(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 3, in);
}

Result wlanLocalManagerOpenSpectatorMode(Service *s)
{
    return serviceMitmDispatch(s, 4);
}

Result wlanLocalManagerCloseSpectatorMode(Service *s, const u8 *data, size_t data_size)
{
    return serviceMitmDispatch(s, 5,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

Result wlanLocalManagerGetMacAddress(Service *s)
{
    return serviceMitmDispatch(s, 6);
}

Result wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 7, in);
}

Result wlanLocalManagerDestroyBss(Service *s)
{
    return serviceMitmDispatch(s, 8);
}

Result wlanLocalManagerStartScan(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 9, in);
}

Result wlanLocalManagerStopScan(Service *s)
{
    return serviceMitmDispatch(s, 10);
}

Result wlanLocalManagerConnect(Service *s, ams::mitm::wlan::ConnectData in)
{
    return serviceMitmDispatchIn(s, 11, in);
}

Result wlanLocalManagerCancelConnect(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 12, in);
}

Result wlanLocalManagerJoin(Service *s, u32 in, Handle *handle)
{
    return serviceMitmDispatchIn(s, 13, in,
                                 .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                                 .out_handles = handle, );
}

Result wlanLocalManagerCancelJoin(Service *s, ams::mitm::wlan::CancelJoinData *out)
{
    return serviceMitmDispatchOut(s, 14, *out);
}

Result wlanLocalManagerDisconnect(Service *s, void *data, size_t data_size)
{
    return serviceMitmDispatch(s, 15,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

Result wlanLocalManagerSetBeaconLostCount(Service *s, Handle *handle)
{
    return serviceMitmDispatch(s, 16,
                               .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                               .out_handles = handle, );
}

Result wlanLocalManagerGetSystemEvent(Service *s, void *data, size_t data_size)
{
    return serviceMitmDispatch(s, 17,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

Result wlanLocalManagerGetConnectionStatus(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 18, *out);
}

Result wlanLocalManagerGetClientStatus(Service *s, u32 *out, void *out_data, size_t out_data_size)
{
    return serviceMitmDispatchOut(s, 19, *out,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_data, out_data_size},
                                  }, );
}

Result wlanLocalManagerGetBssIndicationEvent(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 20, in, *out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

Result wlanLocalManagerGetBssIndicationInfo(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 21, in);
}

Result wlanLocalManagerGetState(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 22,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

Result wlanLocalManagerGetAllowedChannels(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 23, in);
}

Result wlanLocalManagerAddIe(Service *s, u32 in, u32 *out, const void *in_array, size_t in_array_size)
{
    return serviceMitmDispatchInOut(s, 24, in, *out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {
                                        {in_array, in_array_size},
                                    }, );
}

Result wlanLocalManagerDeleteIe(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 25, in);
}

Result wlanLocalManagerPutFrameRaw(Service *s, u64 in)
{
    return serviceMitmDispatchIn(s, 26, in);
}

Result wlanLocalManagerCancelGetFrame(Service *s, u16 in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 27, in, *out);
}

Result wlanLocalManagerCreateRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 28, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

Result wlanLocalManagerDeleteRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 29, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

Result wlanLocalManagerAddEthertypeToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatch(s, 30,
                               .buffer_attrs = {
                                   SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize,
                                   SfBufferAttr_Out | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                                   {out_buffer, out_buffer_size},
                               }, );
}

Result wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, ams::mitm::wlan::DeleteEthertypeFromRxEntryData in, const void *in_array, size_t in_array_size)
{
    return serviceMitmDispatchIn(s, 31, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                 .buffers = {
                                     {in_array, in_array_size},
                                 }, );
}

Result wlanLocalManagerAddMatchingDataToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 32,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

Result wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s)
{
    return serviceMitmDispatch(s, 33);
}

Result wlanLocalManagerGetScanResult(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 34, in, *out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

Result wlanLocalManagerPutActionFrameOneShot(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 35, in);
}

Result wlanLocalManagerSetActionFrameWithBeacon(Service *s, u64 in)
{
    return serviceMitmDispatchIn(s, 36, in);
}

Result wlanLocalManagerCancelActionFrameWithBeacon(Service *s, u32 in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 37, in, *out);
}

Result wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 38, in);
}

Result wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 39, *out);
}

Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 40, in);
}

Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatchOut(s, 41, *out,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_buffer, out_buffer_size},
                                  }, );
}

Result wlanLocalManagerCancelGetActionFrame(Service *s, u8 in)
{
    return serviceMitmDispatchIn(s, 42, in);
}

Result wlanLocalManagerGetRssi(Service *s, ams::mitm::wlan::GetRssiData in)
{
    return serviceMitmDispatchIn(s, 43, in);
}

Result wlanLocalManagerSetMaxAssociationNumber(Service *s, ams::mitm::wlan::UnknownNetworkData in)
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
