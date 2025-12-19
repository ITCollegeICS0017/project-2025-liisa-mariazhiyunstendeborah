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
#include "utilities/xmlpopulate.h"
#include "utilities/xmlsave.h"

int main() {
  // example implementation, create Material, Order, Receptionist, Photographer,
  // Administrator, assignOrder, switchOrderStatus, consumeMaterial, submit
  // ReceptReport, submit PhotoReport, listMaterials
  	const char *clientf = "xmldocs/clients.xml";
	const char *matf = "xmldocs/materials.xml";
	const char *adminf = "xmldocs/administrators.xml";
	const char *photogrf = "xmldocs/photographers.xml";
	const char *receptistf = "xmldocs/receptionists.xml";
	const char *orderf = "xmldocs/orders.xml";
	const char *recrepf = "xmldocs/receptreports.xml";
	const char *phorepf = "xmldocs/photoreports.xml";

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

	
	//auto material = std::make_shared<Material>("paper");
	//auto material1 = std::make_shared<Material>("film");
	//auto material2 = std::make_shared<Material>("food");
	//auto admin = std::make_shared<Administrator>(
	//  order_repository, "Binkle Bonkler", material_repository,
	//  receptreport_repository, photoreport_repository);
	//employee_repository->addEmployee(admin);
	//// Made administrator with employee id: " << admin_id << "\n";


	//admin->addMaterial(material->mat_type, 10);
	//admin->addMaterial(material->mat_type, 10);
	//admin->addMaterial(material1->mat_type, 10);
	//admin->addMaterial(material2->mat_type, 10);
	
	//XMLpopulate::populateClientRepository(*client_repository, clientf);

	//XMLpopulate::populateMaterialRepository(*material_repository, matf);

	//XMLpopulate::populateAdministratorRepository(*employee_repository, *order_repository, *material_repository, *receptreport_repository, *photoreport_repository, adminf);

	//XMLpopulate::populatePhotographerRepository(*employee_repository, *order_repository, *material_repository, *photoreport_repository, clock, photogrf);

	//XMLpopulate::populateReceptionistRepository(*employee_repository, *order_repository, *material_repository, *receptreport_repository, clock, receptistf);

	//XMLpopulate::populateOrderRepository(*order_repository, *client_repository, orderf);

	//XMLpopulate::populateReceptReportRepository(*receptreport_repository, *order_repository, recrepf);

	//XMLpopulate::populatePhotoReportRepository(*photoreport_repository, *order_repository, phorepf);

	
	XMLsave::saveClientRepository(*client_repository, clientf);

	XMLsave::saveMaterialRepository(*material_repository, matf);

	XMLsave::saveAdministratorRepository(*employee_repository, adminf);

	XMLsave::savePhotographerRepository(*employee_repository, photogrf);

	XMLsave::saveReceptionistRepository(*employee_repository, receptistf);

	XMLsave::saveOrderRepository(*order_repository, orderf);

	XMLsave::saveReceptReportRepository(*receptreport_repository, recrepf);

	XMLsave::savePhotoReportRepository(*photoreport_repository, phorepf);



  std::cout << "Example data initialized";
  uimanager->view_main();
}
