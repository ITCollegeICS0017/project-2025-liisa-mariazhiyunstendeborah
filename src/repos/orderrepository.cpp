#include "orderrepository.h"

//Upon not finding an order, returns a nullptr rather than return an error, so it's easier to use in other functions for checking if an order exists.
Order* OrderRepository::findOrder(int orderid) {
    auto iter = orders.find(orderid);
    if (iter != orders.end()) {
        return iter->second.get();
    }
    return nullptr;
}

const std::map<int, std::shared_ptr<Order>>& OrderRepository::getOrders()  const  {
    return orders;
}

//returns map of orders with the completed CompletionStatus in the repository, 
//does not but realistically will need to only find orders of a day/week
std::map<int, std::shared_ptr<Order>> OrderRepository::getCompletedOrders()  const {
    std::map<int, std::shared_ptr<Order>> completed_orders;
    for (const auto& order : orders) {
        if (order.second->compl_status == CompletionStatus::Completed) {
            completed_orders.insert(order);
        }
    }
    return completed_orders;
}

float OrderRepository::calculateProfits(const std::map<int, std::shared_ptr<Order>>& completed_orders) const {
    float profits = 0.0f;
        for (const auto& order : completed_orders) {
            profits += order.second->price;
        }
    return profits;
}

//checks that input order still has a default orderid, if so orderid is set to next_id (which is then incremented) and order is added to repository
//if the above is not true, throws an error
int OrderRepository::addOrder(std::shared_ptr<Order> order)  {
    if (order->orderid == 0) {
    int orderid = next_id++;
    order->orderid = orderid;
    orders.insert({orderid, order});
    return orderid;
    } else {
        throw std::invalid_argument("Order already exists!");
    }
}

void OrderRepository::editOrder(int orderid, std::shared_ptr<Order> updated_order)  {
    if (!findOrder(orderid)) {
        throw std::invalid_argument("Order not found!");
    } else {
        orders.at(orderid) = updated_order;
    }
}

void OrderRepository::deleteOrder(int orderid)  {
    if (!findOrder(orderid)) {
        throw std::invalid_argument("Order does not exist to be deleted!");
    } else {
        orders.erase(orderid);
    }
}
