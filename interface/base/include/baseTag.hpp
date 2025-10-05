#pragma once
#include <stdint.h>
#include <string>
#include <variant>
namespace Interface {

using variants = std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, float, double, bool, std::string>;

class BaseTag {
  public:
    BaseTag(const std::string& name, const std::string& address, const int& polling)
      : name(name)
      , address(address)
      , polling(polling)
      , changed(false) {}

    auto setValue(const variants& newValue) -> void {
        changed   = (value != newValue);
        prevValue = value;
        value     = newValue;
    }

    auto hasChanged() const -> bool { return changed; }
    auto clearChanged() -> void { changed = false; }

    auto getValue() const -> const variants& { return value; }

    [[nodiscard]] auto getName() const -> std::string { return name; }
    [[nodiscard]] auto getAddress() const -> std::string { return address; }
    [[nodiscard]] auto getPolling() const -> int { return polling; }

  private:
    const std::string name;
    const std::string address;
    variants          value;
    variants          prevValue;
    int               polling;
    bool              changed;
};

}