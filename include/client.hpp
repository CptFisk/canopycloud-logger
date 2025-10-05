#pragma once
#include <base.hpp>
#include <memory>
#include <vector>
#include <atomic>
#include <chrono>

namespace Logger {

class Client {
  public:
    Client(std::unique_ptr<Interface::Base> interface, std::atomic<bool>& running);

    auto run() -> void;

  private:
    auto pollTags(const std::vector<Interface::BaseTag*>& tags) -> void;
    std::atomic<bool>& running;

    std::chrono::steady_clock::time_point last100;  ///< Memory for last cyclic run (100ms)
    std::chrono::steady_clock::time_point last200;  ///< Memory for last cyclic run (200ms)
    std::chrono::steady_clock::time_point last500;  ///< Memory for last cyclic run (500ms)
    std::chrono::steady_clock::time_point last1000; ///< Memory for last cyclic run (1000ms)

    std::vector<Interface::BaseTag*> poll100ms;
    std::vector<Interface::BaseTag*> poll200ms;
    std::vector<Interface::BaseTag*> poll500ms;
    std::vector<Interface::BaseTag*> poll1000ms;

    std::unique_ptr<Interface::Base> interface; ///< Interface
};

}