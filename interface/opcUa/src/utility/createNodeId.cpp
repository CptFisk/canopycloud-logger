#include <iostream>
#include <regex>
#include <utility/createNodeId.hpp>

namespace Interface {

auto
createNodeId(const std::string& address) -> std::optional<UA_NodeId> {
    std::smatch match; // Match

    const std::regex numeric(R"(ns=(\d+);i=(\d+))");
    const std::regex string(R"(ns=(\d+);s=([\w\.\-]+))");
    const std::regex guid(R"(ns=(\d+);g=([0-9a-fA-F\-]{36}))");
    const std::regex opaque(R"(ns=(\d+);b=([A-Za-z0-9+/=]+))");

    if (std::regex_match(address, match, numeric))
        return UA_NODEID_NUMERIC(std::stoi(match[1]), std::stoi(match[2]));

    if (std::regex_match(address, match, string) || std::regex_match(address, match, guid) || std::regex_match(address, match, opaque))
        return UA_NODEID_STRING(std::stoi(match[1]), const_cast<char*>(match[2].str().c_str()));
    return std::nullopt;
}

}