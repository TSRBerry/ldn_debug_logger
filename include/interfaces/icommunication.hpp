#pragma once
#include <stratosphere.hpp>
#include <switch.h>

#include "../debug.hpp"
#include "../ldn_types.hpp"

#define AMS_LDN_IUSERLOCALCOMMUNICATION(C, H)                                                                                                                                                                                           \
       AMS_SF_METHOD_INFO(C, H, 0, Result, GetState, (ams::sf::Out<u32> state), (state))                                                                                                                                                \
       AMS_SF_METHOD_INFO(C, H, 1, Result, GetNetworkInfo, (ams::sf::Out<ams::mitm::ldn::NetworkInfo> buffer), (buffer))                                                                                                                \
       AMS_SF_METHOD_INFO(C, H, 2, Result, GetIpv4Address, (ams::sf::Out<LdnIpv4Address> address, ams::sf::Out<LdnSubnetMask> mask), (address, mask))                                                                                   \
       AMS_SF_METHOD_INFO(C, H, 3, Result, GetDisconnectReason, (ams::sf::Out<s16> reason), (reason))                                                                                                                                   \
       AMS_SF_METHOD_INFO(C, H, 4, Result, GetSecurityParameter, (ams::sf::Out<ams::mitm::ldn::SecurityParameter> out), (out))                                                                                                          \
       AMS_SF_METHOD_INFO(C, H, 5, Result, GetNetworkConfig, (ams::sf::Out<LdnNetworkConfig> out), (out))                                                                                                                               \
       AMS_SF_METHOD_INFO(C, H, 100, Result, AttachStateChangeEvent, (ams::sf::Out<ams::sf::CopyHandle> handle), (handle))                                                                                                              \
       AMS_SF_METHOD_INFO(C, H, 101, Result, GetNetworkInfoLatestUpdate, (ams::sf::Out<ams::mitm::ldn::NetworkInfo> buffer, ams::sf::OutArray<ams::mitm::ldn::NodeLatestUpdate> pUpdates), (buffer, pUpdates))                          \
       AMS_SF_METHOD_INFO(C, H, 102, Result, Scan, (ams::sf::Out<s16> count, ams::sf::OutAutoSelectArray<ams::mitm::ldn::NetworkInfo> buffer, u16 channel, ams::mitm::ldn::ScanFilter filter), (count, buffer, channel, filter))        \
       AMS_SF_METHOD_INFO(C, H, 103, Result, ScanPrivate, (ams::sf::Out<s16> count, ams::sf::OutAutoSelectArray<ams::mitm::ldn::NetworkInfo> buffer, u16 channel, ams::mitm::ldn::ScanFilter filter), (count, buffer, channel, filter)) \
       AMS_SF_METHOD_INFO(C, H, 104, Result, SetWirelessControllerRestriction, (ams::mitm::ldn::WirelessControllerRestriction in), (in))                                                                                                \
       AMS_SF_METHOD_INFO(C, H, 200, Result, OpenAccessPoint, (), ())                                                                                                                                                                   \
       AMS_SF_METHOD_INFO(C, H, 201, Result, CloseAccessPoint, (), ())                                                                                                                                                                  \
       AMS_SF_METHOD_INFO(C, H, 202, Result, CreateNetwork, (ams::mitm::ldn::CreateNetworkConfig data), (data))                                                                                                                         \
       AMS_SF_METHOD_INFO(C, H, 203, Result, CreateNetworkPrivate, (ams::mitm::ldn::CreateNetworkPrivateConfig data, ams::sf::InPointerArray<ams::mitm::ldn::AddressEntry> entries), (data, entries))                                   \
       AMS_SF_METHOD_INFO(C, H, 204, Result, DestroyNetwork, (), ())                                                                                                                                                                    \
       AMS_SF_METHOD_INFO(C, H, 205, Result, Reject, (LdnIpv4Address addr), (addr))                                                                                                                                                     \
       AMS_SF_METHOD_INFO(C, H, 206, Result, SetAdvertiseData, (ams::sf::InAutoSelectBuffer data), (data))                                                                                                                              \
       AMS_SF_METHOD_INFO(C, H, 207, Result, SetStationAcceptPolicy, (LdnAcceptPolicy policy), (policy))                                                                                                                                \
       AMS_SF_METHOD_INFO(C, H, 208, Result, AddAcceptFilterEntry, (LdnMacAddress mac), (mac))                                                                                                                                          \
       AMS_SF_METHOD_INFO(C, H, 209, Result, ClearAcceptFilter, (), ())                                                                                                                                                                 \
       AMS_SF_METHOD_INFO(C, H, 300, Result, OpenStation, (), ())                                                                                                                                                                       \
       AMS_SF_METHOD_INFO(C, H, 301, Result, CloseStation, (), ())                                                                                                                                                                      \
       AMS_SF_METHOD_INFO(C, H, 302, Result, Connect, (ams::mitm::ldn::ConnectNetworkData dat, const ams::mitm::ldn::NetworkInfo &data), (dat, data))                                                                                   \
       AMS_SF_METHOD_INFO(C, H, 303, Result, ConnectPrivate, (ams::mitm::ldn::ConnectNetworkPrivateData dat), (dat))                                                                                                                    \
       AMS_SF_METHOD_INFO(C, H, 304, Result, Disconnect, (), ())                                                                                                                                                                        \
       AMS_SF_METHOD_INFO(C, H, 400, Result, Initialize, (const ams::sf::ClientProcessId &client_process_id), (client_process_id))                                                                                                      \
       AMS_SF_METHOD_INFO(C, H, 401, Result, Finalize, (), ())                                                                                                                                                                          \
       AMS_SF_METHOD_INFO(C, H, 402, Result, Initialize2, (u32 unk, const ams::sf::ClientProcessId &client_process_id), (unk, client_process_id))

AMS_SF_DEFINE_INTERFACE(ams::mitm::ldn, IUserLocalCommunicationInterface, AMS_LDN_IUSERLOCALCOMMUNICATION, 0x85280DC3)
