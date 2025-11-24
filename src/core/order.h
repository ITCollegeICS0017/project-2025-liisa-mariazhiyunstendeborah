
#ifndef ORDER_H
#define ORDER_H

#include <memory>
#include <chrono>
#include "client.h"
#include "utilities/clocks.h"
#include "utilities/constantdefs.h"

class Order {
public:
std::shared_ptr<Client> client;
Service service;
//currently used as amount of workdays needed rather than the deadline it appears to be, which makes for my very silly price calculation
unsigned int in_x_days;
IClock& clock;
std::chrono::year_month_day date_created;
//default value of orderid, to be changed when an order is added to the repository
int orderid = 0;
CompletionStatus compl_status = Created;
float price = 0.0f;
//assigned photographer
int assigned_emp_id = 0;

//Constructor, currently implements a pointer to a client, but could potentially be improved.
Order(std::shared_ptr<Client> client, Service service, unsigned int in_x_days, IClock& clock);

virtual ~Order() = default;

//Function used to calculate the price based on the amount of workdays inputted
float priceCalc(unsigned int in_x_days);
};

#endif