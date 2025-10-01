#pragma once
#include <nlohmann/json.hpp>
#include <opcUa/include/json.hpp>
#include <string>

namespace Logger {

class Loader {
  public:
    Loader()  = default;
    ~Loader() = default;

    /**
     * @brief Load a JSON file that SHOULD contain all configuration data for the logger
     * @param path Path to JSON configuration file
     */
    auto loadJson(const std::string& path) -> void;

    /**
     * @return All objects that match the profile of OpcUa
     */
    auto getOpcUa() -> const std::vector<Interface::OpcUaJSON>;
  private:
    nlohmann::json json;

    std::vector<Interface::OpcUaJSON> opcUaJson; ///< Contains all JSON configurations for OPC UA
};

}