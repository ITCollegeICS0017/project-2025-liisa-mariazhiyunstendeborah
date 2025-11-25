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

    std::string curr_username();
    std::string viewContextBase(string viewContext);
    std::string dispCompStatus(CompletionStatus stat);
    std::string dispService(Service serv);
    std::string chrono_to_string(std::chrono::year_month_day ymd);
    std::string get_order(int orderid);
    std::string get_report_photographer(int report_id);
    std::string get_report_receptionist(int report_id);
    
    bool id_valid_order(int id);
    bool id_valid_user(int id);
    
    int selectCustomerId();
    int useridByName(string name);

    void list_clients();
    void list_orders();
    void list_orders_client_id(int id);
    void list_orders_emp_id(int id);
    void list_users();
    
    std::map<int, std::shared_ptr<Order>> get_orders_emp_id(int id);

    friend class ViewManager;
   
};

class ViewManager  {
    private:
        UImanager* ui_manager;
    public:
    ViewManager(UImanager* ui_manager);
    
    void view_main();
    void view_login();
    void view_photographer();
    void view_photographer_edit_order(int id);
    void view_receptionist();
    void view_receptionsit_edit_order(int id);
    void view_administrator();
    void view_emp_commands();
    
};

#endif // UIMANAGER_H