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
    PassServer myServer(10);

    if(myServer.addUser(make_pair("Mason", "password"))) cout << "Successfully added user." << endl;

    cout << "Test. " << endl;

    return 0;
}
