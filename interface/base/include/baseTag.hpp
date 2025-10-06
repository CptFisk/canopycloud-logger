#pragma once
#include <stdint.h>
#include <string>
#include <variant>
namespace Interface {

/**
 * @brief Alias for a variant type that can hold multiple data types.
 */
using variants = std::variant<int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, float, double, bool, std::string>;

/**
 * @class BaseTag
 * @brief Represents a generic tag with a name, address, polling interval, and value.
 */
class BaseTag {
  public:
    /**
     * @brief Constructs a BaseTag with the given name, address, and polling interval.
     * @param name The name of the tag.
     * @param address The address of the tag.
     * @param polling The polling interval in milliseconds.
     */
    BaseTag(const std::string& name, const std::string& address, const int& polling)
      : name(name)
      , address(address)
      , polling(polling)
      , changed(false) {}

    /**
     * @brief Sets a new value for the tag and updates the change status.
     * @param newValue The new value to assign.
     */
    auto setValue(const variants& newValue) -> void {
        changed   = (value != newValue) || changed;
        prevValue = value;
        value     = newValue;
    }

    /**
     * @brief Checks whether the value has changed since the last update.
     * @return True if the value has changed, false otherwise.
     */
    [[nodiscard]] auto hasChanged() const -> bool { return changed; }

    /**
     * @brief Clears the change flag.
     */
    auto clearChanged() -> void { changed = false; }

    /**
     * @brief Gets the current value of the tag.
     * @return A constant reference to the current value.
     */
    [[nodiscard]] auto getValue() const -> const variants& { return value; }

    /**
     * @brief Gets the name of the tag.
     * @return The name of the tag.
     */
    [[nodiscard]] auto getName() const -> std::string { return name; }

    /**
     * @brief Gets the address of the tag.
     * @return The address of the tag.
     */
    [[nodiscard]] auto getAddress() const -> std::string { return address; }
    /**
     * @brief Gets the polling interval of the tag.
     * @return The polling interval in milliseconds.
     */
    [[nodiscard]] auto getPolling() const -> int { return polling; }

    /**
     * @brief Converts the current value to a string representation.
     * @return A string representation of the value.
     */
    [[nodiscard]] auto valueAsString() const -> std::string {
        return std::visit(
          [](const auto& val) -> std::string {
              using T = std::decay_t<decltype(val)>;

              if constexpr (std::is_same_v<T, bool>) {
                  return val ? "true" : "false";
              } else if constexpr (std::is_same_v<T, std::string>) {
                  return "\"" + val + "\"";
              } else if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>) {
                  return std::to_string(static_cast<int>(val));
              } else {
                  return std::to_string(val);
              }
          },
          value);
    }

  private:
    const std::string name;      ///< The name of the tag.
    const std::string address;   ///< The address of the tag.
    variants          value;     ///< The current value of the tag.
    variants          prevValue; ///< The previous value of the tag.
    int               polling;   ///< The polling interval in milliseconds.
    bool              changed;   ///< Indicates whether the value has changed.
};

}