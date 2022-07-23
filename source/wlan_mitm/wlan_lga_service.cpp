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
#include "wlan_mitm/wlan_lga_service.hpp"

namespace ams::mitm::wlan
{
    /* Command forwarders. */
    Result WlanLgaMitmService::GetActionFrame(u32 rxId, u32 in, ams::sf::Out<LdnMacAddress> macAddress, ams::sf::Out<u32> actionFrame, ams::sf::Out<u32> out, ams::sf::OutMapAliasBuffer data)
    {
        DEBUG_LOG("GetActionFrame rxId: %d in value: %d data ptr: %p", rxId, in, data.GetPointer());
        if (m_config->wlan_lga.commands.disable_getactionframe)
        {
            return sm::mitm::ResultShouldForwardToSession();
        }
        Result rc = wlanLocalGetActionFrameGetActionFrame(m_forward_service.get(), rxId, in, macAddress.GetPointer(), actionFrame.GetPointer(), out.GetPointer(), data.GetPointer(), data.GetSize());
        DEBUG_LOG("GetActionFrame rc: %#x", rc);
        DEBUG_DATA_DUMP(macAddress.GetPointer(), sizeof(LdnMacAddress), "GetActionFrame macAddress");
        DEBUG_LOG("GetActionFrame actionFrame: %d", actionFrame.GetValue(), out.GetValue());
        DEBUG_DATA_DUMP(data.GetPointer(), data.GetSize(), "GetActionFrame data");
        return rc;
    }
}
