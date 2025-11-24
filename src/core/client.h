#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
    public:
        //the real client_id will be set when a client is added to the clientrepository
        int client_id = 0;
        std::string client_name;
        

        Client(std::string client_name) : client_name(client_name) { }

        virtual ~Client() = default;
};

#endif
