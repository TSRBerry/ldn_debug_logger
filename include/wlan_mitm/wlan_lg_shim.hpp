#pragma once
#include <switch.h>

/* Command forwarders. */
Result wlanLocalGetFrameGetFrameRaw(Service *s, u32 rxId, u32 *frameSize, void *data, size_t data_size);
