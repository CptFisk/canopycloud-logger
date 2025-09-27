#include <iostream>
#include <opc.hpp>
#include <cert.hpp>
#include <utility.hpp>


namespace Interface {

OpcUa::OpcUa(const OpcConfig& config) : endpoint(config.uri), status{}, client(nullptr), clientConfig(nullptr) {
    client = UA_Client_new();

    if (!client)
        throw std::runtime_error("Failed to create UA_Client");

    //Setup security
    security(config.security);

    X509Certificate cert;
    cert.generate(2048, 365 * 2, "My OPC");
}

auto
OpcUa::security(const Security& security) -> void {
    clientConfig = UA_Client_getConfig(client);
    UA_ClientConfig_setDefault(clientConfig);

    const auto config               = getSecurityConfig(security);
    clientConfig->securityMode      = config.policyType;
    clientConfig->securityPolicyUri = UA_STRING_ALLOC(config.policyUri.c_str());

    if (!security == Security::None) {
        X509Certificate certificate;
        certificate.generate(2048, 365 * 2, "Logger");
        //We need to create and load certificates
        UA_ByteString cert = ByteStringWrapper("cert.der").value;
        UA_ByteString key  = ByteStringWrapper("key.der").value;

        UA_ClientConfig_setDefaultEncryption(clientConfig,
                                     "cert.der",
                                     "key.der",
                                     "trusted/",  // katalog med servercertifikat
                                     nullptr);    // ingen CRL


    }

}


auto
OpcUa::connect() -> bool {
    status = UA_Client_connect(client, endpoint.c_str());
    if (status != UA_STATUSCODE_GOOD)
        throw std::runtime_error("Failed to connect to UA_Client");
    return true;
}

auto
OpcUa::read() -> bool {
    return true;
}
}