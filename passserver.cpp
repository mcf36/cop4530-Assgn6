#include <iostream>
#include <fstream>      // This will be used for reading/writing files later
#include <sstream>      // Using sstream to parse file data
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <functional>
#include "base64-1.cpp"



// ***********************************************
// * Name: passserver.cpp
// * Description: Implements members defined in
// *  PassServer class using the HashTable template.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************


// ***********************************************
// * Name: PassServer Specified Constructor
// * Description: Creates a server with a size
// *  of the largest prime below the parameter.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

using namespace std;

PassServer::PassServer(size_t size)
{
    theTable = new HashTable<string, string>(size);     // Dynamically allocate new hash table
}


// ***********************************************
// * Name: PassServer Destructor
// * Description: First clears hash table, then
// *  deletes dynamically allocated object.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

PassServer::~PassServer()
{
    theTable->clear();                                  // Clear table before deleting it
    delete theTable;                                    // Delete table after
}


// ***********************************************
// * Name: bool load(const char* filename)
// * Description: Reads in user/pass string pairs
// *  from a file and inserts everything into server.
// *  Very similar routine to hashTable() method.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

bool PassServer::load(const char* filename)
{
    ifstream file(filename);                         // Using ifstream to parse file data

    if (!file)                                          // If we cannot open it for any reason, return error
    {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    theTable->clear();                                        // Clear our table before adding to it

    string line;
    while (getline(file, line))                        // Parsing data line-by-line
    {
        istringstream iss(line);                          // Temp variables that will reset each line
        string key;
        string value;

        if (!(iss >> key >> value))                           // If we cannot parse line for any reason, return error
        {
            cerr << "Error parsing line: " << line << endl;
            return false;
        }
        value = encrypt(value);                             // Encrypt value

        theTable->insert(make_pair(key, value));      // Call user-defined method to add to hash table
    }

    file.close();                                             // If file is parsed correctly, close it and return true
    return true;
}


// ***********************************************
// * Name: addUser(pair<string, string>& kv)
// * Description: Reads in user/pass string pair,
// *  encrypts the password using the given base64
// *  files, and adds the pair to the server.
// *  Very similar routine to hashTable() method.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

bool PassServer::addUser(pair<string, string>& kv)
{
    kv.second = encrypt(kv.second);                        // Update value with encrypted password
    return theTable->insert(kv);                              // Add pair to hash table
}


// ***********************************************
// * Name: addUser(pair<string, string>&& kv)
// * Description: Move version of addUser().
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

bool PassServer::addUser(pair<string, string>&& kv)
{
    kv.second = encrypt(kv.second);                        // Update value with encrypted password
    return theTable->insert(kv);                              // Add pair to hash table
}


// ***********************************************
// * Name: removeUser(const string& k)
// * Description: Removes a user/password pair from
// *  the server.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

bool PassServer::removeUser(const string& k)
{
    return theTable->remove(k);                               // Call template function to remove pair
}


// ***********************************************
// * Name: changePassword()
// * Description: Changes a password within the
// *  system. If it is not present or unsuccessfully
// *  inserted, return false and true otherwise.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

bool PassServer::changePassword(const pair<string, string>& p, const string& newpassword)
{
    auto myPair = p;                      // Copy of argument pair to be modified
    myPair.second = encrypt(p.second);               // Need to encrypt our password before comparing it in the table

    if(!theTable->match(myPair)) return false;       // If the pair isn't in the table, we cannot change the password

    myPair.second = encrypt(newpassword);            // Updating the pair's value to encrypted new password before insert

    if(!theTable->insert(myPair)) return false;      // HashTable insert method will update the password
    else return true;                                   // If everything executed properly, return true
}

bool PassServer::find(const string& user)
{
    return theTable->contains(user);
}

void PassServer::dump()
{
    // Implement showing the structure and contents of the hash table
}

// ***********************************************
// * Name: size()
// * Description: Returns number of users on server.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

size_t PassServer::size()
{
    return theTable->size();
}

bool PassServer::write_to_file(const char* filename)
{
    // Implement un-encrypting the password and saving username/password combination to a file
    // Return true if successful, false otherwise
}

// ***********************************************
// * Name: encrypt(const string& str)
// * Description: Private member that encodes a
// *  string in base64 encoding.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

string PassServer::encrypt(const string& str)
{
    BYTE valueIn[100];                                                    // Temp BYTE values for encryption
    BYTE valueOut[100];

    strcpy(valueIn, str.c_str());                             // Copy unencrypted password to BYTE array
    base64_encode(valueIn, valueOut, strlen(valueIn), 1);   // Encode password

    return valueOut;                                                      // Return encrypted string
}


// ***********************************************
// * Name: decrypt(const string& str)
// * Description: Private member that decodes a
// *  string from base64 encoding. Not required for
// *  assignment.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

string PassServer::decrypt(const string& str)
{
    BYTE valueIn[100];                                                   // Temp BYTE values for decryption
    BYTE valueOut[100];

    strcpy(valueIn, str.c_str());                            // Copy unencrypted password to BYTE array
    base64_decode(valueIn, valueOut, strlen(valueIn));   // Decode password

    return valueOut;                                                    // Return decrypted string
}