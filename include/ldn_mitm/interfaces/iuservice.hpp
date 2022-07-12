#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>

#include "../ldn_userlocalcommunication.hpp"

#define AMS_LDN_U_INTERFACE_INFO(C, H) \
    AMS_SF_METHOD_INFO(C, H, 0, Result, CreateUserLocalCommunicationService, (ams::sf::Out<ams::sf::SharedPointer<ams::mitm::ldn::IUserLocalCommunicationInterface>> out), (out))

AMS_SF_DEFINE_MITM_INTERFACE(ams::mitm::ldn, ILdnUMitmInterface, AMS_LDN_U_INTERFACE_INFO, 0x1D8F875E)
