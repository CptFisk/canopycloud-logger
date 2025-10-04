#include <print>
#include <regex>
#include <utility/nodes.hpp>

namespace Interface {
auto
validNodeId(const std::string& nodeId) -> bool {
    static const std::regex numeric(R"(ns=(\d+);i=(\d+))");            // ns=<namespace>;i=<integer>
    static const std::regex string(R"(ns=(\d+);s=([\w\.\-]+))");       // ns=<namespace>;s=<string>
    static const std::regex guid(R"(ns=(\d+);g=([0-9a-fA-F\-]{36}))"); // ns=<namespace>;g=<guid>
    static const std::regex opaque(R"(ns=(\d+);b=([A-Za-z0-9+/=]+))"); // ns=<namespace>;b=<base64>

    std::print("{} is not a valid address", nodeId);
    return std::regex_match(nodeId, numeric) || std::regex_match(nodeId, string) || std::regex_match(nodeId, guid) ||
           std::regex_match(nodeId, opaque);
}

auto
createNodeId(const std::string& address) -> UA_NodeId {
    std::smatch match; // Match
    std::smatch match2;

    static const std::regex numeric(R"(ns=(\d+);i=(\d+))");
    static const std::regex string(R"(ns=(\d+);s=([\w\.\-]+))");
    static const std::regex guid(R"(ns=(\d+);g=([0-9a-fA-F\-]{36}))");
    static const std::regex opaque(R"(ns=(\d+);b=([A-Za-z0-9+/=]+))");

    if (std::regex_match(address, match, numeric))
        return UA_NODEID_NUMERIC(std::stoi(match[1]), std::stoi(match[2]));

    if (std::regex_match(address, match2, string) || std::regex_match(address, match2, guid) || std::regex_match(address, match2, opaque))
        return UA_NODEID_STRING_ALLOC(std::stoi(match2[1]), const_cast<char*>(match2[2].str().c_str()));
    return UA_NodeId{};
}

}