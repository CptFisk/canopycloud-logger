#pragma once
#include <base.hpp>
#include <config.hpp>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/plugin/securitypolicy_default.h>
#include <string>
#include <utility/byteStringClone.hpp>
#include <utility/byteStringLoad.hpp>
#include <vector>

namespace Interface {

class OpcUa : public Base {
  public:
    OpcUa(const OpcConfig& config);
    ~OpcUa() = default;

    auto init() -> bool override;
    auto connect() -> bool override;
    auto read() -> bool override;

  private:
    auto fetchAndSelectCertificate() -> bool;

  protected:
    const OpcConfig config;

    UA_Client*       client;       ///< Client
    UA_ClientConfig* clientConfig; ///< Configuration
    UA_StatusCode    status;       ///< Status code

    ByteStringClone serverCert; ///< OPC-UA server certificate
    ByteStringLoad  clientCert; ///< Interface certificate
    ByteStringLoad  keyCert;    ///< Interface key

    const std::string           endpoint;
    std::vector<UA_ReadValueId> nodes; ///< Nodes to read
};
}