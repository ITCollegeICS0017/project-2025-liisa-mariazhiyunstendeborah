#ifndef ORDERREPOSITORY_H
#define ORDERREPOSITORY_H

#include "interfaces/iorderrepository.h"
#include "core/order.h"
#include "utilities/exceptions.h"

//Order repository, sets order ids, performs CRUD operations, finds orders by order ids, gets completed orders & calculates profits of given orders
class OrderRepository : public IOrderRepository{
    private:
        std::map<int, std::shared_ptr<Order>> orders;
        //ids are set incrementally starting from next_id
        int next_id = 1;

    public:
        Order* findOrder(int orderid);

        const std::map<int, std::shared_ptr<Order>>& getOrders()  const;

        //returns orders with completed status, used for Receptionist.submitReport()
        std::map<int, std::shared_ptr<Order>> getCompletedOrders()  const;

        //calculates total profits of given orders, used for Receptionist.submitReport()
        float calculateProfits(const std::map<int, std::shared_ptr<Order>>& completed_orders) const;

        int addOrder(std::shared_ptr<Order> order);

        void editOrder(int orderid, std::shared_ptr<Order> updated_order);

        void deleteOrder(int orderid);
};

#endif
