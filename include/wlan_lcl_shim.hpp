#pragma once
#include <switch.h>
#include <wlan_lcl_types.hpp>

typedef struct
{
    Service s;
} WlanILocalManagerInterface;

/* Command forwarders. */
Result wlanLocalManagerOpenMasterMode(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerCloseMasterMode(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerOpenClientMode(WlanILocalManagerInterface *doc, ams::mitm::wlan::OpenClientModeData *out);
Result wlanLocalManagerCloseClientMode(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerOpenSpectatorMode(WlanILocalManagerInterface *doc);
Result wlanLocalManagerCloseSpectatorMode(WlanILocalManagerInterface *doc, const ams::mitm::wlan::SpectatorModeData *data);
Result wlanLocalManagerGetMacAddress(WlanILocalManagerInterface *doc);
Result wlanLocalManagerCreateBss(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerDestroyBss(WlanILocalManagerInterface *doc);
Result wlanLocalManagerStartScan(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerStopScan(WlanILocalManagerInterface *doc);
Result wlanLocalManagerConnect(WlanILocalManagerInterface *doc, ams::mitm::wlan::ConnectData in);
Result wlanLocalManagerCancelConnect(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerJoin(WlanILocalManagerInterface *doc, u32 in, Handle *handle);
Result wlanLocalManagerCancelJoin(WlanILocalManagerInterface *doc, ams::mitm::wlan::CancelJoinData *out);
Result wlanLocalManagerDisconnect(WlanILocalManagerInterface *doc, void *data, size_t data_size);
Result wlanLocalManagerSetBeaconLostCount(WlanILocalManagerInterface *doc, Handle *handle);
Result wlanLocalManagerGetSystemEvent(WlanILocalManagerInterface *doc, void *data, size_t data_size);
Result wlanLocalManagerGetConnectionStatus(WlanILocalManagerInterface *doc, u32 *out);
Result wlanLocalManagerGetClientStatus(WlanILocalManagerInterface *doc, u32 *out, ams::mitm::wlan::ClientStatusData *out_data);
Result wlanLocalManagerGetBssIndicationEvent(WlanILocalManagerInterface *doc, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetBssIndicationInfo(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerGetState(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerGetAllowedChannels(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerAddIe(WlanILocalManagerInterface *doc, u32 in, u32 *out, const ams::mitm::wlan::IeData *in_array, size_t in_array_size);
Result wlanLocalManagerDeleteIe(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerPutFrameRaw(WlanILocalManagerInterface *doc, u64 in);
Result wlanLocalManagerCancelGetFrame(WlanILocalManagerInterface *doc, u16 in, u32 *out);
Result wlanLocalManagerCreateRxEntry(WlanILocalManagerInterface *doc, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerDeleteRxEntry(WlanILocalManagerInterface *doc, u32 in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerAddEthertypeToRxEntry(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerDeleteEthertypeFromRxEntry(WlanILocalManagerInterface *doc, ams::mitm::wlan::DeleteEthertypeFromRxEntryData in, const void *in_array, size_t in_array_size);
Result wlanLocalManagerAddMatchingDataToRxEntry(WlanILocalManagerInterface *doc, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerRemoveMatchingDataFromRxEntry(WlanILocalManagerInterface *doc);
Result wlanLocalManagerGetScanResult(WlanILocalManagerInterface *doc, u32 in, u32 *out, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerPutActionFrameOneShot(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerSetActionFrameWithBeacon(WlanILocalManagerInterface *doc, u64 in);
Result wlanLocalManagerCancelActionFrameWithBeacon(WlanILocalManagerInterface *doc, u32 in, u32 *out);
Result wlanLocalManagerCreateRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerDeleteRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 *out);
Result wlanLocalManagerAddSubtypeToRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerDeleteSubtypeFromRxEntryForActionFrame(WlanILocalManagerInterface *doc, u32 *out, void *out_buffer, size_t out_buffer_size);
Result wlanLocalManagerCancelGetActionFrame(WlanILocalManagerInterface *doc, u8 in);
Result wlanLocalManagerGetRssi(WlanILocalManagerInterface *doc, ams::mitm::wlan::GetRssiData in);
Result wlanLocalManagerSetMaxAssociationNumber(WlanILocalManagerInterface *doc, ams::mitm::wlan::UnknownNetworkData in);
Result wlanLocalManagerCmd45(WlanILocalManagerInterface *doc, ams::mitm::wlan::Cmd45Data in, const void *in_buffer, size_t in_buffer_size);
Result wlanLocalManagerCmd46(WlanILocalManagerInterface *doc, u8 in);
Result wlanLocalManagerCmd47(WlanILocalManagerInterface *doc, ams::mitm::wlan::Cmd47Data in, u32 *out);
Result wlanLocalManagerCmd48(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerCmd49(WlanILocalManagerInterface *doc, u32 in);
Result wlanLocalManagerCmd50(WlanILocalManagerInterface *doc);
Result wlanLocalManagerCmd51(WlanILocalManagerInterface *doc, u32 *out);
