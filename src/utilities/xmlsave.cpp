#include "utilities/xmlsave.h"
using namespace tinyxml2;

ClientRepository client_repo;
MaterialRepository mat_repo;
OrderRepository order_repo;
EmployeeRepository empl_repo;
PhotoReportRepository photoreport_repo;
ReceptReportRepository receptreport_repo;
class SystemClock cclock;
class Employee;
class Administrator;
class Photographer;
class Receptionist;

//saving funcs
void XMLsave::saveClientRepository(ClientRepository &client_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *pClients = doc.NewElement("clients");	
	doc.InsertFirstChild(pClients);

	for (auto const& [client_id, client] : client_repo.getClients()) {
		XMLElement *pClient = doc.NewElement("client");

		pClient->SetAttribute("client_id", client_id);

		pClients->InsertEndChild(pClient);

		XMLElement *pElement = doc.NewElement("client_name");

		pElement-> SetText(client->client_name.c_str());

		pClient->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}

void XMLsave::saveMaterialRepository(MaterialRepository &mat_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *pMats = doc.NewElement("materials");	
	doc.InsertFirstChild(pMats);

	for (auto const& mat : mat_repo.getMaterials()) {
		XMLElement *pMat = doc.NewElement("material");

		pMat->SetAttribute ("mat_type", mat->mat_type.c_str());

		pMats->InsertEndChild(pMat);

		XMLElement *pElement = doc.NewElement("stock_qty");
		pElement-> SetText(mat->stock_qty);

		pMat-> InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}

void XMLsave::saveAdministratorRepository(EmployeeRepository &empl_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *pAdmins = doc.NewElement("administrators");	
	doc.InsertFirstChild(pAdmins);

	auto emps = empl_repo.getEmpofType("Administrator");


	for (auto const& [emp_id, emp] : emps) {
		auto admin = std::dynamic_pointer_cast<Administrator>(emp);
		if (!admin) {
			continue;
		}
		XMLElement *pAdmin = doc.NewElement("administrator");

		pAdmin->SetAttribute ("emp_id", emp_id);

		pAdmins->InsertEndChild(pAdmin);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(admin->emp_name.c_str());

		pAdmin->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}


void XMLsave::savePhotographerRepository(EmployeeRepository &empl_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *pPhtgrs = doc.NewElement("photographers");	
	doc.InsertFirstChild(pPhtgrs);

	auto emps = empl_repo.getEmpofType("Photographer");
	for (auto const& [emp_id, emp] : emps) {
		auto photographer = std::dynamic_pointer_cast<Photographer>(emp);
		if (!photographer) {
			continue;
		}

		XMLElement *pPhtgr = doc.NewElement("photographer");

		pPhtgr->SetAttribute ("emp_id", emp_id);

		pPhtgrs->InsertEndChild(pPhtgr);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(photographer->emp_name.c_str());

		pPhtgr->InsertEndChild(pElement);

		XMLElement *pConsMats = doc.NewElement("consumed_materials");
		pPhtgr->InsertEndChild(pConsMats);

		for (auto const& [material, stock_qty] : photographer->getConsumedMaterials()) {
			XMLElement *pSubEle = doc.NewElement("material");

			pSubEle->SetAttribute ("mat_type", material->mat_type.c_str());

			pSubEle->SetText(stock_qty);	

			pConsMats->InsertEndChild(pSubEle);
		}	
	}

	doc.SaveFile(filepath);
}

void XMLsave::saveReceptionistRepository(EmployeeRepository &empl_repo, const char* filepath) { 
	XMLDocument doc;

	XMLElement *pRcpts = doc.NewElement("receptionists");	
	doc.InsertFirstChild(pRcpts);

	auto emps = empl_repo.getEmpofType("Receptionist");


	for (auto const& [emp_id, emp] : emps) {
		auto receptionist = std::dynamic_pointer_cast<Receptionist>(emp);
		if (!receptionist) {
			continue;
		}
		XMLElement *pRcpt = doc.NewElement("receptionist");

		pRcpt->SetAttribute("emp_id", emp_id);

		pRcpts->InsertEndChild(pRcpt);

		XMLElement *pElement = doc.NewElement("emp_name");
		pElement->SetText(receptionist->emp_name.c_str());

		pRcpt->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}

void XMLsave::saveOrderRepository(OrderRepository &order_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *pOrders = doc.NewElement("orders");	
	doc.InsertFirstChild(pOrders);

	for (auto const& [oid, order] : order_repo.getOrders()) {
		XMLElement *pOrder = doc.NewElement("order");

		pOrder->SetAttribute("orderid", oid);

		pOrders->InsertEndChild(pOrder);

		XMLElement *pElement = doc.NewElement("date_created");
		pElement->SetText(CustomFuncs::DatetoString(order->date_created).c_str());

		pOrder->InsertEndChild(pElement);

		pElement = doc.NewElement("client_id");
		pElement->SetText(order->client->client_id);

		pOrder->InsertEndChild(pElement);

		pElement = doc.NewElement("service");
		pElement->SetText(static_cast<int>(order->service));

		pOrder->InsertEndChild(pElement);


		pElement = doc.NewElement("in_x_days");
		pElement->SetText(order->in_x_days);

		pOrder->InsertEndChild(pElement);

		pElement = doc.NewElement("compl_status");
		pElement->SetText(static_cast<int>(order->compl_status));

		pOrder->InsertEndChild(pElement);

		pElement = doc.NewElement("price");
		pElement->SetText(order->price);

		pOrder->InsertEndChild(pElement);

		pElement = doc.NewElement("assigned_emp_id");
		pElement->SetText(order->assigned_emp_id);

		pOrder->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}

void XMLsave::saveReceptReportRepository(ReceptReportRepository &receptreport_repo, const char* filepath) {
	XMLDocument doc;

	XMLElement *eRprts = doc.NewElement("reports");	
	doc.InsertFirstChild(eRprts);

	for (auto const& [reportid, report] : receptreport_repo.reports) {
		XMLElement *eRprt = doc.NewElement("receptreport");
		eRprt->SetAttribute("reportid", reportid);
		eRprt->SetAttribute("creator_id", report->creator_id);
		eRprt->SetAttribute("date_created", CustomFuncs::DatetoString(report->date_created).c_str());

		eRprts->InsertEndChild(eRprt);

		XMLElement *pElement = doc.NewElement("total_revenue");
		pElement->SetText(report->total_revenue);

		eRprt->InsertEndChild(pElement);

		pElement = doc.NewElement("compl_orders");

		for (const auto& [orderid, order] : report->compl_orders) {
			XMLElement *pSubEle = doc.NewElement("order");
			pSubEle->SetText(orderid);

			pElement->InsertEndChild(pSubEle);
		}

		eRprt->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}

void XMLsave::savePhotoReportRepository(PhotoReportRepository &photoreport_repo, const char* filepath) { 
	XMLDocument doc;

	XMLElement *eRprts = doc.NewElement("reports");	
	doc.InsertFirstChild(eRprts);

	for (auto const& [reportid, report] : photoreport_repo.reports) {
		XMLElement *eRprt = doc.NewElement("photoreport");
		eRprt->SetAttribute("reportid", reportid);
		eRprt->SetAttribute("creator_id", report->creator_id);
		eRprt->SetAttribute("date_created", CustomFuncs::DatetoString(report->date_created).c_str());

		eRprts->InsertEndChild(eRprt);

		XMLElement *pElement = doc.NewElement("consumed_materials");

		for (const auto& [material, stock_qty] : report->consumed_materials) {
			XMLElement *pSubEle = doc.NewElement("material");
			pSubEle->SetAttribute("mat_type", material->mat_type.c_str());
			pSubEle->SetText(material->stock_qty);

			pElement->InsertEndChild(pSubEle);
		}

		eRprt->InsertEndChild(pElement);
	}

	doc.SaveFile(filepath);
}
