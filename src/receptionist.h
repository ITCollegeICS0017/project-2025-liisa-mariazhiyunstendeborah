#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "employees.h"

class Receptionist: public Employee {
    private:
        IClock& clock;
        ReceptReportManager* receptreport_manager;

    public:
        Receptionist(InMemoryOrderManager* order_manager, std::string emp_name, IClock& clock, ReceptReportManager* receptreport_manager) : Employee(order_manager, emp_name), clock(clock), receptreport_manager(receptreport_manager) { }

        std::string getEmpType();

        int makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days);

        void assignOrder(Order* assign, int emp_id);

        int submitReport();
};

#endif