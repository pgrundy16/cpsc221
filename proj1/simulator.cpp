#include <iostream>
#include <cstdio> // standard i/o
#include <cstdlib> // for atoi
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

extern Queue takeoffQ, landQ, runwayQ;

void print(Queue q)
{ 
  q.display(cout);
}


void printDivider() {
    cout << "+---------------+---------------+"
          <<"-----------------------+---------------+" << endl;
  }

  void printTabs(int num) {
    for (int i =0; i < num; i++) cout << "\t";
  }
  
  void printEL(){
    cout << "|";
    printTabs(9);
    cout << "|" << endl;
  }

  void printHeader() {
    cout << "+-----------------------------------"
    << "------------------------------------+" << endl;
    
    printEL();
    cout << "|";
    printTabs(3);
    cout <<"ARRIVALS & DEPARTURES";
    printTabs(4);
    cout << "|" << endl;
    printEL();
    printDivider();
  }

 void printTable() {
  printHeader();

  cout << "| Flight\t| Direction\t| Destination\t\t| Gate\t\t|" << endl;
  printDivider();
  
  runwayQ.printRows(3);
  landQ.printRows(1);
  takeoffQ.printRows(2);

  printDivider();

  cout << "\n\n";
 }

void printRow() {

  // takeoffQ.display();


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


  // Queues for our system

  int runway_ID;

  // Random Numbers
  int num_1, num_2;

  // Time Variables
  int time = 1;
  CDate d1;

  // Statistics Variables
  int all_takeoff = 0, all_land = 0;
  int current_takeoff = 0, current_land = 0;
  int max_takeoff = 0, max_land = 0;
  int time_takeoff  = 0, time_land = 0;


/* == Main Simulator Loop == */
  do {
    d1.increment();

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

      cout << "\tPlane " << id_land << " wants to land." << endl;
      cout << "\tPlane " << id_land << " was added to the landing queue." << endl;
      cout << "\tNumber of Planes in Land Queue: " << current_land << ".\n" << endl;
    }

    // Takeoff Request
    if(num_2 < takeoff_rate) { 
      int id_takeoff = time + TAKEOFF_ID;
      takeoffQ.enqueue(id_takeoff);

      all_takeoff++;
      current_takeoff++;
      if(current_takeoff > max_takeoff) max_takeoff = current_takeoff;

      cout << "\tPlane " << id_takeoff << " wants to takeoff." << endl;
      cout << "\tPlane " << id_takeoff << " was added to the takeoff queue." << endl;
      cout << "\tNumber of Planes in Takeoff Queue: " << current_takeoff << ".\n" << endl;
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

        cout << "\t**Plane " << runway_ID << " is occuping runway for landing." << endl;
        cout << "\t**Plane " << runway_ID << " will land in approximately ";
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
        cout << "tTakeoff complete" << endl;
        cout << "\tIn Flight: Plane " << runway_ID << endl; 
        runwayQ.dequeue();
      }

    }

    if(!takeoffQ.empty() || !landQ.empty() || !runwayQ.empty())
      printTable();

    // Sleeps for 1 second
    usleep(1000000);
  } while(time++ < sim_time);
/* == End of Main Loop Simulator == */




/* == Print Statistics == */

  cout << "STATISTICS\n" << endl;

  cout << "Maximum number of planes in landing queue was: "
        << ( max_land ) << endl;

  cout << "Average minutes spent waiting to land: "
        << ( time_land / all_land ) << endl;

  cout << "Maximum number of planes in takeoff queue was: "
        << ( max_takeoff ) << endl;

  cout << "Average minutes spent waiting to takeoff: "
        << ( time_takeoff / all_takeoff ) << endl;

 } 