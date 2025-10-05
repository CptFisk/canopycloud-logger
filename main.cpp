#include <atomic>
#include <client.hpp>
#include <csignal>
#include <iostream>
#include <loader.hpp>
#include <opc.hpp>

std::atomic<bool> running(true);
void
sigHandler(int s) {
    std::cout << "Recived: " << s << std::endl;
    running = false;
}

int
main(int argc, char* argv[]) {
    std::signal(SIGINT, sigHandler);
    std::signal(SIGTERM, sigHandler);
    std::signal(SIGHUP, sigHandler);

    Logger::Loader loader;

    try {
        loader.loadJson("config/config.json");
        Logger::Client client(std::make_unique<Interface::OpcUa>(loader.getOpcUa().front()), running);
        client.run();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}