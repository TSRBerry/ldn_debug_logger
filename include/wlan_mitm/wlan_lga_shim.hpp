#pragma once
#include <switch.h>

/* Command forwarders. */
Result wlanLocalGetActionFrameGetActionFrame(Service *s, u32 rxId, u32 in, LdnMacAddress *macAddress, u32 *actionFrame, u32 *out, void *data, size_t data_size);
