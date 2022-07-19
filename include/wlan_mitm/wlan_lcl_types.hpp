#pragma once
#include <stdint.h>
#include <stdlib.h>

#include <stratosphere.hpp>
#include <switch.h>

namespace ams::mitm::wlan
{
    struct GetMacAddressData
    {
        u8 data[0x6];
    };

    struct UnknownNetworkData
    {
        u8 data[0x84];
    };

    struct DisconnectData
    {
        u8 data[0x10];
    };

    struct GetConnectionStatusData
    {
        u8 data[0x3C];
    };

    // struct ClientStatusData
    // {
    //     u8 unknown[0x10];
    // };

    // struct IeData
    // {
    //     u8 unknown[0x10];
    // };

    struct PutActionFrameOneShotData
    {
        u8 data[0x10];
    };

    struct Cmd43Data
    {
        u8 data[0x6];
    };

    struct Cmd45Data
    {
        u8 data[0x14];
    };

    struct Cmd47Data
    {
        u8 data[0x6];
    };
}
