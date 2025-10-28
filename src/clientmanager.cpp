#include "clientmanager.h"

const std::map<int, std::shared_ptr<Client>>& ClientManager::getClients() const {
            return clients;
}

Client* ClientManager::findClient(int client_id) {
    auto iter = clients.find(client_id);
    if (iter != clients.end()) {
        return iter->second.get();
    }
    return nullptr;
}

int ClientManager::addClient(std::shared_ptr<Client> client) {
    if (!findClient(client->client_id)) {
    int client_id = next_id++;
    client->client_id = client_id;
    clients.insert({client_id, client});
    return client_id;
    } else {
        return -1;
        //Throw an exception of some kind
    }
}

void ClientManager::editClient(int client_id, std::shared_ptr<Client> updated_client) {
    clients.at(client_id) = updated_client;
    //E: ?
}

void ClientManager::deleteClient(int client_id) {
    clients.erase(client_id);
    //E: ?
}
