#pragma once
#include <stdint.h>
#include <stdlib.h>

#include <stratosphere.hpp>
#include <switch.h>

namespace ams::mitm::ldn
{

    enum WirelessControllerRestriction : u32
    {
        Unknown = 0,
        Default = 1
    };

    enum NodeStateChange
    {
        NodeStateChange_None = 0,
        NodeStateChange_Connect = 1,
        NodeStateChange_Disconnect = 2,
        NodeStateChange_DisconnectAndConnect = 3
    };

    enum class CommState
    {
        None,
        Initialized,
        AccessPoint,
        AccessPointCreated,
        Station,
        StationConnected,
        Error
    };

    struct AddressEntry : sf::LargeData
    {
        LdnAddressEntry entry;
    };

    struct CreateNetworkConfig
    {
        LdnSecurityConfig securityConfig;
        LdnUserConfig userConfig;
        LdnNetworkConfig networkConfig;
    };

    struct CreateNetworkPrivateConfig
    {
        LdnSecurityConfig securityConfig;
        LdnSecurityParameter securityParameter;
        LdnUserConfig userConfig;
        LdnNetworkConfig networkConfig;
    };

    struct ConnectNetworkData
    {
        LdnSecurityConfig securityConfig;
        LdnUserConfig userConfig;
        uint32_t localCommunicationVersion;
        uint32_t option;
    };

    struct ConnectNetworkPrivateData
    {
        LdnSecurityConfig securityConfig;
        LdnSecurityParameter securityParameter;
        LdnUserConfig userConfig;
        uint32_t localCommunicationVersion;
        uint32_t option;
        LdnNetworkConfig networkConfig;
    };

    struct Ipv4Address : sf::LargeData
    {
        LdnIpv4Address addr;
    };

    struct SubnetMask : sf::LargeData
    {
        LdnSubnetMask netmask;
    };

    struct NetworkInfo : sf::LargeData
    {
        LdnNetworkInfo networkInfo;
    };

    struct NetworkConfig : sf::LargeData
    {
        LdnNetworkConfig networkConfig;
    };

    struct NodeLatestUpdate : sf::LargeData
    {
        LdnNodeLatestUpdate latestUpdate;
    };

    struct SecurityParameter : sf::LargeData
    {
        LdnSecurityParameter securityParam;
    };
}
