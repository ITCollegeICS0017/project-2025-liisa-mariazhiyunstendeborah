#include "clientrepository.h"

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
    if (client->client_id == 0) {
    int client_id = next_id++;
    client->client_id = client_id;
    clients.insert({client_id, client});
    return client_id;
    } else {
        throw std::invalid_argument("Client already exists!");
    }
}

void ClientManager::editClient(int client_id, std::shared_ptr<Client> updated_client) {
    if (!findClient(client_id)) {
        throw std::invalid_argument("Client not found!");
    }
    clients.at(client_id) = updated_client;
}

void ClientManager::deleteClient(int client_id) {
    if (!findClient(client_id)) {
        throw std::invalid_argument("Client does not exist to be deleted!");
    } else {
        clients.erase(client_id);
    }
}
