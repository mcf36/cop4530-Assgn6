#include <iostream>
#include <string>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

int main()
{
    // AI-Generated Test File (NOT PART OF SUBMISSION)

    HashTable<std::string, int> hashTable(10);

    // Load data from a file into the hash table
    std::cout << "Loading data from file..." << std::endl;
    if (hashTable.load("data.txt")) {
        std::cout << "Data loaded successfully." << std::endl;
    } else {
        std::cout << "Failed to load data from file." << std::endl;
    }

    // Display all entries in the hash table after loading
    std::cout << "Hash table after loading:" << std::endl;
    hashTable.dump();

    // Insert a new key-value pair using the move version of insert
    std::cout << "Inserting a new key-value pair using the move version of insert..." << std::endl;
    hashTable.insert(std::make_pair("grape", 4)); // Using move version
    std::cout << "Insertion completed." << std::endl;

    // Check if keys exist
    std::cout << "Contains 'apple': " << (hashTable.contains("apple") ? "true" : "false") << std::endl;
    std::cout << "Contains 'grape': " << (hashTable.contains("grape") ? "true" : "false") << std::endl;

    // Update value for an existing key
    hashTable.insert(std::make_pair("apple", 5));

    // Check size of the hash table
    std::cout << "Size: " << hashTable.size() << std::endl;

    // Write the hash table data to a file
    std::cout << "Writing data to file..." << std::endl;
    if (hashTable.write_to_file("output.txt")) {
        std::cout << "Data written to file successfully." << std::endl;
    } else {
        std::cout << "Failed to write data to file." << std::endl;
    }

    // Remove a key-value pair
    std::cout << "Removing 'banana'..." << std::endl;
    if (hashTable.remove("banana")) {
        std::cout << "'banana' removed successfully." << std::endl;
    } else {
        std::cout << "'banana' not found in the hash table." << std::endl;
    }

    // Check size after removal
    std::cout << "Size after removal: " << hashTable.size() << std::endl;

    // Display all entries in the updated hash table
    std::cout << "Updated hash table:" << std::endl;
    hashTable.dump();

    return 0;

    return 0;
}
