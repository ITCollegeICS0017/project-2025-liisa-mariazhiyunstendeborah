#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "ui.h"
#include "repos/orderrepository.h"
#include "repos/clientrepository.h"
#include "repos/employeerepository.h"
#include "repos/orderrepository.h"
#include "repos/reportrepository.h"
#include "repos/materialrepository.h"
#include "employees/photographer.h"
#include "employees/receptionist.h"
#include "employees/administrator.h"

#include <format>
#include <functional>
#include <string>
#include <chrono>
#include <memory>

class UImanager {
public:
    UImanager(OrderRepository* order_repository, ClientRepository* client_repository,
              EmployeeRepository* employee_repository, PhotoReportRepository* photoreport_repository,
              ReceptReportRepository* receptreport_repository, MaterialRepository* material_repository);


private:
    OrderRepository *order_repository;
    ReceptReportRepository *receptreport_repository;
    PhotoReportRepository *photoreport_repository;
    EmployeeRepository *employee_repository;
    MaterialRepository *material_repository;
    ClientRepository *client_repository;
    Employee* CurrentUser;
    int emp_id;
//UI helper functions
    std::string currentUsername();
    std::string viewContextBase(string viewContext);
    std::string dispCompStatus(CompletionStatus stat);
    std::string dispService(Service serv);
    std::string chronoToString(std::chrono::year_month_day ymd);
    std::string getOrder(int orderid);
    std::string getReportPhotographer(int report_id);
    std::string getReportReceptionist(int report_id);
    std::map<int, std::shared_ptr<Order>> getOrdersEmpId(int id);
  //validation functions  
    bool idValidOrder(int id);
    bool idValidUser(int id);
// UI actions
    int selectCustomerId();
    int useridByName(string name);
// listing functions
    void listClients();
    void listOrders();
    void listOrdersClientId(int id);
    void listOrdersEmpId(int id);
    void listUsers();
    
// ViewManager needs access to UImanager internals
    friend class ViewManager;
   
};

class ViewManager  {
    private:
        UImanager* ui_manager;
    public:
    ViewManager(UImanager* ui_manager);
    //view functions
    void viewMain();
    void viewLogin();
    void viewPhotographer();
    void viewPhotographerEditOrder(int id);
    void viewReceptionist();
    void viewReceptionistEditOrder(int id);
    void viewAdministrator();
    void viewEmployeeCommands();
    
};

#endif // UIMANAGER_H