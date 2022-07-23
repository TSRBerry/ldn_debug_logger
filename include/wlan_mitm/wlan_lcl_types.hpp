#pragma once
#include <stdint.h>
#include <stdlib.h>

#include <stratosphere.hpp>
#include <switch.h>

namespace ams::mitm::wlan
{
    enum Mode : u32
    {
        Ap,
        Station
    };

    struct Bss
    {
        u8 data[0x84];
    };

    struct ScanRequest : sf::LargeData
    {
        u32 scanType;
        u16 unknown1[38];
        u8 unknown2;
        u8 reserved1[0x3];
        u32 channelScanTime;
        u32 homeChannelTime;
        LdnSsid ssidArr[10];
        u8 ssidCount;
        LdnMacAddress bssid;
        u8 reserved2;
    };

    struct ConnectParam
    {
        LdnSsid ssid;
        LdnMacAddress bssid;
        u8 unknown;
        u8 reserved1;
        u16 channel;
        u32 privacyMode;
        u32 groupPrivacyMode;
        u32 keyIdx;
        u8 securityKey[0x40];
        u32 reserved2;
        u32 beaconLostTimeout;
    };

    struct DisconnectData
    {
        u32 argument;
        LdnMacAddress mac;
    };

    enum ConnectionState : u32
    {
        None,
        Idle,
        Connected,
        Scanning,
        Connecting,
        CancelingScan,
        Disconnecting
    };

    struct ConnectionStatus
    {
        ConnectionState connectionState;
        u32 unknown1;
        u16 channel;
        LdnMacAddress bssid;
        LdnSsid ssid;
        u16 unknown2;
        u16 unknown3;
        u16 unknown4;
        u16 unknown5;
        u16 reserved;
    };

    struct ClientStatus : sf::LargeData
    {
        u8 unknownData[0xE4];
    };

    enum State : u32
    {
        Unknown0,
        Unknown1,
        Unknown2,
        Unknown3,
        Unknown4,
        Unknown5,
        Unknown6,
        Unknown7,
        Unknown8,
        Unknown9,
        Unknown10,
        Unknown11,
        Unknown12,
        Unknown13,
        Unknown14,
        Unknown15,
        Unknown16,
        Unknown17,
        Unknown18,
        Unknown19
    };

    struct BssInfo
    {
        u8 unknownData[0x58];
    };

    struct ScanResult
    {
        u32 scanBufferCapacity;
        u32 bssInfoSize;
        u32 bssInfoCount;
        // variable length
        BssInfo bssInfoArr[];
    };

    struct PutActionFrameOneShotData
    {
        LdnMacAddress bssid;
        u32 channel;
        u32 dwellTime;
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
