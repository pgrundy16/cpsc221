/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
#include <cstdio> // standard i/o
#include <cstdlib> // for atoi
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue()
: myFront(0), myBack(0)
{}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new Queue::Node(original.front());

      // Set pointer to run through original's linked list
      Queue::NodePointer origPtr = original.myFront->next;
      while (origPtr != 0)
      {
         myBack->next = new Queue::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
Queue::~Queue()
{ 
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
const Queue & Queue::operator=(const Queue & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~Queue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = 0;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new Queue::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != 0)
         {
           myBack->next = new Queue::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{ 
   return (myFront == 0); 
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement & value)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

void Queue::enqueue(const QueueElement & value, string city)
{
   Queue::NodePointer newptr = new Queue::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }

   newptr->dest = city;
}

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
}

void Queue::printRows(int flag) {
  // Iterator
  Queue::NodePointer ptr;

  srand(time(NULL));

  // open file  
  ifstream file1("cities.txt");
  std::string line;
  std::vector<std::string> citiesVec;

  while (getline(file1, line))
    citiesVec.push_back(line);

  file1.close();


  for (ptr = myFront; ptr != 0; ptr = ptr->next) 
  {
    // Print Flight ID
    cout << "| ";
    cout << "FX" << setw(6) << setfill(' ') << ptr->data << "\t";
    
    if(flag == 1)
      cout << "| Arriving\t";
    else if (flag == 2)
      cout << "| Departing\t";
    else
      cout << "| Runway\t";

  // Generate a destination
    int r1 = rand() % 93;
    if((ptr->dest).empty()) 
      ptr->dest = citiesVec.at(r1);
    
    if((ptr->dest).length() > 13)
      cout << "| " << ptr->dest  << "\t";
    else if((ptr->dest).length() < 6)
      cout << "| " << ptr->dest  << "\t\t\t";
    else
      cout << "| " << ptr->dest  << "\t\t"; 
  // END of Generate-Destination

  // Generate random gate
    if(flag == 3) {
      cout <<  "| " << "R1";
    } else {
      cout <<  "| " << (char)('A' + rand() % 5);
      cout << (int)(2 + rand() % 40);
    }
      cout << "\t\t|" << endl;
  }


}

//--- Definition of front()
QueueElement Queue::front() const
{
   if (!empty())
      return (myFront->data);
   else
   {
	return 0;
   }
}

//--- Definition of dequeue()
string Queue::dequeue()
{
  string city;
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      city = ptr->dest;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else {}
      // cerr << "*** Queue is empty -- can't remove a value ***\n";
   
   return city;
}

//--- Definition of move_to_front()
/* Completed by Eduardo : 10:01 AM Feb 2, 2017 */
void Queue::move_to_front(const QueueElement & el) 
{
	// when EMPTY or f = b (1 node), return
	if(empty() || (myFront && myFront == myBack)) return; 

	// declare 2 traversal nodes
	Queue::NodePointer it = myFront;
	Queue::NodePointer prev = myFront;

	while(it) {
    // if 'el' is found, key is at 'it'
		if(it->data == el) break;

    //iterate
		prev = it;
		it = it->next;
	}

	// if 'el', & ONLY 1 node in Q
	if(it == prev && it->data == el) {
		// no switch : do nothing
		return;

	// key is found at last node
	} else if(!(it->next) && it->data == el ) {
		// prev points to NULL (bc last el)
		prev->next = 0;

		// move Node to front
		it->next = myFront;
		myFront = it;
		return;
	
	// key is found at x (non-front/back node)
	} else if(it->data == el) {
		prev->next = it->next;

		it->next = myFront;
		myFront = it;
		return;

    // else corresponds to not finding'el'
	} else {}

}

//--- Takes q1 and q2 as two Queues and merges them
//--- into a single queue with absolute order kept
/* Edited by Eduardo : 7:33 PM Feb 1, 2017 */
void Queue::merge_two_queues(Queue & q2) {
	// Q2 EMPTY
  if(q2.empty()) return;

  // Q1 EMPTY, copy all Q2
  if(empty()) {
    *this = q2;
    // calls ~Queue()
    while(!q2.empty())
      q2.dequeue();
    return;
  }

  // Q1, Q2 NON-EMPTY below
  Queue::NodePointer it = myFront;
  Queue::NodePointer prev = myFront;

  while(it && !q2.empty()) {
    // delete node from q2 in all cases
    int new_data = q2.front(); 
    q2.dequeue();

    // when Q2 is smaller that 'it'
    if(it->data > new_data) {
      // first node
      if(it == prev) {
        Queue::NodePointer newptr = new Queue::Node(new_data);
        newptr->next = it;
        myFront = newptr;
        it = myFront;
        prev = it;

      // it MULTIPLE nodes
      } else {
        // declare new Node manually & insert between 'prev'-'it'
        Queue::NodePointer newptr = new Queue::Node(new_data);
        prev->next = newptr;
        newptr->next = it;
      }           

    // when the value was greater than
    } else {
      // declare a new Node and put it after 'it'
      Queue::NodePointer newptr = new Queue::Node(new_data);
      newptr->next = it->next;
      it->next = newptr;

      // iterate
      prev = it;
      it = it->next;

    }
  }

  // when 'it' is done iterating
  if(prev->next == it && !q2.empty()) {
    // add all remaining els to end of Q1
    while(!q2.empty()) {
      enqueue(q2.front());
      q2.dequeue();
    }
  }

} 
