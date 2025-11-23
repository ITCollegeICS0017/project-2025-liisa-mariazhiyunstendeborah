#ifndef IEMPLOYEEREPOSITORY_H
#define IEMPLOYEEREPOSITORY_H

#include <map>
#include <memory>

class Employee;
class IEmployeeManager {
    public:
        IEmployeeManager() = default;

        virtual int addEmployee(std::shared_ptr<Employee> employee) = 0;

        virtual void editEmployee(int emp_id, std::shared_ptr<Employee> updated_employee) = 0;

        virtual void deleteEmployee(int emp_id) = 0;
};

#endif