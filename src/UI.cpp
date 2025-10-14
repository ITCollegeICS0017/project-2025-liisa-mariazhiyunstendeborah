#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
using namespace std;
/*
cmdParser is an easy custom solution to have UI be able to excecute commands without a lot of reusing the same code.

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
class cmdParser {
    private:
    string context; 
    void addExit(){
        commands["exit"] = []() {
            cout << "you have exited" << endl;
            return false;
        };
    }

    void run(string command){
        commands.at(command)();
    }

    public:
    void addCommand(string s, function<void()> f) {
        
        commands[s] = f;

    }
    map<string,function<void()>> commands;

    cmdParser(){
        addExit();
        context = "";
    }
    cmdParser(string ctxt){
        addExit();
        context = ctxt;
    }

    void listCommands(){
        cout << context<< endl;
        cout << "Possible commands: " << endl;
        for (const auto& [key, value] : commands) {
            cout << " - " << key << '\n';
        }
    }

    void loop(){
        bool looping = true;
        while(looping){
            int i = 0;
            map<int, string> sesh;
            cout << context << endl;
            for (const auto& [key, value] : commands) {
                cout << "id: "<< i << " - " << key << '\n';
                sesh[i] = key;
                i++;
            }
            int x;
            cout << "enter command id: ";
            cin >> x;
            cout << "selected command: " << sesh.at(x) << endl;
            if (sesh.at(x) == "exit"){
                looping = false;
                break;
            }
            run(sesh.at(x));
        }
    }
    


};

void view_login(){
    cmdParser parser("Log in view:");
    parser.addCommand("list Users ", [](){return;});
    parser.addCommand("login to user ", [](){return;});
    parser.loop();    
}

int main(){
    cmdParser parser("main screen: ");
    parser.addCommand("login", [](){view_login();});
    
    parser.listCommands();
    parser.addCommand("die",[](){cout << "die"<<endl;});
    parser.listCommands();
    parser.loop();

}