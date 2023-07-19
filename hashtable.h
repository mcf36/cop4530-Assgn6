#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <fstream>      // This will be used for reading/writing files later
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <functional>
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;

using namespace std;

// ***********************************************
// * Name: hashtable.h
// * Description: Declares HashTable class using
// *  a VLP structure (vector, list, pair) from
// *  the c++ STL.
// * Author: Mason Finnell
// * Date: 17 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************


namespace cop4530 {
    template<typename K, typename V>            // Template for our pairs
    class HashTable {
    public:
        HashTable(size_t size = 101);           // Default constructor; default size is 101
        ~HashTable();                           // Destructor
        bool contains(const K &k);              // check if key k is in the hash table.
        bool match(const pair<K, V> &kv);       // check if key-value pair is in the hash table.
        bool insert(const pair<K, V> &kv);      // add the key-value pair kv into the hash table.
        bool insert(pair<K, V> &&kv);         // move version of insert.
        bool remove(const K &k);               // delete the key k and the corresponding value if present
        void clear();                           //  delete all elements in the hash table
        bool load(const char *filename);        // load the content of the file into Hash table
        void dump();                            // display all entries in the hash table.
        bool write_to_file(const char *filename);// write all elements in the hash table to a file
        size_t size();                           // Returns number of entries in table
    private:
        size_t myhash(const K &k);              // Return index of vector where k should be stored
        size_t count = 0;
        vector<list < pair<K, V>>>
        myTable;       // Vector list of pairs representing hash table
        size_t vector_size;                     // Tracking how big our table (vector) is
        // Private helper functions:
        void makeEmpty();                       // Delete all elements in hash table
        void rehash();                          // Rehash when # of elements in table greater than vector size
        unsigned long prime_below(unsigned long n);  // Given function to find largest prime below
        void setPrimes(vector<unsigned long> &vprimes);
    };
}

#include "hashtable.hpp"        // Bring in definition file






#endif
