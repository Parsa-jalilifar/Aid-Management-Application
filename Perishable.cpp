#include "Perishable.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace aid {

	Perishable::Perishable() : Good('P') 
	{
		m_date = Date();
	}

	iGood* CreateProduct(char tag) {

		iGood *good = nullptr;

		if (tag == 'N' || tag == 'n') {
			good = new Good('N');
		}
		else if (tag == 'p' || tag == 'P') {
			good = new Perishable;
		}

		return good;
	}

	std::fstream& Perishable::store(std::fstream& file, bool newline) const {

		Good::store(file, false);

		if (newline == true) {
			file << ',';
			file << m_date << endl;
		}
		else {
			file << ',';
			file << m_date;
		}

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {

		Good::load(file);
		file.ignore();
		m_date.read(file);

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const {

		Good::write(os, linear);

		if (!this->isEmpty() && this->isClear()) {

			if (linear == true)
				os << m_date;
			if (linear == false)
				os << endl << " Expiry date: " << m_date;
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is) {

		char Message[35];
		Good::read(is);


		if (!is.fail()) {

			cout << " Expiry date (YYYY/MM/DD): ";
			is >> m_date;

			if (m_date.bad()) {

				is.setstate(std::ios::failbit);
				 

				if (m_date.errCode() == CIN_FAILED) {
					strcpy(Message, "Invalid Date Entry");
				}
				else if (m_date.errCode() == YEAR_ERROR) {
					strcpy(Message, "Invalid Year in Date Entry");
				}
				else if (m_date.errCode() == MON_ERROR)
				{
					strcpy(Message, "Invalid Month in Date Entry");
				}
				else if (m_date.errCode() == DAY_ERROR)
				{
					strcpy(Message, "Invalid Day in Date entry");
				}
				else if (m_date.errCode() == PAST_ERROR)
				{
					strcpy(Message, "Invalid Expiry in Date Entry");
				}

				Good::message(Message);
			}
		

		}

		return is;

		/*is.clear();
		Product::read(is);

		if (er.isClear()) 
		{
			cout << " Expiry date (YYYY/MM/DD): ";
			m_date.read(is);
		}

		if (m_date.errCode() == CIN_FAILED)
		{
			er.clear();
			er.message("Invalid Date Entry");
		}

		if (m_date.errCode() == YEAR_ERROR)
		{
			er.message("Invalid Year in Date Entry");
		}

		if (m_date.errCode() == MON_ERROR)
		{
			er.clear();
			er.message("Invalid Month in Date Entry");
		}

		if (m_date.errCode() == DAY_ERROR)
		{
			er.clear();
			er.message("Invalid Day in Date Entry");
		}

		if (m_date.errCode())
		{
			is.setstate(std::ios::failbit);
		}

		if (m_date.errCode() != CIN_FAILED && m_date.errCode() != YEAR_ERROR && m_date.errCode() != MON_ERROR && m_date.errCode() != DAY_ERROR)
		{
			er.clear();
		}

		return is;*/
	}

	const Date& Perishable::expiry() const {
		return m_date;
	}


}