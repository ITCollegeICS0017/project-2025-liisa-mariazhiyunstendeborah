#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "ui.h"
#include "ordermanager.h"
#include "clientmanager.h"
#include "employeemanager.h"
#include "ordermanager.h"
#include "reportmanager.h"
#include "materialmanager.h"

#include <functional>
#include <string>

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
    Employee *CurrentUser;
    int emp_id;
    UImanager(OrderManager *omanager, ClientManager *climanager, EmployeeManager *empmanager, PhotoReportManager *prepmanager, ReceptReportManager *repmanager, MaterialManager *matmanager)
    {
        order_manager = omanager;
        receptreport_manager = repmanager;
        photoreport_manager = prepmanager;
        employee_manager = empmanager;
        material_manager = matmanager;
        client_manager = climanager;
    }
    string curr_username(){
        if(CurrentUser == nullptr){
            return "not logged in";
        }
        else {
            return CurrentUser->emp_name;
        }
    }
    string viewContextBase(string viewContext = ""){
        string view = "\n\n";
        view += "User: " + curr_username() + "\n";
        view += viewContext + "\n";
        view += "\n";
        return view;
    }
    void list_users()
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();
        std::cout << "Employees: \n";
        for (auto const &[key, val] : employees)
        {
            std::cout << "Employee ID: " << key << " Employee Name: " << val->emp_name << endl;
        }
        std::cout << "\n";
        return;
    }
    
    
    void view_login()
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();

        cmdParser<int> userParser;
        userParser.setContext(viewContextBase("Choose login method"));
        userParser.addCommand("Using id", [this,&userParser]()
                              {
            list_users();
            bool id_in_range = false;
            while(!id_in_range){
                int id;
                IOhandler<int> inthandler("Employee id");
                id = inthandler.getInput();
                  try
                    {
                CurrentUser = employee_manager->findEmployee(id);
                if (CurrentUser != NULL){
                    id_in_range = true; 
                    emp_id = id; 
                    userParser.setContext(viewContextBase("Choose login method"));
                }
                    }
            catch(const std::exception& e)
                    {
                std::cout << "user not found, invalid valud";
                //std::cerr << e.what() << '\n';
                    }
                if(!id_in_range){
                    std::cout << "Enter value in user id range.";
                }
                else {
                    std::cout << "logged in\n";
                }
            }
            
            return 0; });

        userParser.addCommand("Using name", [this,&userParser]()
            { 
            map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();
            bool logged_in = false;
            while(!logged_in){
                list_users();
                IOhandler<string> strhandler("Employee name"); 
                string name = strhandler.getInput();
                for (auto const &[key, val] : employees)
                    {
                        if( (string)val->emp_name == name){
                            try
                            {
                            CurrentUser = employee_manager->findEmployee(key);
                            if (CurrentUser != NULL){
                                logged_in = true;
                                emp_id = key;
                                userParser.setContext(viewContextBase("Choose login method"));

                                std::cout << "logged in \n";}

                            }
                            catch(const std::exception& e)
                            {
                            std::cout << "user not found, invalid value";
                //std::cerr << e.what() << '\n';
                            }                            
                        }
                    }
            }

                return 0; });
    userParser.loopCommands();
    }
    void view_order(){

    }
    void list_orders(){

    }    
    void emp_orders_id(){

    }
    void list_assigned_orders(){
    }
    void view_Photographer(){
        std::cout << "Role: Photographer\n\n"; 
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Photographer actions:"));

    }
    void view_Administrator(){
        std::cout << "Role: Administrator\n\n"; 
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Administrator actions:"));

    }
    void view_Receptionist(){
        std::cout << "Role: Receptionist\n\n"; 
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Receptionist actions:"));
        parser.addCommand("list orders", [](){return 1;});
        parser.addCommand("assign order to employee", [](){return 1;});
        parser.addCommand("list orders", [](){return 1;});
        parser.addCommand("list orders", [](){return 1;});
        parser.addCommand("list orders", [](){return 1;});
        parser.loopCommands();
    }

    void view_emp_commands(){
        if(CurrentUser == NULL){
            std::cout<< "Not logged in";
            return;
        }

        std::cout << "\n\nWelcome " << curr_username()<< "\nEmployee id: " << emp_id << "\n\n";

        string usertype = CurrentUser->getEmpType();
        
        if (usertype == "Photographer")
        {
            view_Photographer();
        }
        else if (usertype == "Receptionist")
        {
            view_Receptionist();
        }
        else if (usertype == "Administrator")
        {
            view_Administrator();
        }
        else
        {
           std::cout << "Unknown user type, exiting.\n\n";
        }
        return;

    }
    int view_main()
    {
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Photo Studio Main"));
        //parser.setContext("Photography Studio main view\n"+ curr_username());
        // function lusers = [this](){view_list_users();};
        parser.addCommand("List Users", [this]()
                          {
            list_users();
            return 1; });
        parser.addCommand("Login", [this,&parser]()
                          {
                            view_login();
                            parser.setContext(viewContextBase("Photo Studio Main"));
                    
            return 1; });
        parser.addCommand("Employee commands", [this]()
                          {
            view_emp_commands();
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
l*/

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
#endif