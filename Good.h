#ifndef AID_GOOD_H
#define AID_GOOD_H

#include <iostream>
#include "Error.h"
#include "iGood.h"

namespace aid {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax_rate = 0.13;

	class Good : public iGood
	{
	private:
		char m_good_Type;
		char m_good_Sku[max_sku_length + 1];
		char m_good_Unit[max_unit_length + 1];
		char* m_good_Name;
		int m_OnHand;
		int m_Needed;
		double m_Price_BeforeTax;
		bool m_Taxable;

	protected:
		Error m_Err;

		void name(const char* str);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char*);
		bool isClear() const;

	public:

		Good(char type = 'N');
		Good(const char* SKU, const char* name, const char* unit, int quantity = 0, bool taxable = true, double price = 0, int quantityNeeded = 0);
		Good(const Good& rhs);
		~Good();
		Good& operator=(const Good& rhs);
		bool operator==(const char* SKU) const;
		double total_cost() const;
		void quantity(int amount);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* SKU) const;
		bool operator>(const iGood&) const;
		int operator+=(int units);
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

	};

	std::ostream& operator<<(std::ostream&, const iGood&);
	std::istream& operator>>(std::istream& , iGood&);
	double operator+=(double&, const iGood&);

}
#endif