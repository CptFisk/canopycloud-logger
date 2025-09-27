#pragma once
#include <security.hpp>
#include <string>

namespace Interface {

/**
 * @brief Configuration settings for OPC UA interface
 */
struct OpcConfig {
    const std::string uri;      ///< Address to OPC UA server
    const Security    security; ///< Security mode

    const std::string username; ///< Username, if blank assume Anonomyous
    const std::string password;

    OpcConfig(const std::string& uri,
              const Security&    security,
              const std::string& username,
              const std::string& password) : uri(uri), security(security), username(username), password(password) {
    }
};

}