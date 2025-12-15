#include "utilities/xmlsave.h"
using namespace tinyxml2;

extern OrderRepository order_repository;
extern MaterialRepository material_repository;
extern PhotoReportRepository photoreport_repository;
extern ReceptReportRepository receptreport_repository;
extern Clock clock;

//saving funcs
void XMLsave::saveClientRepository(ClientRepository &client_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(clientf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pClients = doc.RootElement();	

	for (auto const& [client_id, client] : client_repo.getClients()) {
		XMLElement *pClient = doc.NewElement("client");

		pClient->SetAttribute("client_id", client_id);

		pClients->InsertEndChild(pClient);

		XMLElement *pElement = doc.NewElement("client_name");

		pElement-> SetText(client->client_name);

		pClient->InsertEndChild(pElement);
	}

	doc.SaveFile(clientf);
}

void XMLsave::saveMaterialRepository(MaterialRepository &mat_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(matf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pMats = doc.RootElement();

	for (auto const& mat : mat_repo.getMaterials()) {
		XMLElement *pMat = doc.NewElement("material");

		pMat->SetAttribute ("mat_type", mat->mat_type);

		pMats->InsertEndChild(pMat);

		XMLElement *pElement = doc.NewElement("stock_qty");
		pElement-> SetText(mat->stock_qty);

		pMat-> InsertEndChild(pElement);
	}

	doc.SaveFile(matf);
}

void XMLsave::saveAdministratorRepository(EmployeeRepository &empl_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(adminf);
	if (err != XML_SUCCESS) {
		return;
	}

	XMLElement *pAdmins = doc.RootElement();	

	std::map<int, std::shared_ptr<Administrator>> admins = empl_repo.getEmpofType("Administrator");

	for (auto const& [admin_id, admin] : admins) {
			XMLElement *pAdmin = doc.NewElement("administrator");

			pAdmin->SetAttribute ("emp_id", admin_id);

			pAdmins->InsertEndChild(pAdmin);

			XMLElement *pElement = doc.NewElement("emp_name");
			pElement->SetText(admin->emp_name);

			pAdmin->InsertEndChild(pElement);
	}

	doc.SaveFile(adminf);
}


void XMLsave::savePhotographerRepository(EmployeeRepository &empl_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(photogrf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pPhtgrs = doc.RootElement();

	std::map<int, std::shared_ptr<Photographer>> photographers = empl_repo.getEmpofType("Photographer");

	for (auto const& [photographer_id, photographer] : photographers) {
		XMLElement *pPhtgr = doc.NewElement("photographer");

		pPhtgr->SetAttribute ("emp_id", photographer_id);

		pPhtgrs->InsertEndChild(pPhtgr);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(photographer->emp_name);

		pPhtgr->InsertEndChild(pElement);

		XMLElement *pConsMats = doc.NewElement("consumed_materials");
		pPhtgr->InsertEndChild(pConsMats);

		for (auto const& material : photographer->consumed_materials->materials) {
			XMLElement *pSubEle = doc.NewElement("material");

			pSubEle->SetAttribute ("mat_type", material->mat_type);

			pSubEle->SetText(material->stock_qty);	

			pConsMats->InsertEndChild(pSubEle);
		}	
	}

	doc.SaveFile(photogrf);
}

void XMLsave::saveReceptionistRepository(EmployeeRepository &empl_repo) { 
	XMLDocument doc;
	XMLError err = doc.LoadFile(receptistf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pRcpts = doc.RootElement();

	std::map<int, std::shared_ptr<Receptionist>> receptionists = empl_repo.getEmpofType("Receptionist");

	for (auto const& [rcpt_id, rcpt] : receptionists) {
		XMLElement *pRcpt = doc.NewElement("receptionist");

		pRcpt->SetAttribute("emp_id", rcpt_id);

		pRcpts->InsertEndChild(pRcpt);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(rcpt->emp_name);

		pRcpt->InsertEndChild(pElement);
	}

	doc.SaveFile(receptistf);
}

void XMLsave::saveOrderRepository(OrderRepository &order_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(orderf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *pOrders = doc.RootElement();

	for (auto const& [oid, order] : order_repo.getOrders()) {
		XMLElement *pOrder = doc.NewElement("order");

		pOrder->SetAttribute("orderid", oid);

		pOrders->InsertEndChild(pOrder);

		XMLElement *pElement = doc.NewElement("date_created");
		pElement->SetText(DatetoString(order->date_created));

		pOrder->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("client_id");
		pElement->SetText(order->client->client_id);

		pOrder->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("service");
		pElement->SetText(static_cast<int>(order->service));

		pOrder->InsertEndChild(pElement);


		XMLElement *pElement = doc.NewElement("in_x_days");
		pElement->SetText(order->in_x_days);

		pOrder->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("compl_status");
		pElement->SetText(static_cast<int>(order->compl_status));

		pOrder->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("price");
		pElement->SetText(order->price);

		pOrder->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("assigned_emp_id");
		pElement->SetText(order->assigned_emp_id);

		pOrder->InsertEndChild(pElement);
	}

	doc.SaveFile(orderf);
}

void XMLsave::saveReceptReportRepository(ReceptReportRepository &receptreport_repo) {
	XMLDocument doc;
	XMLError err = doc.LoadFile(recrepf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *eRprts = doc.RootElement();

	for (auto const& [reportid, report] : receptreport_repo.reports) {
		XMLElement *eRprt = doc.NewElement("receptreport");
		eRprt->SetAttribute("reportid", reportid);
		eRprt->SetAttribute("creator_id", report->creator_id);
		eRprt->SetAttribute("date_created", CustomFuncs::DatetoString(report->date_created));

		eRprts->InsertEndChild(eRprt);

		XMLElement *pElement = doc.NewElement("total_revenue");
		pElement->SetText(report->total_revenue);

		eRprt->InsertEndChild(pElement);

		XMLElement *pElement = doc.NewElement("compl_orders");

		for (const auto& [orderid, order] : report->compl_orders) {
			XMLElement *pSubEle = doc.NewElement("order");
			pSubEle->SetText(orderid);

			pElement->InsertEndChild(pSubEle);
		}

		eRprt->InsertEndChild(pElement);
	}

	doc.SaveFile(recrepf);
}

void XMLsave::savePhotoReportRepository(PhotoReportRepository &photoreport_repo) { 
	XMLDocument doc;
	XMLError err = doc.LoadFile(phorepf);
	if (err != XML_SUCCESS) {
		return;
	}
	
	XMLElement *eRprts = doc.RootElement();

	for (auto const& [reportid, report] : photoreport_repo.reports) {
		XMLElement *eRprt = doc.NewElement("photoreport");
		eRprt->SetAttribute("reportid", reportid);
		eRprt->SetAttribute("creator_id", report->creator_id);
		eRprt->SetAttribute("date_created", CustomFuncs::DatetoString(report->date_created));

		eRprts->InsertEndChild(eRprt);

		XMLElement *pElement = doc.NewElement("consumed_materials");

		for (const auto& [material, stock_qty] : report->consumed_materials) {
			XMLElement *pSubEle = doc.NewElement("material");
			pSubEle->SetAttribute("mat_type", material->mat_type);
			pSubEle->SetText(material->stock_qty);

			pElement->InsertEndChild(pSubEle);
		}

		eRprt->InsertEndChild(pElement);
	}

	doc.SaveFile(phorepf);
}
