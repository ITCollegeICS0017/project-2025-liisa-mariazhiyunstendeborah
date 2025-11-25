#ifndef IORDERREPOSITORY_H
#define IORDERREPOSITORY_H

#include <map>
#include <memory>

//interface for OrderRepository, CRUD operations and constructor/destructor
class Order;
class IOrderRepository {
    public:
        IOrderRepository() = default;

        virtual ~IOrderRepository() = default;

        virtual int addOrder(std::shared_ptr<Order> order) = 0;

        virtual void editOrder(int orderid, std::shared_ptr<Order> updated_order) = 0;

        virtual void deleteOrder(int orderid) = 0;
};

#endif