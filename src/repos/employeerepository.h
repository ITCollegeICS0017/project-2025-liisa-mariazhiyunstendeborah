#ifndef EMPLOYEEREPOSITORY_H
#define EMPLOYEEREPOSITORY_H

#include <stdexcept>
#include "interfaces/iemployeerepository.h"
#include "core/employee.h"

class EmployeeManager {
    private:
        std::map<int, std::shared_ptr<Employee>> employees;
        int next_id = 1;


    public:
        const std::map<int, std::shared_ptr<Employee>>& getEmployees() const;

        Employee* findEmployee(int emp_id);

        int addEmployee(std::shared_ptr<Employee> employee);

        void editEmployee(int emp_id, std::shared_ptr<Employee> updated_employee);

        void deleteEmployee(int emp_id);
};

#endif
