#include "material.h"
#include "client.h"
#include "clientmanager.h"
#include "employees.h"
#include "order.h"
#include "employeemanager.h"

#include <iostream>

int main() {
//example implementation, create Material, Order, Receptionist, Photographer, Administrator, assignOrder,
//switchOrderStatus, consumeMaterial, submit ReceptReport, submit PhotoReport, listMaterials
//Todo: Add employee names and removing materials, employees, reports implementation
	OrderManager* order_manager = new OrderManager();
	ReceptReportManager* receptreport_manager = new ReceptReportManager();
	PhotoReportManager* photoreport_manager = new PhotoReportManager();
	EmployeeManager* employee_manager = new EmployeeManager();
	MaterialManager* material_manager = new MaterialManager();
	ClientManager* client_manager = new ClientManager();

	auto material = std::make_shared<Material>("paper", 20);
	auto material1 = std::make_shared<Material>("film", 10);
	auto material2 = std::make_shared<Material>("food", 500);
	auto admin = std::make_shared<Administrator>(order_manager, "Binkle Bonkler", material_manager, receptreport_manager, photoreport_manager);
	int admin_id = employee_manager->addEmployee(admin);
	std::cout << "Made administrator with employee id: " << admin_id << "\n";

	admin->addMaterial(material, 10);
	admin->addMaterial(material, 10);
	admin->addMaterial(material1, 10);
	admin->addMaterial(material2, 10);

	std::vector<std::shared_ptr<Material>> materials = admin->listMaterials();
	std::cout << "Materials: \n";

	for (size_t i = 0; i < materials.size(); i++) {
		auto& mat = materials[i];
		std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
	}

//Todo: this doesn't work :(
	admin->removeMaterial(material2->mat_type);
	materials = admin->listMaterials();
	std::cout << "Materials after removing food: \n";

	for (size_t i = 0; i < materials.size(); i++) {
		auto& mat = materials[i];
		std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
	}

	auto client = std::make_shared<Client>("Bones Jones");
	client_manager->addClient(client);

	Service service = Photo_printing;
	Service service2 = Film_devel;
	int in_x_days = 3;

	auto receptionist = std::make_shared<Receptionist>(order_manager, "Schmongler", receptreport_manager);
	int receptionist_id = employee_manager->addEmployee(receptionist);
	std::cout << "Made receptionist with employee id: " << receptionist_id << "\n";

	int orderid = receptionist->makeOrder(client, service, in_x_days);
	Order* order = order_manager->findOrder(orderid);
	if (!order) {
    std::cerr << "Order not found!" << std::endl;
	}
	int orderid1 = receptionist->makeOrder(client, service2, 1);
	Order* order1 = order_manager->findOrder(orderid1);
	if (!order1) {
		std::cerr << "Order not found!" << std::endl;
	}

	std::map<int, std::shared_ptr<Order>> orders =  order_manager->getOrders();
	std::cout << "Current orders: " << "\n";

	for (auto order : orders) {
	std::cout << "Orderid: " << order.first << ", Client's name: " << order.second->client->client_name << ", date created: " << order.second->date_created;
	}

	std::cout << "Price of first order(" << orderid << "): " << order->price << "\n";
	std::cout << "Price of second order(" << orderid1 << "): " << order1->price << "\n";


	auto photographer = std::make_shared<Photographer>(order_manager, "Kababoomgler", material_manager, photoreport_manager);
	int photographer_id = employee_manager->addEmployee(photographer);
	std::cout << "Made photographer with employee id: " << photographer_id << "\n";

	receptionist->assignOrder(order, photographer_id);
	receptionist->assignOrder(order1, photographer_id);

	CompletionStatus compl_status = Completed;
	photographer->switchOrderStatus(order, compl_status);
	photographer->consumeMaterial(material, 10);
	photographer->switchOrderStatus(order1, compl_status);
	photographer->consumeMaterial(material1, 3);

	std::cout << "Orders were completed." << "\n";

	std::cout << "Materials after consumption: \n";

	for (size_t i = 0; i < materials.size(); i++) {
		auto& mat = materials[i];
		std::cout << mat->mat_type << ", in stock: " << mat->stock_qty << "\n";
	}

	int photoreportid = photographer->submitReport(photographer_id);
	int receptreportid = receptionist->submitReport(receptionist_id);

	std::cout << "Total revenue of completed orders: " << receptreport_manager->findReport(receptreportid)->total_revenue << "\n";

	std::cout << "Consumed materials: " << "\n";
	for (const auto& [material, quantity] : photoreport_manager->findReport(photoreportid)->consumed_materials) {
	    std::cout << material->mat_type << ": " << quantity << "\n";
	}

	std::cout << "Receptionist reports that exist: " << "\n";
   for (const auto& [reportid, reportPtr] : admin->listReceptReports()) {
		std::cout << "Report ID: " << reportid << "\n";
		std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
		std::cout << "Date created: " << reportPtr->date_created << "\n";
   }

	std::cout << "Photographer reports that exist: " << "\n";
	for (const auto& [reportid, reportPtr] : admin->listPhotoReports()) {
		std::cout << "Report ID: " << reportid << "\n";
		std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
		std::cout << "Date created: " << reportPtr->date_created << "\n";
	}
}
