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
	UImanager* uimanager = new UImanager(order_repository, client_repository, employee_repository, photoreport_repository, receptreport_repository, material_repository);
	ViewManager* viewmanager = new ViewManager(uimanager);
  auto material = std::make_shared<Material>("paper");
  auto material1 = std::make_shared<Material>("film");
  auto material2 = std::make_shared<Material>("food");
  auto admin = std::make_shared<Administrator>(
      order_repository, "Binkle Bonkler", material_repository,
      receptreport_repository, photoreport_repository);
  // int admin_id = employee_repository->addEmployee(admin);
  // std::cout << "Made administrator with employee id: " << admin_id << "\n";


  admin->addMaterial(material->mat_type, 10);
  admin->addMaterial(material->mat_type, 10);
  admin->addMaterial(material1->mat_type, 10);
  admin->addMaterial(material2->mat_type, 10);

  std::vector<std::shared_ptr<Material>> materials = admin->listMaterials();
  // std::cout << "Materials: \n";

  // for (size_t i = 0; i < materials.size(); i++) {
  //	auto& mat = materials[i];
  //	std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
  // }

  admin->deleteMaterial(material2->mat_type);
  materials = admin->listMaterials();
  // std::cout << "Materials after removing food: \n";
  // for (size_t i = 0; i < materials.size(); i++) {
  //	auto& mat = materials[i];
  //	std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
  // }

  auto client = std::make_shared<Client>("Bones Jones");
  client_repository->addClient(client);

  Service service = Photo_printing;
  Service service2 = Film_devel;
  int in_x_days = 3;

  auto receptionist = std::make_shared<Receptionist>(
      order_repository, "Schmongler", clock, receptreport_repository);
  // int receptionist_id = employee_repository->addEmployee(receptionist);
  // std::cout << "Made receptionist with employee id: " << receptionist_id <<
  // "\n";

  auto badreceptionist =
      std::make_shared<Receptionist>(order_repository, "Terrible Receptionist",
                                     clock, receptreport_repository);
  int badreceptionist_id = employee_repository->addEmployee(badreceptionist);
  // std::cout << "Made bad receptionist with employee id: " <<
  // badreceptionist_id << "\n";

  std::map<int, std::shared_ptr<Employee>> employees =
      employee_repository->getEmployees();
  // std::cout << "List of employees: " << "\n";

  // for (auto employee : employees) {
  // std::cout << "Employee id: " << employee.first << ", Employee's name: " <<
  // employee.second->emp_name << "\n";
  // }

  employee_repository->deleteEmployee(badreceptionist_id);

  employees = employee_repository->getEmployees();
  // std::cout << "List of employees after removing terrible receptionist: " <<
  // "\n";

  // for (auto employee : employees) {
  // std::cout << "Employee id: " << employee.first << ", Employee's name: " <<
  // employee.second->emp_name << "\n";
  // }

  int orderid = receptionist->makeOrder(client, service, in_x_days);
  Order* order = order_repository->findOrder(orderid);
  if (!order) {
    std::cerr << "Order not found!" << std::endl;
  }
  int orderid1 = receptionist->makeOrder(client, service2, 1);
  Order* order1 = order_repository->findOrder(orderid1);
  if (!order1) {
    std::cerr << "Order not found!" << std::endl;
  }

  std::map<int, std::shared_ptr<Order>> orders = order_repository->getOrders();
  // std::cout << "Current orders: " << "\n";

  // for (auto order : orders) {
  // std::cout << "Orderid: " << order.first << ", Client's name: " <<
  // order.second->client->client_name << ", date created: " <<
  // order.second->date_created << "\n";
  // }

  // std::cout << "Price of first order(" << orderid << "): " << order->price <<
  // "\n"; std::cout << "Price of second order(" << orderid1 << "): " <<
  // order1->price << "\n";

  auto photographer = std::make_shared<Photographer>(
      order_repository, "Kababoomgler", clock, material_repository,
      photoreport_repository);
  int photographer_id = employee_repository->addEmployee(photographer);
  // std::cout << "Made photographer with employee id: " << photographer_id <<
  // "\n";

  receptionist->assignOrder(order, photographer_id);
  receptionist->assignOrder(order1, photographer_id);

  CompletionStatus compl_status = Completed;
  photographer->switchOrderStatus(order, compl_status);
  photographer->consumeMaterial(material->mat_type, 10);
  photographer->switchOrderStatus(order1, compl_status);
  photographer->consumeMaterial(material1->mat_type, 3);

  // std::cout << "Orders were completed." << "\n";

  // std::cout << "Materials after consumption: \n";
  materials = admin->listMaterials();
  // for (size_t i = 0; i < materials.size(); i++) {
  //	auto& mat = materials[i];
  //	std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
  // }

  // int photoreportid = photographer->submitReport();
  int receptreportid = receptionist->submitReport();

  // std::cout << "Total revenue of completed orders: " <<
  // receptreport_repository->findReport(receptreportid)->total_revenue << "\n";

  ////std::cout << "Consumed materials: " << "\n";
  // for (const auto& [material, quantity] :
  // photoreport_repository->findReport(photoreportid)->consumed_materials) {
  //     std::cout << material->mat_type << ": " << quantity << "\n";
  // }

  // std::cout << "Receptionist reports that exist: " << "\n";
  // for (const auto& [reportid, reportPtr] : admin->listReceptReports()) {
  //  	std::cout << "Report ID: " << reportid << "\n";
  //  	std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
  //  	std::cout << "Date created: " << reportPtr->date_created << "\n";
  // }

  // std::cout << "Photographer reports that exist: " << "\n";
  // for (const auto& [reportid, reportPtr] : admin->listPhotoReports()) {
  //	std::cout << "Report ID: " << reportid << "\n";
  //	std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
  //	std::cout << "Date created: " << reportPtr->date_created << "\n";
  // }


	//std::cout << "Photographer reports that exist: " << "\n";
	//for (const auto& [reportid, reportPtr] : admin->listPhotoReports()) {
	//	std::cout << "Report ID: " << reportid << "\n";
	//	std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
	//	std::cout << "Date created: " << reportPtr->date_created << "\n";
	//}


	receptreport_repository->deleteReport(receptreportid);
	//std::cout << "Removed receptionist's report." << "\n";
	//std::cout << "Receptionist reports that exist: " << "\n";
	//for (const auto& [reportid, reportPtr] : admin->listReceptReports()) {
	//	std::cout << "Report ID: " << reportid << "\n";
	//	std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
	//	std::cout << "Date created: " << reportPtr->date_created << "\n";
	//}
	//std::cout << "\n\n\n";
	std::cout << "Example data initialized";
	viewmanager->viewMain();

}
