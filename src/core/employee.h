#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "order.h"
#include "material.h"
#include "reports.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "utilities/clocks.h"
#include "repos/employeerepository.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>


//abstract class for employees
class Employee {
    protected:
        OrderRepository* order_repository;

    public:
        //employee id set to a valid value once added to the employee repository
        int emp_id = 0;
        std::string emp_name;

        Employee(OrderRepository* order_repository, std::string emp_name) : order_repository(order_repository), emp_name(emp_name) { }

        virtual ~Employee() = default;

        //virtual function to get an Employee's type
        virtual std::string getEmpType() = 0;
};

#endif
