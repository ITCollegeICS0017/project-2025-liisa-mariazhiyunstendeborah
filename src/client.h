#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
    public:
        std::string client_name;
        //any other data we'd expect to get from one and
        //want to store in a hypothetical database

        Client(std::string client_name) : client_name(client_name) { }

        virtual ~Client() = default;
};

#endif
