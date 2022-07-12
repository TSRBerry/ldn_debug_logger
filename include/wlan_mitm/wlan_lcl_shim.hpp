#pragma once
#include <switch.h>
#include "wlan_lcl_types.hpp"

/* Command forwarders. */
Result wlanLocalManagerOpenMasterMode(Service *s, u32 in);
Result wlanLocalManagerCloseMasterMode(Service *s, u32 in);
Result wlanLocalManagerOpenClientMode(Service *s, ams::mitm::wlan::OpenClientModeData *out);
Result wlanLocalManagerCloseClientMode(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerOpenSpectatorMode(Service *s);
Result wlanLocalManagerCloseSpectatorMode(Service *s, const u8 *data, size_t data_size);
Result wlanLocalManagerGetMacAddress(Service *s);
Result wlanLocalManagerCreateBss(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerDestroyBss(Service *s);
Result wlanLocalManagerStartScan(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerStopScan(Service *s);
Result wlanLocalManagerConnect(Service *s, ams::mitm::wlan::ConnectData in);
Result wlanLocalManagerCancelConnect(Service *s, u32 in);
Result wlanLocalManagerJoin(Service *s, u32 in, Handle *handle);
Result wlanLocalManagerCancelJoin(Service *s, ams::mitm::wlan::CancelJoinData *out);
Result wlanLocalManagerDisconnect(Service *s, void *data, size_t data_size);
Result wlanLocalManagerSetBeaconLostCount(Service *s, Handle *handle);
Result wlanLocalManagerGetSystemEvent(Service *s, void *data, size_t data_size);
Result wlanLocalManagerGetConnectionStatus(Service *s, u32 *out);
Result wlanLocalManagerGetClientStatus(Service *s, u32 *out, void *out_data, size_t out_data_size);
Result wlanLocalManagerGetBssIndicationEvent(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetBssIndicationInfo(Service *s, u32 in);
Result wlanLocalManagerGetState(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetAllowedChannels(Service *s, u32 in);
Result wlanLocalManagerAddIe(Service *s, u32 in, u32 *out, const void *in_array, size_t in_array_size);
Result wlanLocalManagerDeleteIe(Service *s, u32 in);
Result wlanLocalManagerPutFrameRaw(Service *s, u64 in);
Result wlanLocalManagerCancelGetFrame(Service *s, u16 in, u32 *out);
Result wlanLocalManagerCreateRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteRxEntry(Service *s, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerAddEthertypeToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerDeleteEthertypeFromRxEntry(Service *s, ams::mitm::wlan::DeleteEthertypeFromRxEntryData in, const void *in_array, size_t in_array_size);
Result wlanLocalManagerAddMatchingDataToRxEntry(Service *s, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerRemoveMatchingDataFromRxEntry(Service *s);
Result wlanLocalManagerGetScanResult(Service *s, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerPutActionFrameOneShot(Service *s, u32 in);
Result wlanLocalManagerSetActionFrameWithBeacon(Service *s, u64 in);
Result wlanLocalManagerCancelActionFrameWithBeacon(Service *s, u32 in, u32 *out);
Result wlanLocalManagerCreateRxEntryForActionFrame(Service *s, u32 in);
Result wlanLocalManagerDeleteRxEntryForActionFrame(Service *s, u32 *out);
Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(Service *s, u32 in);
Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(Service *s, u32 *out, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerCancelGetActionFrame(Service *s, u8 in);
Result wlanLocalManagerGetRssi(Service *s, ams::mitm::wlan::GetRssiData in);
Result wlanLocalManagerSetMaxAssociationNumber(Service *s, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerCmd45(Service *s, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCmd46(Service *s, u8 in);
Result wlanLocalManagerCmd47(Service *s, ams::mitm::wlan::Cmd47Data in, u32 *out);
Result wlanLocalManagerCmd48(Service *s, u32 in);
Result wlanLocalManagerCmd49(Service *s, u32 in);
Result wlanLocalManagerCmd50(Service *s);
Result wlanLocalManagerCmd51(Service *s, u32 *out);
