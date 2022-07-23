/*
 * Copyright (c) TSRBerry
 *  -> adapted for wlan:lga
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
#include "wlan_mitm/wlan_lga_shim.hpp"

/* Command forwarders. */
Result wlanLocalGetActionFrameGetActionFrame(Service *s, u32 rxId, u32 in, LdnMacAddress *macAddress, u32 *actionFrame, u32 *out, void *data, size_t data_size)
{
    const struct
    {
        u32 rxId;
        u32 in;
    } in_data = {rxId, in};

    struct
    {
        LdnMacAddress mac;
        u32 actionFrame;
        u32 out;
    } out_data;

    Result rc = serviceMitmDispatchInOut(s, 0, in_data, out_data,
                                         .buffer_attrs = {SfBufferAttr_Out | SfBufferAttr_HipcMapAlias},
                                         .buffers = {
                                             {data, data_size},
                                         }, );
    *macAddress = out_data.mac;
    *actionFrame = out_data.actionFrame;
    *out = out_data.out;

    return rc;
}
