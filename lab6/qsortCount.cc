#include <iostream>
#include <ctime>
#include <cstdlib>

int * x;
int comps = 0;

using namespace std;

void swap(int & a, int & b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int randint(int a, int b) {
  return a + (rand() % (b - a + 1));
}

void quicksort(int a, int b) {
  if (a >= b) return;
  
  int p = randint(a,b); // pivot
  swap(x[a], x[p]);
  int m = a;
  int i;
  
  // in-place partition:
  for (i = a+1; i <= b; i++) {
    if (x[i] < x[a]) {
      comps++;
      swap(x[++m], x[i]);
    }
  }
  
  swap(x[a],x[m]);
  quicksort(a, m-1);
  quicksort(m+1, b);
}

// #define NN 100

int qs(int n) {
  int a = 0, comparisons = 0;

  if(a >= n) return 0;

  int p = randint(a, n); // pivot
  // swap(x[a], x[p]);
  int m = a;
  int i;
  
  // in-place partition:
  for (i = a+1; i <= n; i++) {
    if (x[i] < x[a]) {
      comparisons++;
      // swap(x[++m], x[i]);
    }
  }
  
  // swap(x[a],x[m]);
  comparisons += qs(a, m-1);
  comparisons += qs(m+1, n);
  return comparisons;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  /* Creates an array in heap with 100 els. */
  int NN;
  cout << "Enter number of elements to generate and sort: ";
  cin >> NN;

  x = new int[NN];
  for (int i=0; i<NN; ++i) {
    x[i] = rand() % NN;
  }

  // Prints out sorted values
/*  for (int i=0; i<NN; ++i) {
    std::cout << x[i] << std::endl;
  }*/

  /* Runs 10 times. */
  int sum = 0;
  for(int i = 0; i < 10; i++) 
  {
    quicksort(0, NN-1);
    cout << comps << endl;
    sum += comps;
    comps = 0;
  }

  cout << "Average: " << (double) sum / 10 << endl;

  cout << "Part 3 - Count: " << qs(NN-1) << endl;

  delete[] x;
  return 0;
}

