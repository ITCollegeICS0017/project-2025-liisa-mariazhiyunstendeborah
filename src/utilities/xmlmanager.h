#include <vector>
#include <memory>
#include <string>

#include "tinyxml2-git/tinyxml2.hpp"
#include "repos/orderrepository.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "utilities/miscfunctions.h"

namespace XMLManager {
	const char *clientf = "xmldocs/clients.xml";
	const char *matf = "xmldocs/materials.xml";
	const char *photogrf = "xmldocs/photographers.xml";
	const char *receptistf = "xmldocs/receptionists.xml";
	const char *orderf = "xmldocs/orders.xml";
	const char *recrepf = "xmldocs/receptreports.xml";
	const char *phorepf = "xmldocs/photoreports.xml";

//populationfuncs:
	void populateClientRepository(ClientRepository &client_repo);

	void populateMaterialRepository(MaterialRepository &mat_repo);

	void populatePhotographerRepository(EmployeeRepository &empl_repo);

	void populateReceptionistRepository(EmployeeRepository &empl_repo);

	void populateOrderRepository(OrderRepository &order_repo);

	void populateReceptReportRepository(ReceptReportRepository &receptreport_repo);

	void populatePhotoReportRepository(PhotoReportRepository &photoreport_repo);

//saving funcs
	void saveClientRepository(ClientRepository &client_repo);

	void saveMaterialRepository(MaterialRepository &mat_repo);

	void savePhotographerRepository(EmployeeRepository &empl_repo);

	void saveReceptionistRepository(EmployeeRepository &empl_repo);

	void saveOrderRepository(OrderRepository &order_repo);

	void saveReceptReportRepository(ReceptReportRepository &receptreport_repo);

	void savePhotoReportRepository(PhotoReportRepository &photoreport_repo);
}
