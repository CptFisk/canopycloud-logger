#pragma once
#include <stdint.h>
#include <string>
#include <variant>
#include <vector>

namespace Interface {

/**
 * @brief Container to hold tag-values.
 */
struct BaseTag {
    const std::string                                                                                     name;
    const std::string                                                                                     address;
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
    Base(const std::string& name)
      : name(name) {}
    ~Base() = default;

    [[nodiscard]] virtual auto init() -> bool    = 0;
    [[nodiscard]] virtual auto connect() -> bool = 0;
    [[nodiscard]] virtual auto read() -> bool    = 0;

    [[nodiscard]] auto getTags() -> std::vector<BaseTag>& { return baseTags; }
    [[nodiscard]] auto getName() -> const std::string& { return name; }

  protected:
    const std::string    name;
    std::vector<BaseTag> baseTags;
};

}
