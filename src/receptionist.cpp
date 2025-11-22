#include "receptionist.h"

std::string Receptionist::getEmpType() {
    return "Receptionist";
}

int Receptionist::makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days) {
    auto order = std::make_shared<Order>(client, service, in_x_days, clock);
    return order_manager->addOrder(order);
}

void Receptionist::assignOrder(Order* assign, int emp_id){
    if (assign != nullptr) {
        assign->assigned_emp_id = emp_id;
    } else {
        throw std::invalid_argument("Passed in a nullptr!");
    }
}

int Receptionist::submitReport(){
    auto completed_orders = order_manager->getCompletedOrders();
    auto total_profits = order_manager->calculateProfits(completed_orders);
    auto receptreport = std::make_shared<ReceptReport>(emp_id, clock, completed_orders, total_profits);
    return receptreport_manager->addReport(receptreport);
}