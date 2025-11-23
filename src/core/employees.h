#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "order.h"
#include "material.h"
#include "reports.h"
#include "managers/ordermanager.h"
#include "managers/reportmanager.h"
#include "managers/materialmanager.h"
#include "utilities/clocks.h"
#include "managers/employeemanager.h"

#include <string>
#include <map>
#include <memory>
#include <iostream>


//Note: most likely, when there are no employees, the
//first employee should always be the administrator

class Employee {
    protected:
        InMemoryOrderManager* order_manager;

    public:
        int emp_id = 0;
        std::string emp_name;

        Employee(InMemoryOrderManager* order_manager, std::string emp_name) : order_manager(order_manager), emp_name(emp_name) { }

        virtual std::string getEmpType() = 0;

        virtual ~Employee() = default;
};

#endif
