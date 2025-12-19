#ifndef XMLSAVE_H
#define XMLSAVE_H

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

#include <fstream>
#include <ios>
#include <vector>
#include <memory>
#include <string>

namespace XMLsave {


//saving funcs
	void saveClientRepository(ClientRepository &client_repo, const char* file);

	void saveMaterialRepository(MaterialRepository &mat_repo, const char* file);

	void saveAdministratorRepository(EmployeeRepository &empl_repo, const char* file);

	void savePhotographerRepository(EmployeeRepository &empl_repo, const char* file);

	void saveReceptionistRepository(EmployeeRepository &empl_repo, const char* file);

	void saveOrderRepository(OrderRepository &order_repo, const char* file);

	void saveReceptReportRepository(ReceptReportRepository &receptreport_repo, const char* file);

	void savePhotoReportRepository(PhotoReportRepository &photoreport_repo, const char* file);
}

#endif
