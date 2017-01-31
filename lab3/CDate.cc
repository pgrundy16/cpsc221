// ..................................................  
// CDate class definitions
// Adapted from Hagit Schechter, Jan 2007 for 2014W2 
// ..................................................

#include <iostream>
#include <string>
#include "CDate.h"

CDate::CDate(void){
	m_year = m_month = m_day = 0;
}

CDate::CDate(int year, int month, int day){
	setDate( year, month, day );        
}

// Edited by Eduardo : 7:41 PM Jan 29, 2017
CDate::CDate(int year, std::string month, int day){
	setDate(year, monthStr2Num(month), day);
}

// Edited by Eduardo : 7:42 PM Jan 29, 2017
bool CDate::isValidDate(int year, int month, int day){
	// check the validity of a year, month, and day
	bool year_bool = year > 0;
	bool month_bool = (month > 0) && (month < 13);
	bool day_bool = isValidDay(year, month, day);

	return year_bool && month_bool && day_bool;
}

// Edited by Eduardo : 7:44 PM Jan 29, 2017
bool CDate::isValidDate(int year, std::string month, int day){
	int i_month = monthStr2Num(month);

	return isValidDate(year, i_month, day);
}

// Edited by Eduardo : 7:41 PM Jan 29, 2017
int CDate::monthStr2Num(std::string month){
	
	if(month == "January") return 1;
	if(month == "February") return 2;
	if(month == "March") return 3;
	if(month == "April") return 4;
	if(month == "May") return 5;
	if(month == "June") return 6;
	if(month == "July") return 7;
	if(month == "August") return 8;
	if(month == "September") return 9;
	if(month == "October") return 10;
	if(month == "November") return 11;
	if(month == "December") return 12;
	
	return -1;
}

bool CDate::isValidDay(int year, int month, int day){
	if ((day < 1) || (day > 31)) return false;

	switch (month) {
		// 31 days cases
		case 1: return day <= 31;
		case 3: return day <= 31;
		case 5: return day <= 31;
		case 7: return day <= 31;
		case 8: return day <= 31;
		case 10: return day <= 31;
		case 12: return day <= 31;

		case 2:
			// handles all the leap year rules for February.
			if ((year % 4) != 0) return day <=28;
			else if ((year % 400) == 0) return day <= 29;
			else if ((year % 100) == 0) return day <= 28;
			else return day <= 29;

		// 30 days cases
		case 4: return day <= 30;
		case 6: return day <= 30;
		case 9: return day <= 30;
		case 11: return day <= 30;
		default: break; 
	}

	return false;
}

void CDate::setDate(int year, int month, int day){
	if(isValidDate(year, month, day)){    
		m_year = year;
		m_month = month;
		m_day = day;
	}
	else {
		m_year = m_month = m_day = 0;
	}
}


void CDate::setDate(int year, std::string month, int day){
	int i_month = monthStr2Num(month);
	setDate(year,i_month, day);
}

void CDate::print(void){
	std::cout << m_year << "/" << m_month << "/" << m_day << std::endl;
}

int CDate::getDate(void){
	return (m_year * 10000) + (m_month * 100) + m_day;
}

