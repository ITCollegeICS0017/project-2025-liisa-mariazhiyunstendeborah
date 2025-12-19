#include "order.h"

// Constructor, creates clock to set date of creation & calculates the price
// based on in_x_days.
Order::Order(std::shared_ptr<Client> client, Service service,
             unsigned int in_x_days, IClock *clock)
    : client(client), service(service), in_x_days(in_x_days), clock(clock) {
  auto now = clock->now();
  date_created = std::chrono::floor<std::chrono::days>(now);
  price = priceCalc(in_x_days);
}

// Takes the amount of workdays required through in_x_days and returns a float
// price. expr_surcharge and pay_per_day are defined in utilities/constantdefs.h
float Order::priceCalc(unsigned int in_x_days) {
  price = pay_per_day * in_x_days;
  if (in_x_days < 2) {
    price *= expr_surcharge;
  }
  return price;
}