#pragma once
#include "open62541/transport_generated.h"

#include <nlohmann/json.hpp>
#include <open62541/client.h>
#include <string>

namespace Interface {

enum Security {
    None,
    Basic128Rsa15Sign,
    Basic256Rsa15SignEncrypt,
    Basic256Sign,
    Basic256SignEncrypt,
    Basic256Sha256Sign,
    Basic256Sha256SignEncrypt,
    Aes128Sha256RsaOaepSign,
    Aes128Sha256RsaOaepSignEncrypt,
    Aes256Sha256RsaPssSign,
    Aes256Sha256RsaPssSignEncrypt,
};

struct SecurityConfig {
    std::string            policyUri;
    UA_MessageSecurityMode policyType;

    SecurityConfig(const std::string& uri, UA_MessageSecurityMode type)
      : policyUri(uri)
      , policyType(type) {}
};

/**
 * @brief Maps a Security enum value to its corresponding OPC UA security policy URI
 *        and message security mode.
 *
 * This function translates a given Security level into the appropriate
 * securityPolicyUri string and UA_MessageSecurityMode value required for
 * configuring an OPC UA client connection.
 *
 * @param sec The desired security configuration, represented as a value from the Security enum.
 * @return A SecurityConfig struct containing the matching policy URI and message security mode.
 */
auto
getSecurityConfig(const Security& sec) -> SecurityConfig;

NLOHMANN_JSON_SERIALIZE_ENUM(Security,
                             { { Security::None, "None" },
                               { Basic128Rsa15Sign, "Basic128Rsa15Sign" },
                               { Basic256Rsa15SignEncrypt, "Basic256Rsa15SignEncrypt" },
                               { Basic256Sign, "Basic256Sign" },
                               { Basic256SignEncrypt, "Basic256SignEncrypt" },
                               { Basic256Sha256Sign, "Basic256Sha256Sign" },
                               { Basic256Sha256SignEncrypt, "Basic256Sha256SignEncrypt" },
                               { Aes128Sha256RsaOaepSign, "Aes128Sha256RsaOaepSign" },
                               { Aes128Sha256RsaOaepSignEncrypt, "Aes128Sha256RsaOaepSignEncrypt" },
                               { Aes256Sha256RsaPssSign, "Aes256Sha256RsaPssSign" },
                               { Aes256Sha256RsaPssSignEncrypt, "Aes256Sha256RsaPssSignEncrypt" } })

}