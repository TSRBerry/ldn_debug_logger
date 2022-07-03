#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "debug.hpp"
#include "interfaces/ilclservice.hpp"
#include "wlan_lcl_shim.hpp"

namespace ams::mitm::wlan
{

    class WlanLclMitMService : public sf::MitmServiceImplBase
    {
    private:
        using RedirectOnlyLocationResolverFactory = sf::ObjectFactory<sf::StdAllocationPolicy<std::allocator>>;

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        WlanLclMitMService(std::shared_ptr<::Service> &&s, const sm::MitmProcessInfo &c);

        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            LogFormat("should_mitm pid: %" PRIu64 " tid: %" PRIx64, client_info.process_id, client_info.program_id);
            return true;
        }

    public:
        /* Overridden commands. */
    };
    static_assert(ams::mitm::wlan::IsIWlanLclMitMService<WlanLclMitMService>);

}
