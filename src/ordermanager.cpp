#include "ordermanager.h"

//pretys rue nothing in ordermanager needs defining

Order* OrderManager::findOrder(int orderid) {
    auto iter = orders.find(orderid);
    if (iter != orders.end()) {
        return iter->second.get();
    }
    //E: make err
    return nullptr;
}

const std::map<int, std::shared_ptr<Order>>& OrderManager::getOrders()  const  {
    return orders;
    //E: ?
}

std::map<int, std::shared_ptr<Order>> OrderManager::getCompletedOrders()  const {
    std::map<int, std::shared_ptr<Order>> completed_orders;
    for (const auto& order : orders) {
        if (order.second->compl_status == CompletionStatus::Completed) {
            completed_orders.insert(order);
        }
    }
    return completed_orders;
    //E: ?
}

float OrderManager::calculateProfits(const std::map<int, std::shared_ptr<Order>>& completed_orders) const {
    float profits = 0.0f;
        for (const auto& order : completed_orders) {
            profits += order.second->price;
        }
    //E: ?
    return profits;
}

int OrderManager::addOrder(std::shared_ptr<Order> order)  {
    int orderid = next_id++;
    orders.insert({orderid, order});
    return orderid;
}

void OrderManager::editOrder(int orderid, std::shared_ptr<Order> updated_order)  {
    orders.at(orderid) = updated_order;
    //E: ? check updated_order valid maybe?
}

void OrderManager::deleteOrder(int orderid)  {
    //I: leaves gaps when erasing cuz of how
    //orderid is set
    orders.erase(orderid);
}
