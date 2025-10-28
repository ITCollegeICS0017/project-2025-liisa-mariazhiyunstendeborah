#include "ui.h"

/*
cmdParser is an easy custom solution to have UI be able to excecute commands without a lot of reusing the same code.



*/

template <typename T>
IOhandler<T>::IOhandler()
{
    context = "value of type " + string(typeid(T).name());
}

template <typename T>
IOhandler<T>::IOhandler(string ctxt)
{
    context = ctxt;
}

template <typename T>
T IOhandler<T>::getInput()
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

template <typename T>
void cmdParser<T>::addExit()
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

template <typename T>
T cmdParser<T>::run(string command)
{
    return commands.at(command)();
}

template <typename T>
void cmdParser<T>::addCommand(string s, function<T()> f)
{

    commands[s] = f;
}

template <typename T>
cmdParser<T>::cmdParser()
{
    // addExit();
    context = "";
}

template <typename T>
cmdParser<T>::cmdParser(string ctxt)
{
    //  if(add_exit){addExit();}
    context = ctxt;
}

template <typename T>
void cmdParser<T>::listCommands()
{
    cout << context << endl;
    cout << "Possible commands: " << endl;
    for (const auto &[key, value] : commands)
    {
        cout << " - " << key << '\n';
    }
}

template <typename T>
T cmdParser<T>::loopCommands(bool add_exit)
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
template <typename T>
string cmdParser<T>::getContext()
{
    return context;
}

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
