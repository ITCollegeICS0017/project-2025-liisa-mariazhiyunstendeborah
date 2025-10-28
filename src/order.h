#ifndef ORDER_H
#define ORDER_H

#include <memory>
#include <chrono>
#include "client.h"
#include "clocks.h"

extern unsigned int pay_per_day;
extern double expr_surcharge;

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
        IClock& clock;
        std::chrono::year_month_day date_created;
        int orderid = 0;
        CompletionStatus compl_status = Created;
        float price = 0.0f;
        int assigned_emp_id;

        Order(std::shared_ptr<Client> client, Service service, unsigned int in_x_days, IClock& clock);

        virtual ~Order() = default;

        float priceCalc(unsigned int in_x_days);
};

#endif
