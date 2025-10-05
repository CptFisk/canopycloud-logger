#pragma once
#include <stdint.h>
#include <string>
#include <types.hpp>
#include <variant>
#include <vector>

namespace Interface {

/**
 * @brief Container to hold tag-values.
 */
struct BaseTag {
    std::string                                                                                           name;
    std::string                                                                                           address;
    std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, float, double, bool, std::string> value;
    int                                                                                                   polling;
    BaseTag(const std::string& name, const std::string& address, const int& polling)
      : name(name)
      , address(address)
      , polling(polling) {}
};

/**
 * @brief Baseclass for all communication interfaces
 */
class Base {
  public:
    virtual auto init() -> bool    = 0;
    virtual auto connect() -> bool = 0;
    virtual auto read() -> bool    = 0;

    auto getTags() -> std::vector<BaseTag>& { return baseTags; }

  protected:
    std::vector<BaseTag> baseTags;
};

}
