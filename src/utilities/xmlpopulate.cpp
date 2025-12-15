#include "utilities/xmlpopulate.h"
using namespace tinyxml2;

extern OrderRepository order_repository;
extern MaterialRepository material_repository;
extern PhotoReportRepository photoreport_repository;
extern ReceptReportRepository receptreport_repository;
extern Clock clock;

//populationfuncs:
void XMLpopulate::populateClientRepository(ClientRepository &client_repo) { 
	XMLDocument doc;
	XMLError err = doc.LoadFile(clientf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pClients = doc.RootElement();	
	if (!pClients) {
		return;
	}
	
	XMLElement *pClient = pClients->FirstChildElement("client");

	int client_id;
	std::string client_name;

	while (pClient) {
		pClient->QueryIntAttribute("client_id", &client_id);
		XMLElement *pClNameEle = pClient->FirstChildElement("client_name");
		client_name = pClNameEle ? pClNameEle->GetText() : "";

		auto client = std::make_shared<Client>(client_id, client_name);
		client_repo.addExistingClient(client);

		pClient = pClient->NextSiblingElement("client");
	}	
}

void XMLpopulate::populateMaterialRepository(MaterialRepository &mat_repo) {	
	XMLDocument doc;
	XMLError err = doc.LoadFile(matf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pMaterials = doc.RootElement();	
	if (!pMaterials) {
		return;
	}
	
	XMLElement *pMaterial = pMaterials->FirstChildElement("material");

	std::string mat_type;
	int stock_qty;

	while (pMaterial) {
		const char *pMatType = pMaterial->Attribute("mat_type");
		mat_type = pMatType ? pMatType : "";

		XMLElement *pMatEle = pMaterial->FirstChildElement("stock_qty");
		if (!pMatEle) {
			pMaterial = pMaterial->NextSiblingElement("material");
			continue;
		}
		pMatEle->QueryIntText(&stock_qty);

		auto material = std::make_shared<Material>(mat_type, stock_qty);
		mat_repo.addMaterial(material);

		pMaterial = pMaterial->NextSiblingElement("material");
	}	 
}

void XMLpopulate::populateAdministratorRepository(EmployeeRepository &empl_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(adminf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pAdmins = doc.RootElement();	
	if (!pAdmins) {
		return;
	}

	XMLElement *pAdmin = pAdmins->FirstChildElement("administrator");

	int emp_id; //attribute
	std::string emp_name;

	while (pAdmin) {
		pAdmin->QueryIntAttribute("emp_id", &emp_id);

		XMLElement *pENameEle = pAdmin->FirstChildElement("emp_name");
		emp_name = pENameEle ? pENameEle->GetText() : "";

		auto admin = std::make_shared<Administrator>(order_repo, emp_id, emp_name, mat_repo, receptreport_repo, photoreport_repo);

		empl_repo.addExistingEmployee(admin);

		pAdmin = pAdmin->NextSiblingElement("administrator");
	}

}

void XMLpopulate::populatePhotographerRepository(EmployeeRepository &empl_repo) { 	
	XMLDocument doc;
	XMLError err = doc.LoadFile(photogrf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pPhotographers = doc.RootElement();	
	if (!pPhotographers) {
		return;
	}
	
	XMLElement *pPhotographer = pPhotographers->FirstChildElement("photographer");

	int emp_id; //attribute
	std::string emp_name;
	std::string mat_type;
	int stock_qty;
	MaterialRepository *consumed_materials;

	while (pPhotographer) {
		pPhotographer->QueryIntAttribute("emp_id", &emp_id);

		XMLElement *pENameEle = pPhotographer->FirstChildElement("emp_name");
		emp_name = pENameEle ? pENameEle->GetText() : "";

		auto photographer = std::make_shared<Photographer>(order_repository, emp_id, emp_name, clock, material_repository, photoreport_repository);

		XMLElement *pMatsEle = pPhotographer->FirstChildElement("consumed_materials");
		if (!pMatsEle) {
			pPhotographer = pPhotographer->NextSiblingElement("photographer");
			continue;
		}

		XMLElement *pMat = pMatsEle->FirstChildElement("material");

		while (pMat) {
			const char *pMatType = pMat->Attribute("mat_type");
			mat_type = pMatType ? pMatType : "";

			pMat->QueryIntText(&stock_qty);

			photographer->consumeMaterial(mat_type, stock_qty);

			pMat = pMat->NextSiblingElement("material");
		}

		empl_repo.addExistingEmployee(photographer);

		pPhotographer = pPhotographer->NextSiblingElement("photographer");
	}
}

void XMLpopulate::populateReceptionistRepository(EmployeeRepository &empl_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(receptistf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pReceptionists = doc.RootElement();
	if (!pReceptionists) {
		return;
	}
	
	XMLElement *pReceptionist = pReceptionists->FirstChildElement("receptionist");

	int emp_id; //attribute
	std::string emp_name;

	while (pReceptionist) {
		pReceptionist->QueryIntAttribute("emp_id", &emp_id);

		XMLElement *pENameEle = pReceptionist->FirstChildElement("emp_name");
		emp_name = pENameEle ? pENameEle->GetText() : "";

		//order_repository, emp_id, emp_name), clock(clock), receptreport_repository(receptreport_repository

		auto receptionist = std::make_shared<Receptionist>(order_repository, emp_id, emp_name, clock, receptreport_repository);

		empl_repo.addExistingEmployee(receptionist);

		pReceptionist = pReceptionist->NextSiblingElement("receptionist");
	}
}

void XMLpopulate::populateOrderRepository(OrderRepository &order_repo, ClientRepository &client_repo) { 
	XMLDocument doc;
	XMLError err = doc.LoadFile(orderf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pOrders = doc.RootElement();
	if (!pOrders) {
		return;
	}
	
	XMLElement *pOrder = pOrders->FirstChildElement("order");

	std::string temp;
	int tempint;

	int orderid;
	int client_id;
	std::chrono::year_month_day date_created;
	Service service;
	int in_x_days;
	CompletionStatus compl_status;
	float price;
	int assigned_emp_id;
	

	while (pOrder) {
		pOrder->QueryIntAttribute("orderid", &orderid);

		const char *pDate = pOrder->Attribute("date_created");
		temp = pDate ? pDate : "";
		date_created = CustomFuncs::DatefromStringStream(temp);
		
		pOrder->QueryIntAttribute("client_id", &client_id);
		if (!client_repo.findClient(client_id)) {
			pOrder = pOrder->NextSiblingElement("order");
			continue;
		}

		auto client = client_repo.findClient(client_id);

		XMLElement *pOEle = pOrder->FirstChildElement("service");
		pOEle->QueryIntText(&tempint);
		service = CustomFuncs::ServicefromInt(tempint);
		
		pOEle = pOrder->FirstChildElement("in_x_days");
		pOEle->QueryIntText(&in_x_days);

	pOEle = pOrder->FirstChildElement("compl_status");
		pOEle->QueryIntText(&tempint);
		compl_status = CustomFuncs::ComplStatusfromInt(tempint);

		pOEle = pOrder->FirstChildElement("price");
		if (!pOEle) {
			pOrder = pOrder->NextSiblingElement("order");
			continue;
		}

		temp = pOEle ? pOEle->GetText() : "";
		price = std::stof(temp);

		pOEle = pOrder->FirstChildElement("assigned_emp_id");
		pOEle->QueryIntText(&assigned_emp_id);

		auto order = std::make_shared<Order>(client, service, in_x_days, date_created, orderid, compl_status, price, assigned_emp_id);

		order_repo.addOrder(order);

		pOrder = pOrder->NextSiblingElement("order");
	}
}

void XMLpopulate::populateReceptReportRepository(ReceptReportRepository &receptreport_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(recrepf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pReports = doc.RootElement();
	if (!pReports) {
		return;
	}

	XMLElement *pReport = pReports->FirstChildElement("receptreport");

	std::string temp;

	int reportid;
	int creator_id;
	std::chrono::year_month_day date_created;
	int total_revenue;
	int orderid;

	while (pReport) {
		pReport->QueryIntAttribute("reportid", &reportid);

		pReport->QueryIntAttribute("creator_id", &creator_id);

		const char *pDate = pReport->Attribute("date_created");
		temp = pDate ? pDate : "";
		date_created = CustomFuncs::DatefromStringStream(temp);

		XMLElement *pOEle = pReport->FirstChildElement("compl_orders");
		pOEle->QueryIntAttribute("total_revenue", &total_revenue);

		auto report = std::make_shared<ReceptReport>(reportid, creator_id, date_created, total_revenue);

		XMLElement *pCompOrder = pOEle->FirstChildElement("order");
		while (pCompOrder) {
			pCompOrder->QueryIntAttribute("orderid", &orderid);
			if (!order_repo.findOrder(orderid)) {
				pReport = pReport->NextSiblingElement("receptreport");
				continue;
			}

			auto order = order_repo.findOrder(orderid);

			report->compl_orders.insert({orderid, order});

			pCompOrder = pCompOrder->NextSiblingElement("order");
		}
		
		receptreport_repo.addExistingReport(report);

		pReport = pReport->NextSiblingElement("receptreport");
	}
}

void XMLpopulate::populatePhotoReportRepository(PhotoReportRepository &photoreport_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(phorepf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pReports = doc.RootElement();
	if (!pReports) {
		return;
	}

	XMLElement *pReport = pReports->FirstChildElement("photoreport");

	std::string temp;

	int reportid;
	int creator_id;
	std::chrono::year_month_day date_created;
	std::string mat_type;
	int stock_qty;

	while (pReport) {
		pReport->QueryIntAttribute("reportid", &reportid);

		pReport->QueryIntAttribute("creator_id", &creator_id);

		const char *pDate = pReport->Attribute("date_created");
		temp = pDate ? pDate : "";
		date_created = CustomFuncs::DatefromStringStream(temp);

		XMLElement *pOEle = pReport->FirstChildElement("consumed_materials");

		auto report = std::make_shared<PhotoReport>(reportid, creator_id, date_created);

		XMLElement *pMat = pOEle->FirstChildElement("material");
		while (pMat) {
			const char *pMatType = pMat->Attribute("mat_type");
			mat_type = pMatType ? pMatType : "";
			
			pMat->QueryIntText(&stock_qty);

			auto material = std::make_shared<Material>(mat_type, stock_qty);

			report->consumed_materials.insert({material, stock_qty});

			pMat = pMat->NextSiblingElement("material");
		}
		
		photoreport_repo.addExistingReport(report);

		pReport = pReport->NextSiblingElement("photoreport");
	}
}

