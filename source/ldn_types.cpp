#include <cstring>

#include "ldn_types.hpp"

namespace ams::mitm::ldn
{
    bool MacAddress::operator==(const MacAddress &b) const
    {
        return std::memcmp(this->raw, b.raw, sizeof(MacAddress)) == 0;
    }

    bool Ssid::operator==(const Ssid &b) const
    {
        return (this->length == b.length) && (std::memcmp(this->raw, b.raw, this->length) == 0);
    }

    Ssid &Ssid::operator=(const char *s)
    {
        std::strcpy(this->raw, s);
        this->length = std::strlen(s);
        return *this;
    }

    bool SessionId::operator==(const SessionId &b) const
    {
        return (this->low == b.low) && (this->high == b.high);
    }
}
