#include "order.h"

unsigned int pay_per_day = 1400;
double expr_surcharge = 1.25;

Order::Order(std::shared_ptr<Client> client, Service service, unsigned int in_x_days, IClock& clock) : client(client), service(service), in_x_days(in_x_days), clock(clock) {
    auto now = clock.now();
    date_created = std::chrono::floor<std::chrono::days>(now);
    price = priceCalc(in_x_days);
}

float Order::priceCalc(unsigned int in_x_days){
    price = pay_per_day * in_x_days;
    if (in_x_days < 2) {
        price *= expr_surcharge;
    }
    return price;
}
