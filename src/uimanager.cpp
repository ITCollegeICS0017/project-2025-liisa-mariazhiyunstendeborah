#include <iostream>
#include "ui.h"
#include "ordermanager.h"
#include "clientmanager.h"
#include "employeemanager.h"
#include "ordermanager.h"
#include "reportmanager.h"
#include "materialmanager.h"

#include <functional>

//	UImanager* uimanager = new UImanager(order_manager, client_manager, employee_manager, photoreport_manager, receptreport_manager, material_manager);

class UImanager
{
private:
    OrderManager *order_manager;
    ReceptReportManager *receptreport_manager;
    PhotoReportManager *photoreport_manager;
    EmployeeManager *employee_manager;
    MaterialManager *material_manager;
    ClientManager *client_manager;

public:
    UImanager(OrderManager *omanager, ClientManager *climanager, EmployeeManager *empmanager, PhotoReportManager *prepmanager, ReceptReportManager *repmanager, MaterialManager *matmanager)
    {
        order_manager = omanager;
        receptreport_manager = repmanager;
        photoreport_manager = prepmanager;
        employee_manager = empmanager;
        material_manager = matmanager;
        client_manager = climanager;
    }

    void view_list_users()
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();

        for (auto const &[key, val] : employees)
        {
            std::cout << "Employee ID: " << key << " Employee Name: " << val->emp_name << endl;
        }
        return;
    }

    int view_main()
    {
        cmdParser<int> parser("Photography Studio main view");
        // function lusers = [this](){view_list_users();};
        int currentuser = 0;
        parser.addCommand("List Users", [this]()
                          {
            view_list_users();
            return 1; });
        parser.addCommand("Login", [this, currentuser]()
                          {
            std::cout << "to be implemented";
            return 1; });
        parser.addCommand("List Orders", [this]()
                          {
            std::cout << "to be implemented";
            return 1; });
        //  parser.listCommands();
        parser.loopCommands();
        return 1;
    }
};
/*
int main(){
    OrderManager* order_manager = new OrderManager();
    ReceptReportManager* receptreport_manager = new ReceptReportManager();
    PhotoReportManager* photoreport_manager = new PhotoReportManager();
    EmployeeManager* employee_manager = new EmployeeManager();
    MaterialManager* material_manager = new MaterialManager();
    ClientManager* client_manager = new ClientManager();
    UImanager* uimanager = new UImanager(order_manager, client_manager, employee_manager, photoreport_manager, receptreport_manager, material_manager);
    uimanager->view_main();
}
*/

/*
Views tree:
Main
Login
ListUsers
LogintoUser
Receptionist
CreateOrder
ManageOrder
                    ListOrders
                    ViewOrder
                    SubmitReport
                    AssignOrder
                    Admin
                    ViewReports
                    ListOrders
                    ViewOrder
                    CreateUser
                    Materials
                    ADD
                    REMOVE
                    LIST
                    Photographer
                    ListOrders
                    ViewOrder
                    ChangeOrderStatus
                    MarkMaterials
                    SubmitReport


                    Exit

*/