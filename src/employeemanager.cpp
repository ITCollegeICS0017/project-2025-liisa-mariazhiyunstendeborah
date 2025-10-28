#include "employeemanager.h"

const std::map<int, std::shared_ptr<Employee>>& EmployeeManager::getEmployees() const  {
    //E: ? if employees is empty, has invalid values...?
    return employees;
}

Employee* EmployeeManager::findEmployee(int emp_id) {
    auto iter = employees.find(emp_id);
    if (iter != employees.end()) {
        return iter->second.get();
    }
    //E: handle this error properly
    return nullptr;
}

int EmployeeManager::addEmployee(std::shared_ptr<Employee> employee)  {
    int emp_id = next_id++;
    employee->emp_id = emp_id;
    employees.insert({emp_id, employee});
    return emp_id;
    //E: ? copies of employees possible?
}

void EmployeeManager::editEmployee(int emp_id, std::shared_ptr<Employee> updated_employee)  {
    employees.at(emp_id) = updated_employee;
    //E: if emp_id not found
}

void EmployeeManager::deleteEmployee(int emp_id)  {
    employees.erase(emp_id);
    //E: if emp_id not found
}
