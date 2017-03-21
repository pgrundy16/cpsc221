#include <iostream>
#include <ctime>
#include <cstdlib>

#define NUM_TRIALS 10

/* [Global] Array of integers.*/
int * x;

/* [Global] Number of Comparisons */
long comps;

using namespace std;

/* 
 * Swap() : Swaps the array elements at index 
 *  locations a and b.
 */
void swap(int & a, int & b) {
  int tmp = a;
  a = b;
  b = tmp;
}

/* 
 * RandInt() : Returns a random number.
 */
int randint(int a, int b) {
  return a + (rand() % (b - a + 1));
}

/*
 * A QuickSort recursive function to
 *  sort a list of integers.
 */
void quicksort(int a, int b) {
  if (a >= b) 
    return;
  
  /* Select a random pivot. */
  int p = randint(a,b); // pivot

  swap(x[a], x[p]);

  int m = a;
  int i;
  
  /* In-Place Partition */  
  for (i = a+1; i <= b; i++) {
    /* Increment comparisons*/
    comps++;
    if (x[i] < x[a]) 
    {

      /* Swap. */
      swap(x[++m], x[i]);
    }
  }
  
  swap(x[a],x[m]);
  quicksort(a, m-1);
  quicksort(m+1, b);
}

/*
 * Qc() : Returns the number of comparisons
 *  that a quick-sort algorithm would perform.
 */
int qc(int N) 
{ 
  /* When our list is no-elements. */
  if(N == 0) return 0;

  int pivot = randint(0, N-1);

  /* Partion : N-1 comparisons + 
   * qc(pivot) refers to LEFT sublist from 0 to piv-1
   * qc(N-1 - pivot) refers to RIGHT sublist with 
      from 0 to (N-1-pivot) elements
   * Therefore by looking at 'element'-size instead of actual 
      indeces we can find num comps. 
   */
  return qc(pivot) + qc((N-1) - pivot) + (N-1);
}

/*
 * The Main Fuction of our program.
 */
int main(int argc, char *argv[]) {
  srand(time(0));

  /* Test Program Comparisons for three NN sizes. */  
  int sizes[3] = {10, 100, 1000};
  for(int NN : sizes) 
  {
    /* Initialize comps to 0. */
    comps = 0;

    /* Create a new List. */
    x = new int[NN];

    /* Generate NN random numbers and initialize all array els. */
    for (int i = 0; i < NN; ++i) 
      x[i] = rand() % NN;

    /* Execute NUM_TRIALS trials for each size. */
    int i, tally = 0;
    for(i = 0; i < NUM_TRIALS; i++) {
      /* Reset params. */
      comps = 0;

      /* Run QuickSort */
      quicksort(0, NN-1);
      
      /* Run Custom QuickSort Comps Counter. */
      cout << "Custom QC: " << qc(NN) << endl;

      /* Add number of comparisons to tally. */
      tally += comps;

      cout << "Size: " << NN << " at Round: " << (i+1) 
        << " with Comparisons: " << comps << "\n" << endl;
    }

    cout << "++ Average Comparisons for 10 Trials: "
      << (double) (tally / 10) << " ++\n" << endl;

    /* Print Sorted List. */
    // for (int i=0; i<NN; ++i) 
    //   std::cout << x[i] << " ";
    // std::cout << std::endl;

    /* Deallocate DRAM and return from Main. */
    delete[] x;
  }


  /* Call QuickSort on global List x. */
  // quicksort(0, NN-1);

  return 0;
}
