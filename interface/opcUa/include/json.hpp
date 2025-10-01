#pragma once
#include <security.hpp>
#include <string>
#include <tags.hp>
#include <vector>

namespace Interface {

struct OpcUaJSON {
    std::string           endpoint;
    std::string           username;
    std::string           password;
    Security              policy;
    std::vector<OpcUaTag> Tags;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(OpcUaJSON, endpoint, username, password, Tags)

inline void
from_json(const nlohmann::json& j, OpcUaJSON& obj) {
    j.at("Endpoint").get_to(obj.endpoint);
    j.at("Username").get_to(obj.username);
    j.at("Password").get_to(obj.password);
    j.at("Policy").get_to(obj.policy);
    j.at("Tags").get_to(obj.Tags);
}

}
