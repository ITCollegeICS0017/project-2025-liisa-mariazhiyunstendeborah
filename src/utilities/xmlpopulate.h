#ifndef XMLPOPULATE_H
#define XMLPOPULATE_H
 
#include "tinyxml2.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "utilities/miscfunctions.h"

#include <vector>
#include <memory>
#include <string>

namespace XMLpopulate {
	const char *clientf = "xmldocs/clients.xml";
	const char *matf = "xmldocs/materials.xml";
	const char *adminf = "xmldocs/administrators.xml"
	const char *photogrf = "xmldocs/photographers.xml";
	const char *receptistf = "xmldocs/receptionists.xml";
	const char *orderf = "xmldocs/orders.xml";
	const char *recrepf = "xmldocs/receptreports.xml";
	const char *phorepf = "xmldocs/photoreports.xml";

//populationfuncs:
	void populateClientRepository(ClientRepository &client_repo);

	void populateMaterialRepository(MaterialRepository &mat_repo);

	void XMLpopulate::populateAdministratorRepository(EmployeeRepository &empl_repo)

	void populatePhotographerRepository(EmployeeRepository &empl_repo);

	void populateReceptionistRepository(EmployeeRepository &empl_repo);

	void populateOrderRepository(OrderRepository &order_repo, ClientRepository &client_repo);

	void populateReceptReportRepository(ReceptReportRepository &receptreport_repo);

	void populatePhotoReportRepository(PhotoReportRepository &photoreport_repo);

}

#endif
