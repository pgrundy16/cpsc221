/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/
// Libraries 
#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <fstream>

// Files included
#include "LQueue.h"
#include "CDate.h"

#define LAND_ID 2000 
#define TAKEOFF_ID 7000 
#define PLANE_ID 5000

using namespace std;  

// Our Queues are GLOBAL
Queue takeoffQ, landQ, runwayQ;

void print(Queue q) { q.display(cout);}

void printDivider() 
{
    cout << "+---------------+---------------+"
          <<"-----------------------+---------------+" << endl;
}

void printTabs(int num) { for (int i =0; i < num; i++) cout << "\t"; }

void printEL() 
{
  cout << "|";
  printTabs(9);
  cout << "|" << endl;
}

void printHeader() 
{
  // Print top
  cout << "+-----------------------------------"
  << "------------------------------------+" << endl; 
  // print empty line
  printEL();
  // print title
  cout << "|";
  printTabs(3);
  cout <<"ARRIVALS & DEPARTURES";
  printTabs(4);
  cout << "|" << endl;
  // print empty line
  printEL();
  // opening-bottom divider
  printDivider();
}

void printTable() {
  if(!takeoffQ.empty() || !landQ.empty() || !runwayQ.empty()) {

    // Print table title
    printHeader();

    // print table header
    cout << "| Flight\t| Direction\t| Destination\t\t| Gate\t\t|" << endl;
    printDivider();
    
    if(!runwayQ.empty()) {
      // print section Runway
      runwayQ.printRows(3);
      printDivider();
    }

    if(!landQ.empty()) {
      // print section Landing
      landQ.printRows(1);
      printDivider();
    }

    if(!takeoffQ.empty()) {
      // print section Takeoff
      takeoffQ.printRows(2);
      printDivider();
    }
  }
}


void runwaySimulator() {
  // generate different random variables
  srand(time(NULL));

  // Input Variables with DEFAULT values
  int land_time = 3, takeoff_time = 4, land_rate = 11, takeoff_rate = 10;
  int sim_time = 120;


  // User Input Parameters
  cout << "Enter: " << endl;
  // IO #1
  cout << "\tRequired Time to Land (in minutes): ";
  cin >> land_time;
  // IO #2
  cout << "\tRequired Time to Take-Off (in minutes): ";
  cin >> takeoff_time;
  // IO #3
  cout << "\tLanding Rate (planes per hour): ";
  cin >> land_rate;
  // IO #4
  cout << "\tTakeoff Rate (planes per hour): ";
  cin >> takeoff_rate;
  // IO #5 
  cout << "\tMinutes to Simulate: ";
  cin >> sim_time;
  cout << endl;

  // plane ID on runway
  int runway_ID;

  // Random Numbers
  int num_1, num_2;

  // Time Variables
  CDate d1;
  int time = 1; // tracker

  // Statistics Variables
  int all_takeoff = 0, all_land = 0;
  int current_takeoff = 0, current_land = 0;
  int max_takeoff = 0, max_land = 0;
  int time_takeoff  = 0, time_land = 0;


/* == Main Simulator Loop == */
  do {
    // print out current TIME
    d1.increment();

    // Print the table
    printTable();

    // Generate 2 random numbers
    num_1 = rand() % 60;
    num_2 = rand() % 60;
  
    // Landing Request
    if(num_1 < land_rate) {
      int id_land = time + LAND_ID;
      landQ.enqueue(id_land);

      all_land++;
      current_land++;
      if(current_land > max_land) max_land = current_land;

      cout << "[REQUEST]: " << endl;
      cout << "\tPlane " << id_land << " wants to land.";
      cout << " Added to the landing queue." << endl;
      cout << "\tNumber of Planes in Land Queue: " << current_land << "." << endl;
    }

    // Takeoff Request
    if(num_2 < takeoff_rate) { 
      int id_takeoff = time + TAKEOFF_ID;
      takeoffQ.enqueue(id_takeoff);

      all_takeoff++;
      current_takeoff++;
      if(current_takeoff > max_takeoff) max_takeoff = current_takeoff;
      
      cout << "[REQUEST]: " << endl;
      cout << "\tPlane " << id_takeoff << " wants to takeoff.";
      cout << "Added to the takeoff queue." << endl;
      cout << "\tNumber of Planes in Takeoff Queue: " << current_takeoff << "." << endl;
    }

    // Check Runway (EMPTY)
    if (runwayQ.empty()) 
    { 
      // Priority to landQ
      if( !landQ.empty() ) {
        // set the planeID and time tracker
        int initL = landQ.front();
        runway_ID = initL;

        // remove from landQ and put into runway
        landQ.dequeue();
        runwayQ.enqueue(time);
        current_land--;

        cout << "[RUNWAY UPDATE]" << endl;
        cout << "\tPlane " << runway_ID << " is occuping runway for landing." << endl;
        cout << "\tPlane " << runway_ID << " will land in approximately ";
        cout << land_rate << " minutes." << endl;

        // timesum(land) = t - t0 
        time_land += ( time - initL + LAND_ID  );

        // cout << "\t"

      // LandQ empty : TakeoffQ NOT-EMPTY
      } else if ( !takeoffQ.empty() ) 
      {
        int initT = takeoffQ.front();
        runway_ID = initT;

        takeoffQ.dequeue();
        runwayQ.enqueue(time);
        current_takeoff--;

        cout << "\t**Plane " << runway_ID << " is occuping runway for landing." << endl;
        cout << "\t**Plane " << runway_ID << " will land in approximately ";
        cout << takeoff_rate << " minutes." << endl;


        // timesum(land) = t - t0 
        time_takeoff += ( time - initT + TAKEOFF_ID );

      // both Queues are EMPTY
      } else { /* do nothing */ }


    // Check Runway (NOT-EMPTY)
    } else 
    { 
      int timeInit = runwayQ.front();
      
      // when time to land
      if( time - timeInit == land_time) {
        cout << "\tLanding complete" << endl;
        cout << "\tLanded: Plane " << runway_ID << endl; 
        runwayQ.dequeue();
      }

      if( time - timeInit == takeoff_time ) {
        cout << "\tTakeoff complete" << endl;
        cout << "\tIn Flight: Plane " << runway_ID << endl; 
        runwayQ.dequeue();
      }

    }

    // Sleeps for 1 second
    usleep(1000000);
    cout << "\n\n";
  } while(time++ < sim_time);
/* == End of Main Loop Simulator == */




/* == Print Statistics == */

  double avg_land = (double) (time_land / all_land );
  double avg_takeoff = (double) (time_takeoff / all_takeoff);

  cout << "STATISTICS\n" << endl;

  cout << "Maximum number of planes in landing queue was: "
        << ( max_land ) << endl;

  cout << "Average minutes spent waiting to land: "
        << avg_land << endl;

  cout << "Maximum number of planes in takeoff queue was: "
        << ( max_takeoff ) << endl;

  cout << "Average minutes spent waiting to takeoff: "
        << avg_takeoff << endl;

 } 



int main(void)
{
  srand(time(NULL));
/*
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
*/

/* ====== Eduardo Testing Part A ======== */
/*
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
*/


/* ====== End of Eduardo Testing Part A ======== */

/*
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

*/

/* ====== Eduardo Testing Part B ======== */

   runwaySimulator();
  // printTable();

  // CDate d1;
  // d1.printDate();

    
/* ====== End of Eduardo Testing Part B ======== */

   //system("PAUSE");
   return 0;
}
