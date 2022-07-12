#pragma once
#include <switch.h>
#include <ldn_types.hpp>

typedef struct
{
    Service s;
} LdnIUserLocalCommunicationInterface;

/* Command forwarders. */
Result ldnGetIUserLocalCommunicationInterfaceFwd(Service *s, LdnIUserLocalCommunicationInterface *out);

Result ldnUserCommunicationGetState(LdnIUserLocalCommunicationInterface *doc, u32 *state);
Result ldnUserCommunicationGetNetworkInfo(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out);
Result ldnUserCommunicationGetIpv4Address(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::Ipv4Address *addr, ams::mitm::ldn::SubnetMask *netmask);
Result ldnUserCommunicationGetDisconnectReason(LdnIUserLocalCommunicationInterface *doc, s16 *reason);
Result ldnUserCommunicationGetSecurityParameter(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::SecurityParameter *out);
Result ldnUserCommunicationGetNetworkConfig(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkConfig *out);
Result ldnUserCommunicationAttachStateChangeEvent(LdnIUserLocalCommunicationInterface *doc, Handle *handle);
Result ldnUserCommunicationGetNetworkInfoLatestUpdate(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::NetworkInfo *out, ams::mitm::ldn::NodeLatestUpdate *out_buffer, size_t out_buffer_size);
Result ldnUserCommunicationScan(LdnIUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter);
Result ldnUserCommunicationScanPrivate(LdnIUserLocalCommunicationInterface *doc, s16 *total_out, ams::mitm::ldn::NetworkInfo *out_buffer, size_t out_buffer_size, s16 channel, LdnScanFilter filter);
Result ldnUserCommunicationSetWirelessControllerRestriction(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::WirelessControllerRestriction in);
Result ldnUserCommunicationSetBluetoothAudioDeviceConnectableMode(LdnIUserLocalCommunicationInterface *doc, u32 in);
Result ldnUserCommunicationOpenAccessPoint(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCloseAccessPoint(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCreateNetwork(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkConfig data);
Result ldnUserCommunicationCreateNetworkPrivate(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::CreateNetworkPrivateConfig data, const ams::mitm::ldn::AddressEntry *entries, size_t entires_size);
Result ldnUserCommunicationDestroyNetwork(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationReject(LdnIUserLocalCommunicationInterface *doc, LdnIpv4Address *addr);
Result ldnUserCommunicationSetAdvertiseData(LdnIUserLocalCommunicationInterface *doc, const void *advertiseData, size_t advertiseData_size);
Result ldnUserCommunicationSetStationAcceptPolicy(LdnIUserLocalCommunicationInterface *doc, LdnAcceptPolicy *policy);
Result ldnUserCommunicationAddAcceptFilterEntry(LdnIUserLocalCommunicationInterface *doc, LdnMacAddress *mac);
Result ldnUserCommunicationClearAcceptFilter(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationOpenStation(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationCloseStation(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationConnect(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkData *dat, const LdnNetworkInfo *data);
Result ldnUserCommunicationConnectPrivate(LdnIUserLocalCommunicationInterface *doc, ams::mitm::ldn::ConnectNetworkPrivateData *dat);
Result ldnUserCommunicationDisconnect(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationInitialize(LdnIUserLocalCommunicationInterface *doc, u64 pid);
Result ldnUserCommunicationFinalize(LdnIUserLocalCommunicationInterface *doc);
Result ldnUserCommunicationInitialize2(LdnIUserLocalCommunicationInterface *doc, u32 unk, u64 pid);

void ldnIUserLocalCommunicationInterfaceClose(LdnIUserLocalCommunicationInterface *doc);
