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
#include "wlan_mitm/wlan_lg_service.hpp"

namespace ams::mitm::wlan
{
    /* Command forwarders. */
    Result WlanLgMitmService::GetFrameRaw(u32 rxId, ams::sf::Out<u32> frameSize, ams::sf::OutMapAliasBuffer data)
    {
        DEBUG_LOG("GetFrameRaw rxId: %d data ptr: %p", rxId, data.GetPointer());
        if (m_config->wlan_lg.commands.disable_getframeraw)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalGetFrameGetFrameRaw(m_forward_service.get(), rxId, frameSize.GetPointer(), data.GetPointer(), data.GetSize());
        DEBUG_LOG("GetFrameRaw rc: %#x", rc);
        DEBUG_LOG("GetFrameRaw frameSize: %d", frameSize.GetValue());
        DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "GetFrameRaw data");
        return rc;
    }
}
