#include <iostream>
#include <fstream>      // This will be used for reading/writing files later
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

