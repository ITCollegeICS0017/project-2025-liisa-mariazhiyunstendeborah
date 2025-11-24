#include "employeerepository.h"

const std::map<int, std::shared_ptr<Employee>>&
EmployeeRepository::getEmployees() const {
  return employees;
}

// Upon not finding an employee, returns a nullptr rather than return an error,
// so it's easier to use in other functions for checking if an employee exists.
Employee* EmployeeRepository::findEmployee(int emp_id) {
  auto iter = employees.find(emp_id);
  if (iter != employees.end()) {
    return iter->second.get();
  }
  return nullptr;
}

// checks if employee's emp_id is the default, if so the employee's id is set to
// next_id (which is then incremented) and added to the repository if employee's
// emp_id is not the default, assumes employee has already been added and throws
// an error
int EmployeeRepository::addEmployee(std::shared_ptr<Employee> employee) {
  if (employee->emp_id == 0) {
    int emp_id = next_id++;
    employee->emp_id = emp_id;
    employees.insert({emp_id, employee});
    return emp_id;
  } else {
    throw std::invalid_argument("Employee already exists!");
  }
}

void EmployeeRepository::editEmployee(
    int emp_id, std::shared_ptr<Employee> updated_employee) {
  if (!findEmployee(emp_id)) {
    throw std::invalid_argument("Employee not found!");
  } else {
    employees.at(emp_id) = updated_employee;
  }
}

void EmployeeRepository::deleteEmployee(int emp_id) {
  if (!findEmployee(emp_id)) {
    throw std::invalid_argument("Employee does not exist to be deleted!");
  } else {
    employees.erase(emp_id);
  }
}
