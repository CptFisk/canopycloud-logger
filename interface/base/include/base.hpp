#pragma once
#include <string>
#include <vector>
#include <baseTag.hpp>
namespace Interface {

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
