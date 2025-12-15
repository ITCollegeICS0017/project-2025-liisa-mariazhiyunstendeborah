#ifndef XMLSAVE_H
#define XMLSAVE_H

#include "tinyxml2/tinyxml2.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "utilities/miscfunctions.h"

#include <vector>
#include <memory>
#include <string>

namespace XMLsave {
	const char *clientf = "xmldocs/clients.xml";
	const char *matf = "xmldocs/materials.xml";
	const char *adminf = "xmldocs/administrators.xml"
	const char *photogrf = "xmldocs/photographers.xml";
	const char *receptistf = "xmldocs/receptionists.xml";
	const char *orderf = "xmldocs/orders.xml";
	const char *recrepf = "xmldocs/receptreports.xml";
	const char *phorepf = "xmldocs/photoreports.xml";

//saving funcs
	void saveClientRepository(ClientRepository &client_repo);

	void saveMaterialRepository(MaterialRepository &mat_repo);

	void saveAdministratorRepository(EmployeeRepository &empl_repo);

	void savePhotographerRepository(EmployeeRepository &empl_repo);

	void saveReceptionistRepository(EmployeeRepository &empl_repo);

	void saveOrderRepository(OrderRepository &order_repo);

	void saveReceptReportRepository(ReceptReportRepository &receptreport_repo);

	void savePhotoReportRepository(PhotoReportRepository &photoreport_repo);
}

#endif
