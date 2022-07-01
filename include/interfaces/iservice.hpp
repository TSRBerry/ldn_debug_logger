#pragma once
#include <cstring>
#include <atomic>

#include <stratosphere.hpp>

#include "../debug.hpp"
#include "../ldn_icommunication.hpp"

#define AMS_ILDN_MITM_SERVICE(C, H)                                                                                                                                      \
    AMS_SF_METHOD_INFO(C, H, 0, Result, CreateUserLocalCommunicationService, (ams::sf::Out<ams::sf::SharedPointer<ams::mitm::ldn::IUserLocalCommunicationInterface>> out), (out)) \

AMS_SF_DEFINE_MITM_INTERFACE(ams::mitm::ldn, ILdnMitMService, AMS_ILDN_MITM_SERVICE, 0x1D8F875E)
