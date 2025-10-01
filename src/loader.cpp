#include <fstream>
#include <iostream>
#include <loader.hpp>
#include <print>

namespace Logger {

auto
Loader::loadJson(const std::string& path) -> void {
    std::ifstream file(path);

    if (!file.is_open())
        throw std::runtime_error("Failed to open file");

    try {
        json = nlohmann::json::parse(file);
    } catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }

    if (json.contains("OPC UA")) {
        for (const auto& device : json["OPC UA"]["Devices"]) {
            opcUaJson.emplace_back(device.get<Interface::OpcUaJSON>());
        }
    }
    std::print("OPC Serverns: {}\n", opcUaJson.size());
}

}