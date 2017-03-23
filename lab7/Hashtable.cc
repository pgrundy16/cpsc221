#include "Hashtable.h"
#include <cstdlib>
#include <iostream>
#include <cassert> 
#include <math.h>

using namespace std; 

/* Constructor */
Hashtable::Hashtable(int size) {
	int prime = nextPrime( size ); 
	_size = size;
	
	/* Declare Hashtable size as the closest prime number to 'size'. */
	if (prime != size) 
	{ 
	  cout << "Warning: size = " << size << " is not a prime number." << endl; 
/* uncomment these if you want */ 
	  cout << "Using " << prime << " instead." << endl; 
	  _size = prime; 
	}

	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 
	_table = new int [ _size ];

	/* Initialize all Hashtable elements to -1. */
	for (int ii=0; ii < _size; ii++) 
		_table[ ii ] = EMPTY;
}

/* Clear (Resert) Hashtable. */
void Hashtable::clear(void) {
	_totalProbes = 0;
	_numInserts = 0;
	_numFailures = 0; 

	/* Set all Hashtable elements to -1. */
	for (int ii=0; ii < _size; ii++) 
		_table[ ii ] = EMPTY;
}    
    
/* Destructor. */
Hashtable::~Hashtable() {
	/* Deallocate memory space in heap. */
	delete[] _table;
}


/* Add the number of probes, p, for one insert operation to the tally. */
void Hashtable::tallyProbes(int p) {
	_totalProbes += p;
	_numInserts += 1;
}

/* Print Statistics:
 * 	=> Average Probes (per Insert)
 *  
 *	=> Size of Hashtable
 *
 *	=> Number of Failures
 *
 */
void Hashtable::printStats() {
	cout << "Average probes/insert = " <<
			probeRate() << " = " <<
			_totalProbes << "/" << _numInserts;
	cout <<", size = "<< _size;
	cout <<", failures = " << _numFailures << endl;
}

/* Returns the probe rate for printStats() */
float Hashtable::probeRate() {
	return (float)_totalProbes / (float)_numInserts;
}

/* Returns the remainder of k into _size. */
int Hashtable::hash(int k) {
	return k % _size;
}

/* Returns the seconary hash function. */
int Hashtable::hash2(int k)
{
	/* My prime number */
	int r = 3;

	return ( r - ( k % r) );
}

/* Quadratic Probing Insert Algorithm
 *
 * Precondition: 
 *	Takes a number key k
 *
 * Postcondition:
 *	Puts it into _table[k mod(_size)] if empty
 * 	 or into first available index using _table[i*i]
 *	 where 'i' goes from 1 -> forward until first spot is
 *	 found and loops back around, if necessary.   
 */
void Hashtable::qinsert(int k) {
// Insert k in the hash table.
// Use open addressing with quadratic probing and hash(k) = k % _size.

// Tips:
// - Look at the lecture slides if you don't remember how to implement these.
// - You need to prevent against infinite loops. You should limit the number
// of times you probe and print an error message upon exceeding this limit.
// - You're welcome to add new declarations to hash.h, add to the constructor,
// include libraries, or anything else you need. 
// - You're also welcome to modify the main() method to automate your testing.

    // ************* ADD YOUR CODE HERE *******************
    
    bool flag = false;
    int original_index = hash(k);
    int index = original_index;
    int numProbes = 0;
    int multiple = 1;

	/* If desired index is empty. */	
	if(_table[index] == -1) 
	{
		// Testing
		cout << "Empty location found for key " 
		<< k << " at index " << index << endl;
		
		_table[index] = k;
		tallyProbes(numProbes); 
		return; 
	}

	index = index + pow((multiple++), 2);
	numProbes++;

	/* Loop around. */
	if(index >= _size)
	{
		/* Turn flag */
		flag = true;
		index = index % _size;
	}

	/* Quadratic Probing */
	while( (original_index <= index && !flag) || (index <= original_index && flag) )
	{

		/* Check if empty spot found. */
		if(_table[index] == -1)
		{
			// Testing
			cout << "Other location found for " << k 
			<< " at index " << index << endl; 
			
			_table[index] = k;
			tallyProbes(numProbes);
			return;
		}

		/* Loop around. */
		if(index >= _size && !flag)
		{
			/* Turn flag */
			flag = true;
			index = index % _size;
		}
		
		index += pow((multiple++), 2);
		numProbes++;
		
	}
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: qinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

void Hashtable::linsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with linear probing and hash(k) = k % _size.

    // ************* ADD YOUR CODE HERE *******************
    
    int original_index = hash(k);
    int index = original_index;
    int numProbes = 0;
	
	/* If desired index is empty. */	
	if(_table[index] == -1) 
	{
		// Testing
		cout << "Empty location found for key " 
		<< k << " at index " << index << endl;
		
		_table[index] = k; 
		tallyProbes(numProbes);
		return; 
	}		

	/* Look until first empty index is found. */
	index = (index == _size) ? 0 : (index + 1);
	numProbes++;

	while(index != original_index)
	{
		/* Loop back around. */
		if(index == _size) 
			index = 0;

		if(_table[index] == -1)
		{
			_table[index] = k;
			tallyProbes(numProbes);

			// Testing
			cout << "Other location found for " << k 
			<< " at index " << index << endl; 
			return;
		}
		
		index++;
		numProbes++;
	}
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: linsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

void Hashtable::dinsert(int k) {
	// Insert k in the hash table.
	// Use open addressing with double hashing. Use the existing hash function
	// and also implement a second hash function.

    // ************* ADD YOUR CODE HERE *******************
    
    bool flag = false;
    int original_index = hash(k);
    int index = original_index;
    int numProbes = 0;

	/* If desired index is empty. */	
	if(_table[index] == -1) 
	{
		// Testing
		cout << "Empty location found for key " 
		<< k << " at index " << index << endl;
		
		_table[index] = k; 
		tallyProbes(numProbes);
		return; 
	}

	/* Declare only a second-hash on collisions. */
    int multiple = 1;
	int buckets = hash2(k);

	/* Look until first empty index is found. */
	index = ( index + (buckets * multiple++) ) % _size;
	numProbes++;
	
	/* Loop around. */
	if(index >= _size && !flag)
	{
		/* Turn flag */
		flag = true;
		index = index % _size;
	}


	/* Quadratic Probing */
	while( (original_index < index && !flag) || (index < original_index && flag) )
	{
		/* Check if empty spot found. */
		if(_table[index] == -1)
		{
			_table[index] = k;
			tallyProbes(numProbes);

			// Testing
			cout << "Other location found for " << k 
			<< " at index " << index << endl; 
			return;
		}
		
		/* Loop around. */
		if(index >= _size && !flag)
		{
			/* Turn flag */
			flag = true;
		}
		
		numProbes++;
		index = ( index + (buckets * multiple++) ) % _size;
	}
    
    // Your method should return after it stores the value in an EMPTY slot 
    // and calls tallyProbes, so if it gets here, it didn't find an EMPTY slot 
    _numFailures += 1; 
    cout << "Warning: dinsert(" << k << ") found no EMPTY slot, so no insert was done." << endl; 
}

/* Print the content of the hash table. */
void Hashtable::print() {
	for (int i=0; i<_size; i++) {
		cout<<"["<<i<<"] ";
		if (_table[i] != EMPTY)
			cout << _table[i];
		cout << endl;
	}
}

/* Check if value k is at index i. */
bool Hashtable::checkValue(int k, int i) { return (_table[i] == k); }

/* Returns the next prime number closest to n. */
int Hashtable::nextPrime( int n ) { 
    int loops = (n < 100) ? 100 : n;
    for (int ii = 0; ii < loops; ii++ ){ 
      if ( isPrime( n + ii ) ) return (n + ii); 
    }
    assert( false ); // logic error 
}

/* Checks if the number n is prime. */
bool Hashtable::isPrime( int n ) { 
    if (n < 2) return false; 
    if (n == 2) return true;
    if (n % 2 == 0) return false;  
    return isPrime( n, 3 ); 
}
/* Helper Method :: isPrime(..) */
bool Hashtable::isPrime( int n, int divisor ){ 
    if ((divisor * divisor) > n) return true; 
    if ((n % divisor) == 0) return false; 
    return isPrime( n, divisor + 2 ); 
}

