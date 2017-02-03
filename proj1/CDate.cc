// ..................................................  
// Date& Time class definitions
// Eduardo Garza
// ..................................................

#include <iostream>
#include <string>
#include <iomanip>

#include "CDate.h"

using namespace std;

CDate::CDate()
{
	m_year = 2017;
	m_month = 2;
	m_day = 2;
	m_hour = 20;
	m_minute = 59;
}

void CDate::printDate(void)
{
	string disp_month;

	if(m_month == 1) disp_month = "January";
	if(m_month == 2) disp_month = "February";
	if(m_month == 3) disp_month = "March";
	if(m_month == 4) disp_month = "April";
	if(m_month == 5) disp_month = "May";
	if(m_month == 6) disp_month = "June";
	if(m_month == 7) disp_month = "July";
	if(m_month == 8) disp_month = "August";
	if(m_month == 9) disp_month = "September";
	if(m_month == 10) disp_month = "October";
	if(m_month == 11) disp_month = "November";
	if(m_month == 12) disp_month = "December";

	cout << disp_month << " " << m_day << ", " << m_year << endl; 
}

void CDate::printTime(void) 
{
	cout << "Time: ";

	if(m_hour > 12) {
		cout << setw(2) << setfill('0') << m_hour - 12;
		cout << ":";
		cout << setw(2) << setfill('0') << m_minute;
		cout << " PM" << endl;
	} else {
		cout << setw(2) << setfill('0') << m_hour ;
		cout << ":";
		cout << setw(2) << setfill('0') << m_minute;
		cout << " AM" << endl;
	}


}

void CDate::incrementMinutes() 
{
	if(m_minute == 59) m_minute = 0;
	else m_minute++;
	incrementHour();
}

void CDate::incrementHour() {
	if(m_minute == 0 && m_hour == 23) m_hour = 0;
	else if(m_minute == 0) m_hour++;
	incrementDate();
}

void CDate::incrementDate() {
	int flag = 0; 

	if(m_hour == 0) {

	// Check depending on month/day
		switch (m_month) {
			// 31 days cases
			case 1: 
			case 3: 
			case 5: 
			case 7: 
			case 8: 
			case 10: 
			case 12: flag = 31; break;

			case 2:
				// handles all the leap year rules for February.
				if ((m_year % 4) != 0) {
					flag = 28; 
					break;
				} else if ((m_year % 400) == 0) {
					flag = 29; 
					break;
				} else if ((m_year % 100) == 0) {
					flag = 28; 
					break;
				} else { 
					flag = 29; 
					break;
				}
			// 30 days cases
			case 4: 
			case 6: 
			case 9: 
			case 11: flag = 30; 
			default: break;
		}


		if(flag == 31) {
			if(m_day == 31) {
				m_day = 1;

				if(m_month == 12) {
					m_month = 1;
					m_year++;
				} else 
					m_month++;

			} else
				m_day++;

		} else if(flag == 30) {
			if(m_day == 30) {
				m_day = 1;

				if(m_month == 12) {
					m_month = 1;
					m_year++;
				} else 
					m_month++;

			} else
				m_day++;

		} else if(flag == 29) {
			if(m_day == 29) {
				m_day = 1;

				if(m_month == 12) {
					m_month = 1;
					m_year++;
				} else 
					m_month++;

			} else
				m_day++;

		} else if(flag == 28) {
			if(m_day == 28) {
				m_day = 1;

				if(m_month == 12) {
					m_month = 1;
					m_year++;
				} else 
					m_month++;

			} else
				m_day++;

		} else {}
	}
}

void CDate::increment() {
	incrementMinutes();
	printTime();
	printDate();
}