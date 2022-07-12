/*
 * Copyright (c) 2022 TSRBerry
 *  -> added ldn forward service
 *  -> changed log messages
 * Copyright (c) 2018 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <switch.h>

#include "debug.hpp"
#include "ldn_service.hpp"
#include "ldn_icommunication.hpp"

namespace ams::mitm::ldn
{
    using ObjectFactory = ams::sf::ObjectFactory<ams::sf::StdAllocationPolicy<std::allocator>>;

    LdnMitMService::LdnMitMService(std::shared_ptr<::Service> &&s, const sm::MitmProcessInfo &c) : sf::MitmServiceImplBase(std::forward<std::shared_ptr<::Service>>(s), c)
    {
        LogFormat("ldn:u Created");
    }

    Result LdnMitMService::CreateUserLocalCommunicationService(sf::Out<sf::SharedPointer<IUserLocalCommunicationInterface>> out)
    {
        LogFormat("CreateUserLocalCommunicationService: enabled out_service ptr: %p", &out);
        LdnIUserLocalCommunicationInterface doc;
        R_TRY(ldnGetIUserLocalCommunicationInterfaceFwd(m_forward_service.get(), std::addressof(doc)));
        const sf::cmif::DomainObjectId target_object_id{serviceGetObjectId(std::addressof(doc.s))};

        out.SetValue(sf::CreateSharedObjectEmplaced<IUserLocalCommunicationInterface, IUserLocalCommunicationService>(std::make_unique<LdnIUserLocalCommunicationInterface>(doc)), target_object_id);
        R_SUCCEED();
    }
}
