README.txt

Name: 		Eduardo Garza
Student ID:	60002152
Class:		CPSC 221
Lab Section:	L2F

Title: 		Project 1 | Queues, Simulation of an Airport Runway


+===============================================================+
			Instructions for Marker
+===============================================================+

i. Part A of the program was to implement:
	
	void move_to_front(const QueueElement & el);
	void merge_two_queues(Queue & q2);
   
   The tests for these two functions can be found within
	LQueue_driver.C

   *** Part A tests are labeled within the file specified BUT
	are commented out like other sections.
   **  Uncomment the the <code> within Part A ONLY to test
	that section, then do the same for Part B/C


ii. Part B was to implement an airport runway simulation.
    My simulation can be found within
	LQueue_driver.C 

   ** DO NOT TEST Part B without reading instruction 'iii'


iii. Part C was to implement a creative touch to the simulation.

	I implemented two new aspects : a real time counter and
	a UI table that displays on every clock count.

   [Explanation]:
	- My simulation uses the Sleep at the end of each loop
	  cycle to generate each minute as a single second.
	  I recommend that you try this mode because it gives
	  you a great preview of what is happening during the simulation.
	
	- On each iteration the table below is displayed:

Time: 09:05 PM
+-----------------------------------------------------------------------+
|																		|
|						ARRIVALS & DEPARTURES							|
|																		|
+---------------+---------------+-----------------------+---------------+
| Flight		| Direction		| Destination			| Gate			|
+---------------+---------------+-----------------------+---------------+
| FX     1		| Runway		| Louisville			| A3			|
+---------------+---------------+-----------------------+---------------+
| FX  2002		| Arriving		| Calgary				| A3			|
| FX  2005		| Arriving		| Dallas				| B8			|
+---------------+---------------+-----------------------+---------------+
| FX  7004		| Departing		| Quebec City			| A3			|
| FX  7005		| Departing		| Dallas				| B8			|
+---------------+---------------+-----------------------+---------------+
	
	This table includes real-time counter, using 9:00 PM as t0 since
	that was the due date. The counter is implemented within a class
	called CDate, which is a modification from the class called
	CDate that we used for Lab 3 of CPSC221.
	
	Secondly, it uses the Node->data item as the 
	flight ID, which is also the time that it entered the queue
	= Arrivals have ID = 2000 + timeAdded > ex. 2000 + t=2
	= Departues have ID = 7000 + timeAdded > ex. 7000 + t=5
	Having the time in the ID allows you to calculate the average 
	time once the node is dequed without any additional vars.
	= Runway IDs are different to create a unique ID since only
	one can be on the runway at once.

	Thirdly, it reads from a file called "cities.txt" with the
	top ~100 most populated cities of the world to generate
	a random city to accompany a flight.

	Finally, it uses a random generate with a character typecast
	to produce random gate numbers within a specified range.

iv. Below the TABLE is also the information that the project requested us
	to compute:
<ex.>
	[REQUEST]: 
		Plane 7007 wants to takeoff.Added to the takeoff queue.
		Number of Planes in Takeoff Queue: 3.
	[RUNWAY UPDATE]
		**Plane 2002 is occuping runway for landing.
		**Plane 2002 will land in approximately 10 minutes.


+===============================================================+
			    HOW TO RUN
+===============================================================+
1. The program will already compiled but if you want to make 
	sure that it works you can compile it like this:

	make LQueue_driver

2. Then run the program:

	./LQueue_driver


+===============================================================+
			   End of README
+===============================================================+
