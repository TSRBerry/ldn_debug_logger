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
#include "wlan_lcl_shim.hpp"

/* Command forwarders. */
static Result _wlanLocalManagerOpenMasterMode(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 0, in);
}

static Result _wlanLocalManagerCloseMasterMode(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 1, in);
}

static Result _wlanLocalManagerOpenClientMode(Service *s, ams::mitm::wlan::OpenClientModeData *out)
{
    return serviceMitmDispatchOut(s, 2, out);
}

static Result _wlanLocalManagerCloseClientMode(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 3, in);
}

static Result _wlanLocalManagerOpenSpectatorMode(Service *s)
{
    return serviceMitmDispatch(s, 4);
}

static Result _wlanLocalManagerCloseSpectatorMode(Service *s, const ams::mitm::wlan::SpectatorModeData *data)
{
    return serviceMitmDispatch(s, 5,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, sizeof(ams::mitm::wlan::SpectatorModeData)},
                               }, );
}

static Result _wlanLocalManagerGetMacAddress(Service *s)
{
    return serviceMitmDispatch(s, 6);
}

static Result _wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 7, in);
}

static Result _wlanLocalManagerDestroyBss(Service *s)
{
    return serviceMitmDispatch(s, 8);
}

static Result _wlanLocalManagerStartScan(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 9, in);
}

static Result _wlanLocalManagerStopScan(Service *s)
{
    return serviceMitmDispatch(s, 10);
}

static Result _wlanLocalManagerConnect(Service *s, ams::mitm::wlan::ConnectData in)
{
    return serviceMitmDispatchIn(s, 11, in);
}

static Result _wlanLocalManagerCancelConnect(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 12, in);
}

static Result _wlanLocalManagerJoin(Service *s, u32 in, Handle *handle)
{
    return serviceMitmDispatchIn(s, 13, in,
                                 .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                                 .out_handles = handle, );
}

static Result _wlanLocalManagerCancelJoin(Service *s, ams::mitm::wlan::CancelJoinData *out)
{
    return serviceMitmDispatchOut(s, 14, out);
}

static Result _wlanLocalManagerDisconnect(Service *s, void *data, size_t data_size)
{
    return serviceMitmDispatch(s, 15,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

static Result _wlanLocalManagerSetBeaconLostCount(Service *s, Handle *handle)
{
    return serviceMitmDispatch(s, 16,
                               .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                               .out_handles = handle, );
}

static Result _wlanLocalManagerGetSystemEvent(Service *s, void *data, size_t data_size)
{
    return serviceMitmDispatch(s, 17,
                               .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias | SfBufferAttr_FixedSize},
                               .buffers = {
                                   {data, data_size},
                               }, );
}

static Result _wlanLocalManagerGetConnectionStatus(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 18, out);
}

static Result _wlanLocalManagerGetClientStatus(Service *s, u32 *out, ams::mitm::wlan::ClientStatusData *out_data)
{
    return serviceMitmDispatchOut(s, 19, out,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_data, sizeof(ams::mitm::wlan::ClientStatusData)},
                                  }, );
}

static Result _wlanLocalManagerGetBssIndicationEvent(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 20, in, out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

static Result _wlanLocalManagerGetBssIndicationInfo(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 21, in);
}

static Result _wlanLocalManagerGetState(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 22,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

static Result _wlanLocalManagerGetAllowedChannels(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 23, in);
}

static Result _wlanLocalManagerAddIe(Service *s, u32 in, u32 *out, const ams::mitm::wlan::IeData *in_array, size_t in_array_size)
{
    return serviceMitmDispatchInOut(s, 24, in, out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {{in_array, sizeof(ams::mitm::wlan::IeData) * in_array_size}});
}

static Result _wlanLocalManagerDeleteIe(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 25, in);
}

static Result _wlanLocalManagerPutFrameRaw(Service *s, u64 in)
{
    return serviceMitmDispatchIn(s, 26, in);
}

static Result _wlanLocalManagerCancelGetFrame(Service *s, u16 in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 27, in, out);
}

static Result _wlanLocalManagerCreateRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 28, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

static Result _wlanLocalManagerDeleteRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 29, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

static Result _wlanLocalManagerAddEthertypeToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size)
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

static Result _wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, ams::mitm::wlan::DeleteEthertypeFromRxEntryData in, const void *in_array, size_t in_array_size)
{
    return serviceMitmDispatchIn(s, 31, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                 .buffers = {
                                     {in_array, in_array_size},
                                 }, );
}

static Result _wlanLocalManagerAddMatchingDataToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatch(s, 32,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                               .buffers = {
                                   {in_buffer, in_buffer_size},
                               }, );
}

static Result _wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s)
{
    return serviceMitmDispatch(s, 33);
}

static Result _wlanLocalManagerGetScanResult(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchInOut(s, 34, in, out,
                                    .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                    .buffers = {
                                        {in_buffer, in_buffer_size},
                                    }, );
}

static Result _wlanLocalManagerPutActionFrameOneShot(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 35, in);
}

static Result _wlanLocalManagerSetActionFrameWithBeacon(Service *s, u64 in)
{
    return serviceMitmDispatchIn(s, 36, in);
}

static Result _wlanLocalManagerCancelActionFrameWithBeacon(Service *s, u32 in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 37, in, out);
}

static Result _wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 38, in);
}

static Result _wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 39, out);
}

static Result _wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 40, in);
}

static Result _wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatchOut(s, 41, out,
                                  .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcPointer},
                                  .buffers = {
                                      {out_buffer, out_buffer_size},
                                  }, );
}

static Result _wlanLocalManagerCancelGetActionFrame(Service *s, u8 in)
{
    return serviceMitmDispatchIn(s, 42, in);
}

static Result _wlanLocalManagerGetRssi(Service *s, ams::mitm::wlan::GetRssiData in)
{
    return serviceMitmDispatchIn(s, 43, in);
}

static Result _wlanLocalManagerSetMaxAssociationNumber(Service *s, ams::mitm::wlan::UnknownNetworkData in)
{
    return serviceMitmDispatchIn(s, 44, in);
}

static Result _wlanLocalManagerCmd45(Service *s, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size)
{
    return serviceMitmDispatchIn(s, 45, in,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcMapAlias},
                                 .buffers = {
                                     {in_buffer, in_buffer_size},
                                 }, );
}

static Result _wlanLocalManagerCmd46(Service *s, u8 in)
{
    return serviceMitmDispatchIn(s, 46, in);
}

static Result _wlanLocalManagerCmd47(Service *s, ams::mitm::wlan::Cmd47Data in, u32 *out)
{
    return serviceMitmDispatchInOut(s, 47, in, out);
}

static Result _wlanLocalManagerCmd48(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 48, in);
}

static Result _wlanLocalManagerCmd49(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 49, in);
}

static Result _wlanLocalManagerCmd50(Service *s)
{
    return serviceMitmDispatch(s, 50);
}

static Result _wlanLocalManagerCmd51(Service *s, u32 *out)
{
    return serviceMitmDispatchOut(s, 51, out);
}

Result wlanLocalManagerOpenMasterMode(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerOpenMasterMode(&doc->s, in);
}

Result wlanLocalManagerCloseMasterMode(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerCloseMasterMode(&doc->s, in);
}

Result wlanLocalManagerOpenClientMode(WlanILocalManagerInterface *doc, ams::mitm::wlan::OpenClientModeData *out)
{
    return _wlanLocalManagerOpenClientMode(&doc->s, out);
}

Result wlanLocalManagerCloseClientMode(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in)
{
    return _wlanLocalManagerCloseClientMode(&doc->s, in);
}

Result wlanLocalManagerOpenSpectatorMode(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerOpenSpectatorMode(&doc->s);
}

Result wlanLocalManagerCloseSpectatorMode(WlanILocalManagerInterface *doc, const ams::mitm::wlan::SpectatorModeData *data)
{
    return _wlanLocalManagerCloseSpectatorMode(&doc->s, data);
}

Result wlanLocalManagerGetMacAddress(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerGetMacAddress(&doc->s);
}

Result wlanLocalManagerCreateBss(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in)
{
    return _wlanLocalManagerCreateBss(&doc->s, in);
}

Result wlanLocalManagerDestroyBss(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerDestroyBss(&doc->s);
}

Result wlanLocalManagerStartScan(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in)
{
    return _wlanLocalManagerStartScan(&doc->s, in);
}

Result wlanLocalManagerStopScan(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerStopScan(&doc->s);
}

Result wlanLocalManagerConnect(WlanILocalManagerInterface *doc, ams::mitm::wlan::ConnectData in)
{
    return _wlanLocalManagerConnect(&doc->s, in);
}

Result wlanLocalManagerCancelConnect(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerCancelConnect(&doc->s, in);
}

Result wlanLocalManagerJoin(WlanILocalManagerInterface *doc, u32 in, Handle *handle)
{
    return _wlanLocalManagerJoin(&doc->s, in, handle);
}

Result wlanLocalManagerCancelJoin(WlanILocalManagerInterface *doc, ams::mitm::wlan::CancelJoinData *out)
{
    return _wlanLocalManagerCancelJoin(&doc->s, out);
}

Result wlanLocalManagerDisconnect(WlanILocalManagerInterface *doc, void *data, size_t data_size)
{
    return _wlanLocalManagerDisconnect(&doc->s, data, data_size);
}

Result wlanLocalManagerSetBeaconLostCount(WlanILocalManagerInterface *doc, Handle *handle)
{
    return _wlanLocalManagerSetBeaconLostCount(&doc->s, handle);
}

Result wlanLocalManagerGetSystemEvent(WlanILocalManagerInterface *doc, void *data, size_t data_size)
{
    return _wlanLocalManagerGetSystemEvent(&doc->s, data, data_size);
}

Result wlanLocalManagerGetConnectionStatus(WlanILocalManagerInterface *doc, u32 *out)
{
    return _wlanLocalManagerGetConnectionStatus(&doc->s, out);
}

Result wlanLocalManagerGetClientStatus(WlanILocalManagerInterface *doc, u32 *out, ams::mitm::wlan::ClientStatusData *out_data)
{
    return _wlanLocalManagerGetClientStatus(&doc->s, out, out_data);
}

Result wlanLocalManagerGetBssIndicationEvent(WlanILocalManagerInterface *doc, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerGetBssIndicationEvent(&doc->s, in, out, in_buffer, in_buffer_size);
}

Result wlanLocalManagerGetBssIndicationInfo(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerGetBssIndicationInfo(&doc->s, in);
}

Result wlanLocalManagerGetState(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerGetState(&doc->s, in_buffer, in_buffer_size);
}

Result wlanLocalManagerGetAllowedChannels(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerGetAllowedChannels(&doc->s, in);
}

Result wlanLocalManagerAddIe(WlanILocalManagerInterface *doc, u32 in, u32 *out, const ams::mitm::wlan::IeData *in_array, size_t in_array_size)
{
    return _wlanLocalManagerAddIe(&doc->s, in, out, in_array, in_array_size);
}

Result wlanLocalManagerDeleteIe(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerDeleteIe(&doc->s, in);
}

Result wlanLocalManagerPutFrameRaw(WlanILocalManagerInterface *doc, u64 in)
{
    return _wlanLocalManagerPutFrameRaw(&doc->s, in);
}

Result wlanLocalManagerCancelGetFrame(WlanILocalManagerInterface *doc, u16 in, u32 *out)
{
    return _wlanLocalManagerCancelGetFrame(&doc->s, in, out);
}

Result wlanLocalManagerCreateRxEntry(WlanILocalManagerInterface *doc, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerCreateRxEntry(&doc->s, in, in_buffer, in_buffer_size);
}

Result wlanLocalManagerDeleteRxEntry(WlanILocalManagerInterface *doc, u32 in, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerDeleteRxEntry(&doc->s, in, in_buffer, in_buffer_size);
}

Result wlanLocalManagerAddEthertypeToRxEntry(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size)
{
    return _wlanLocalManagerAddEthertypeToRxEntry(&doc->s, in_buffer, in_buffer_size, out_buffer, out_buffer_size);
}

Result wlanLocalManagerDeleteEthertypeFromRxEntry(WlanILocalManagerInterface *doc, ams::mitm::wlan::DeleteEthertypeFromRxEntryData in, const void *in_array, size_t in_array_size)
{
    return _wlanLocalManagerDeleteEthertypeFromRxEntry(&doc->s, in, in_array, in_array_size);
}

Result wlanLocalManagerAddMatchingDataToRxEntry(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerAddMatchingDataToRxEntry(&doc->s, in_buffer, in_buffer_size);
}

Result wlanLocalManagerRemoveMatchingDataFromRxEntry(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerRemoveMatchingDataFromRxEntry(&doc->s);
}

Result wlanLocalManagerGetScanResult(WlanILocalManagerInterface *doc, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerGetScanResult(&doc->s, in, out, in_buffer, in_buffer_size);
}

Result wlanLocalManagerPutActionFrameOneShot(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerPutActionFrameOneShot(&doc->s, in);
}

Result wlanLocalManagerSetActionFrameWithBeacon(WlanILocalManagerInterface *doc, u64 in)
{
    return _wlanLocalManagerSetActionFrameWithBeacon(&doc->s, in);
}

Result wlanLocalManagerCancelActionFrameWithBeacon(WlanILocalManagerInterface *doc, u32 in, u32 *out)
{
    return _wlanLocalManagerCancelActionFrameWithBeacon(&doc->s, in, out);
}

Result wlanLocalManagerCreateRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerCreateRxEntryForActionFrame(&doc->s, in);
}

Result wlanLocalManagerDeleteRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 *out)
{
    return _wlanLocalManagerDeleteRxEntryForActionFrame(&doc->s, out);
}

Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerAddSubtypeToRxEntryForActionFrame(&doc->s, in);
}

Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 *out, void *out_buffer, size_t out_buffer_size)
{
    return _wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(&doc->s, out, out_buffer, out_buffer_size);
}

Result wlanLocalManagerCancelGetActionFrame(WlanILocalManagerInterface *doc, u8 in)
{
    return _wlanLocalManagerCancelGetActionFrame(&doc->s, in);
}

Result wlanLocalManagerGetRssi(WlanILocalManagerInterface *doc, ams::mitm::wlan::GetRssiData in)
{
    return _wlanLocalManagerGetRssi(&doc->s, in);
}

Result wlanLocalManagerSetMaxAssociationNumber(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in)
{
    return _wlanLocalManagerSetMaxAssociationNumber(&doc->s, in);
}

Result wlanLocalManagerCmd45(WlanILocalManagerInterface *doc, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size)
{
    return _wlanLocalManagerCmd45(&doc->s, in, in_buffer, in_buffer_size);
}

Result wlanLocalManagerCmd46(WlanILocalManagerInterface *doc, u8 in)
{
    return _wlanLocalManagerCmd46(&doc->s, in);
}

Result wlanLocalManagerCmd47(WlanILocalManagerInterface *doc, ams::mitm::wlan::Cmd47Data in, u32 *out)
{
    return _wlanLocalManagerCmd47(&doc->s, in, out);
}

Result wlanLocalManagerCmd48(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerCmd48(&doc->s, in);
}

Result wlanLocalManagerCmd49(WlanILocalManagerInterface *doc, u32 in)
{
    return _wlanLocalManagerCmd49(&doc->s, in);
}

Result wlanLocalManagerCmd50(WlanILocalManagerInterface *doc)
{
    return _wlanLocalManagerCmd50(&doc->s);
}

Result wlanLocalManagerCmd51(WlanILocalManagerInterface *doc, u32 *out)
{
    return _wlanLocalManagerCmd51(&doc->s, out);
}
