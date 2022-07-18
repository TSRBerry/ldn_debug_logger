/*
 * Copyright (c) TSRBerry
 *  -> adapted for LDN
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
#include "ldn_mitm/ldn_shim.hpp"

/* Command forwarders. */
Result ldnGetUserLocalCommunicationInterfaceFwd(Service *s, LdnUserLocalCommunicationInterface *out)
{
    return serviceMitmDispatch(s, 0,
                               .out_num_objects = 1,
                               .out_objects = &out->s, );
}

static Result _ldnUserCommunicationGetState(Service *s, u32 *state)
{
    return serviceMitmDispatchOut(s, 0, *state);
}

static Result _ldnUserCommunicationGetNetworkInfo(Service *s, ams::mitm::ldn::NetworkInfo *out)
{
    return serviceMitmDispatch(s, 1,
                               .buffer_attrs = {SfBufferAttr_FixedSize | SfBufferAttr_HipcPointer | SfBufferAttr_Out},
                               .buffers = {
                                   {out, sizeof(ams::mitm::ldn::NetworkInfo)},
                               }, );
}

static Result _ldnUserCommunicationGetIpv4Address(Service *s, LdnIpv4Address *addr, LdnSubnetMask *subnetMask)
{
    struct
    {
        u32 addr;
        u32 netmask;
    } out;
    Result rc = serviceMitmDispatchOut(s, 2, out);
    addr->addr = out.addr;
    subnetMask->mask = out.netmask;
    return rc;
}

static Result _ldnUserCommunicationGetDisconnectReason(Service *s, s16 *reason)
{
    return serviceMitmDispatchOut(s, 3, reason);
}

static Result _ldnUserCommunicationGetSecurityParameter(Service *s, LdnSecurityParameter *out)
{
    return serviceMitmDispatchOut(s, 4, *out);
}

static Result _ldnUserCommunicationGetNetworkConfig(Service *s, LdnNetworkConfig *out)
{
    return serviceMitmDispatchOut(s, 5, *out);
}

static Result _ldnUserCommunicationAttachStateChangeEvent(Service *s, Handle *handle)
{
    return serviceMitmDispatch(s, 100,
                               .out_handle_attrs = {SfOutHandleAttr_HipcCopy},
                               .out_handles = handle, );
}

static Result _ldnUserCommunicationGetNetworkInfoLatestUpdate(Service *s, ams::mitm::ldn::NetworkInfo *out, LdnNodeLatestUpdate *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatch(s, 101,
                               .buffer_attrs = {SfBufferAttr_HipcPointer | SfBufferAttr_Out},
                               .buffers = {
                                   {out, sizeof(ams::mitm::ldn::NetworkInfo)},
                                   {out_buffer, out_buffer_size},
                               }, );
}

static Result _ldnUserCommunicationScan(Service *s, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter)
{
    const struct
    {
        // 0x02
        s16 channel;
        // 0x06
        u8 _pad[6];
        // 0x60
        LdnScanFilter filter;
    } in = {channel, {0}, filter};
    return serviceMitmDispatchInOut(s, 102, in, *total_out,
                                    .buffer_attrs = {SfBufferAttr_HipcAutoSelect | SfBufferAttr_Out},
                                    .buffers = {
                                        {out_buffer, out_buffer_size * sizeof(ams::mitm::ldn::NetworkInfo)},
                                    }, );
}

static Result _ldnUserCommunicationScanPrivate(Service *s, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter)
{
    const struct
    {
        // 0x02
        s16 channel;
        // 0x06
        u8 _pad[6];
        // 0x60
        LdnScanFilter filter;
    } in = {channel, {0}, filter};
    return serviceMitmDispatchInOut(s, 103, in, *total_out,
                                    .buffer_attrs = {SfBufferAttr_HipcAutoSelect | SfBufferAttr_Out},
                                    .buffers = {
                                        {out_buffer, out_buffer_size * sizeof(ams::mitm::ldn::NetworkInfo)},
                                    }, );
}

static Result _ldnUserCommunicationSetWirelessControllerRestriction(Service *s, ams::mitm::ldn::WirelessControllerRestriction in)
{
    return serviceMitmDispatchIn(s, 104, in);
}

static Result _ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(Service *s, u32 in)
{
    return serviceMitmDispatchIn(s, 105, in);
}

static Result _ldnUserCommunicationOpenAccessPoint(Service *s)
{
    return serviceMitmDispatch(s, 200);
}

static Result _ldnUserCommunicationCloseAccessPoint(Service *s)
{
    return serviceMitmDispatch(s, 201);
}

static Result _ldnUserCommunicationCreateNetwork(Service *s, ams::mitm::ldn::CreateNetworkConfig data)
{
    return serviceMitmDispatchIn(s, 202, data);
}

static Result _ldnUserCommunicationCreateNetworkPrivate(Service *s, ams::mitm::ldn::CreateNetworkPrivateConfig data, const LdnAddressEntry *entries, size_t entries_size)
{
    return serviceMitmDispatchIn(s, 203, data,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer},
                                 .buffers = {
                                     {entries, entries_size},
                                 }, );
}

static Result _ldnUserCommunicationDestroyNetwork(Service *s)
{
    return serviceMitmDispatch(s, 204);
}

static Result _ldnUserCommunicationReject(Service *s, LdnIpv4Address *addr)
{
    return serviceMitmDispatchIn(s, 205, addr);
}

static Result _ldnUserCommunicationSetAdvertiseData(Service *s, const void *advertiseData, size_t advertiseData_size)
{
    return serviceMitmDispatch(s, 206,
                               .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcAutoSelect},
                               .buffers = {
                                   {advertiseData, advertiseData_size},
                               }, );
}

static Result _ldnUserCommunicationSetStationAcceptPolicy(Service *s, LdnAcceptPolicy *policy)
{
    return serviceMitmDispatchIn(s, 207, policy);
}

static Result _ldnUserCommunicationAddAcceptFilterEntry(Service *s, LdnMacAddress *mac)
{
    return serviceMitmDispatchIn(s, 208, mac);
}

static Result _ldnUserCommunicationClearAcceptFilter(Service *s)
{
    return serviceMitmDispatch(s, 209);
}

static Result _ldnUserCommunicationOpenStation(Service *s)
{
    return serviceMitmDispatch(s, 300);
}

static Result _ldnUserCommunicationCloseStation(Service *s)
{
    return serviceMitmDispatch(s, 301);
}

static Result _ldnUserCommunicationConnect(Service *s, ams::mitm::ldn::ConnectNetworkData *dat, const LdnNetworkInfo *data)
{
    return serviceMitmDispatchIn(s, 302, dat,
                                 .buffer_attrs = {SfBufferAttr_In | SfBufferAttr_HipcPointer | SfBufferAttr_FixedSize},
                                 .buffers = {
                                     {data, sizeof(ams::mitm::ldn::NetworkInfo)},
                                 }, );
}

static Result _ldnUserCommunicationConnectPrivate(Service *s, ams::mitm::ldn::ConnectNetworkPrivateData *dat)
{
    return serviceMitmDispatchIn(s, 303, dat);
}

static Result _ldnUserCommunicationDisconnect(Service *s)
{
    return serviceMitmDispatch(s, 304);
}

static Result _ldnUserCommunicationInitialize(Service *s, u64 pid)
{
    u64 pid_placeholder = 0;
    return serviceMitmDispatchIn(s, 400, pid_placeholder, .in_send_pid = true, .override_pid = pid, );
}

static Result _ldnUserCommunicationFinalize(Service *s)
{
    return serviceMitmDispatch(s, 401);
}

static Result _ldnUserCommunicationInitialize2(Service *s, u32 unk, u64 pid)
{
    const struct
    {
        u32 unk;
        u64 pid_placeholder;
    } in = {unk, 0};
    return serviceMitmDispatchIn(s, 402, in, .in_send_pid = true, .override_pid = pid, );
}

Result ldnUserCommunicationGetState(LdnUserLocalCommunicationInterface *doc, u32 *state)
{
    return _ldnUserCommunicationGetState(&doc->s, state);
}

Result ldnUserCommunicationGetNetworkInfo(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out)
{
    return _ldnUserCommunicationGetNetworkInfo(&doc->s, out);
}

Result ldnUserCommunicationGetIpv4Address(LdnUserLocalCommunicationInterface *doc, LdnIpv4Address *addr, LdnSubnetMask *netmask)
{
    return _ldnUserCommunicationGetIpv4Address(&doc->s, addr, netmask);
}

Result ldnUserCommunicationGetDisconnectReason(LdnUserLocalCommunicationInterface *doc, s16 *reason)
{
    return _ldnUserCommunicationGetDisconnectReason(&doc->s, reason);
}

Result ldnUserCommunicationGetSecurityParameter(LdnUserLocalCommunicationInterface *doc, LdnSecurityParameter *out)
{
    return _ldnUserCommunicationGetSecurityParameter(&doc->s, out);
}

Result ldnUserCommunicationGetNetworkConfig(LdnUserLocalCommunicationInterface *doc, LdnNetworkConfig *out)
{
    return _ldnUserCommunicationGetNetworkConfig(&doc->s, out);
}

Result ldnUserCommunicationAttachStateChangeEvent(LdnUserLocalCommunicationInterface *doc, Handle *handle)
{
    return _ldnUserCommunicationAttachStateChangeEvent(&doc->s, handle);
}

Result ldnUserCommunicationGetNetworkInfoLatestUpdate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out, LdnNodeLatestUpdate *out_buffer, size_t out_buffer_size)
{
    return _ldnUserCommunicationGetNetworkInfoLatestUpdate(&doc->s, out, out_buffer, out_buffer_size);
}

Result ldnUserCommunicationScan(LdnUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter)
{
    return _ldnUserCommunicationScan(&doc->s, total_out, out_buffer, out_buffer_size, channel, filter);
}

Result ldnUserCommunicationScanPrivate(LdnUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter)
{
    return _ldnUserCommunicationScanPrivate(&doc->s, total_out, out_buffer, out_buffer_size, channel, filter);
}

Result ldnUserCommunicationSetWirelessControllerRestriction(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::WirelessControllerRestriction in)
{
    return _ldnUserCommunicationSetWirelessControllerRestriction(&doc->s, in);
}

Result ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(LdnUserLocalCommunicationInterface *doc, u32 in)
{
    return _ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(&doc->s, in);
}

Result ldnUserCommunicationOpenAccessPoint(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationOpenAccessPoint(&doc->s);
}

Result ldnUserCommunicationCloseAccessPoint(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationCloseAccessPoint(&doc->s);
}

Result ldnUserCommunicationCreateNetwork(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkConfig data)
{
    return _ldnUserCommunicationCreateNetwork(&doc->s, data);
}

Result ldnUserCommunicationCreateNetworkPrivate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkPrivateConfig data, const LdnAddressEntry *entries, size_t entries_size)
{
    return _ldnUserCommunicationCreateNetworkPrivate(&doc->s, data, entries, entries_size);
}

Result ldnUserCommunicationDestroyNetwork(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationDestroyNetwork(&doc->s);
}

Result ldnUserCommunicationReject(LdnUserLocalCommunicationInterface *doc, LdnIpv4Address *addr)
{
    return _ldnUserCommunicationReject(&doc->s, addr);
}

Result ldnUserCommunicationSetAdvertiseData(LdnUserLocalCommunicationInterface *doc, const void *advertiseData, size_t advertiseData_size)
{
    return _ldnUserCommunicationSetAdvertiseData(&doc->s, advertiseData, advertiseData_size);
}

Result ldnUserCommunicationSetStationAcceptPolicy(LdnUserLocalCommunicationInterface *doc, LdnAcceptPolicy *policy)
{
    return _ldnUserCommunicationSetStationAcceptPolicy(&doc->s, policy);
}

Result ldnUserCommunicationAddAcceptFilterEntry(LdnUserLocalCommunicationInterface *doc, LdnMacAddress *mac)
{
    return _ldnUserCommunicationAddAcceptFilterEntry(&doc->s, mac);
}

Result ldnUserCommunicationClearAcceptFilter(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationClearAcceptFilter(&doc->s);
}

Result ldnUserCommunicationOpenStation(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationOpenStation(&doc->s);
}

Result ldnUserCommunicationCloseStation(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationCloseStation(&doc->s);
}

Result ldnUserCommunicationConnect(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkData *dat, const LdnNetworkInfo *data)
{
    return _ldnUserCommunicationConnect(&doc->s, dat, data);
}

Result ldnUserCommunicationConnectPrivate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkPrivateData *dat)
{
    return _ldnUserCommunicationConnectPrivate(&doc->s, dat);
}

Result ldnUserCommunicationDisconnect(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationDisconnect(&doc->s);
}

Result ldnUserCommunicationInitialize(LdnUserLocalCommunicationInterface *doc, u64 pid)
{
    return _ldnUserCommunicationInitialize(&doc->s, pid);
}

Result ldnUserCommunicationFinalize(LdnUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationFinalize(&doc->s);
}

Result ldnUserCommunicationInitialize2(LdnUserLocalCommunicationInterface *doc, u32 unk, u64 pid)
{
    return _ldnUserCommunicationInitialize2(&doc->s, unk, pid);
}

void ldnUserLocalCommunicationInterfaceClose(LdnUserLocalCommunicationInterface *doc)
{
    serviceClose(&doc->s);
}
