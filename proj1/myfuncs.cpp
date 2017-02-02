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

	return this*;
} 


