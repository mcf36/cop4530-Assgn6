#include <iostream>
#include <fstream>      // This will be used for reading/writing files later
#include <sstream>      // Using sstream to parse file data
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <functional>
#include "passserver.h"
#include "base64-1.cpp"

using namespace std;


PassServer::PassServer(size_t size)
{
    theTable = new HashTable<string, string>(size);     // Dynamically allocate new hash table
}

PassServer::~PassServer()
{
    theTable->clear();                                  // Clear table before deleting it
    delete theTable;                                    // Delete table after
}

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
        BYTE valueIn[100];
        BYTE valueOut[100];

        if (!(iss >> key >> valueIn))                           // If we cannot parse line for any reason, return error
        {
            cerr << "Error parsing line: " << line << endl;
            return false;
        }
        base64_encode(valueIn, valueOut, strlen(valueIn), 1);   // Encode password before adding it

        theTable->insert(make_pair(key, valueOut));            // Call user-defined method to add to hash table
    }

    file.close();                                             // If file is parsed correctly, close it and return true
    return true;
}

bool PassServer::addUser(std::pair<std::string, std::string>& kv)
{

}

bool PassServer::addUser(std::pair<std::string, std::string>&& kv)
{
    // Implement the move version of addUser
    // Encrypt the password before insertion
    // Return true if successful, false otherwise
}

bool PassServer::removeUser(const std::string& k) {
    // Implement removing an existing user with the username k from the hash table
    // Return true if successful, false otherwise
}

bool PassServer::changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword) {
    // Implement changing an existing user's password
    // Encrypt both old and new passwords before interacting with the hash table
    // Return true if successful, false otherwise
}

bool PassServer::find(const std::string& user) {
    // Implement checking if a user exists in the hash table
    // Return true if found, false otherwise
}

void PassServer::dump() {
    // Implement showing the structure and contents of the hash table
}

size_t PassServer::size() {
    // Implement returning the size of the hash table (number of username/password pairs)
}

bool PassServer::write_to_file(const char* filename) {
    // Implement un-encrypting the password and saving username/password combination to a file
    // Return true if successful, false otherwise
}

std::string PassServer::encrypt(const std::string& str) {
    // Implement the encryption of the parameter str and return the encrypted string
}