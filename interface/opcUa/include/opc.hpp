#pragma once
#include <config.hpp>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/securitypolicy_default.h>
#include <open62541/plugin/log_stdout.h>
#include <string>
#include <base.hpp>
#include <vector>

namespace Interface {

class OpcUa : public Base {
public:
    OpcUa(const OpcConfig& config);

    auto connect() -> bool override;

    auto read() -> bool override;

private:
protected:
    UA_Client*       client;       ///< Client
    UA_ClientConfig* clientConfig; ///< Configuration
    UA_StatusCode    status;       ///< Status code

    const std::string           endpoint;
    std::vector<UA_ReadValueId> nodes; ///< Nodes to read

    auto security(const Security& security) -> void;
};
}