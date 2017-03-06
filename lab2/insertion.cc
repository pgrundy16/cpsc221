#include <iostream>
#include <cstdlib>
#include "insertion.h"

using namespace std;

// store command-line arguments in x[] array 
void getArgs( int argc, char **argv ) {
  // the number of items passed equals argc - 1 b/c the 1st arg is the filename
  x_size = argc - 1;
  for( int i = 0; i < x_size; i++ ) {
    // for each element, convert every (arg1 to arg10), store 10 long-ints into array x
    x[i] = atoi( argv[ i+1 ] );    
  }
}

void scootOver( int j ) {
  int k;
  for( k = y_size; k > j; k-- )
    y[k] = y[ k-1 ];
}

void insert( int xx ) {
  int j;

  // if y array is empty, put first item in index=0 position
  if( y_size == 0 ) {
    y[0] = xx;
    return;
  }
  // Need to insert just before the first y element that xx is less than
  for( j=0; j< y_size; j++ ) {
    if( xx < y[j] ) {
      // shift y[j], y[j+1], ... rightward before inserting xx
      scootOver( j );
      y[j] = xx;
      return;
    }
  }  
  // if it reaches the end of the for loop and a value has still not been returned
  y[y_size] = xx;
  return;
}

// --- this function has no errors
void processData() {
  for( y_size = 0; y_size < x_size; y_size++ )  {
    // insert x value in the proper place among y[0],....,y[y_size-1]    
    insert( x[ y_size ] );
  }
}

void printResults() {
  for( int i=0; i<x_size; i++ )
    cout << y[i] << " ";
  cout << endl;
}

int main( int argc, char ** argv ) {
  getArgs( argc, argv ); // --- this call has no errors
  processData(); // --- found one error inside scootover for-loop with = sign to evaluate correctly
  printResults();
  return 0;
}
