// ...........................................................
// Simulator
// Author: Eduardo, 2017
// ...........................................................
#include <iostream>
#include <cstdio> // standard i/o
#include <cstdlib> // for atoi
#include <unistd.h>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>

// Files included
#include "LQueue.h"
#include "CDate.h"

using namespace std;

#ifndef _C_DATE_
#define _C_DATE_

class simulator
{
public:
  simulator();
  
  void printDate( void );
  void printTime(void);
  void incrementMinutes(void);
  void incrementHour(void);
  void incrementDate(void);
  void increment(void);
  
private:
  int m_year;
  int m_month;
  int m_day;
  int m_hour;
  int m_minute;
};

#endif
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

class simulator { 
  public: 
    void printDivider();
    void printTabs(int num); 
    void printEL();
    void printHeader();
    void printTable(); 
    void printRow(); 

    void runwaySimulator();

  private:

};

