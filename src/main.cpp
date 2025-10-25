#include "material.h"
#include "client.h"
#include "employees.h"
#include "order.h"
#include "employeemanager.h"

#include <iostream>

int main() {
//example implementation, create Material, Order, Receptionist, Photographer, Administrator, assignOrder,
//switchOrderStatus, consumeMaterial, submit ReceptReport, submit PhotoReport, listMaterials
	OrderManager* order_manager = new OrderManager();
	ReceptReportManager* receptreport_manager = new ReceptReportManager();
	PhotoReportManager* photoreport_manager = new PhotoReportManager();
	EmployeeManager* employee_manager = new EmployeeManager();

	Material material("paper", 20);
	Material material1("film", 10);
	auto client = std::make_shared<Client>("Bones Jones");
	Service service = Photo_printing;
	Service service2 = Film_devel;
	int in_x_days = 3;

	Receptionist receptionist(order_manager, receptreport_manager);
	auto recept_ptr = std::make_shared<Receptionist>(order_manager, receptreport_manager);
	int receptionist_id = employee_manager->addEmployee(recept_ptr);
	std::cout << "Made receptionist with employee id: " << receptionist_id << "\n";

	int orderid = receptionist.makeOrder(client, service, in_x_days);
	Order* order = order_manager->findOrder(orderid);
	int orderid1 = receptionist.makeOrder(client, service2, 1);
	Order* order1 = order_manager->findOrder(orderid1);
	std::cout << "Price of first order(" << orderid << "): " << order->price << "\n";
	std::cout << "Price of second order(" << orderid1 << "): " << order1->price << "\n";

	Photographer photographer(order_manager, photoreport_manager);
	auto photographer_ptr = std::make_shared<Photographer>(order_manager, photoreport_manager);
	int photographer_id = employee_manager->addEmployee(photographer_ptr);
	std::cout << "Made photographer with employee id: " << photographer_id << "\n";

	receptionist.assignOrder(order, photographer_id);
	receptionist.assignOrder(order1, photographer_id);
	CompletionStatus compl_status = Completed;
	photographer.switchOrderStatus(order, compl_status);
	photographer.consumeMaterial("paper", 10);
	photographer.switchOrderStatus(order1, compl_status);
	photographer.consumeMaterial("film", 3);

	int photoreportid = photographer.submitReport(photographer_id);
	int receptreportid = receptionist.submitReport(receptionist_id);

	std::cout << "Total revenue of completed orders: " << receptreport_manager->findReport(receptreportid)->total_revenue << "\n";

	std::cout << "Consumed materials: ";
	for (const auto& [mat_type, quantity] : photoreport_manager->findReport(photoreportid)->consumed_materials) {
	    std::cout << "" << mat_type << ": " << quantity << "\n";
	}
}
