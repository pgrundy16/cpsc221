#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#define EMPTY -1	// indicates an empty slot (so don't hash -1)

/* Defined Hashtable with functions. */
class Hashtable {
public:
	/* Constructor / Destructor */
	Hashtable(int size);
	~Hashtable();

	/* Public Functions Below. */

	int hash(int key);

	// Quadratic Probing
	void qinsert(int key);
	
	// Linear Probing
	void linsert(int key);

	// Double Hashing
	void dinsert(int key);

	void print();
	void printStats();
	float probeRate();
	void clear(); 
	bool checkValue(int key, int index);

private:
	int* _table;
	int _size;
	int _totalProbes;
	int _numInserts;
	int _numFailures;
	
	void tallyProbes(int p);	
	int nextPrime(int n);
	bool isPrime(int n);
	bool isPrime(int n, int divisor); 
};

#endif
