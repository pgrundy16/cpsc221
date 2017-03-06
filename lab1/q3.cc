#include <iostream>
// global array-int variable for our functions below
#define SIZE 10
 int glbl_array[SIZE];
 
// function declarations
 void fill_array();
 void fill_array(int a, int b);
 void printArray();
 
 /*
 * Declare a global array with 10 elements 
 * 
 * A) Write a function 'fill_array', no params., to fill the elements with numbers 1 to 10
 * Call 'fill_array' from main(), and print contents of array to screen
 *
 * B) Modify the function (and its call) so it accepts to int's as params.
 * First int represents the vlaue to be assigned to 1st el.,
 * Second int represents increment between each element.
 * Contens of array should be printed to screen after 'fill_array()' returns
 *
 */
int main(void) {
	int initial, increment;
	
	// calling part A
	fill_array();
	printArray();
	
	// calling part B
 std::cout << "Enter Initial Value" << std::endl;
 std::cin >> initial;
 std::cout << "Enter Increment Value" << std::endl;
 std::cin >> increment;
	fill_array(initial,increment);
	printArray();
	
	return 0;	
} 

void fill_array() {
	for(int i=0; i<SIZE;i++) glbl_array[i]=i+1;
	return;
} 

void fill_array(int a, int b) {
	glbl_array[0]=a;
	for(int i=1; i<SIZE; i++) glbl_array[i]=a + (b*i);
	return;
}

void printArray() {
	for(int i=0;i<SIZE;i++) std::cout << glbl_array[i] << std::endl;
}
