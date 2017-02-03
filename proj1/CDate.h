// ...........................................................
// Date & Time
// Author: Eduardo, 2017
// ...........................................................
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

#ifndef _C_DATE_
#define _C_DATE_

class CDate
{
public:
	CDate( void );
	
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
