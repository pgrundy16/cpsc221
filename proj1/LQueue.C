--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/
 
#include <iostream>
using namespace std;

#include "LQueue.h"

//--- Definition of Queue constructor
Queue::Queue(): myFront(0), myBack(0)
{

}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue & original)
{
   myFront = myBack = 0;
   // when the Queue is not empty
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
   if (this != &rightHandSide)         // check that not q = q (same addr)
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

//--- Definition of display()
void Queue::display(ostream & out) const
{
   Queue::NodePointer ptr;
   for (ptr = myFront; ptr != 0; ptr = ptr->next)
     out << ptr->data << "  ";
   out << endl;
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
void Queue::dequeue()
{
   if (!empty())
   {
      Queue::NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == 0)     // queue is now empty
         myBack = 0;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

/* ======== Part 1 ======== */

 //--- Search through a queue for a particular key value
 //--- If found, move node to front
 /* Edited by Eduardo : 5:56 PM Feb 1, 2017 */
void Queue::move_to_front(const Queue & q1, const QueueElement & el) 
{
	// return when empty, or only one node
	if(q1.empty() || (q1.myFront && q1.myFront == q1.myBack)) return; 

	// declare 2 traversal nodes
	Queue::NodePointer it = q1.myFront;
	Queue::NodePointer prev = q1.myFront;

	// iterate until key is found
	while(it) {
		if(it->data == el) break;

		prev = it;
		it = it->next;
	}

	// key is found in 1 node only
	if(it == prev && it->data == el) {
		// first node : do nothing
		return;

	// key is found at last node
	} else if(!(it->next) && it->key == el ) {
		// prev points to NULL (bc last el)
		prev->next = 0;

		// point key to front
		it->next = q1.myFront;
		q1.myFront = it;
		return;
	
	// key is found at x (non-front/back node)
	} else if(it->data == el) {
		prev->next = it->next;

		it->next = q1.myFront;
		q1.myFront = it;
		return;
	} else {}

}

//--- Takes q1 and q2 as two Queues and merges them
//--- into a single queue with absolute order kept
/* Edited by Eduardo : 7:33 PM Feb 1, 2017 */
void Queue::merge_two_queues(const Queue & q2) {
	if(q2.empty()) return * this;

	// point the back of q1 to beg of q2
	myBack->next = q2.myFront;

	// set q2 to null to signify that it is empty
	q2.myFront = q2.myBack = 0;

	// now SORT the queue
	NodePointer index = myFront; 
	NodePointer jindex = myFront;
	NodePointer least = myFront;

	while(index) {
		least = index;

		while(jindex) {
			if(least->data > jindex->data)
				least = jindex;
			prev = jindex;
			jindex = jindex->next;
		}

	// switch if least != index 
		// case: switch first & last node
		if(least != index && least == myBack && index == myFront) {
			// where last is at least
			least->next = myFront;


		// case: switch first and non-last nodes
		} else if () {



		// case: switch non-first and last nodes
		} else if () {



		// case: switch non-first and non-last nodes
		} else if() {


		} else { /* no switch */ }



		// iterate after switch
		prev = index;
		index = index->next;
	}

	return this*l=;
} 


/* ======== Part 2 ======== */
/* 
For each minute, generate two random numbers:
num1 % 60 < landingRate:		
				"landing request" has been generated & plane is added to 'landing' queue

num2 < takeoffRate:
				"takeoff request" has been generated & plane is added to 'takeoff queue'

NEXT:
	= check if runway is free
		if true :
			check if landing queue is non-empty 1st and allow planes to land
			ELSE, consider the takeoff queue

	= have program calculate the maximum queue length and average time that a plane 
		spends in a queue
	
	** DO NOT add priv elements to class. it is not necessary. 		
*/

 