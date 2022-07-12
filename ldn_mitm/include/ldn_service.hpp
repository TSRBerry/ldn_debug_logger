#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>
#include <switch.h>

#include "debug.hpp"
#include "interfaces/iservice.hpp"
#include "ldn_icommunication.hpp"
#include "ldn_shim.hpp"

namespace ams::mitm::ldn
{

    class LdnMitMService : public sf::MitmServiceImplBase
    {
    private:
        using RedirectOnlyLocationResolverFactory = sf::ObjectFactory<sf::StdAllocationPolicy<std::allocator>>;

    public:
        using MitmServiceImplBase::MitmServiceImplBase;

    public:
        LdnMitMService(std::shared_ptr<::Service> &&s, const sm::MitmProcessInfo &c);

        static bool ShouldMitm(const sm::MitmProcessInfo &client_info)
        {
            LogFormat("should_mitm pid: %" PRIu64 " tid: %" PRIx64, client_info.process_id, client_info.program_id);
            return true;
        }

    public:
        /* Overridden commands. */
        Result CreateUserLocalCommunicationService(sf::Out<sf::SharedPointer<IUserLocalCommunicationInterface>> out);
    };
    static_assert(ams::mitm::ldn::IsILdnMitMService<LdnMitMService>);

}
