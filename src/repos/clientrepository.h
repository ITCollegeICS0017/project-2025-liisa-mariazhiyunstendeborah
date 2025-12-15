#ifndef CLIENTREPOSITORY_H
#define CLIENTREPOSITORY_H

#include "interfaces/iclientrepository.h"
#include "core/client.h"
#include "utilities/exceptions.h"

//in memory client repository, sets client ids, uses crud operations and finds clients by id.
class ClientRepository : public IClientRepository{
    private:
        std::map<int, std::shared_ptr<Client>> clients;
        //ids are set incrementally starting from next_id
        int next_id = 1;

    public:
        const std::map<int, std::shared_ptr<Client>>& getClients() const;

        //may be desirable to add a findClient method that takes in a client's name as well
        Client* findClient(int client_id);

        int addClient(std::shared_ptr<Client> client);

        void ClientRepository::addExistingClient(std::shared_ptr<Client> client);

        void editClient(int client_id, std::shared_ptr<Client> updated_client);

        void deleteClient(int client_id);
};

#endif
