#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <stdexcept>
#include <map>
#include <memory>
#include "core/order.h"

class OrderManager {
    private:
        std::map<int, std::shared_ptr<Order>> orders;
        int next_id = 1;

    public:
        OrderManager() = default;

        ~OrderManager() = default;

        Order* findOrder(int orderid);

        const std::map<int, std::shared_ptr<Order>>& getOrders()  const;

        std::map<int, std::shared_ptr<Order>> getCompletedOrders()  const;

        float calculateProfits(const std::map<int, std::shared_ptr<Order>>& completed_orders) const;

        int addOrder(std::shared_ptr<Order> order);

        void editOrder(int orderid, std::shared_ptr<Order> updated_order);

        void deleteOrder(int orderid);
};

#endif
