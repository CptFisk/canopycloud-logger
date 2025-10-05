#pragma once
#include <opcTag.hp>
#include <security.hpp>
#include <string>
#include <vector>

namespace Interface {

struct OpcUaJSON {
    std::string           name;     ///< Name of server
    std::string           endpoint; ///< Endpoint address
    std::string           username; ///< Username, if blank assume Anonymous
    std::string           password; ///< Password
    Security              policy;   ///< Desired security policy
    std::vector<OpcUaTag> tags;     ///< List of tags
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OpcUaJSON, endpoint, username, password, tags)

inline void
from_json(const nlohmann::json& j, OpcUaJSON& obj) {
    j.at("Name").get_to(obj.name);
    j.at("Endpoint").get_to(obj.endpoint);
    j.at("Username").get_to(obj.username);
    j.at("Password").get_to(obj.password);
    j.at("Policy").get_to(obj.policy);
    j.at("Tags").get_to(obj.tags);
}

}
