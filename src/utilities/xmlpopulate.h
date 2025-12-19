#ifndef XMLPOPULATE_H
#define XMLPOPULATE_H
 
#include "tinyxml2.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "core/employee.h"
#include "employees/administrator.h"
#include "employees/photographer.h"
#include "employees/receptionist.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "utilities/miscfunctions.h"

#include <vector>
#include <memory>
#include <string>

namespace XMLpopulate {
//populationfuncs:
	void populateClientRepository(ClientRepository &client_repo, const char* filepath);

	void populateMaterialRepository(MaterialRepository &mat_repo, const char* filepath);

	void populateAdministratorRepository(EmployeeRepository &empl_repo, OrderRepository &order_repo, MaterialRepository &mat_repo, ReceptReportRepository &receptreport_repo, PhotoReportRepository &photoreport_repo, const char* filepath);

	void populatePhotographerRepository(EmployeeRepository &empl_repo, OrderRepository &order_repo, MaterialRepository &mat_repo, PhotoReportRepository &photoreport_repo, SystemClock cclock, const char* filepath);

	void populateReceptionistRepository(EmployeeRepository &empl_repo, OrderRepository &order_repo, MaterialRepository &mat_repo, ReceptReportRepository &receptreport_repo, SystemClock cclock, const char* filepath);

	void populateOrderRepository(OrderRepository &order_repo, ClientRepository &client_repo, const char* filepath);

	void populateReceptReportRepository(ReceptReportRepository &receptreport_repo, OrderRepository &order_repo, const char* filepath);

	void populatePhotoReportRepository(PhotoReportRepository &photoreport_repo, OrderRepository &order_repo, const char* filepath);

}

#endif
