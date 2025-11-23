#ifndef ICLIENTREPOSITORY_H
#define ICLIENTREPOSITORY_H

#include <map>
#include <memory>

class Client;
class IClientManager {
    public:
        IClientManager() = default;
        virtual ~IClientManager() = default;

        virtual int addClient(std::shared_ptr<Client> client) = 0;

        virtual void editClient(int client_id, std::shared_ptr<Client> updated_client) = 0;

        virtual void deleteClient(int client_id) = 0;
};

#endif