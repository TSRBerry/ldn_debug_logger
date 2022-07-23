#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "logging.hpp"
#include "dlog_config.hpp"
#include "interfaces/ilgservice.hpp"
#include "wlan_lg_shim.hpp"

namespace ams::mitm::wlan
{

    class WlanLgMitmService : public sf::MitmServiceImplBase
    {
    private:
        DLogConfig *m_config = ams::mitm::GetConfigInstance();

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            DEBUG_LOG("[wlan:lg] should_mitm pid: %" PRIu64 " tid: 0%" PRIx64, client_info.process_id, client_info.program_id);
            if (!ams::mitm::GetConfigInstance()->wlan_lg.enable_mitm)
            {
                return false;
            }
            return true;
        }

    public:
        /* Overridden commands. */
        Result GetFrameRaw(u32 rxId, ams::sf::Out<u32> frameSize, ams::sf::OutMapAliasBuffer data);
    };

    static_assert(ams::mitm::wlan::IsIWlanLgMitmInterface<WlanLgMitmService>);
}
