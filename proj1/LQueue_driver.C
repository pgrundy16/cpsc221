/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
using namespace std;
  

void print(Queue q)
{ q.display(cout); }

int main(void)
{
   Queue q1;
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;

   Queue q2;
   q2 = q1;
   cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
   print(q2); 
   cout << endl;

   cout << "Queue q2 empty? " << q2.empty() << endl;

   cout << "Front value in q2: " << q2.front() << endl;

/* ====== Eduardo Testing Part A ======== */
  cout << "\nMoving elements" << endl;
   q1.move_to_front(300);
   q1.move_to_front(300);
   q1.move_to_front(500);
   print(q1);
   cout << endl;

   cout << "\nMerging Queues" << endl;
   int index = 1;
     Queue q3;  
   while(index < 10) {
    q3.enqueue(-1 * index);
    index++;
  }
   cout << "Queue 2: ";
   print(q2);
   cout << "Queue 3: ";
   print(q3);
   cout << endl;

   q2.merge_two_queues(q3);
   print(q2);
   cout << endl;

/* ====== End of Eduardo Testing Part A ======== */

   while (!q2.empty())
   {
     cout << "Remove front -- Queue contents: ";
     q2.dequeue();
     q2.display(cout);
   }
   cout << "Queue q2 empty? " << q2.empty() << endl;
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();
   //system("PAUSE");
   return 0;
}