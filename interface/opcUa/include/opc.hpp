#pragma once
#include <base.hpp>
#include <json.hpp>
#include <open62541/client_config_default.h>
#include <string>
#include <utility/byteStringClone.hpp>
#include <utility/byteStringLoad.hpp>
#include <vector>

namespace Interface {

class OpcUa : public Base {
  public:
    OpcUa(const OpcUaJSON& config);
    ~OpcUa() = default;

    auto init() -> bool override;
    auto connect() -> bool override;
    auto read() -> bool override;

  private:
    auto fetchAndSelectCertificate() -> bool;

  protected:
    const OpcUaJSON config;

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