#include "ordermanager.h"


Order* OrderManager::findOrder(int orderid) {
    auto iter = orders.find(orderid);
    if (iter != orders.end()) {
        return iter->second.get();
    }
    return nullptr;
}

const std::map<int, std::shared_ptr<Order>>& OrderManager::getOrders()  const  {
    return orders;
}

std::map<int, std::shared_ptr<Order>> OrderManager::getCompletedOrders()  const {
    std::map<int, std::shared_ptr<Order>> completed_orders;
    for (const auto& order : orders) {
        if (order.second->compl_status == CompletionStatus::Completed) {
            completed_orders.insert(order);
        }
    }
    return completed_orders;
}

float OrderManager::calculateProfits(const std::map<int, std::shared_ptr<Order>>& completed_orders) const {
    float profits = 0.0f;
        for (const auto& order : completed_orders) {
            profits += order.second->price;
        }
    return profits;
}

int OrderManager::addOrder(std::shared_ptr<Order> order)  {
    if (order->orderid == 0) {
    int orderid = next_id++;
    order->orderid = orderid;
    orders.insert({orderid, order});
    return orderid;
    } else {
        throw std::invalid_argument("Order already exists!");
    }
}

void OrderManager::editOrder(int orderid, std::shared_ptr<Order> updated_order)  {
    if (!findOrder(orderid)) {
        throw std::invalid_argument("Order not found!");
    } else {
        orders.at(orderid) = updated_order;
    }
}

void OrderManager::deleteOrder(int orderid)  {
    if (!findOrder(orderid)) {
        throw std::invalid_argument("Order does not exist to be deleted!");
    } else {
        orders.erase(orderid);
    }
}
