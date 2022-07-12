#pragma once
#include <stratosphere.hpp>
#include <cstdarg>

namespace ams::log
{

    Result Initialize();
    void Finalize();

    void DebugLog(const char *fmt, ...);
    void DebugDataDump(const void *data, size_t size, const char *fmt, ...);

#define DEBUG_LOG(fmt, ...) DebugLog(fmt "\n", ##__VA_ARGS__)
#define DEBUG_DATA_DUMP(data, size, fmt, ...) DebugDataDump(data, size, fmt "[%#x]:\n", ##__VA_ARGS__, size)

}
