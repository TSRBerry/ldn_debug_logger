/*
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
#include "ldn_shim.hpp"

/* Command forwarders. */
Result ldnGetIUserLocalCommunicationInterfaceFwd(Service *s, LdnIUserLocalCommunicationInterface *out)
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

static Result _ldnUserCommunicationGetSecurityParameter(Service *s, ams::mitm::ldn::SecurityParameter *out)
{
    return serviceMitmDispatchOut(s, 4, out);
}

static Result _ldnUserCommunicationGetNetworkConfig(Service *s, ams::mitm::ldn::NetworkConfig *out)
{
    return serviceMitmDispatchOut(s, 5, out);
}

static Result _ldnUserCommunicationAttachStateChangeEvent(Service *s, ams::os::NativeHandle handle)
{
    return serviceMitmDispatch(s, 100,
                               .out_handles = &handle, );
}

static Result _ldnUserCommunicationGetNetworkInfoLatestUpdate(Service *s, ams::mitm::ldn::NetworkInfo *out, ams::mitm::ldn::NodeLatestUpdate *out_buffer, size_t out_buffer_size)
{
    return serviceMitmDispatch(s, 101,
                               .buffer_attrs = {SfBufferAttr_HipcPointer | SfBufferAttr_Out},
                               .buffers = {
                                   {out, sizeof(ams::mitm::ldn::NetworkInfo)},
                                   {out_buffer, out_buffer_size},
                               }, );
}

static Result _ldnUserCommunicationScan(Service *s, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, ams::mitm::ldn::ScanFilter filter)
{
    const struct
    {
        s16 channel;
        ams::mitm::ldn::ScanFilter filter;
    } in = {channel, filter};
    return serviceMitmDispatchInOut(s, 102, in, total_out,
                                    .buffer_attrs = {SfBufferAttr_HipcAutoSelect | SfBufferAttr_Out},
                                    .buffers = {
                                        {out_buffer, out_buffer_size},
                                    }, );
}

static Result _ldnUserCommunicationScanPrivate(Service *s, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, ams::mitm::ldn::ScanFilter filter)
{
    const struct
    {
        s16 channel;
        ams::mitm::ldn::ScanFilter filter;
    } in = {channel, filter};
    return serviceMitmDispatchInOut(s, 103, in, total_out,
                                    .buffer_attrs = {SfBufferAttr_HipcAutoSelect | SfBufferAttr_Out},
                                    .buffers = {
                                        {out_buffer, out_buffer_size},
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

static Result _ldnUserCommunicationCreateNetworkPrivate(Service *s, ams::mitm::ldn::CreateNetworkPrivateConfig data, const ams::mitm::ldn::AddressEntry *entries, size_t entries_size)
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

static Result _ldnUserCommunicationInitialize(Service *s, u64 pid)
{
    u64 pid_placeholder = 0;
    return serviceMitmDispatchIn(s, 400, pid_placeholder, .in_send_pid = true, .override_pid = pid, );
}

static Result _ldnUserCommunicationFinalize(Service *s)
{
    return serviceMitmDispatch(s, 401);
}

Result ldnUserCommunicationGetState(LdnIUserLocalCommunicationInterface *doc, u32 *state)
{
    return _ldnUserCommunicationGetState(&doc->s, state);
}

Result ldnUserCommunicationGetNetworkInfo(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out)
{
    return _ldnUserCommunicationGetNetworkInfo(&doc->s, out);
}

Result ldnUserCommunicationGetIpv4Address(LdnIUserLocalCommunicationInterface *doc, LdnIpv4Address *addr, LdnSubnetMask *netmask)
{
    return _ldnUserCommunicationGetIpv4Address(&doc->s, addr, netmask);
}

Result ldnUserCommunicationGetDisconnectReason(LdnIUserLocalCommunicationInterface *doc, s16 *reason)
{
    return _ldnUserCommunicationGetDisconnectReason(&doc->s, reason);
}

Result ldnUserCommunicationGetSecurityParameter(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::SecurityParameter *out)
{
    return _ldnUserCommunicationGetSecurityParameter(&doc->s, out);
}

Result ldnUserCommunicationGetNetworkConfig(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkConfig *out)
{
    return _ldnUserCommunicationGetNetworkConfig(&doc->s, out);
}

Result ldnUserCommunicationAttachStateChangeEvent(LdnIUserLocalCommunicationInterface *doc, ams::os::SystemEvent *handle)
{
    return _ldnUserCommunicationAttachStateChangeEvent(&doc->s, handle->GetReadableHandle());
}

Result ldnUserCommunicationGetNetworkInfoLatestUpdate(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out, ams::mitm::ldn::NodeLatestUpdate *out_buffer, size_t out_buffer_size)
{
    return _ldnUserCommunicationGetNetworkInfoLatestUpdate(&doc->s, out, out_buffer, out_buffer_size);
}

Result ldnUserCommunicationScan(LdnIUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, ams::mitm::ldn::ScanFilter filter)
{
    return _ldnUserCommunicationScan(&doc->s, total_out, out_buffer, out_buffer_size, channel, filter);
}

Result ldnUserCommunicationScanPrivate(LdnIUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, ams::mitm::ldn::ScanFilter filter)
{
    return _ldnUserCommunicationScanPrivate(&doc->s, total_out, out_buffer, out_buffer_size, channel, filter);
}

Result ldnUserCommunicationSetWirelessControllerRestriction(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::WirelessControllerRestriction in)
{
    return _ldnUserCommunicationSetWirelessControllerRestriction(&doc->s, in);
}

Result ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(LdnIUserLocalCommunicationInterface *doc, u32 in)
{
    return _ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(&doc->s, in);
}

Result ldnUserCommunicationOpenAccessPoint(LdnIUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationOpenAccessPoint(&doc->s);
}

Result ldnUserCommunicationCloseAccessPoint(LdnIUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationCloseAccessPoint(&doc->s);
}

Result ldnUserCommunicationCreateNetwork(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkConfig data)
{
    return _ldnUserCommunicationCreateNetwork(&doc->s, data);
}

Result ldnUserCommunicationCreateNetworkPrivate(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkPrivateConfig data, const ams::mitm::ldn::AddressEntry *entries, size_t entries_size)
{
    return _ldnUserCommunicationCreateNetworkPrivate(&doc->s, data, entries, entries_size);
}

Result ldnUserCommunicationDestroyNetwork(LdnIUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationDestroyNetwork(&doc->s);
}

Result ldnUserCommunicationReject(LdnIUserLocalCommunicationInterface *doc, LdnIpv4Address *addr)
{
    return _ldnUserCommunicationReject(&doc->s, addr);
}

Result ldnUserCommunicationSetAdvertiseData(LdnIUserLocalCommunicationInterface *doc, const void *advertiseData, size_t advertiseData_size)
{
    return _ldnUserCommunicationSetAdvertiseData(&doc->s, advertiseData, advertiseData_size);
}

Result ldnUserCommunicationInitialize(LdnIUserLocalCommunicationInterface *doc, u64 pid)
{
    return _ldnUserCommunicationInitialize(&doc->s, pid);
}

Result ldnUserCommunicationFinalize(LdnIUserLocalCommunicationInterface *doc)
{
    return _ldnUserCommunicationFinalize(&doc->s);
}

void ldnIUserLocalCommunicationInterfaceClose(LdnIUserLocalCommunicationInterface *doc)
{
    serviceClose(&doc->s);
}
