#include "order.h"

Order::Order(std::shared_ptr<Client> client, Service service, unsigned int in_x_days) : client(client), service(service), in_x_days(in_x_days) {
    auto now = std::chrono::system_clock::now();
    date_created = std::chrono::floor<std::chrono::days>(now);
    price = priceCalc(in_x_days);
}

Order* Order::viewOrder() {
    //add code here...
    return this;
}

float Order::priceCalc(unsigned int in_x_days){
    //E: invalid pay_per_day, in_x_days, what if negative result...
    price = pay_per_day * in_x_days;
    if (in_x_days < 2) {
        price *= expr_surcharge;
    }
    return price;
}
