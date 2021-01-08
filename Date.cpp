#include <iostream>
#include <cstring>
#include "Date.h"

using namespace std;

namespace aid {

	Date::Date() {

		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_comparator = 0;
		errCode(NO_ERROR);
	}

	Date::Date(int year, int month, int day) {

		int date = year * 372 + month * 31 + day;

		if (year >= min_year && year <= max_year && month >= 1 && month <= 12 && day >= 1 && day <= mdays(year, month) && date >= min_date) {

			m_year = year;
			m_month = month;
			m_day = day;
			m_comparator = date;
			errCode(NO_ERROR);

		}
		else if (year < min_year || year > max_year) {
			*this = Date();
			errCode(YEAR_ERROR);
		}
		else if (month < 1 || month > 12) {
			*this = Date();
			errCode(MON_ERROR);
		}
		else if (day < 1 || day > mdays(year, month)) {
			*this = Date();
			errCode(DAY_ERROR);
		}
		else if (date < min_date) {
			*this = Date();
			errCode(PAST_ERROR);
		}
	}

	int Date::mdays(int year, int mon) const {

		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));

	}

	void Date::errCode(int errorcode) {
		m_errorState = errorcode;
	}

	int Date::errCode() const {
		return m_errorState;
	}

	bool Date::bad() const {
		
		if (m_errorState != NO_ERROR) {
			return true;
		}
		else{
			return false;
		}
	}

	std::istream& Date::read(std::istream& istr) {

		int tYear, tMonth, tDay;
		char symbol;
		istr >> tYear >> symbol >> tMonth >> symbol >> tDay;


		if (cin.fail() != true)
		{
			if (tYear >= min_year && tYear <= max_year)
			{
				if (tMonth >= 1 && tMonth <= 12)
				{
					if (tDay >= 1 && tDay <= mdays(tYear, tMonth))
					{
						int total = tYear * 372 + tMonth * 31 + tDay;

						if (total >= min_date)
						{
							m_year = tYear;
							m_month = tMonth;
							m_day = tDay;
							istr.clear();
						}
						else
						{
							errCode(PAST_ERROR);
						}
					}
					else
					{
						errCode(DAY_ERROR);
					}
				}
				else
				{
					errCode(MON_ERROR);
				}
			}
			else
			{
				errCode(YEAR_ERROR);
			}
		}
		else
		{
			errCode(CIN_FAILED);
		}
		return istr;
	}

	std::ostream& Date::write(std::ostream& ostrm) const {

		char slash = '/';

		ostrm.fill('0');
		ostrm.width(1);
		ostrm << m_year << slash;

		ostrm.width(2);
		ostrm.unsetf(ios::left);
		ostrm.fill('0');
		ostrm << m_month << slash;

		ostrm.width(2);
		ostrm.unsetf(ios::left);
		ostrm.fill('0');
		ostrm << m_day;

		ostrm.fill(' ');

		return ostrm;
	}

	std::istream& operator>>(istream& is, Date& rhs) {
		return rhs.read(is);
	}

	std::ostream& operator<<(ostream& os, const Date& rhs) {
		return rhs.write(os);
	}

	bool Date::operator==(const Date& rhs) const {

		if (this->m_comparator == rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator!=(const Date& rhs) const {

		if (this->m_comparator != rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<(const Date& rhs) const {

		if (this->m_comparator < rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>(const Date& rhs) const {

		if (this->m_comparator > rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator<=(const Date& rhs) const {

		if (this->m_comparator <= rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Date::operator>=(const Date& rhs) const {

		if (this->m_comparator >= rhs.m_comparator) {
			return true;
		}
		else
		{
			return false;
		}
	}

}