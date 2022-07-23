#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>

#define AMS_WLAN_LG_INTERFACE_INFO(C, H) \
    AMS_SF_METHOD_INFO(C, H, 0, Result, GetFrameRaw, (u32 rxId, ams::sf::Out<u32> frameSize, ams::sf::OutMapAliasBuffer data), (rxId, frameSize, data))

AMS_SF_DEFINE_MITM_INTERFACE(ams::mitm::wlan, IWlanLgMitmInterface, AMS_WLAN_LG_INTERFACE_INFO, 0x28461B63)
