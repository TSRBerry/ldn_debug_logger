#pragma once
#include <switch.h>
#include "ldn_types.hpp"

typedef struct
{
    Service s;
} LdnUserLocalCommunicationInterface;

/* Command forwarders. */
Result ldnGetUserLocalCommunicationInterfaceFwd(Service *s, LdnUserLocalCommunicationInterface *out);

Result ldnUserCommunicationGetState(LdnUserLocalCommunicationInterface *doc, u32 *state);
Result ldnUserCommunicationGetNetworkInfo(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out);
Result ldnUserCommunicationGetIpv4Address(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::Ipv4Address *addr, ams::mitm::ldn::SubnetMask *netmask);
Result ldnUserCommunicationGetDisconnectReason(LdnUserLocalCommunicationInterface *doc, s16 *reason);
Result ldnUserCommunicationGetSecurityParameter(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::SecurityParameter *out);
Result ldnUserCommunicationGetNetworkConfig(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkConfig *out);
Result ldnUserCommunicationAttachStateChangeEvent(LdnUserLocalCommunicationInterface *doc, Handle *handle);
Result ldnUserCommunicationGetNetworkInfoLatestUpdate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out, ams::mitm::ldn::NodeLatestUpdate *out_buffer, size_t out_buffer_size);
Result ldnUserCommunicationScan(LdnUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter);
Result ldnUserCommunicationScanPrivate(LdnUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter);
Result ldnUserCommunicationSetWirelessControllerRestriction(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::WirelessControllerRestriction in);
Result ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(LdnUserLocalCommunicationInterface *doc, u32 in);
Result ldnUserCommunicationOpenAccessPoint(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCloseAccessPoint(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCreateNetwork(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkConfig data);
Result ldnUserCommunicationCreateNetworkPrivate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkPrivateConfig data, const ams::mitm::ldn::AddressEntry *entries, size_t entires_size);
Result ldnUserCommunicationDestroyNetwork(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationReject(LdnUserLocalCommunicationInterface *doc, LdnIpv4Address *addr);
Result ldnUserCommunicationSetAdvertiseData(LdnUserLocalCommunicationInterface *doc, const void *advertiseData, size_t advertiseData_size);
Result ldnUserCommunicationSetStationAcceptPolicy(LdnUserLocalCommunicationInterface *doc, LdnAcceptPolicy *policy);
Result ldnUserCommunicationAddAcceptFilterEntry(LdnUserLocalCommunicationInterface *doc, LdnMacAddress *mac);
Result ldnUserCommunicationClearAcceptFilter(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationOpenStation(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCloseStation(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationConnect(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkData *dat, const LdnNetworkInfo *data);
Result ldnUserCommunicationConnectPrivate(LdnUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkPrivateData *dat);
Result ldnUserCommunicationDisconnect(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationInitialize(LdnUserLocalCommunicationInterface *doc, u64 pid);
Result ldnUserCommunicationFinalize(LdnUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationInitialize2(LdnUserLocalCommunicationInterface *doc, u32 unk, u64 pid);

void ldnUserLocalCommunicationInterfaceClose(LdnUserLocalCommunicationInterface *doc);
