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
using namespace cop4530;            // Custom namespace

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
HashTable<K, V>::HashTable(size_t size) : count(0) {
    size = prime_below(size);
    myTable.resize(size);
}

template<typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& k) {
    auto& l = myTable[myhash(k)];
    for (const auto& kv : l) {
        if (kv.first == k) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V>& kv) {
    auto& l = myTable[myhash(kv.first)];
    for (const auto& pair : l) {
        if (pair == kv) {
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V>& kv) {
    auto& l = myTable[myhash(kv.first)];
    for (auto& pair : l) {
        if (pair.first == kv.first) {
            pair.second = kv.second;
            return true;
        }
    }
    l.push_back(kv);
    if (++count > myTable.size())
        rehash();
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V>&& kv) {
    auto& l = myTable[myhash(kv.first)];
    for (auto& pair : l) {
        if (pair.first == kv.first) {
            pair.second = move(kv.second);
            return true;
        }
    }
    l.push_back(move(kv));
    if (++count > myTable.size())
        rehash();
    return true;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& k) {
    auto& l = myTable[myhash(k)];
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (it->first == k) {
            l.erase(it);
            --count;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}

template<typename K, typename V>
bool HashTable<K, V>::load(const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    makeEmpty();

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        K key;
        V value;
        if (!(iss >> key >> value)) {
            cerr << "Error parsing line: " << line << endl;
            return false;
        }
        insert(make_pair(key, value));
    }

    file.close();
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::dump() {
    for (const auto& list : myTable) {
        for (const auto& pair : list) {
            cout << pair.first << ":" << pair.second << "; ";
        }
        cout << endl;
    }
}

template<typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    for (const auto& list : myTable) {
        for (const auto& pair : list) {
            file << pair.first << " " << pair.second << endl;
        }
    }

    file.close();
    return true;
}

template<typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (auto& list : myTable) {
        list.clear();
    }
    count = 0;
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

