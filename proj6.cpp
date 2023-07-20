#include <iostream>
#include "passserver.h"

using namespace std;

void Menu()                                             // Displays input options to std output
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main ()
{
    PassServer myServer;

    if(myServer.addUser(make_pair("Mason", "password0"))) cout << "Successfully added user." << endl;

    if(myServer.find("Mason")) cout << "Successfully found user." << endl;

    myServer.addUser(make_pair("John", "password1"));
    myServer.addUser(make_pair("Joe", "password2"));
    myServer.addUser(make_pair("Sal", "password3"));
    myServer.addUser(make_pair("Quinn", "password4"));
    myServer.addUser(make_pair("Richard", "password5"));

   // myServer.write_to_file("tempOut.txt");
    myServer.dump();

    cout << "Routine complete. " << endl;

    return 0;
}
