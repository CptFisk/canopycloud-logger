#include <cert.hpp>
#include <iostream>
#include <opc.hpp>
#include <utility/convert.hpp>

namespace Interface {

OpcUa::OpcUa(const OpcUaJSON& config)
  : endpoint(config.endpoint)
  , status{}
  , client(nullptr)
  , clientConfig(nullptr)
  , config(config) {
    // Initialize
    client       = UA_Client_new();
    clientConfig = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(clientConfig);
}

auto
OpcUa::init() -> bool {
    if (!fetchAndSelectCertificate())
        return false;

    // Create certificates
    X509Certificate cert;
    cert.generate(2048, 365, "Canopy", "client.der", "key.der");
    // Load files
    clientCert.set("client.der");
    keyCert.set("key.der");

    // Configure encryption
    const UA_ByteString trustList[] = { serverCert.getValue() };

    if (UA_ClientConfig_setDefaultEncryption(clientConfig, clientCert.getValue(), keyCert.getValue(), trustList, 1, nullptr, 0) !=
        UA_STATUSCODE_GOOD) {
        std::cerr << "Kunde inte konfigurera kryptering: " << UA_StatusCode_name(status) << std::endl;
        UA_Client_delete(client);
        return false;
    }
    return true;
}

auto
OpcUa::fetchAndSelectCertificate() -> bool {
    size_t                  endpointCount = {};
    UA_EndpointDescription* endpoints;

    // Fetch server certificate
    if (UA_Client_getEndpoints(client, endpoint.c_str(), &endpointCount, &endpoints) != UA_STATUSCODE_GOOD || endpointCount == 0) {
        return false;
    }
    UA_EndpointDescription* selected = nullptr;
    auto                    security = getSecurityConfig(config.policy);

    bool matched = false;
    for (auto i = 0; i < endpointCount; ++i) {
        if (endpoints[i].securityMode == security.policyType && uaToStdString(endpoints[i].securityPolicyUri) == security.policyUri) {
            selected = &endpoints[i];
            matched  = true;
            break;
        }
    }

    if (!matched)
        return false;

    serverCert.set(selected->serverCertificate);
    return true;
}

auto
OpcUa::connect() -> bool {
    return UA_Client_connect(client, config.endpoint.c_str()) == UA_STATUSCODE_GOOD ? true : false;
}

auto
OpcUa::read() -> bool {
    return true;
}
}