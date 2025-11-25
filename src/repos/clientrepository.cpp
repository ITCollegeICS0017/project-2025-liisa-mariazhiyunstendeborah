#include "clientrepository.h"

const std::map<int, std::shared_ptr<Client>>& ClientRepository::getClients()
    const {
  return clients;
}

Client* ClientRepository::findClient(int client_id) {
  auto iter = clients.find(client_id);
  if (iter != clients.end()) {
    return iter->second.get();
  }
  return nullptr;
}

// checks if client's id is default, if so it sets the id to the current next id
// (which is then incremented) and adds the client to the repository if client's
// id is not default, assumes client has already been added to repository and
// throws error
int ClientRepository::addClient(std::shared_ptr<Client> client) {
  if (client->client_id == 0) {
    int client_id = next_id++;
    client->client_id = client_id;
    clients.insert({client_id, client});
    return client_id;
  } else {
    throw DuplicateObjectException(std::to_string(client->client_id));
  }
}

void ClientRepository::editClient(int client_id,
                                  std::shared_ptr<Client> updated_client) {
  if (!findClient(client_id)) {
    throw MissingObjectException(std::to_string(client_id));
  }
  clients.at(client_id) = updated_client;
}

void ClientRepository::deleteClient(int client_id) {
  if (!findClient(client_id)) {
    throw MissingObjectException(std::to_string(client_id));
  } else {
    clients.erase(client_id);
  }
}
