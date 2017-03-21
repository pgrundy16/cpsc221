#include "Hashtable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;


void usage(char* argv[]) {
	cerr << "Usage: " << argv[0] << " scheme numberOfKeys sizeOfTable" << endl;
	exit(-1);
}

/* Main Function Testing
 * 
 * Run : ./hash [charHashType] [numKeys] [sizeofHashtable]
 * 
 * Exampe: ./hash q 900000 1000000 
 * Runs quadratic probing with 900,000 keys in a size 1,000,000 Hashtable.
 *
 * Where,	argc 	: num arguments
 * 			argv[] 	: the two-dimensional character array with all args
 *			
 *			argv[0][0] : ./hash
 *			argv[1][0] : [charHashType]
 *			argv[2][0] : [numKeys]
 *			argv[3][0] : [sizeofHashtable]
 */
int main(int argc, char *argv[]) {
	int n, m;
	srand(time(0));

	/* If only passed the type of Hash algorithm to run. */
	if (argc == 1) 
	{
		/* Check if success. */
		cout << "You are running Eduardo's tests." << endl;

		/* ADD YOUR TEST CODE HERE */


		return 0;
	}
	
	/* If argument count is not valid,
		call usage() and exit program. */
	if (argc != 4) usage(argv);

	/* Atoi : ASCII to Integer
		Where,
			n = [numKeys]
			m = [sizeofHashtable]
	*/
	n = atoi(argv[2]);
	m = atoi(argv[3]);

	/* Initialize a Hashtable. */
	Hashtable H(m);
	
	/* Switch statement with [charType] algorithm. */
	switch(argv[1][0]) 
	{
	/* Run Linear Probing. */
	case 'l':
		/* Insert n random numbers into Hashtable
			using Linear Probing. */
		for (int i=0; i<n; ++i) 
			H.linsert(rand() + 1);

		//    H.print();
		cout << "Linear: ";  
		H.printStats();
		break;

	/* Run Quadratic Probing */
	case 'q':
		/* Insert n random numbers into Hashtable
			using Quadratic Probing. */
		for (int i=0; i<n; ++i) 
			H.qinsert(rand() + 1);

		//    H.print();
		cout << "Quadratic: ";
		H.printStats();
		break;

	/* Run Double Hashing */
	case 'd':
		/* Insert n random numbers into Hashtable 
			using Double Hashing. */
		for (int i=0; i<n; ++i) 
			H.dinsert(rand() + 1);

		//    H.print();
		cout << "Double Hashing: "; 
		H.printStats();
		break;

	/* Exit program if char not valid. */
	default:
		usage(argv);
	}
}

