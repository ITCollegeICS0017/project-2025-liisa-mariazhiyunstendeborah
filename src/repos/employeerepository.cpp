#include "employeerepository.h"

const std::map<int, std::shared_ptr<Employee>>& EmployeeManager::getEmployees() const  {
    return employees;
}

Employee* EmployeeManager::findEmployee(int emp_id) {
    auto iter = employees.find(emp_id);
    if (iter != employees.end()) {
        return iter->second.get();
    }
    return nullptr;
}

int EmployeeManager::addEmployee(std::shared_ptr<Employee> employee)  {
    if (employee->emp_id == 0) {
    int emp_id = next_id++;
    employee->emp_id = emp_id;
    employees.insert({emp_id, employee});
    return emp_id;
    } else {
        throw std::invalid_argument("Employee already exists!");
    }
}

void EmployeeManager::editEmployee(int emp_id, std::shared_ptr<Employee> updated_employee)  {
    if (!findEmployee(emp_id)) {
        throw std::invalid_argument("Employee not found!");
    } else {
        employees.at(emp_id) = updated_employee;
    }
}

void EmployeeManager::deleteEmployee(int emp_id)  {
    if (!findEmployee(emp_id)) {
        throw std::invalid_argument("Employee does not exist to be deleted!");
    } else {
        employees.erase(emp_id);
    }
}
