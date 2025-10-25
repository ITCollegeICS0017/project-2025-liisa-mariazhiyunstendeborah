#include "clientmanager.h"

const std::map<int, std::shared_ptr<Client>>& ClientManager::getClients() const {
            return clients;
}

Client* ClientManager::findClient(int client_id) {
    auto iter = clients.find(client_id);
    if (iter != clients.end()) {
        return iter->second.get();
    }
    //E: make err
    return nullptr;
}

int ClientManager::addClient(std::shared_ptr<Client> client) {
    int client_id = next_id++;
    clients.insert({client_id, client});
    return client_id;
    //E: handle Client existing already
}

void ClientManager::editClient(int client_id, std::shared_ptr<Client> updated_client) {
    clients.at(client_id) = updated_client;
    //E: ?
}

void ClientManager::deleteClient(int client_id) {
    clients.erase(client_id);
    //E: ?
}
