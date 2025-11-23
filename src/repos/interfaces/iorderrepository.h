#ifndef IORDERREPOSITORY_H
#define IORDERREPOSITORY_H

#include <map>
#include <memory>

class Order;
class IOrderManager {
    public:
        IOrderManager() = default;

        virtual ~IOrderManager() = default;

        virtual int addOrder(std::shared_ptr<Order> order) = 0;

        virtual void editOrder(int orderid, std::shared_ptr<Order> updated_order) = 0;

        virtual void deleteOrder(int orderid) = 0;
};

#endif