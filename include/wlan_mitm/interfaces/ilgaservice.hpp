#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#define AMS_WLAN_LGA_INTERFACE_INFO(C, H) \
    AMS_SF_METHOD_INFO(C, H, 0, Result, GetActionFrame, (u32 rxId, u32 in, ams::sf::Out<LdnMacAddress> macAddress, ams::sf::Out<u32> actionFrame, ams::sf::Out<u32> out, ams::sf::OutMapAliasBuffer data), (rxId, in, macAddress, actionFrame, out, data))

AMS_SF_DEFINE_MITM_INTERFACE(ams::mitm::wlan, IWlanLgaMitmInterface, AMS_WLAN_LGA_INTERFACE_INFO, 0xDA0D5608)
