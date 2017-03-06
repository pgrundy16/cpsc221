#include <cstdlib> // for atoi
#include <iostream>

// prototype
void moveDisks(int n, const char* FROM, const char* VIA, const char* TO);

int main(int argc, char *argv[]) {
 if (argc != 2) {
 std::cout << "Usage: " << argv[0] << " number_of_disks" << std::endl;
 return -1;
 }
 moveDisks( atoi(argv[1]), "peg A", "peg B", "peg C" );
 return 0;
}

/* Towers of Hanoi using Recursion
 *
 * pegs A,B,C
 * The objective is to move the entire stack from peg A to C
 *
 * RULES
 * - only one disk moved at a time
 * - each move consists of taking the upper disk and sliding it
 	onto another peg
 * - no disk may be placed on top of a smaller disk
 */
void moveDisks(int n, const char* FROM, const char* VIA, const char* TO) {
/* Expected Output
Move disk from peg A to peg C
Move disk from peg A to peg B
Move disk from peg C to peg B
Move disk from peg A to peg C
Move disk from peg B to peg A
Move disk from peg B to peg C
Move disk from peg A to peg C 
*/
	if(n == 0) return;
	// move n-1 disks from A(FROM) to C(VIA)
	moveDisks(n-1, FROM, TO, VIA);
	std::cout << "Move disk from " << FROM << " to " << TO << std::endl;
	// move n-1 disks from B(VIA) to C(TO)
	moveDisks(n-1, VIA, FROM, TO);
}


 
