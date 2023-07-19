#include <iostream>
#include <fstream>      // This will be used for reading/writing files later
#include <sstream>      // Using sstream to parse file data
#include <string>
#include <list>
#include <vector>
#include <iterator>
#include <utility>
#include <functional>

using namespace std;


// ***********************************************
// * Name: hashtable.hpp
// * Description: Implements HashTable ADT class
// *  from hashtable.h.
// * Author: Mason Finnell
// * Date: 17 July 2023
// * References: Data Structures and Algorithms,
// *   4th Edition, Mark A. Weiss
// *   Dr. David A. Gaitros.
// ***********************************************

template<typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
    count = 0;

    size_t tempsize = prime_below(size);
    myTable.resize(tempsize);
}

template<typename K, typename V>
HashTable<K, V>::~HashTable()
{
    this->makeEmpty();              // Call user-defined clear function
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& k)
{
    auto& l = myTable[myhash(k)];               // Find vector index using myhash() function and iterate through it

    for (const auto& kv : l)                    // range-based for loop
    {
        if (kv.first == k)                      // Check keys (ordered first in pair); return true if found
        {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V>& kv)
{
    auto& l = myTable[myhash(kv.first)];

    for (const auto& pair : l)
    {
        if (pair == kv)
        {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V>& kv)
{
    auto& l = myTable[myhash(kv.first)];                // Call myhash() to find table index with the list we want

    for (auto& pair : l)                                // Range-based for loop
    {
        if (pair.first == kv.first)                     // Checking if we already have the key stored
        {
            if(pair.second == kv.second) return false;  // If it's already in the hash table, return false

            pair.second = kv.second;                    // If only keys are identical, update the value and return true
            return true;
        }
    }
    l.push_back(kv);                                    // If key isn't present, add pair to the END of list

    ++count;                                           // Update private count of pairs
    if (count > myTable.size()) rehash();              // Checking if we need to rehash all pairs or not

    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V>&& kv)
{
    auto& l = myTable[myhash(kv.first)];                 // Call myhash() to find table index with the list we want

    for (auto& pair : l)                                 // Range-based for loop
    {
        if (pair.first == kv.first)                     // Checking if we already have the key stored
        {
            if(pair.second == kv.second) return false;  // If it's already in the hash table, return false

            pair.second = move(kv.second);              // Update value with std::move
            return true;
        }
    }
    l.push_back(move(kv));                             // If key isn't present, move pair to the END of list

    ++count;                                           // Update private count of pairs
    if (count > myTable.size()) rehash();              // Checking if we need to rehash all pairs or not

    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k)
{
    auto& l = myTable[myhash(k)];                      // Call myhash() to find table index with the list we want


    for(auto& pair : l)                               // Range-based for loop
    {
        if (pair.first == k)                          // Looking for key of pair to be deleted
        {
            l.erase(pair);
            --count;
            return true;
        }
    }
    return false;                                       // If we couldn't find pair to delete, return false
}

template<typename K, typename V>
void HashTable<K, V>::clear()
{
    makeEmpty();                                        // Call private member to empty vector table
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename)
{
    ifstream file(filename);                         // Using ifstream to parse file data

    if (!file)                                          // If we cannot open it for any reason, return error
    {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    this->makeEmpty();                                        // Clear our table before adding to it

    string line;
    while (getline(file, line))                        // Parsing data line-by-line
    {
        istringstream iss(line);                          // Temp variables that will reset each line
        K key;
        V value;

        if (!(iss >> key >> value))                           // If we cannot parse line for any reason, return error
        {
            cerr << "Error parsing line: " << line << endl;
            return false;
        }
        this->insert(make_pair(key, value));            // Call user-defined method to add to hash table
    }

    file.close();                                             // If file is parsed correctly, close it and return true
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump()
{
    for (const auto& list : myTable)                          // Range-based for loop; iterate through vector
    {
        for (const auto& pair : list)                         // Nested range-based for loop; iterate through list
        {
            cout << pair.first << ":" << pair.second << "; ";   // Output each pair with a ':' as delimiter
        }
        cout << endl;
    }
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename)
{
    ofstream file(filename);                                // Use ofstream to create file

    if (!file)                                                // If we cannot open it for any reason, return error
    {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    for (const auto& list : myTable)                        // Range-based for loop; iterate through vector
    {
        for (const auto& pair : list)                       // Nested range-based for loop; iterate through list
        {
            file << pair.first << " " << pair.second << endl;   // Write one pair per line with " " as delimiter
        }
    }

    file.close();                                           // If file is written correctly, close it and return true
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
    for (auto& list : myTable)          // Range-based for loop
    {
        list.clear();                   // Use std clear() method to vacate the list
    }

    count = 0;                          // Reset count
}

template<typename K, typename V>
void HashTable<K, V>::rehash()
{
    vector<list<pair<K, V>>> oldTable = myTable;            // Temp copy of current table

    myTable.resize(prime_below(2 * myTable.size()));     // Double current table's size

    this->makeEmpty();                                     // Clear table after resizing it

    for (const auto& list : oldTable)                      // Range-based for loop using old table as iterator
    {
        for (const auto& pair : list)                      // Nested range-based for loop iterating through each old list
        {
            this->insert(pair);                           // Insert each old pair into new table
        }
    }
}

template<typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k)                  // fixme: Redo this hash function later
{
    static hash<K> hf;
    return hf(k) % myTable.size();
}

// ***********************************************
// * Name: unsigned long prime_below()
// * Description: Returns largest prime number <= n
// *  or zero if input is too large. This is likely
// *  to be more efficient than prime_above(), because
// *  it only needs a vector of size n.
// * Author: Dr. David A. Gaitros
// * Date: 17 July 2023
// * References: N/A
// ***********************************************

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below(unsigned long n)
{
  if (n > max_prime)
    {
      cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}


// ***********************************************
// * Name: void setPrimes(vector<unsigned long>& vprimes)
// * Description: Sets all prime number indexes to 1.
// *  Called by method prime_below(n).
// * Author: Dr. David A. Gaitros
// * Date: 17 July 2023
// * References: N/A
// ***********************************************

template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

