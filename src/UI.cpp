#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <any>
#include <limits>
#include <type_traits>
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
template <typename T>
class IOhandler
{
private:
    string context;

public:
    IOhandler()
    {
        context = "value of type " + string(typeid(T).name());
    }
    IOhandler(string ctxt)
    {
        context = ctxt;
    }

    T getInput()
    {
        bool correct_conversion = false;
        T input;
        do
        {
            cout << "Enter " << context << ": ";
            cin >> input;
            correct_conversion = true;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid value type. Must be " << typeid(T).name() << endl;
                correct_conversion = false;
            }

        } while (!correct_conversion);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        return input;
    }
};

template <typename T>
class cmdParser
{
private:
    string context;
    map<string, function<T()>> commands;

    void addExit()
    {
        commands["exit"] = []()
        {
            cout << "you have exited" << endl;
            if (is_void_v<T>)
            {
                return;
            };
            return T();
        };
    }

    T run(string command)
    {
        return commands.at(command)();
    }

public:
    void addCommand(string s, function<T()> f)
    {

        commands[s] = f;
    }

    cmdParser()
    {
        // addExit();
        context = "";
    }

    cmdParser(string ctxt)
    {
        //  if(add_exit){addExit();}
        context = ctxt;
    }

    void listCommands()
    {
        cout << context << endl;
        cout << "Possible commands: " << endl;
        for (const auto &[key, value] : commands)
        {
            cout << " - " << key << '\n';
        }
    }

    T loopCommands(bool add_exit = true)
    {
        if (add_exit)
        {
            addExit();
        }
        bool looping = true;
        while (looping)
        {
            int i = 0;
            map<int, string> sesh;
            cout << context << endl;
            for (const auto &[key, value] : commands)
            {
                cout << "id: " << i << " - " << key << '\n';
                sesh[i] = key;
                i++;
            }
            int x = 0;
            do
            {
                if (x > i)
                {
                    cout << "value must be smaller than: " << i << endl;
                }
                if (x < 0)
                {
                    cout << "value must not be negative" << endl;
                }
                x = IOhandler<int>("Command ID").getInput();

            } while (x > i || x < 0);

            cout << "selected command: " << sesh.at(x) << endl;
            if (sesh.at(x) == "exit")
            {
                looping = false;
                break;
            }
            else
            {
                run(sesh.at(x));
            }
        }
    }
};

/*
void view_login()
{
cmdParser<void> parser("Log in view:");
parser.addCommand("list Users ", []()
      { return; });
parser.addCommand("login to user ", []()
      { return; });
parser.loopCommands();
}

int main()
{
string i = IOhandler<string>().getInput();
cout << i << endl;
cmdParser<void> parser("main screen: ");
parser.addCommand("login", []()
{ view_login(); });

parser.listCommands();
parser.addCommand("die", []()
{ cout << "die" << endl; });
parser.listCommands();
parser.loopCommands();
}

*/