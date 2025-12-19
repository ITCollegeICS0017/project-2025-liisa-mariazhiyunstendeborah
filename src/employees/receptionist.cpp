#include "receptionist.h"

std::string Receptionist::getEmpType() { return "Receptionist"; }

int Receptionist::makeOrder(std::shared_ptr<Client> client, Service service,
                            unsigned int in_x_days) {
  auto order = std::make_shared<Order>(client, service, in_x_days, clock);
  return order_repository->addOrder(order);
}

// checks that provided order pointer is not null, throws an error if it is,
// else edits the assigned employee id of the order to the employee specified
void Receptionist::assignOrder(Order* assign, int emp_id) {
  if (assign != nullptr) {
    assign->assigned_emp_id = emp_id;
  } else {
    throw std::invalid_argument("Order* input is a nullptr!");
  }
}
//!!!TODO!!!: how to handle checking if employee exists? 
//Adding employee repository actions to Receptionist only for this purpose seems odd...

// uses the order repository to fetch completed orders and calculate their total
// revenue, constructs a report and adds it to a receptionist report repository
int Receptionist::submitReport() {
  auto completed_orders = order_repository->getCompletedOrders();
  auto total_profits = order_repository->calculateProfits(completed_orders);
  auto receptreport = std::make_shared<ReceptReport>(
      emp_id, clock, completed_orders, total_profits);
  return receptreport_repository->addReport(receptreport);
}