#ifndef ASSGN6_PASSSERVER_H
#define ASSGN6_PASSSERVER_H

#include <string>
#include "hashtable.h"                  // Hash table template file

using namespace std;
using namespace cop4530;

// ***********************************************
// * Name: passserver.h
// * Description: Declares PassServer class using
// *  the HashTable template created earlier. Types
// *  will both be strings for each pair.
// * Author: Mason Finnell
// * Date: 19 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

class PassServer
{
public:
    PassServer(size_t size = 101);      // Default constructor; default size is 101
    ~PassServer();                      // Destructor
    bool load(const char* filename);            // Load a file containing
    bool addUser(pair<string, string>& kv);     // Adds a user (pair) to the system (hash table)
    bool addUser(std::pair<std::string, std::string>&& kv); // Move version
    bool removeUser(const std::string& k);
    bool changePassword(const std::pair<std::string, std::string>& p, const std::string& newpassword);
    bool find(const std::string& user);
    void dump();
    size_t size();
    bool write_to_file(const char* filename);
private:
    string encrypt(const string& str);                  // encrypt using base64 encoding files given
    HashTable<string, string> theTable;                 // Hash table containing string pairs
};



#endif //ASSGN6_PASSSERVER_H
