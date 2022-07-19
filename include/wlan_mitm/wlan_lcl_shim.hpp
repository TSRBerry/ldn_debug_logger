#pragma once
#include <switch.h>
#include "wlan_lcl_types.hpp"

/* Command forwarders. */
Result wlanLocalManagerOpenMode(Service *s, u32 in);
Result wlanLocalManagerCloseMode(Service *s, u32 in);
Result wlanLocalManagerGetMacAddress(Service *s, ams::mitm::wlan::GetMacAddressData *out);
Result wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerDestroyBss(Service *s);
Result wlanLocalManagerStartScan(Service *s, const u8 *data, size_t data_size);
Result wlanLocalManagerStopScan(Service *s);
Result wlanLocalManagerConnect(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerCancelConnect(Service *s);
Result wlanLocalManagerJoin(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerCancelJoin(Service *s);
Result wlanLocalManagerDisconnect(Service *s, ams::mitm::wlan::DisconnectData in);
Result wlanLocalManagerSetBeaconLostCount(Service *s, u32 in);
Result wlanLocalManagerGetSystemEvent(Service *s, u32 in, Handle *handle);
Result wlanLocalManagerGetConnectionStatus(Service *s, ams::mitm::wlan::GetConnectionStatusData *out);
Result wlanLocalManagerGetClientStatus(Service *s, void *data, size_t data_size);
Result wlanLocalManagerGetBssIndicationEvent(Service *s, Handle *handle);
Result wlanLocalManagerGetBssIndicationInfo(Service *s, void *data, size_t data_size);
Result wlanLocalManagerGetState(Service *s, u32 *out);
Result wlanLocalManagerGetAllowedChannels(Service *s, u32 *out, void *out_data, size_t out_data_size);
Result wlanLocalManagerAddIe(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteIe(Service *s, u32 in);
Result wlanLocalManagerPutFrameRaw(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCancelGetFrame(Service *s, u32 in);
Result wlanLocalManagerCreateRxEntry(Service *s, u32 in, u32 *out, const void *in_array, size_t in_array_size);
Result wlanLocalManagerDeleteRxEntry(Service *s, u32 in);
Result wlanLocalManagerAddEthertypeToRxEntry(Service *s, u64 in);
Result wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, u16 in, u32 *out);
Result wlanLocalManagerAddMatchingDataToRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetScanResult(Service *s, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerPutActionFrameOneShot(Service *s, ams::mitm::wlan::PutActionFrameOneShotData in, const void *in_array, size_t in_array_size);
Result wlanLocalManagerSetActionFrameWithBeacon(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCancelActionFrameWithBeacon(Service *s);
Result wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 in);
Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u64 in);
Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 in, u32 *out);
Result wlanLocalManagerCancelGetActionFrame(Service *s, u32 in);
Result wlanLocalManagerGetRssi(Service *s, u32 *out);
Result wlanLocalManagerSetMaxAssociationNumber(Service *s, u32 in);
Result wlanLocalManagerCmd41(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerCmd42(Service *s, u8 in);
Result wlanLocalManagerCmd43(Service *s, ams::mitm::wlan::Cmd43Data in);
Result wlanLocalManagerCmd44(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerCmd45(Service *s, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCmd46(Service *s, u8 in);
Result wlanLocalManagerCmd47(Service *s, ams::mitm::wlan::Cmd47Data in, u32 *out);
Result wlanLocalManagerCmd48(Service *s, u32 in);
Result wlanLocalManagerCmd49(Service *s, u32 in);
Result wlanLocalManagerCmd50(Service *s);
Result wlanLocalManagerCmd51(Service *s, u32 *out);
