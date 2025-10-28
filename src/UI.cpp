#include "ui.h"
#include "order.h"

/*
cmdParser is an easy custom solution to have UI be able to excecute commands without a lot of reusing the same code.
*/


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
template class IOhandler<int>;
template class IOhandler<string>;
template class cmdParser<int>;
//template class cmdParser<void>;
template class cmdParser<string>;
template class cmdParser<float>;
template class cmdParser<char>;
template class cmdParser<CompletionStatus>;
template class cmdParser<Service>;