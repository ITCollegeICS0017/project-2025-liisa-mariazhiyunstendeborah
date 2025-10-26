#ifndef ORDER_H
#define ORDER_H

#include <memory>
#include <chrono>
#include "client.h"


constexpr int pay_per_day = 1400;
constexpr double expr_surcharge = 1.25;

enum Service
{
    Photo_printing,
    Film_devel,
};

enum CompletionStatus
{
    Created,
    Assigned,
    InProgress,
    Completed,
};


class Order {
    public:
        std::shared_ptr<Client> client;
        Service service;
        unsigned int in_x_days;
        CompletionStatus compl_status = Created;
        float price = 0.0f;
        std::chrono::year_month_day date_created;
        int assigned_emp_id;

        Order(std::shared_ptr<Client> client, Service service, unsigned int in_x_days);

        virtual ~Order() = default;

        Order* viewOrder();

        float priceCalc(unsigned int in_x_days);
};

#endif
