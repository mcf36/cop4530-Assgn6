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
/*    PassServer myServer;

    if(myServer.addUser(make_pair("Mason", "password0"))) cout << "Successfully added user." << endl;

    if(myServer.find("Mason")) cout << "Successfully found user." << endl;

    cout << "--------------------------------" << endl;

    myServer.addUser(make_pair("John", "password1"));
    myServer.addUser(make_pair("Joe", "password2"));
    myServer.addUser(make_pair("Sal", "password3"));
    myServer.addUser(make_pair("Quinn", "password4"));
    myServer.addUser(make_pair("Richard", "password5"));

    myServer.write_to_file("tempOut.txt");
    myServer.dump();
    myServer.removeUser("Mason");
    cout << "--------------------------------" << endl;
    myServer.dump();
    myServer.removeUser("John");
    cout << "--------------------------------" << endl;
    myServer.dump();


    cout << "Routine complete. " << endl;       */

    PassServer myServer;                        // Server object
    string inStr;                               // Input string

    while(inStr != "x") {
        Menu();                                 // Display menu
        cin >> inStr;

        if (inStr == "l")                       // Load a file
        {
            string fileStr;
            cout << "Enter name of file to load: ";
            cin >> fileStr;

            if(myServer.load(fileStr.c_str()))
                cout << "File loaded successfully. Returning to menu." << endl;
            else
                cout << "ERROR: Could not load data file." << endl;
        }
        else if(inStr == "a")                   // Add a user
        {
            string user, pass;                  // Temp strings to hold input for username and password
            cout << "Enter a username: ";
            cin >> user;
            cout << "Enter a password: ";
            cin >> pass;

            if(myServer.addUser(make_pair(user, pass)))             // Checking if we successfully added user
                cout << "User added successfully. Returning to menu." << endl;
            else
                cout << "ERROR: Could not add user to server." << endl;
        }
        else if(inStr == "r")                   // Remove a user
        {
            string remUser;
            cout << "Enter name of user to remove: ";
            cin >> remUser;

            if(myServer.removeUser(remUser))
                cout << "User removed successfully. Returning to menu." << endl;
            else
                cout << "ERROR: Could not remove user from server." << endl;
        }
        else if(inStr == "c")                   // Change a password
        {
            string chgUser;
            cout << "Enter name of user to modify: ";
            cin >> chgUser;

            if(myServer.find(chgUser))
            {
                string oldPass, newPass;
                cout << "Enter old password for verification: ";
                cin >> oldPass;

                cout << "Enter new password: ";
                cin >> newPass;

                if(myServer.changePassword(make_pair(chgUser, oldPass), newPass))
                    cout << "Password changed successfully. Returning to menu." << endl;
                else
                    cout << "ERROR: Invalid password." << endl;
            }
            else cout << "ERROR: Could not find user." << endl;
        }
        else if (inStr == "f")                       // Find a user
        {
            string findStr;
            cout << "Enter name of user in the server: ";
            cin >> findStr;

            if(myServer.find(findStr))
                cout << "User is on the server. Returning to menu." << endl;
            else
                cout << "ERROR: Could not find user." << endl;
        }
        else if (inStr == "d")                       // Dump unencrypted contents of the server
        {
            cout << "Server List: " << endl;
            cout << "----------------------" << endl;
            myServer.dump();
        }
        else if (inStr == "s")                       // Return number of user/password pairs on server
        {
            cout << "Server Size: " << myServer.size() << endl;
            cout << "Returning to menu." << endl;
        }
        else if (inStr == "w")                       // Write server contents to a file
        {
            string fileStr;
            cout << "Enter name of file to be written: ";
            cin >> fileStr;

            if(myServer.write_to_file(fileStr.c_str()))
                cout << "File written successfully. Returning to menu." << endl;
            else
                cout << "ERROR: Could not write data file." << endl;
        }
        else if (inStr == "x")                      // Exit menu.
        {
            break;
        }
        else
        {
            cout << "ERROR: Invalid input." << endl;
        }
    }

    return 0;
}
