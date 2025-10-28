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
    IOhandler();
    IOhandler(string ctxt);

    T getInput();
};

template <typename T>
class cmdParser
{
private:
    string context;
    map<string, function<T()>> commands;
    void addExit();
    T run(string command);

public:
    void addCommand(string s, function<T()> f);
    cmdParser();
    cmdParser(string ctxt);
    void listCommands();
    T loopCommands(bool add_exit = true);
    string getContext();
};