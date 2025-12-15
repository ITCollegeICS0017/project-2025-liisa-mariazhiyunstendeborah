#ifndef EMPLOYEEREPOSITORY_H
#define EMPLOYEEREPOSITORY_H

#include <string>
#include "interfaces/iemployeerepository.h"
#include "core/employee.h"
#include "utilities/exceptions.h"

//in memory Employee Repository, sets employee ids, performs CRUD operations and finds employees
class EmployeeRepository : public IEmployeeRepository {
    private:
        std::map<int, std::shared_ptr<Employee>> employees;
        //ids are set incrementally starting from next_id
        int next_id = 1;

    public:
        const std::map<int, std::shared_ptr<Employee>>& getEmployees() const;

        Employee* findEmployee(int emp_id);

        int addEmployee(std::shared_ptr<Employee> employee);

        void addExistingEmployee(std::shared_ptr<Employee> employee);

        void editEmployee(int emp_id, std::shared_ptr<Employee> updated_employee);

        void deleteEmployee(int emp_id);
};

#endif
