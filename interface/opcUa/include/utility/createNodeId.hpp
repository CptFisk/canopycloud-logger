#pragma once
#include <open62541/types.h>
#include <optional>
#include <string>

namespace Interface {

/**
 * @brief Parse an OPC UA NodeID from a string address
 * @param address Input in correct format
 * @return If format is valid return a UA_NodeId
 */
auto createNodeId(const std::string& address) -> std::optional<UA_NodeId>;

}