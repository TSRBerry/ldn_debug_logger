#include <stratosphere.hpp>

#include "dlog_init.hpp"
#include "wlan_mitm/wlan_module.hpp"
#include "ldn_mitm/ldn_module.hpp"

namespace ams::mitm
{
    void LaunchModules()
    {
        R_ABORT_UNLESS(ams::mitm::wlan::Launch());
        R_ABORT_UNLESS(ams::mitm::ldn::Launch());
    }

    void WaitModules()
    {
        ams::mitm::wlan::WaitFinished();
        ams::mitm::ldn::WaitFinished();
    }
}
