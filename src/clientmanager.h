#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <map>
#include <memory>
#include "client.h"

class ClientManager {
    private:
        std::map<int, std::shared_ptr<Client>> clients;
        int next_id = 1;
    public:
        ClientManager() = default;
        virtual ~ClientManager() = default;

        const std::map<int, std::shared_ptr<Client>>& getClients() const;

        Client* findClient(int client_id);

        int addClient(std::shared_ptr<Client> client);

        void editClient(int client_id, std::shared_ptr<Client> updated_client);

        void deleteClient(int client_id);
};

#endif
