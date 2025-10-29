#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <any>
#include <limits>
#include <type_traits>
using namespace std;

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
template <>
inline std::string IOhandler<std::string>::getInput()
{
    std::string input;
    std::cout << "Enter " << context << ": ";
    std::getline(std::cin >> std::ws, input); // read full line, trimming leading whitespace
    return input;
}

template <typename T>
class cmdParser
{
private:
    string context;
    map<string, function<T()>> commands;


public:
    cmdParser(){
        context = "";
    }
    T run(string command)
    {
        return commands.at(command)();
    }
    void addCommand(string s, function<T()> f)
    {

        commands[s] = f;
    };

    void listCommands()
    {
        cout << context << endl;
        cout << "Possible commands: " << endl;
        for (const auto &[key, value] : commands)
        {
            cout << " - " << key << '\n';
        }
    }
    T valueFromCommand(T defaultVal, string default_string = "Default Value"){
        T returnVal = defaultVal;
        int x = 0;
        
        while (true)
        {

            int i = 1;
            map<int, string> sesh;

            sesh[0] = default_string;

            cout << context << endl;
            
            
            cout << "select value from: \n";
            for (const auto &[key, value] : commands)
            {
                cout << "[" << i << "] - " << key << '\n';
                sesh[i] = key;
                i++;
            }
            i--;
            do
            {
                if (x > i)
                {
                    cout << "number must be between 0 and " << i << endl;
                }
                if (x < 0)
                {
                    cout << "value must not be negative" << endl;
                }
                cout << "enter 0 to exit with: "<< sesh[x] <<endl << endl;
                x = IOhandler<int>("Command ID").getInput();
                
            } while (x > i || x < 0);
            cout << "\n\n";
            if (sesh.at(x) == default_string)
            {
                return returnVal;
            }
            else
            {
                returnVal = run(sesh.at(x));
            }
        }
    }
    void loopCommands(bool looping = true)
    {
        do
        {
            
            int i = 1;
            map<int, string> sesh;
            
            cout << context << endl;
            for (const auto &[key, value] : commands)
            {
                cout << "[" << i << "] - " << key << '\n';
                sesh[i] = key;
                i++;
            }
                sesh[0] = "exit";
                cout << "enter 0 to exit" <<endl;
                
            int x = 0;
            do
            {
                if (x >= i)
                {
                    cout << "value must be smaller than: " << i << endl;
                }
                if (x < 0)
                {
                    cout << "value must not be negative" << endl;
                }
                x = IOhandler<int>("Command ID").getInput();

            } while (x > i || x < 0);
            
            cout << "selected command: " << sesh.at(x) << "\n\n";
            if (sesh.at(x) == "exit")
            {
                looping = false;
                break;
            }
            else
            {
                run(sesh.at(x));
            }
        }while (looping);
    }

    string getContext()
    {
        return context;
    }
    void setContext(string ctxt){
        context = ctxt;
    }
};


#endif