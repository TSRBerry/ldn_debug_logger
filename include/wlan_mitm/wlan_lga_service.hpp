#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "logging.hpp"
#include "dlog_config.hpp"
#include "interfaces/ilgaservice.hpp"
#include "wlan_lga_shim.hpp"

namespace ams::mitm::wlan
{

    class WlanLgaMitmService : public sf::MitmServiceImplBase
    {
    private:
        DLogConfig *m_config = ams::mitm::GetConfigInstance();

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            DEBUG_LOG("[wlan:lga] should_mitm pid: %" PRIu64 " tid: 0%" PRIx64, client_info.process_id, client_info.program_id);
            if (!ams::mitm::GetConfigInstance()->wlan_lga.enable_mitm)
            {
                return false;
            }
            return true;
        }

    public:
        /* Overridden commands. */
        Result GetActionFrame(u32 rxId, u32 in, ams::sf::Out<LdnMacAddress> macAddress, ams::sf::Out<u32> actionFrame, ams::sf::Out<u32> out, ams::sf::OutMapAliasBuffer data);
    };

    static_assert(ams::mitm::wlan::IsIWlanLgaMitmInterface<WlanLgaMitmService>);
}
