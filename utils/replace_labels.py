#!/usr/bin/env python3
import os
import subprocess

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
SEARCH_LIST = [
    "./config_template.ini",
    "./source/*",
    "./include/*",
    "./source/wlan_mitm/*",
    "./include/wlan_mitm/*",
    "./include/wlan_mitm/interfaces/*"
]

# 0-1: hpp, 2: cpp
EXCLUDE_DLOG_CONFIG_LINES = [13, 42, 20]
EXCLUDE_CONFIG_LINES = (5, 34)
SHIM_PREFIX = "wlanLocalManager"

replace_label_map = {
    "OpenMasterMode": "OpenMode",
    "CloseMasterMode": "CloseMode",
    "OpenClientMode": "GetMacAddress",
    "CloseClientMode": "CreateBss",
    "OpenSpectatorMode": "DestroyBss",
    "CloseSpectatorMode": "StartScan",
    "GetMacAddress": "StopScan",
    "CreateBss": "Connect",
    "DestroyBss": "CancelConnect",
    "StartScan": "Join",
    "StopScan": "CancelJoin",
    "Connect": "Disconnect",
    "CancelConnect": "SetBeaconLostCount",
    "Join": "GetSystemEvent",
    "CancelJoin": "GetConnectionStatus",
    "Disconnect": "GetClientStatus",
    "SetBeaconLostCount": "GetBssIndicationEvent",
    "GetSystemEvent": "GetBssIndicationInfo",
    "GetConnectionStatus": "GetState",
    "GetClientStatus": "GetAllowedChannels",
    "GetBssIndicationEvent": "AddIe",
    "GetBssIndicationInfo": "DeleteIe",
    "GetState": "PutFrameRaw",
    "GetAllowedChannels": "CancelGetFrame",
    "AddIe": "CreateRxEntry",
    "DeleteIe": "DeleteRxEntry",
    "PutFrameRaw": "AddEthertypeToRxEntry",
    "CancelGetFrame": "DeleteEthertypeFromRxEntry",
    "CreateRxEntry": "AddMatchingDataToRxEntry",
    "DeleteRxEntry": "RemoveMatchingDataFromRxEntry",
    "AddEthertypeToRxEntry": "GetScanResult",
    "DeleteEthertypeFromRxEntry": "PutActionFrameOneShot",
    "AddMatchingDataToRxEntry": "SetActionFrameWithBeacon",
    "RemoveMatchingDataFromRxEntry": "CancelActionFrameWithBeacon",
    "GetScanResult": "CreateRxEntryForActionFrame",
    "PutActionFrameOneShot": "DeleteRxEntryForActionFrame",
    "SetActionFrameWithBeacon": "AddSubtypeToRxEntryForActionFrame",
    "CancelActionFrameWithBeacon": "DeleteSubtypeFromRxEntryForActionFrame",
    "CreateRxEntryForActionFrame": "CancelGetActionFrame",
    "DeleteRxEntryForActionFrame": "GetRssi",
    "AddSubtypeToRxEntryForActionFrame": "SetMaxAssociationNumber",
    "DeleteSubtypeFromRxEntryForActionFrame": "Cmd41",
    "CancelGetActionFrame": "Cmd42",
    "GetRssi": "Cmd43",
    "SetMaxAssociationNumber": "Cmd44"
}

match_dict = {}

for old_label in replace_label_map.keys():
    command = ["bash", "-c", "grep --color=never -wnosi " +
        f"-e {old_label} -e disable_{old_label} -e {SHIM_PREFIX}{old_label} -e {old_label}Data {' '.join(SEARCH_LIST)}"]
    label_grep = subprocess.run(command, cwd=ROOT_DIR, stdout=subprocess.PIPE)
    match_dict[old_label] = []
    for line in label_grep.stdout.decode().splitlines():
        result = line.rsplit(":", maxsplit=1)[0]
        if result not in match_dict[old_label]:
            match_dict[old_label].append(result)

for old_label, match_list in match_dict.items():
    new_label = replace_label_map[old_label]
    print(f"Replacing {old_label} with {new_label}...")
    # easy, but dumb way of doing this
    for g_match in match_list:
        # 0: file, 1: line number
        g_match = g_match.split(":")
        if g_match[0] == SEARCH_LIST[0]:
            if int(g_match[1]) >= EXCLUDE_CONFIG_LINES[0] and int(g_match[1]) <= EXCLUDE_CONFIG_LINES[1]:
                continue
        elif g_match[0] == SEARCH_LIST[1][:-1] + "dlog_config.cpp":
            if int(g_match[1]) == EXCLUDE_DLOG_CONFIG_LINES[2]:
                continue
        elif g_match[0] == SEARCH_LIST[2][:-1] + "dlog_config.hpp":
            if int(g_match[1]) >= EXCLUDE_DLOG_CONFIG_LINES[0] and int(g_match[1]) <= EXCLUDE_DLOG_CONFIG_LINES[1]:
                continue
        print("Opening:", g_match[0])
        with open(g_match[0], "r") as file:
            text = file.readlines()
        index = int(g_match[1]) - 1
        line = text[index]
        if f"disable_{old_label.lower()}" in line:
            line = line.replace(f"disable_{old_label.lower()}", f"disable_{new_label.lower()}")
        elif old_label in line:
            line = line.replace(old_label, new_label)
        else:
            print(f"Couldn't find '{old_label}' in line: {index + 1}")
            exit(1)
        print("Writing new line:", line)
        text[index] = line
        with open(g_match[0], "w") as file:
            file.writelines(text)
    print("Label successfully replaced.")
