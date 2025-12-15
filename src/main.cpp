#include <iostream>

#include "core/client.h"
#include "core/employee.h"
#include "core/material.h"
#include "core/order.h"
#include "employees/administrator.h"
#include "employees/photographer.h"
#include "employees/receptionist.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "ui/uimanager.h"
#include "utilities/clocks.h"

int main() {
  // example implementation, create Material, Order, Receptionist, Photographer,
  // Administrator, assignOrder, switchOrderStatus, consumeMaterial, submit
  // ReceptReport, submit PhotoReport, listMaterials

  SystemClock clock;
  OrderRepository* order_repository = new OrderRepository();
  ReceptReportRepository* receptreport_repository =
      new ReceptReportRepository();
  PhotoReportRepository* photoreport_repository = new PhotoReportRepository();
  EmployeeRepository* employee_repository = new EmployeeRepository();
  MaterialRepository* material_repository = new MaterialRepository();
  ClientRepository* client_repository = new ClientRepository();
  UImanager* uimanager = new UImanager(
      order_repository, client_repository, employee_repository,
      photoreport_repository, receptreport_repository, material_repository);
      
  std::cout << "Example data initialized";
  uimanager->view_main();
}
