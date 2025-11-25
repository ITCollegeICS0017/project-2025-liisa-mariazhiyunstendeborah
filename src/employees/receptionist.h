#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#include "core/employee.h"
#include "utilities/exceptions.h"

//employee receptionist, creates & assigns orders and submits receptionist reports
class Receptionist: public Employee {
    private:
        IClock& clock;
        ReceptReportRepository* receptreport_repository;

    public:
        Receptionist(OrderRepository* order_repository, std::string emp_name, IClock& clock, ReceptReportRepository* receptreport_repository) : Employee(order_repository, emp_name), clock(clock), receptreport_repository(receptreport_repository) { }

        //returns receptionist class name
        std::string getEmpType();

        //creates an order
        int makeOrder(std::shared_ptr<Client> client, Service service, unsigned int in_x_days);

        //assigns an order to a specified photographer
        void assignOrder(Order* assign, int emp_id);

        //submits a receptionist report based on orders obtained from order repository
        //currently does not consider date of creation but likely should in future so as to avoid submitting old completed orders
        int submitReport();
};

#endif