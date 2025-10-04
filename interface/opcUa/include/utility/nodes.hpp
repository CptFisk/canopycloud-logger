#pragma once
#include <open62541/types.h>
#include <string>

namespace Interface {

/**
 * @param nodeId Name of the address
 * @return True if valid
 */
auto
validNodeId(const std::string& nodeId) -> bool;


/**
 * @brief Parse an OPC UA NodeID from a string address, this should only be called when a
 * name is known to be valid. If the node was not a numeric the memory needs to be freed manually
 * @param address Input in correct format
 * @return If format is valid return a UA_NodeId
 */
auto
createNodeId(const std::string& address) -> UA_NodeId;

}