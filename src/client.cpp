#include <chrono>
#include <client.hpp>
#include <iostream>
#include <thread>

namespace Logger {

void
hello() {
    std::cout << "Hello world" << std::endl;
}

Client::Client(std::unique_ptr<Interface::Base> interface, std::atomic<bool>& running)
  : interface(std::move(interface))
  , running(running) {

    auto& tags = this->interface->getTags();
    for (auto& tag : tags) {
        switch (tag.polling) {
            case 100:
                poll100ms.push_back(&tag);
                break;
            case 200:
                poll200ms.push_back(&tag);
                break;
            case 500:
                poll500ms.push_back(&tag);
                break;
            case 1000:
                poll1000ms.push_back(&tag);
                break;
            default:
                std::cerr << "Unknown polling tag: " << tag.polling << std::endl;
        }
    }
}

auto
Client::run() -> void {
    if (!interface->init() || !interface->connect())
        std::cerr << "Failed to connect to server" << std::endl;
    auto startTime = std::chrono::steady_clock::now();
    auto interval  = [](int interval, auto& last, auto func) {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count() >= interval)
            func(), last = now;
    };

    while (running) {
        interface->read();
        interval(100, last100, [&] { pollTags(poll100ms); });
        interval(200, last200, [&] { pollTags(poll200ms); });
        interval(500, last500, [&] { pollTags(poll500ms); });
        interval(1000, last1000, [&] { pollTags(poll1000ms); });
        std::this_thread::sleep_for(std::chrono::milliseconds(5L));
    }
}

auto
Client::pollTags(const std::vector<Interface::BaseTag*>& tags) -> void {
    for (const auto& tag : tags) {
        std::visit([](auto arg) { std::cout << arg << std::endl; }, tag->value);
    }
}

}