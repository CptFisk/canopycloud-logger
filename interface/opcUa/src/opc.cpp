#include <cert.hpp>
#include <iostream>
#include <opc.hpp>
#include <open62541/client.h>
#include <print>
#include <utility/convert.hpp>
#include <utility/nodes.hpp>
#include <utility/mapper.hpp>

namespace Interface {
OpcUa::OpcUa(const OpcUaJSON& config)
  : endpoint(config.endpoint)
  , status{}
  , client(nullptr)
  , clientConfig(nullptr)
  , config(config)
  , readRequest{}
  , readResponse{} {
    // Initialize
    client       = UA_Client_new();
    clientConfig = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(clientConfig);
}

OpcUa::~OpcUa() {
    // Cleaning
    for (auto i = 0; i < readRequest.nodesToReadSize; ++i) {
        UA_NodeId_clear(&readRequest.nodesToRead[i].nodeId);
    }
    UA_ReadResponse_clear(&readResponse);
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
        std::print("Could not configure encryption {}", UA_StatusCode_name(status));
        UA_Client_delete(client);
        client = nullptr;
        return false;
    }

    // Check if tags is valid
    for (const auto& tag : config.tags) {
        if (validNodeId(tag.address)) {
            // It's a valid tag
            baseTags.push_back({ tag.name, tag.address });
        }
    }
    // Create a read request
    UA_ReadRequest_init(&readRequest);
    readRequest.nodesToReadSize = baseTags.size();
    readRequest.nodesToRead     = static_cast<UA_ReadValueId*>(UA_Array_new(baseTags.size(), &UA_TYPES[UA_TYPES_READVALUEID]));

    if (!readRequest.nodesToRead) {
        std::print("Failed to allocate memory, exiting");
        return false;
    }

    for (auto i = 0; i < baseTags.size(); ++i) {
        UA_ReadValueId_init(&readRequest.nodesToRead[i]);
        readRequest.nodesToRead[i].attributeId = UA_ATTRIBUTEID_VALUE;
        readRequest.nodesToRead[i].nodeId      = createNodeId(baseTags[i].address);
    }

    return true;
}

auto
OpcUa::fetchAndSelectCertificate() -> bool {
    size_t                  endpointCount = {};
    UA_EndpointDescription* endpoints     = nullptr;

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
    readResponse = UA_Client_Service_read(client, readRequest);

    if (readResponse.responseHeader.serviceResult == UA_STATUSCODE_GOOD) {

        for (size_t i = 0; i < readResponse.resultsSize; ++i) {
            const UA_DataValue& val = readResponse.results[i];

            if (!val.hasValue) {
                std::cerr << "No value for node " << i << std::endl;
                continue;
            }
            applyVariantToBaseTag(val.value, baseTags[i], i);
        }
    } else {
        std::print("Read failed");
        return false;
    }
    return true;
}

}