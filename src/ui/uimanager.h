#ifndef UIMANAGER_H
#define UIMANAGER_H
#include "ui.h"
#include "managers/ordermanager.h"
#include "managers/clientmanager.h"
#include "managers/employeemanager.h"
#include "managers/ordermanager.h"
#include "managers/reportmanager.h"
#include "managers/materialmanager.h"

#include <format>
#include <functional>
#include <string>
#include <chrono>
#include <memory>

//	UImanager* uimanager = new UImanager(order_manager, client_manager, employee_manager, photoreport_manager, receptreport_manager, material_manager);

/*
enum CompletionStatus
{
    Created,
    Assigned,
    InProgress,
    Completed,
};
*/

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
    string curr_username()
    {
        if (CurrentUser == nullptr)
        {
            return "not logged in";
        }
        else
        {
            return CurrentUser->emp_name;
        }
    }
    string viewContextBase(string viewContext = "")
    {
        string view = "\n\n";
        view += "User: " + curr_username() + "\n";
        view += viewContext + "\n";
        view += "\n";
        return view;
    }
    string dispCompStatus(CompletionStatus stat){

        switch (stat)
        {
        case CompletionStatus::Created:
            return "Created";

            /* code */
            break;
        case CompletionStatus::Assigned:
            return "Assigned";
            /* code */
            break;
        case CompletionStatus::InProgress:
            return "In Progress";

            /* code */
            break;
        case CompletionStatus::Completed:
            return "Completed";

            /* code */
            break;

        default:
            return "unknown status";
            break;
        }
    }
    string dispService(Service serv)
    {

        switch (serv)
        {
        case Service::Photo_printing:
            return "Photo Printing";

            /* code */
            break;
        case Service::Film_devel:
            return "Develop Film";
            /* code */
            break;

        default:
            return "unknown status";
            break;
        }
    }
    string chrono_to_string(std::chrono::year_month_day ymd)
    {
        std::string s = std::format("{:%Y-%m-%d}", std::chrono::sys_days{ymd});
        return s;
    }
    
    int selectCustomerId(){
         IOhandler<int> inthandler("User id");
            cmdParser<int> clientParser;
            clientParser.setContext("Select Client");
            std::map<int, std::shared_ptr<Client>> clients = client_manager->getClients();
            for (auto const &[key, val] : clients)
                {
                    clientParser.addCommand((string(val->client_name) + " - id: " + to_string(key)), [key](){
                        return key;
                    });
                }
            return clientParser.valueFromCommand(-1, "no client");
    }
    void view_login()
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();

        cmdParser<int> userParser;
        
        for(auto const &[key, val] : employees){
            string uname = val->emp_name;
            string uid = to_string(key);
            string role = val->getEmpType();

            userParser.addCommand("id - " + uid + " " + uname + " Role - " + role,[this,key](){
                CurrentUser = employee_manager->findEmployee(key);
                emp_id = key; 
                return 1;
            });
        }
        userParser.setContext(viewContextBase("choose employee"));
        /*
        userParser.setContext(viewContextBase("Choose login method"));
        
        userParser.addCommand("Using id", [this, &userParser]()
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
                if (CurrentUser != nullptr){
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

        userParser.addCommand("Using name", [this, &userParser]()
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
                            if (CurrentUser != nullptr){
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
        */
        userParser.loopCommands(false);
    }
    void list_users()
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();
        std::cout << "Employees: \n";
        for (auto const &[key, val] : employees)
        {
            std::cout << "Employee ID: " << key << " Name: " << val->emp_name << " | Role:  " << val->getEmpType() << endl;
        }
        std::cout << "\n";
        return;
    }
    string get_order(int id)
    {
        Order *order = order_manager->findOrder(id);
        string orderstr = "";
        if (order == nullptr)
        {
            std::cout << "order not found\n";

            return orderstr;
        }
        string name = order->client->client_name;
        string date = chrono_to_string(order->date_created);
        string comp = dispCompStatus(order->compl_status);
        string service = dispService(order->service);
        string indays = to_string(order->in_x_days);
        string price = to_string(order->priceCalc(order->in_x_days));
        orderstr += "\nID: " + to_string(id) + " Client: " + name + "\n";
        orderstr += "Date created: " + date + "\n";
        orderstr += "Status: " + comp + "\n";

        if (order->assigned_emp_id > 0)
        {
            orderstr += "Assigned Employee id: " + to_string(order->assigned_emp_id) + "\n";
        }
        else
        {
            orderstr += "No assigned employee\n";
        }
        orderstr += "Service: " + service + "\n";
        orderstr += "To be done in: " + indays + "days\n";
        orderstr += "Price: " + price + "€\n";
        orderstr += "\n";
        return orderstr;
    }
    string get_report_photographer(int report_id){
        string repstr = "";
        auto report = photoreport_manager->findReport(report_id);
        string repid = to_string(report->reportid);
        string cid = to_string(report->creator_id);
        string created = chrono_to_string(report->date_created);
        repstr += "ID: " + repid + " Employee ID: " + cid + "\n";
        repstr += "Creation date: " + created + "\n";
        repstr += "Materials Consumed: \n";

        for (const auto& [key, val] : report->consumed_materials) {
            string mat = key->mat_type;
            string q = to_string(val);
            repstr += mat + " Quantity: "+q+"\n";
        }
        return repstr;
    }
    string get_report_receptionist(int report_id){
        string repstr = "";
        auto report = receptreport_manager->findReport(report_id);
        string repid = to_string(report->reportid);
        string cid = to_string(report->creator_id);
        string created = chrono_to_string(report->date_created);
        repstr += "ID: " + repid + " Employee ID: " + cid + "\n";
        repstr += "Creation date: " + created + "\n";
        repstr += "Completed Orders: \n";

        for (const auto& [key, val] : report->compl_orders) {
            repstr += get_order(key);

        }
        return repstr;
    }
    bool id_valid_order(int id)
    {
        Order *order = order_manager->findOrder(id);
        if (order != nullptr)
        {
            return true;
        }
        return false;
    }
    bool id_valid_user(int id)
    {
        Employee *emp = employee_manager->findEmployee(id);
        if (emp != nullptr)
        {
            return true;
        }
        return false;
    }
    void list_clients(){
         std::map<int, std::shared_ptr<Client>> clients = client_manager->getClients();
            for (auto const &[key, val] : clients)
                {
                    std::cout << "Client ID: " << key <<" Client name: " << val->client_name << "\n"; 
                }
    }

    void list_orders()
    {
        std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
        std::cout << "Orders: \n";
        for (auto const &[key, val] : orders)
        {
            std::cout << "\nID: " << key << " Client: " << val->client->client_name << endl;
            std::cout << "Date created: " << val->date_created << "\n";
            std::cout << "Status: " << dispCompStatus(val->compl_status) << "\n";

            int tmpint = val->assigned_emp_id;
            if (val->assigned_emp_id > 0)
            {
                std::cout << "Assigned Employee id: " << tmpint << "\n";
            }
            else
            {
                std::cout << "No assigned employee\n";
            }
        }
    }
    void list_orders_client_id(int id){
        std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
        std::cout << "Orders: \n";
        for (auto const &[key, val] : orders)
        {
            if (val->client->client_id == id)
            {
                std::cout << get_order(key);
            }
        }
    }
    void list_orders_emp_id(int id)
    {
        std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
        std::cout << "Orders: \n";
        for (auto const &[key, val] : orders)
        {
            if (val->assigned_emp_id == id)
            {
                std::cout << get_order(key);
            }
        }
    }
        std::map<int, std::shared_ptr<Order>> get_orders_emp_id(int id){
            std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
            std::map<int, std::shared_ptr<Order>> emporders;
            std::cout << "Orders: \n";
            for (auto const &[key, val] : orders)
            {
                if (val->assigned_emp_id == id)
                {
                    emporders[key] = val;
                    //std::cout << get_order(key);
                }
            }
            return emporders;
        }
    int useridByName(string name)
    {
        map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();
        for (auto const &[key, val] : employees)
        {
            if ((string)val->emp_name == name)
            {
                return key;
            }
        }
        return -1;
    }
    void view_photographer_edit_order(int id){
         cmdParser<int> parser;
        Order *order = order_manager->findOrder(id);
        function<void()> updateheader = [this, id, &parser]()
        {
            string header = "editing order [" + to_string(id) + "]";
            header += get_order(id);
            parser.setContext(viewContextBase(header));
            return;
        };
        updateheader();
        parser.addCommand("Edit Status",[&order,updateheader,this](){
            cmdParser<int> statParser;
            statParser.setContext("Select Status");
            statParser.addCommand("In Progress",[&order,this](){dynamic_cast<Photographer*>(CurrentUser)->switchOrderStatus(order,CompletionStatus::InProgress); return 1; });
            statParser.addCommand("Completed",[&order,this](){dynamic_cast<Photographer*>(CurrentUser)->switchOrderStatus(order,CompletionStatus::Completed); return 1; });
            
            
            statParser.loopCommands(false);
            updateheader(); 
            return 1;});
       
        parser.loopCommands();
    }
    void view_photographer()
    {
        std::cout << "Role: Photographer\n\n";
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Photographer actions:"));

        parser.addCommand("View my assigned orders", [this]()
                          {list_orders_emp_id(emp_id); return 1; });

        parser.addCommand("Edit my assigned order", [this]()
                          {
                            cmdParser<int> ordParser;
                            ordParser.setContext("Select Order");
                            for(auto const&[key,val] : get_orders_emp_id(emp_id)){
                                 string name = val->client->client_name;
                                string k = to_string(key);
                                string date = chrono_to_string(val->date_created);
                                string comp = dispCompStatus(val->compl_status);
                                string service = dispService(val->service);
                                string indays = to_string(val->in_x_days);
                                string price = to_string(val->priceCalc(val->in_x_days));
                                ordParser.addCommand("ID: "+k+ " Status: "+ comp+ " Client: " + name + " Date Created: "+ date,[key](){
                                    return key;
                                });
                            }
                            int ordid = ordParser.valueFromCommand(-1, "None");
                            if (ordid == -1){return 1;}
                            view_photographer_edit_order(ordid);
                            ; return 1; });
        parser.addCommand("Submit report",[this](){
            int reportid = dynamic_cast<Photographer*>(CurrentUser)->submitReport();
                std::cout << "\nSubmitted Report, id:" << reportid << " \n";
                std::cout << get_report_photographer(reportid);

        return 1;});

         parser.addCommand("Consume materials",[this](){
            std::vector<std::shared_ptr<Material>> materials = material_manager->getMaterials();
            cmdParser<string> matparser;
            matparser.setContext("Select Material");

            for(auto &material : materials){
                string mat = material->mat_type;
                string stock = to_string(material->stock_qty);
                matparser.addCommand( mat + " Quantity: " + stock,[mat,material,this]()
                {
                    IOhandler<int> inthandler("Amount to remove");
                    int remove = -1;
                    while (remove < 0 || (int(material->stock_qty) - remove) < 0){
                        remove = inthandler.getInput();
                        if(remove < 0){
                            std::cout << "Must be positive number\n";
                        }
                        if((int(material->stock_qty) - remove) < 0)
                        {

                            std::cout << "Cannot more remove materials than there are";
                        }
                        
                    }
                    std::cout << "\nQuantity after removing " << (int(material->stock_qty) - remove) << "\n";
                    unsigned int uremove = unsigned(remove);
                    dynamic_cast<Photographer*>(CurrentUser)->consumeMaterial(material->mat_type,uremove);

                    return mat;
                } );
            }
            matparser.loopCommands(false);

            return 1;});
        parser.loopCommands();
    }
   
    void view_administrator()
    {
        std::cout << "Role: Administrator\n\n";
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Administrator actions:"));
        parser.addCommand("List Receptionist Reports",[this](){
            cmdParser<int> reportParser;
            reportParser.setContext("Choose report to view: ");

            //std::cout << "Receptionist Reports\n";
               
            for (const auto& [reportid, reportPtr] : dynamic_cast<Administrator*>(CurrentUser)->listReceptReports()) {
                    string rid = to_string(reportid);
                    string rctr = to_string(reportPtr->creator_id);
                    string rdate = chrono_to_string(reportPtr->date_created);
            /*
            std::cout << "Report ID: " << reportid << "\n";
            std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
            std::cout << "Date created: " << reportPtr->date_created << "\n";
            */
                    reportParser.addCommand("ID: "+rid+" Employee: "+rctr+"\nDate created: "+rdate, [this,reportid](){
                        std::cout << get_report_receptionist(reportid);
                    return 1;
                    });


                    }
            reportParser.loopCommands();
            return 1;});
        parser.addCommand("List Photographer Reports",[this](){
            std::cout << "Photographer reports that exist: " << "\n";
            for (const auto& [reportid, reportPtr] : dynamic_cast<Administrator*>(CurrentUser)->listPhotoReports()) {
                std::cout << get_report_photographer(reportid) <<"\n";
            }
            return 1;});
        parser.addCommand("List Materials",[this](){
            std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(CurrentUser)->listMaterials();
            for(auto &material : materials){
                std::cout << material->mat_type << " Amount: " << material->stock_qty << "\n";
            }
            return 1;});
        parser.addCommand("Remove Materials",[this](){
            std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(CurrentUser)->listMaterials();

            cmdParser<string> matparser;
            matparser.setContext("Select Material to Remove Permanently");

            for(auto &material : materials){
                string mat = material->mat_type;
                string stock = to_string(material->stock_qty);
                matparser.addCommand( mat + " Quantity: " + stock,[mat,material,this]()
                {
                    dynamic_cast<Administrator*>(CurrentUser)->removeMaterial(material->mat_type);
                    return mat;
                } );
            }
            matparser.loopCommands(false);
            return 1;});
        parser.addCommand("Add Material",[this](){
            std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(CurrentUser)->listMaterials();
            cmdParser<string> matparser;
            matparser.setContext("Select material to add");
            for(auto &material : materials){
                string mat =  material->mat_type ;
                string qty =  to_string(material->stock_qty);
                matparser.addCommand(mat + " Amount: " + qty, [mat](){
                    return mat;
                });
            }
            string mat = matparser.valueFromCommand("New Material", "New Material");
            if (mat == "New Material"){
                IOhandler<string> strhandler("New Material Name");
                mat = strhandler.getInput();
            }
            int i = -1;
            IOhandler<int> inthandler("quantity to add");
            while (i < 0){
                i = inthandler.getInput();
            }
            unsigned int j = unsigned(i);
            dynamic_cast<Administrator*>(CurrentUser)->addMaterial(mat,j);
            return 1;});
        parser.loopCommands();
    }

     void view_receptionsit_edit_order(int id)
    {
        cmdParser<int> parser;
        Order *order = order_manager->findOrder(id);
        function<void()> updateheader = [this, id, &parser]()
        {
            string header = "editing order [" + to_string(id) + "]";
            header += get_order(id);
            parser.setContext(viewContextBase(header));
            return;
        };
        updateheader();
        parser.addCommand("Assign Photographer", [this, &order, updateheader]()
                          {
            IOhandler<int> inthandler("Enter Photographer ID");
            cmdParser<int> Photographers;
            Photographers.setContext("choose a photographer");
            map<int, std::shared_ptr<Employee>> employees = employee_manager->getEmployees();
            for (auto const &[key, val] : employees)
                {
                    if( (string)val->getEmpType() == "Photographer"){
                        string kstring = string(to_string(key));
                        Photographers.addCommand(((val->emp_name) + " - id: " + kstring),[key](){return key;});                            
                        order->compl_status = CompletionStatus::Assigned;
                    }
                }
            int pid = Photographers.valueFromCommand(-1,"no changes");

            if (pid == -1){
                std::cout << "No changes made\n\n";
                return 1;    
            }
            dynamic_cast<Receptionist*>(CurrentUser)->assignOrder(order,pid);
            updateheader();
            return 1; });
        parser.addCommand("Edit Status",[&order,updateheader](){
            cmdParser<CompletionStatus> statParser;
            statParser.setContext("Select Status");
          //  statParser.addCommand("Assigned",[](){return CompletionStatus::Assigned;});
            statParser.addCommand("Created",[&order](){
                order->assigned_emp_id = 0;
                return CompletionStatus::Created;});
            statParser.addCommand("In Progress",[](){return CompletionStatus::InProgress;});
            statParser.addCommand("Completed",[](){return CompletionStatus::Completed;});
            order->compl_status = statParser.valueFromCommand(order->compl_status, "no changes");
            updateheader(); 
            return 1;});
        parser.loopCommands();
    }

    void view_receptionist()
    {
        std::cout << "Role: Receptionist\n\n";
        cmdParser<int> parser;
        parser.setContext(viewContextBase("Receptionist actions:"));
        parser.addCommand("list orders", [this]()
                          {list_orders();return 1; });
        // parser.addCommand("assign order to employee", [this](){return 1;});
        parser.addCommand("View Order", [this]()
                          {
            std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
           // std::cout << "Orders: \n";
            cmdParser<int> ordParser;
            ordParser.setContext("Select order to view");
            for (auto const &[key, val] : orders)
            {
                string ord_id = to_string(val->orderid);
                string ord_name = val->client->client_name;
                string ord_date = chrono_to_string(val->date_created);
                ordParser.addCommand("ID: "+ord_id+" Client: "+ord_name+"\n   Date: "+ord_date+"\n   "+ dispCompStatus(val->compl_status),[this,key](){
                    std::cout << get_order(key);
                    return 1;
                });
            }
            ordParser.loopCommands();
                return 1; });
        parser.addCommand("Edit Order", [this]()
                          {
                        std::map<int, std::shared_ptr<Order>> orders = order_manager->getOrders();
           // std::cout << "Orders: \n";
            cmdParser<int> ordParser;
            ordParser.setContext("Select order to edit");
            for (auto const &[key, val] : orders)
            {
                string ord_id = to_string(val->orderid);
                string ord_name = val->client->client_name;
                string ord_date = chrono_to_string(val->date_created);
                ordParser.addCommand("ID: "+ord_id+" Client: "+ord_name+"\n   Date: "+ord_date+"\n   "+ dispCompStatus(val->compl_status),[this,key](){
                    //std::cout << get_order(key);
                    view_receptionsit_edit_order(key);
                    return 1;
                });
            }
            ordParser.loopCommands(false);
             return 1; });
        parser.addCommand("List Clients",[this](){list_clients();return 1;});
        parser.addCommand("List Client Orders",[this](){
                int id = selectCustomerId();
            if(id == -1){
                return 1;
            }
            list_orders_client_id(id);
            return 1;});
        parser.addCommand("Add Order", [this](){
            int cli_id = selectCustomerId(); 
            if(cli_id == -1){
                std::cout << "No client selected. Exiting.\n\n";
                return 1;
            }

          //// shared_ptr<Client> client = _client;
            cmdParser<Service> srvParser;
            std::shared_ptr<Client> client(client_manager->findClient(cli_id), [](Client*) {});

            srvParser.setContext("Select service");
            srvParser.addCommand("Photo printing",[](){return Service::Photo_printing;});
            srvParser.addCommand("Film Development",[](){return Service::Film_devel;});
            Service srv = srvParser.valueFromCommand(Service::Photo_printing, "Photo Print");
            IOhandler<int> dayparser("How many days to complete");
            unsigned int days;
            bool days_correct = false;
            do{
                int i = dayparser.getInput();
                if (i > 0){
                    days_correct = true;
                    days = unsigned(i);
                }
                else{
                    std::cout << "Enter value over 0\n";
                }

            } while(!days_correct);
            int id = dynamic_cast<Receptionist*>(CurrentUser)->makeOrder(client,srv,days);
            std::cout << get_order(id);

            return 1;});
        parser.addCommand("Add Client",[this](){
            IOhandler<string> strhandler("Client name: ");
            auto client = std::make_shared<Client>(strhandler.getInput());
            client_manager->addClient(client);
            return 1;
        });
        parser.addCommand("Submit Report",[this](){
            int repid = dynamic_cast<Receptionist*>(CurrentUser)->submitReport();

            std::cout << "Submitted Report: \n" << get_report_receptionist(repid);
            
            return 1;
        });

        parser.loopCommands();
    }

    void view_emp_commands()
    {
        if (CurrentUser == NULL)
        {
            std::cout << "Not logged in";
            return;
        }

        std::cout << "\n\nWelcome " << curr_username() << "\nEmployee id: " << emp_id << "\n\n";

        string usertype = CurrentUser->getEmpType();

        if (usertype == "Photographer")
        {
            view_photographer();
        }
        else if (usertype == "Receptionist")
        {
            view_receptionist();
        }
        else if (usertype == "Administrator")
        {
            view_administrator();
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
        // parser.setContext("Photography Studio main view\n"+ curr_username());
        //  function lusers = [this](){view_list_users();};
        parser.addCommand("List Users", [this]()
                          {
            list_users();
            return 1; });
        parser.addCommand("Login", [this, &parser]()
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