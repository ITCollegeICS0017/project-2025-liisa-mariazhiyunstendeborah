#include "uimanager.h"

UImanager::UImanager(OrderRepository *omanager, ClientRepository *climanager, EmployeeRepository *empmanager, PhotoReportRepository *prepmanager, ReceptReportRepository *repmanager, MaterialRepository *matmanager)
    {
        this->order_repository = omanager;
        this->receptreport_repository = repmanager;
        this->photoreport_repository = prepmanager;
        this->employee_repository = empmanager;
        this->material_repository = matmanager;
        this->client_repository = climanager;
}

std::string UImanager::currentUsername(){
        if (this->CurrentUser == nullptr)
        {
            return "not logged in";
        }
        else
        {
            return this->CurrentUser->emp_name;
        }
    }

std::string UImanager::viewContextBase(string viewContext = ""){
        string view = "\n\n";
        view += "User: " + currentUsername() + "\n";
        view += viewContext + "\n";
        view += "\n";
        return view;
}

std::string UImanager::dispCompStatus(CompletionStatus stat){

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

std::string UImanager::dispService(Service serv){

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

std::string UImanager::chronoToString(std::chrono::year_month_day ymd){
        std::string s = std::format("{:%Y-%m-%d}", std::chrono::sys_days{ymd});
        return s;
    }

std::string UImanager::getOrder(int orderid){
        Order *order = this->order_repository->findOrder(orderid);
        string orderstr = "";
        if (order == nullptr)
        {
            std::cout << "order not found\n";

            return orderstr;
        }
        string name = order->client->client_name;
        string date = chronoToString(order->date_created);
        string comp = dispCompStatus(order->compl_status);
        string service = dispService(order->service);
        string indays = to_string(order->in_x_days);
        string price = to_string(order->priceCalc(order->in_x_days));
        orderstr += "\nID: " + to_string(orderid) + " Client: " + name + "\n";
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

std::string UImanager::getReportPhotographer(int report_id){
        string repstr = "";
        auto report = this->photoreport_repository->findReport(report_id);
        string repid = to_string(report->reportid);
        string cid = to_string(report->creator_id);
        string created = chronoToString(report->date_created);
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

std::string UImanager::getReportReceptionist(int report_id){
        string repstr = "";
        auto report = this->receptreport_repository->findReport(report_id);
        string repid = to_string(report->reportid);
        string cid = to_string(report->creator_id);
        string created = chronoToString(report->date_created);
        repstr += "ID: " + repid + " Employee ID: " + cid + "\n";
        repstr += "Creation date: " + created + "\n";
        repstr += "Completed Orders: \n";

        for (const auto& [key, val] : report->compl_orders) {
            repstr += getOrder(key);

        }
        return repstr;
}

bool UImanager::idValidOrder(int id){
        Order *order = this->order_repository->findOrder(id);
        if (order != nullptr)
        {
            return true;
        }
        return false;
}

bool UImanager::idValidUser(int id){
        Employee *emp = this->employee_repository->findEmployee(id);
        if (emp != nullptr)
        {
            return true;
        }
        return false;
}
    
int UImanager::selectCustomerId(){
         IOhandler<int> inthandler("User id");
            cmdParser<int> clientParser;
            clientParser.setContext("Select Client");
            std::map<int, std::shared_ptr<Client>> clients = this->client_repository->getClients();
            for (auto const &[key, val] : clients)
                {
                    clientParser.addCommand((string(val->client_name) + " - id: " + to_string(key)), [key](){
                        return key;
                    });
                }
            return clientParser.valueFromCommand(-1, "no client");
}

int UImanager::useridByName(string name)
    {
        map<int, std::shared_ptr<Employee>> employees = this->UImanager::employee_repository->getEmployees();
        for (auto const &[key, val] : employees)
        {
            if ((string)val->emp_name == name)
            {
                return key;
            }
        }
        return -1;
}

void UImanager::listClients(){
    std::map<int, std::shared_ptr<Order>> orders = this->order_repository->getOrders();
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
void UImanager::listOrders(){
    std::map<int, std::shared_ptr<Order>> orders = this->order_repository->getOrders();
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
void UImanager::listOrdersClientId(int id){
    std::map<int, std::shared_ptr<Order>> orders = this->order_repository->getOrders();
    std::cout << "Orders: \n";
    for (auto const &[key, val] : orders)
    {
        if (val->client->client_id == id)
        {
            std::cout << getOrder(key);
        }
    }
}
void UImanager::listOrdersEmpId(int id){
    std::map<int, std::shared_ptr<Order>> orders = this->order_repository->getOrders();
    std::cout << "Orders: \n";
    for (auto const &[key, val] : orders)
    {
        if (val->assigned_emp_id == id)
        {
            std::cout << getOrder(key);
        }
    }
}
void UImanager::listUsers(){
    map<int, std::shared_ptr<Employee>> employees = this->employee_repository->getEmployees();
    std::cout << "Employees: \n";
    for (auto const &[key, val] : employees)
    {
        std::cout << "Employee ID: " << key << " Name: " << val->emp_name << " | Role:  " << val->getEmpType() << endl;
    }
    std::cout << "\n";
    return;
}

std::map<int, std::shared_ptr<Order>> UImanager::getOrdersEmpId(int id){
    std::map<int, std::shared_ptr<Order>> orders = this->order_repository->getOrders();
    std::map<int, std::shared_ptr<Order>> emporders;
    std::cout << "Orders: \n";
    for (auto const &[key, val] : orders)
    {
        if (val->assigned_emp_id == id)
        {
            emporders[key] = val;
            //std::cout << getOrder(key);
        }
    }
    return emporders;
}

ViewManager::ViewManager(UImanager* ui_manager){
    this->ui_manager = ui_manager;
}

void ViewManager::viewMain(){
    cmdParser<int> parser;
    parser.setContext(this->ui_manager->viewContextBase("Photo Studio Main"));
    // parser.setContext("Photography Studio main view\n"+ currentUsername());
    //  function lusers = [this](){view_listUsers();};
    parser.addCommand("List Users", [this]()
                        {
        this->ui_manager->listUsers();
        return 1; });
    parser.addCommand("Login", [this, &parser]()
                        {
                        viewLogin();
                        parser.setContext(this->ui_manager->viewContextBase("Photo Studio Main"));
                
        return 1; });
    parser.addCommand("Employee commands", [this]()
                        {
        viewEmployeeCommands();
        return 1; });
    //  parser.listCommands();
    parser.loopCommands();
    return;
}

void ViewManager::viewLogin(){
    map<int, std::shared_ptr<Employee>> employees = this->ui_manager->employee_repository->getEmployees();

    cmdParser<int> userParser;
    
    for(auto const &[key, val] : employees){
        string uname = val->emp_name;
        string uid = to_string(key);
        string role = val->getEmpType();

        userParser.addCommand("id - " + uid + " " + uname + " Role - " + role,[this,key](){
            this->ui_manager->CurrentUser = this->ui_manager->employee_repository->findEmployee(key);
            this->ui_manager->emp_id = key; 
            return 1;
        });
    }
    userParser.setContext(this->ui_manager->viewContextBase("choose employee"));
    userParser.loopCommands(false);
}

void ViewManager::viewPhotographer(){
    std::cout << "Role: Photographer\n\n";
    cmdParser<int> parser;
    parser.setContext(this->ui_manager->viewContextBase("Photographer actions:"));

    parser.addCommand("View my assigned orders", [this]()
                        {this->ui_manager->listOrdersEmpId(this->ui_manager->emp_id); return 1; });

    parser.addCommand("Edit my assigned order", [this]()
                        {
                        cmdParser<int> ordParser;
                        ordParser.setContext("Select Order");
                        for(auto const&[key,val] : this->ui_manager->getOrdersEmpId(this->ui_manager->emp_id)){
                                string name = val->client->client_name;
                            string k = to_string(key);
                            string date = this->ui_manager->chronoToString(val->date_created);
                            string comp = this->ui_manager->dispCompStatus(val->compl_status);
                            string service = this->ui_manager->dispService(val->service);
                            string indays = to_string(val->in_x_days);
                            string price = to_string(val->priceCalc(val->in_x_days));
                            ordParser.addCommand("ID: "+k+ " Status: "+ comp+ " Client: " + name + " Date Created: "+ date,[key](){
                                return key;
                            });
                        }
                        int ordid = ordParser.valueFromCommand(-1, "None");
                        if (ordid == -1){return 1;}
                        viewPhotographerEditOrder(ordid);
                        ; return 1; });
    parser.addCommand("Submit report",[this](){
        int reportid = dynamic_cast<Photographer*>(this->ui_manager->CurrentUser)->submitReport();
            std::cout << "\nSubmitted Report, id:" << reportid << " \n";
            std::cout << this->ui_manager->getReportPhotographer(reportid);

    return 1;});

        parser.addCommand("Consume materials",[this](){
        std::vector<std::shared_ptr<Material>> materials = this->ui_manager->material_repository->getMaterials();
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
                dynamic_cast<Photographer*>(this->ui_manager->CurrentUser)->consumeMaterial(material->mat_type,uremove);

                return mat;
            } );
        }
        matparser.loopCommands(false);

        return 1;});
    parser.loopCommands();
}
void ViewManager::viewPhotographerEditOrder(int id){
    cmdParser<int> parser;
    Order *order = this->ui_manager->order_repository->findOrder(id);
    function<void()> updateheader = [this, id, &parser]()
    {
        string header = "editing order [" + to_string(id) + "]";
        header += this->ui_manager->getOrder(id);
        parser.setContext(this->ui_manager->viewContextBase(header));
        return;
    };
    updateheader();
    parser.addCommand("Edit Status",[&order,updateheader,this](){
        cmdParser<int> statParser;
        statParser.setContext("Select Status");
        statParser.addCommand("In Progress",[&order,this](){dynamic_cast<Photographer*>(this->ui_manager->CurrentUser)->switchOrderStatus(order,CompletionStatus::InProgress); return 1; });
        statParser.addCommand("Completed",[&order,this](){dynamic_cast<Photographer*>(this->ui_manager->CurrentUser)->switchOrderStatus(order,CompletionStatus::Completed); return 1; });
        
        
        statParser.loopCommands(false);
        updateheader(); 
        return 1;});
    
    parser.loopCommands();
}
void ViewManager::viewReceptionist(){
    std::cout << "Role: Receptionist\n\n";
    cmdParser<int> parser;
    parser.setContext(this->ui_manager->viewContextBase("Receptionist actions:"));
    parser.addCommand("list orders", [this]()
                        {this->ui_manager->listOrders();return 1; });
    // parser.addCommand("assign order to employee", [this](){return 1;});
    parser.addCommand("View Order", [this]()
                        {
        std::map<int, std::shared_ptr<Order>> orders = this->ui_manager->order_repository->getOrders();
        // std::cout << "Orders: \n";
        cmdParser<int> ordParser;
        ordParser.setContext("Select order to view");
        for (auto const &[key, val] : orders)
        {
            string ord_id = to_string(val->orderid);
            string ord_name = val->client->client_name;
            string ord_date = this->ui_manager->chronoToString(val->date_created);
            ordParser.addCommand("ID: "+ord_id+" Client: "+ord_name+"\n   Date: "+ord_date+"\n   "+ this->ui_manager->dispCompStatus(val->compl_status),[this,key](){
                std::cout << this->ui_manager->getOrder(key);
                return 1;
            });
        }
        ordParser.loopCommands();
            return 1; });
    parser.addCommand("Edit Order", [this]()
                        {
        std::map<int, std::shared_ptr<Order>> orders = this->ui_manager->order_repository->getOrders();
        // std::cout << "Orders: \n";
        cmdParser<int> ordParser;
        ordParser.setContext("Select order to edit");
        for (auto const &[key, val] : orders)
        {
            string ord_id = to_string(val->orderid);
            string ord_name = val->client->client_name;
            string ord_date = this->ui_manager->chronoToString(val->date_created);
            ordParser.addCommand("ID: "+ord_id+" Client: "+ord_name+"\n   Date: "+ord_date+"\n   "+ this->ui_manager->dispCompStatus(val->compl_status),[this,key](){
                //std::cout << getOrder(key);
                viewReceptionistEditOrder(key);
                return 1;
            });
        }
        ordParser.loopCommands(false);
            return 1; });
    parser.addCommand("List Clients",[this](){this->ui_manager->listClients();return 1;});
    parser.addCommand("List Client Orders",[this](){
            int id = this->ui_manager->selectCustomerId();
        if(id == -1){
            return 1;
        }
        this->ui_manager->listOrdersClientId(id);
        return 1;});
    parser.addCommand("Add Order", [this](){
        int cli_id = this->ui_manager->selectCustomerId(); 
        if(cli_id == -1){
            std::cout << "No client selected. Exiting.\n\n";
            return 1;
        }

        //// shared_ptr<Client> client = _client;
        cmdParser<Service> srvParser;
        std::shared_ptr<Client> client(this->ui_manager->client_repository->findClient(cli_id), [](Client*) {});

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
        int id = dynamic_cast<Receptionist*>(this->ui_manager->CurrentUser)->makeOrder(client,srv,days);
        std::cout << this->ui_manager->getOrder(id);

        return 1;});
    parser.addCommand("Add Client",[this](){
        IOhandler<string> strhandler("Client name: ");
        auto client = std::make_shared<Client>(strhandler.getInput());
        this->ui_manager->client_repository->addClient(client);
        return 1;
    });
    parser.addCommand("Submit Report",[this](){
        int repid = dynamic_cast<Receptionist*>(this->ui_manager->CurrentUser)->submitReport();

        std::cout << "Submitted Report: \n" << this->ui_manager->getReportReceptionist(repid);
        
        return 1;
    });

    parser.loopCommands();
}
void ViewManager::viewReceptionistEditOrder(int id){
    cmdParser<int> parser;
    Order *order = this->ui_manager->order_repository->findOrder(id);
    function<void()> updateheader = [this, id, &parser]()
    {
        string header = "editing order [" + to_string(id) + "]";
        header += this->ui_manager->getOrder(id);
        parser.setContext(this->ui_manager->viewContextBase(header));
        return;
    };
    updateheader();
    parser.addCommand("Assign Photographer", [this, &order, updateheader]()
                        {
        IOhandler<int> inthandler("Enter Photographer ID");
        cmdParser<int> Photographers;
        Photographers.setContext("choose a photographer");
        map<int, std::shared_ptr<Employee>> employees = this->ui_manager->employee_repository->getEmployees();
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
        dynamic_cast<Receptionist*>(this->ui_manager->CurrentUser)->assignOrder(order,pid);
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
void ViewManager::viewAdministrator(){
    std::cout << "Role: Administrator\n\n";
    cmdParser<int> parser;
    parser.setContext(this->ui_manager->viewContextBase("Administrator actions:"));
    parser.addCommand("List Receptionist Reports",[this](){
        cmdParser<int> reportParser;
        reportParser.setContext("Choose report to view: ");

        //std::cout << "Receptionist Reports\n";
            
        for (const auto& [reportid, reportPtr] : dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->listReceptReports()) {
                string rid = to_string(reportid);
                string rctr = to_string(reportPtr->creator_id);
                string rdate = this->ui_manager->chronoToString(reportPtr->date_created);
        /*
        std::cout << "Report ID: " << reportid << "\n";
        std::cout << "ID of report creator: " << reportPtr->creator_id << "\n";
        std::cout << "Date created: " << reportPtr->date_created << "\n";
        */
                reportParser.addCommand("ID: "+rid+" Employee: "+rctr+"\nDate created: "+rdate, [this,reportid](){
                    std::cout << this->ui_manager->getReportReceptionist(reportid);
                return 1;
                });


                }
        reportParser.loopCommands();
        return 1;});
    parser.addCommand("List Photographer Reports",[this](){
        std::cout << "Photographer reports that exist: " << "\n";
        for (const auto& [reportid, reportPtr] : dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->listPhotoReports()) {
            std::cout << this->ui_manager->getReportPhotographer(reportid) <<"\n";
        }
        return 1;});
    parser.addCommand("List Materials",[this](){
        std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->listMaterials();
        for(auto &material : materials){
            std::cout << material->mat_type << " Amount: " << material->stock_qty << "\n";
        }
        return 1;});
    parser.addCommand("Remove Materials",[this](){
        std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->listMaterials();

        cmdParser<string> matparser;
        matparser.setContext("Select Material to Remove Permanently");

        for(auto &material : materials){
            string mat = material->mat_type;
            string stock = to_string(material->stock_qty);
            matparser.addCommand( mat + " Quantity: " + stock,[mat,material,this]()
            {
                dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->deleteMaterial(material->mat_type);
                return mat;
            } );
        }
        matparser.loopCommands(false);
        return 1;});
    parser.addCommand("Add Material",[this](){
        std::vector<std::shared_ptr<Material>> materials = dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->listMaterials();
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
        dynamic_cast<Administrator*>(this->ui_manager->CurrentUser)->addMaterial(mat,j);
        return 1;});
    parser.loopCommands();
}
void ViewManager::viewEmployeeCommands(){
    if (this->ui_manager->CurrentUser == nullptr)
    {
        std::cout << "Not logged in";
        return;
    }

    std::cout << "\n\nWelcome " << this->ui_manager->currentUsername() << "\nEmployee id: " << this->ui_manager->emp_id << "\n\n";

    string usertype = this->ui_manager->CurrentUser->getEmpType();

    if (usertype == "Photographer")
    {
        viewPhotographer();
    }
    else if (usertype == "Receptionist")
    {
        viewReceptionist();
    }
    else if (usertype == "Administrator")
    {
        viewAdministrator();
    }
    else
    {
        std::cout << "Unknown user type, exiting.\n\n";
    }
    return;
}