#pragma once
#include <functional>
#include <iostream>
#include <open62541/client.h>
#include <string>
#include <unordered_map>
#include <variant>

namespace Interface {

using VariantHandler = std::function<void(const UA_Variant&, BaseTag&)>;

inline const std::unordered_map<const UA_DataType*, VariantHandler>&
getVariantHandlers() {
    static const std::unordered_map<const UA_DataType*, VariantHandler> handlers = {
        { &UA_TYPES[UA_TYPES_BOOLEAN], [](const UA_Variant& v, BaseTag& tag) { tag.value = *static_cast<UA_Boolean*>(v.data) != 0; } },
        { &UA_TYPES[UA_TYPES_SBYTE],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<int8_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_BYTE],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<uint8_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_INT16],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<int16_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_UINT16],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<uint16_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_INT32],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<int32_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_UINT32],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<int>(*static_cast<uint32_t*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_FLOAT], [](const UA_Variant& v, BaseTag& tag) { tag.value = *static_cast<float*>(v.data); } },
        { &UA_TYPES[UA_TYPES_DOUBLE],
          [](const UA_Variant& v, BaseTag& tag) { tag.value                      = static_cast<float>(*static_cast<double*>(v.data)); } },
        { &UA_TYPES[UA_TYPES_STRING],
          [](const UA_Variant& v, BaseTag& tag) {
              const UA_String*                                          uaStr    = static_cast<UA_String*>(v.data);
              tag.value                                                          = std::string(reinterpret_cast<char*>(uaStr->data), uaStr->length);
          } },
    };
    return handlers;
}

inline void
applyVariantToBaseTag(const UA_Variant& variant, BaseTag& tag, size_t index = 0) {
    const auto& handlers = getVariantHandlers();
    auto        it       = handlers.find(variant.type);
    if (it != handlers.end()) {
        try {
            it->second(variant, tag);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing value for tag[" << index << "]: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "Unsupported data type for tag[" << index << "]" << std::endl;
    }
}

} // namespace Interface
