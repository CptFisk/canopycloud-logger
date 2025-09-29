#pragma once
#include <open62541/types.h>
#include <string>

namespace Interface {

inline auto uaToStdString(const UA_String& uaStr) -> std::string {
    if (!uaStr.data || uaStr.length == 0)
        return std::string();
    return std::string(reinterpret_cast<const char*>(uaStr.data), uaStr.length);
}

}