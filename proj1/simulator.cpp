void runwaySimulator() {

  // Declared Variables
  long land_time;
  long takeoff_time;
  long land_rate;
  long takeoff_rate;
  long timeinit = 0;
  long time;

  int PLANENUM = 1000;

  // Queues for our system
  Queue takeoff_queue;
  Queue landing_queue;
  Queue runway_queue;

  // Get user input
  cout << "\tEnter: " << endl;
  // IO #1
  cout << "\n\tTime for a plane to land (in minutes): ";
  cin >> land_time;
  // IO #2
  cout << "\n\tTime for a plane to takeOff (in minutes): ";
  cin >> takeoff_time;
  // IO #3
  cout << "\n\tLanding rate (planes per hour): ";
  cin >> land_rate;
  // IO #4
  cout << "\n\tTakeoff rate (planes per hour): ";
  cin >> takeoff_rate;
  // IO #5 
  cout << "\n\tHow long to run simulation (in minutes): ";
  cin >> time;


  // Loop Numbers
  int number_1, number_2;

  // Main Loop
  while(timeinit++ < time) {
    // Print the current time
    cout << "Time: " << timeinit << endl;

    // randomize 2 numbers
    number_1 = rand() % 60;
    number_2 = rand() % 60;
  
    // generate new landing plane
    if(number_1 % 60 < land_rate) {
      // generate land-request and add plane to land queue
      Queue::NodePointer n1ptr = new Queue::Node(PLANENUM++);
      landing_queue.enqueue( n1ptr );
    }

    // generate new takeoff plane
    if(number_2 < takeoff_rate) { 
      // generate a takeoff-request and add plane to takeoff queue
      Queue::NodePointer n2ptr = new Queue::Node(PLANENUM++);
      takeoff_queue.enqueue( n2ptr );
    }

    // THEN, check if runway is free
    if (runway_queue.empty()) { 

      // check for landing-queue NON-EMPTY and allow planes to land before takeoff
      if( landing_queue.empty()) {
        // enqueue new el into runway and dequeue from reg queue
        runway_queue.enqueue(landing_queue.front());
        landing_queue.dequeue();
      
      // check for takeoff-queue NON-EMPTY and allow planes to be added
      } else if (takeoff_queue.empty() ) {
        runway_queue.enqueue(takeoff_queue.front());
        takeoff_queue.dequeue();

      }

    // if the runway queue was not empty.. we have pending ops. WAIT.
    } else { }


    
    // Sleeps for 1 second
    usleep(1000000);
  }

  // have program calculate the maximum queue length and average time that a plane spends in a queue



 } 
