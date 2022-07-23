#pragma once
#include <switch.h>
#include "wlan_lcl_types.hpp"

/* Command forwarders. */
Result wlanLocalManagerOpenMode(Service *s, ams::mitm::wlan::Mode mode);
Result wlanLocalManagerCloseMode(Service *s, ams::mitm::wlan::Mode mode);
Result wlanLocalManagerGetMacAddress(Service *s, LdnMacAddress *out);
Result wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::Bss in);
Result wlanLocalManagerDestroyBss(Service *s);
Result wlanLocalManagerStartScan(Service *s, const ams::mitm::wlan::ScanRequest *request);
Result wlanLocalManagerStopScan(Service *s);
Result wlanLocalManagerConnect(Service *s, ams::mitm::wlan::ConnectParam in);
Result wlanLocalManagerCancelConnect(Service *s);
Result wlanLocalManagerJoin(Service *s, ams::mitm::wlan::ConnectParam in);
Result wlanLocalManagerCancelJoin(Service *s);
Result wlanLocalManagerDisconnect(Service *s, ams::mitm::wlan::DisconnectData in);
Result wlanLocalManagerSetBeaconLostCount(Service *s, u32 beaconLostCount);
Result wlanLocalManagerGetSystemEvent(Service *s, u32 systemEventType, Handle *eventHandle);
Result wlanLocalManagerGetConnectionStatus(Service *s, ams::mitm::wlan::ConnectionStatus *status);
Result wlanLocalManagerGetClientStatus(Service *s, ams::mitm::wlan::ClientStatus *status, size_t status_size);
Result wlanLocalManagerGetBssIndicationEvent(Service *s, Handle *eventHandle);
Result wlanLocalManagerGetBssIndicationInfo(Service *s, void *data, size_t data_size);
Result wlanLocalManagerGetState(Service *s, ams::mitm::wlan::State *state);
Result wlanLocalManagerGetAllowedChannels(Service *s, u32 *allowedChannelsCount, void *out_data, size_t out_data_size);
Result wlanLocalManagerAddIe(Service *s, u32 managementFrameType, u32 *ie, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteIe(Service *s, u32 ie);
Result wlanLocalManagerPutFrameRaw(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCancelGetFrame(Service *s, u32 rxId);
Result wlanLocalManagerCreateRxEntry(Service *s, u32 capacity, u32 *rxId, const void *in_array, size_t in_array_size);
Result wlanLocalManagerDeleteRxEntry(Service *s, u32 rxId);
Result wlanLocalManagerAddEthertypeToRxEntry(Service *s, u32 rxId, u32 protocol);
Result wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, u16 protocol, u32 *out);
Result wlanLocalManagerAddMatchingDataToRxEntry(Service *s, u32 rxId, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s, u32 rxId, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetScanResult(Service *s, const void *in_buffer, size_t in_buffer_size, ams::mitm::wlan::ScanResult *result, size_t result_size);
Result wlanLocalManagerPutActionFrameOneShot(Service *s, ams::mitm::wlan::PutActionFrameOneShotData in, const void *in_array, size_t in_array_size);
Result wlanLocalManagerSetActionFrameWithBeacon(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCancelActionFrameWithBeacon(Service *s);
Result wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 capacity, u32 *rxId, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 rxId);
Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u32 rxId, u32 subType);
Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 subType, u32 *out);
Result wlanLocalManagerCancelGetActionFrame(Service *s, u32 rxId);
Result wlanLocalManagerGetRssi(Service *s, u32 *rssi);
Result wlanLocalManagerSetMaxAssociationNumber(Service *s, u32 maxAssociationNumber);
Result wlanLocalManagerCmd41(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerCmd42(Service *s, u8 in);
Result wlanLocalManagerCmd43(Service *s, ams::mitm::wlan::Cmd43Data in);
Result wlanLocalManagerCmd44(Service *s, ams::mitm::wlan::Bss in);
Result wlanLocalManagerCmd45(Service *s, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCmd46(Service *s, u8 in);
Result wlanLocalManagerCmd47(Service *s, ams::mitm::wlan::Cmd47Data in, u32 *out);
Result wlanLocalManagerCmd48(Service *s, u32 in);
Result wlanLocalManagerCmd49(Service *s, u32 in);
Result wlanLocalManagerCmd50(Service *s);
Result wlanLocalManagerCmd51(Service *s, u32 *out);
