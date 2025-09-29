#pragma once
#include "types.hpp"

#include <types.hpp>

namespace Interface {
/**
 * @brief Baseclass for all communication interfaces
 */
class Base {
  public:
    auto getType() const -> Types;

    virtual auto init() -> bool    = 0;
    virtual auto connect() -> bool = 0;
    virtual auto read() -> bool    = 0;

  private:
    Types type;
};
}
