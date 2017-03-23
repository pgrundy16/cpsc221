#include "Hashtable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/* Additional Questions

(i) Under what load factors is linear probing just as good as quadratic probing? When does quadratic
begin to win out?
	Quadratic creates less cluster formations. The average number of probes
	  will be lower because entries are more spread out.


(ii) How does the choice of hash function affect double hashing? Can you devise a hash function that
makes double hashing just as good as quadratic probing? Can you make it even better? Make
sure you try a few to be able to justify your answer.
	The '3' limits the hash to jumps of 1, 2, 3 which creates more clusters than the quadratic
	  probing algorithm becuase the jumps are closer together.
	A better hash function would be a lastPrime (within _size) method. Where,
	  
		hash2(k) = lastPrime - (k % lastPrime)

	  becuase you could have jumps anywhere from 1, 2, ... , lastPrime
	  and if the values are large enough you will be able to create less cluster formations
	  and still have a very fast algorithm. 


(iii) When does double hashing begin to win against both of the other schemes? (i.e., at what capacities
and load factors do you see a significant gain over the other methods?)
	With large tables, but mainly, when numberKeys > hashTable.. an issue that becomes a problem
	  very fast with linear probing and also with quadratic probing over time.

(iv) Finally, which open addressing scheme would you choose and why? Would you always choose this
scheme?
	Quadratic Hashing. It is easy/cheap to implement and works better than linear-probing
	  on large-scale project applications.


End of Questions */

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

		/* Testing Linear Probing Functionality 
	
			Size = 8 -> Goes to 11 (1st prime)
			Adding (In Order) 	: 		
			[8]		8 mod 11 = 8 		-> Set at index 8
			[7]		7 mod 11 = 7		-> Set at index 7
			[11]	11 mod 11 = 0		-> Set at index 0
			[22]	22 mod 11 = 0		-> Tries at 0, sets at 1
			[10]	10 mod 11 = 10		-> Sets at index 10
			[21]	21 mod 11 = 10		-> Tries 10, tries 0, tries 1, sets at index 2
		*/

		Hashtable htl(8);

		cout << "\n++ Linear Probing ++\n" << endl;

		/* Normal Inputs. */
		htl.linsert(8); 	
		htl.linsert(7);		
		htl.linsert(15); 	
		htl.linsert(11);
		/* First Collision */
		htl.linsert(22);
		/* Loopback Collision */
		htl.linsert(10);
		htl.linsert(21);

		/* Reset Hashtable. */
		htl.clear();

		/* Testing Quadratic Probing Functionality 
	
			Size = 8 -> Goes to 11 (1st prime)
			[2]		2 mod 11 = 2		-> Set at index 2
			[13]	13 mod 11 = 2		-> Tries index 2, sets at index 3 (1^2)
			[24] 	24 mod 11 = 2		-> Tries index 2, tries index 3, sets at index 7 (3 + 2^2)
			[35]	35 mod 11 = 2		-> Tries index 2, tries index 3, tries index 7, loops and fails.
			[10]	10 mod 11 = 10		-> Set at index 10
			[21]	21 mod 11 = 10		-> Tries at index 10, loops and inserts at index 0
		*/

		cout << "\n++ Quadratic Probing ++\n" << endl;

		/* Normal Input */
		htl.qinsert(2);
		/* Adjacent Collision */
		htl.qinsert(13);
		/* By-Two Collision */
		htl.qinsert(24);
		/* Miss. */
		htl.qinsert(35);
		/* Show Looping Works */
		htl.qinsert(10);
		/* Collision. */
		htl.qinsert(21);

		/* Reset hashtable. */
		htl.clear();

		/* Testing Functionality of Double-Hashing 
		
			Size = 8 -> Goes to 11 (1st prime)
			[1]	1 mod 11 = 1			-> Set at index 1
			[12] 12 mod 11 = 1			-> Tries at index 1, sets with hash2 at index 4
			[23] 23 mod 11 = 1			-> Tries index 1, sets with hash2 at index 2
		*/

		cout << "\n++ Double Hashing ++\n" << endl;

		/* Normal insert. */
		htl.dinsert(1);
		/* Collisions. */
		htl.dinsert(12);
		htl.dinsert(23);

		/* Reset hashtable. */
		htl.clear();


		/* Testing All Algorithms for Large Numbers. */
		int size1 = 10000;

		Hashtable lin(size1);
		Hashtable quad(size1);
		Hashtable doub(size1);

		/* === Test 1 === */

		for (int i = 0; i < 7500; i++) {
			lin.linsert(rand() + 1);
			quad.qinsert(rand() + 1);
			doub.linsert(rand() + 1);
		}

		cout << "\n++ Stats 1: \n" << endl;

		lin.printStats();
		quad.printStats();
		doub.printStats();

		/* === Test 2 === */
		lin.clear();
		quad.clear();
		doub.clear();
		
		for (int i = 0; i < 20000; i++) {
			lin.linsert(rand() + 1);
			quad.qinsert(rand() + 1);
			doub.linsert(rand() + 1);
		}	

		cout << "\n++ Stats 2: \n" << endl;

		lin.printStats();
		quad.printStats();
		doub.printStats();	

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

