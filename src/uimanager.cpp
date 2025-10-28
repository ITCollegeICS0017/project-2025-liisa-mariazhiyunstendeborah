#include <iostream>
#include "ui.h"
#include "ordermanager.h"
#include "clientmanager.h"
#include "employeemanager.h"
#include "ordermanager.h"
#include "reportmanager.h"
#include "materialmanager.h"

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
    PhotoStudioManager(*OrderManager omanager, *ClientManager climanager, *EmployeeManager empmanager, *PhotoReportManager prepmanager, *ReceptReportManager repmanager, *MaterialManager matmanager)
    {
        order_manager = omanager;
        receptreport_manager = repmanager;
        photoreport_manager = prepmanager;
        employee_manager = empmanager;
        material_manager = matmanager;
        client_manager = climanager;
    }

    void view_list_users(){
        map<int, std::shared_ptr<Employee>> *employees = employee_manager->getEmployyees(); 

        for (auto const& [key, val] : employees){
            std::cout >> "Employee ID: " >> key >> endl; 
        }
    }

    int view_main(){
        parser = cmdParser<int>("Photography Studio main view")
        parser.addCommand("List Users", [](){
            view_list_users();
            return 1;
        })

    }
};
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