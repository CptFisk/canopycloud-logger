#include <opc.hpp>
#include <config.hpp>
int main(int argc, char *argv[]) {

    Interface::OpcUa* client;
    Interface::OpcConfig config("localhost", Interface::Security::Basic256SignEncrypt, "username", "pass");

    client = new Interface::OpcUa(config);
    delete client;

}