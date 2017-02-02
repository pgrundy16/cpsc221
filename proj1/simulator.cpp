#include <iostream>
#include <cstdio> // standard i/o
#include <cstdlib> // for atoi
#include <unistd.h>

#define LAND_ID 2000 // corresponds to cR = 1
#define TAKEOFF_ID 7000 // corresponds to cR = 2
#define PLANE_ID 5000

void runwaySimulator() {
  // generate different random variables
  srand(time(NULL));

  // Input Variables with DEFAULT values
  int land_time = 10, takeoff_time = 10, land_rate = 20, takeoff_rate = 20;
  int sim_time = 120;

  // User Input Parameters
  cout << "Enter: " << endl;
  // IO #1
  cout << "\tRequired Time to Land (in minutes): ";
  cin >> land_time;
  // IO #2
  cout << "\n\tRequired Time to Take-Off (in minutes): ";
  cin >> takeoff_time;
  // IO #3
  cout << "\n\tLanding Rate (planes per hour): ";
  cin >> land_rate;
  // IO #4
  cout << "\n\tTakeoff Rate (planes per hour): ";
  cin >> takeoff_rate;
  // IO #5 
  cout << "\n\tMinutes to Simulate: ";
  cin >> sim_time;
  cout << endl;

  // Queues for our system
  Queue takeoffQ, landQ, runwayQ;
  int runway_type, runway_ID;

  // Random Numbers
  int num_1, num_2;
  int time = 0; 

  // Statistics Variables
  int all_takeoff = 0, all_land = 0;
  int current_takeoff = 0, current_land = 0;
  int max_takeoff = 0, max_land = 0;
  int time_takeoff  = 0, time_land = 0;


/* == Main Simulator Loop == */
  while(time++ < sim_time) {
    cout << "Time: " << time << "." << endl;

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

      cout << "Plane " << id_land << " wants to land." << endl;
      cout << "Plane " << id_land << " was added to the landing queue." << endl;
      cout << "Number in Land Queue: " << current_land << ".\n" << endl;
    }

    // Takeoff Request
    if(num_2 < takeoff_rate) { 
      int id_takeoff = time + TAKEOFF_ID;
      takeoffQ.enqueue(id_takeoff);

      all_takeoff++;
      current_takeoff++;
      if(current_takeoff > max_takeoff) max_takeoff = current_takeoff;

      cout << "Plane " << id_takeoff << " wants to takeoff." << endl;
      cout << "Plane " << id_takeoff << " was added to the takeoff queue." << endl;
      cout << "Number in Takeoff Queue: " << current_takeoff << ".\n" << endl;
    }


    // Check Runway (EMPTY)
    if (runwayQ.empty()) 
    { 
      // Priority to landQ
      if( !landQ.empty() ) {
        int initL = landQ.front();
        runway_ID = initL;

        landQ.dequeue();
        runwayQ.enqueue(time);
        current_land--;
        runway_type = 1;

        // timesum(land) = t - t0 
        time_land += ( time - initL + LAND_ID  );

      // LandQ empty : TakeoffQ NOT-EMPTY
      } else if ( !takeoffQ.empty() ) 
      {
        int initT = takeoffQ.front();
        runway_ID = initT;

        takeoffQ.dequeue();
        runwayQ.enqueue(time);
        current_takeoff--;
        runway_type = 2;

        // timesum(land) = t - t0 
        time_takeoff += ( time - initT + TAKEOFF_ID );

      // both Queues are EMPTY
      } else { /* do nothing */ }


    // Check Runway (NOT-EMPTY)
    } else 
    { 
      int timeInit = runwayQ.front();
      int curType = (runway_type == 1) ? LAND_ID : TAKEOFF_ID; 
      
      // when time to land
      if( time - timeInit + curType == land_time) {
        cout << "Landing complete" << endl;
        cout << "Landed: Plane " << runway_ID << endl; 
      }

      if( time - timeInit +  curType == takeoff_time ) {
        cout << "Takeoff complete" << endl;
        cout << "In Flight: Plane " << runway_ID << endl; 
      }

    }

    // Sleeps for 1 second
    // usleep(1000000);
  } 
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
