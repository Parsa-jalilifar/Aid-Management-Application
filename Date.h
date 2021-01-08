#ifndef AID_DATE_H
#define AID_DATE_H

namespace aid {

    #define NO_ERROR 0      
    #define CIN_FAILED 1    
    #define DAY_ERROR 2     
    #define MON_ERROR 3     
    #define YEAR_ERROR 4    
    #define PAST_ERROR 5    


	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {
	private:

		int m_year;
		int m_month;
		int m_day;
		int m_comparator;
		int m_errorState;

		void errCode(int errorCode);
		int mdays(int year, int mon) const;

	public:

		Date();
		Date(int year, int month, int day);
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::istream& operator>>(std::istream& is, Date& rhs);
	std::ostream& operator<<(std::ostream& os, const Date& rhs);

}
#endif 