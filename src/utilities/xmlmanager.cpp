#include "utilities/xmlmanager.h"
using namespace tinyxml2;

//populationfuncs:
void populateClientRepository(ClientRepository &client_repo) { 
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

void populateMaterialRepository(MaterialRepository &mat_repo) {	
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

void populatePhotographerRepository(EmployeeRepository &empl_repo) { 	
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

		//IMPORTANT!!! define these
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

void populateReceptionistRepository(EmployeeRepository &empl_repo) {
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

void populateOrderRepository(OrderRepository &order_repo) { 
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
		date_created = DateFromStringStream(temp);
		
		pOrder->QueryIntAttribute("client_id", &client_id);
		if (!findClient(client_id)) {
			pOrder = pOrder->NextSiblingElement("order");
			continue;
		}

		auto client = client_repo.findClient(client_id);

		XMLElement *pOEle = pOrder->FirstChildElement("service");
		pOEle->QueryIntText(&tempint);
		service = ServicefromInt(tempint);
		
		pOEle = pOrder->FirstChildElement("in_x_days");
		pOEle->QueryIntText(&in_x_days);

		pOEle = pOrder->FirstChildElement("compl_status");
		pOEle->QueryIntText(&tempint);
		compl_status = ComplStatusfromInt(tempint);

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

void populateReceptReportRepository(ReceptReportRepository &receptreport_repo) {
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
		date_created = DateFromStringStream(temp);

		XMLElement *pOEle = pReport->FirstChildElement("compl_orders");
		pOEle->QueryIntAttribute("total_revenue", &total_revenue);

		auto report = std::make_shared<ReceptReport>(reportid, creator_id, date_created, total_revenue);

		XMLElement *pCompOrder = pOEle->FirstChildElement("order");
		while (pCompOrder) {
			pCompOrder->QueryIntAttribute("orderid", &orderid);
			if (!findOrder(orderid)) {
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

void populatePhotoReportRepository(PhotoReportRepository &photoreport_repo) {
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
		date_created = DateFromStringStream(temp);

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

//saving funcs
void saveClientRepository(ClientRepository &client_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(clientf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pClients = doc.RootElement();	

	for (auto const& [client_id, client] : client_repo.clients) {
		XMLNode *pClient = doc.NewElement("client");

		pClient->SetAttribute("client_id", client_id);

		pClients->InsertEndChild(pClient);

		XMLElement *pElement = doc.NewElement("client_name");

		pElement-> SetText(client->client_name);

		pClient->InsertEndChild(pElement);
	}
}

void saveMaterialRepository(MaterialRepository &mat_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(clientf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pMats = doc.RootElement();

	for (auto const& mat : mat_repo.materials) {
		XMLNode *pMat = doc.NewElement("material");

		pMat->SetAttribute ("mat_type", mat_repo.materials[i]->mat_type);

		pMats->InsertEndChild(pMat);

		XMLElement *pElement = doc.NewElement("stock_qty");
		pElement-> SetText(mat_repo.materials[i]->stock_qty);

		pMat-> InsertEndChild(pElement);
	}
}

void savePhotographerRepository(EmployeeRepository &empl_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(clientf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pPhotographer = doc.RootElement();

	std::map<int, std::shared_ptr<Employee>> photographers = empl_repo.getEmpofType("Photographer");

	for (auto const& [phtgr_id, phtgr] : photographers) {
		XMLNode *pPhtgr = doc.NewElement("photographer");

		pPhtgr->SetAttribute ("emp_id", phtgr_id);

		pPhtgr->InsertEndChild(pPhtgr);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(phtgr->emp_name);

		pPhgr->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("consumed_materials");

		pPhgr->InsertEndChild(pElement);

		for (auto const& material : phtgr->consumed_materials) {
			XMLElement *pElement = doc.NewElement("material");

			pElement->SetAttribute ("mat_type", material->mat_type);

			pElement->SetText(material->stock_qty);	
		}	
	}
}

void saveReceptionistRepository(EmployeeRepository &empl_repo) { }

void saveOrderRepository(OrderRepository &order_repo) { }

void saveReceptReportRepository(ReceptReportRepository &receptreport_repo) { }

void savePhotoReportRepository(PhotoReportRepository &photoreport_repo) { }
