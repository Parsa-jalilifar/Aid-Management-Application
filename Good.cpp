#include <iostream>
#include <fstream>
#include <cstring>
#include "Good.h"
#include "Error.h"

using namespace std;

namespace aid {

	Good::Good(char type) {

		m_good_Type = type;
		m_good_Sku[0] = '\0';
		m_good_Unit[0] = '\0';
		m_good_Name = nullptr;
		m_OnHand = 0;
		m_Needed = 0;
		m_Price_BeforeTax = 0.0;
		m_Taxable = false;
	}

	Good::Good(const char* SKU, const char* name, const char* unit, int quantityOnhand, bool taxable, double price, int quantityNeeded) {

		if (name == nullptr)
		{
			*this = Good();
		}
		else
		{
			this->m_good_Type = 'N';
			this->m_good_Name = nullptr;
			this->m_Needed = quantityNeeded;
			this->m_OnHand = quantityOnhand;
			this->m_Price_BeforeTax = price;
			this->m_Taxable = taxable;
			strcpy(this->m_good_Sku, SKU);
			strcpy(this->m_good_Unit, unit);
			this->m_good_Name = new char[strlen(name) + 1];
			strcpy(this->m_good_Name, name);
		}

	}

	void Good::name(const char * name) {

		if (name != nullptr) {
			
			delete[] m_good_Name;
			int length = strlen(name);

			if (length <= max_name_length)
			{
				m_good_Name = new char[length + 1];
				strncpy(m_good_Name, name, length);
				m_good_Name[length] = '\0';
			}
			else
			{
				m_good_Name = new char[max_name_length + 1];
				strncpy(m_good_Name, name, max_name_length);
				m_good_Name[max_name_length] = '\0';
			}

		}
		else 
		{
			delete[] m_good_Name;
		}
	}

	const char* Good::name() const {

		return (m_good_Name[0] == '\0') ? nullptr : m_good_Name;
	}

	const char* Good::sku() const {
		return m_good_Sku;
	}

	const char* Good::unit() const {
		return m_good_Unit;
	}

	bool Good::taxed() const {
		return m_Taxable;
	}

	double Good::itemPrice() const {
		return m_Price_BeforeTax;
	}

	double Good::itemCost() const {

		double itemCost = 0;

		if (m_Taxable) {
			itemCost += (m_Price_BeforeTax + (m_Price_BeforeTax * tax_rate));
		}
		else
		{
			itemCost = m_Price_BeforeTax;
		}

		return itemCost;
	}

	void Good::message(const char* str) {
		m_Err.message(str);
	}

	bool Good::isClear() const {
		return m_Err.isClear();
	}

	Good::Good(const Good& rhs) {

		m_good_Type = rhs.m_good_Type;
		strncpy(m_good_Sku, rhs.m_good_Sku, max_sku_length);
		m_good_Sku[max_sku_length] = '\0';

		if (strlen(rhs.m_good_Name) < max_name_length)
		{
			m_good_Name = new char[strlen(rhs.m_good_Name) + 1];
			strncpy(m_good_Name, rhs.m_good_Name, strlen(rhs.m_good_Name));
			m_good_Name[strlen(rhs.m_good_Name)] = '\0';
		}
		else {
			m_good_Name = new char[max_name_length + 1];
			strncpy(m_good_Name, rhs.m_good_Name, max_name_length);
			m_good_Name[max_name_length] = '\0';
		}

		strncpy(m_good_Unit, rhs.m_good_Unit, max_unit_length);
		m_good_Unit[max_unit_length] = '\0';

		m_OnHand = rhs.m_OnHand;
		m_Taxable = rhs.m_Taxable;
		m_Price_BeforeTax = rhs.m_Price_BeforeTax;
		m_Needed = rhs.m_Needed;

	}

	Good::~Good()
	{
		if (m_good_Name != nullptr) {
			delete[] m_good_Name;
		}
	}

	Good& Good::operator=(const Good& rhs) {

		if (this != &rhs) {

			this->m_good_Type = rhs.m_good_Type;

			strncpy(m_good_Sku, rhs.m_good_Sku, max_sku_length);
			m_good_Sku[max_sku_length] = '\0';

			delete[] this->m_good_Name;
			m_good_Name = new char[max_name_length + 1];
			strncpy(m_good_Name, rhs.m_good_Name, max_name_length);
			m_good_Name[max_name_length] = '\0';


			strncpy(m_good_Unit, rhs.m_good_Unit, max_unit_length);
			m_good_Unit[max_unit_length] = '\0';

			m_OnHand = rhs.m_OnHand;
			m_Taxable = rhs.m_Taxable;
			m_Price_BeforeTax = rhs.m_Price_BeforeTax;
			m_Needed = rhs.m_Needed;

		}

		return *this;
	}

	bool Good::operator==(const char* SKU) const {

		return (this->m_good_Sku == SKU) ? true : false;
	}

	double Good::total_cost() const {

		double totalCost = 0;
		totalCost += itemCost() * m_OnHand;

		return totalCost;
	}

	void Good::quantity(int amount) {
		if (amount > 0) {
			m_OnHand = amount;
		}
	}

	bool Good::isEmpty() const {
		return (m_good_Sku[0] == '\0' && m_good_Unit[0] == '\0' && m_good_Name == nullptr && m_Price_BeforeTax == 0 && m_OnHand == 0) ? true : false; 
	}

	int Good::qtyNeeded() const {
		return m_Needed;
	}

	int Good::quantity() const {
		return m_OnHand;
	}

	bool Good::operator>(const char* SKU) const {

		if (strcmp(m_good_Sku, SKU) > 0) {
			return true;
		}
		else
		{
			return false;
		}
		
	}


	bool Good::operator>(const iGood& rhs) const {
		
		if (strcmp(m_good_Name, rhs.name()) > 0) {
			return true;
		}
		else
		{
			return false;
		}
	}

	int Good::operator+=(int units) {
		if (units > 0) {
			m_OnHand += units;
		}
		return m_OnHand;
	}

	std::fstream& Good::store(std::fstream& file, bool newLine) const {

		file << m_good_Type << ',' << m_good_Sku << ',' << m_good_Name << ',' << m_good_Unit << ',' << m_Taxable
			<< "," << m_Price_BeforeTax << "," << m_OnHand << "," << m_Needed;

		if (newLine == true) {
			file << endl;
		}

		return file;		
	}

	std::fstream& Good::load(std::fstream& file) {

		char SKU[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		int quantity;
		int quantityNeeded;
		double price;
		bool taxable;


		file.getline(SKU, max_sku_length, ',');
		file.getline(name, max_name_length, ',');
		file.getline(unit, max_unit_length, ',');
		file >> taxable;
		file.ignore();
		file >> price;
		file.ignore();
		file >> quantity;
		file.ignore();
		file >> quantityNeeded;


		*this = Good(SKU, name, unit, quantity, taxable, price, quantityNeeded);

		return file;
	}

	std::ostream& Good::write(std::ostream& os, bool linear) const {

		if (!m_Err.isClear()) {

			cout << m_Err.message();

		}
		else if (!isEmpty() && linear == true) {

			os.setf(ios::fixed);
			os.setf(ios::left);
			os.width(max_sku_length);
			os << m_good_Sku << "|";
			os.width(20);
			os << m_good_Name << "|";
			os.unsetf(ios::left);
			os.precision(2);
			os.width(7);

			if (m_Taxable) {
				os << (m_Price_BeforeTax + (m_Price_BeforeTax * tax_rate)) << "|";
			}
			else
			{
				os << m_Price_BeforeTax << "|";
			}

			os.width(4);
			os << m_OnHand << "|";
			os.setf(ios::left);
			os.width(10);
			os << m_good_Unit << "|";
			os.unsetf(ios::left);
			os.width(4);
			os << m_Needed << "|";

		}
		else if (!isEmpty() && linear == false) {


			os << " Sku: " << m_good_Sku << endl;
			os << " Name (no spaces): ";
			os << m_good_Name << endl;
			os << " Price: " << m_Price_BeforeTax << endl;

			os << " Price after tax: ";
			if (m_Taxable == true) {
				os << m_Price_BeforeTax + (m_Price_BeforeTax * tax_rate) << endl;
			}
			else {
				os << " N/A" << endl;
			}

			os << " Quantity on Hand: " << m_OnHand << ' ' << m_good_Unit << endl;
			os << " Quantity needed: " << m_Needed;

		}

		return os;
	}

	std::istream& Good::read(std::istream& is) {

		char SKU[max_sku_length + 1];
		char *name = new char[max_name_length + 1];
		char unit[max_unit_length + 1];
		int quantityOnhand;
		int quantityNeeded;
		double price;
		bool taxable;

		bool error = false;
		char tax;
		char type = m_good_Type;


		m_Err.clear();

		cout << " Sku: ";
		is >> SKU;

		if (is.fail()) {
			error = true;
		}

		if (!error) {
			cout << " Name (no spaces): ";
			is >> name;
		}

		if (is.fail()) {
			error = true;
		}

		if (!error) {
			cout << " Unit: ";
			is >> unit;
		}

		if (is.fail()) {
			error = true;
		}

		if (!error) {

			cout << " Taxed? (y/n): ";
			is >> tax;

			if (tax == 'y' || tax == 'Y') {
				taxable = true;
			}
			else if (tax == 'n' || tax == 'N') {
				taxable = false;
			}
			else
			{
				error = true;
				is.setstate(std::ios::failbit);
				m_Err.message("Only (Y)es or (N)o are acceptable");
			}
		}

		if (!error) {

			cout << " Price: ";
			is >> price;

			if (is.fail()) {
				error = true;
				is.setstate(std::ios::failbit);
				m_Err.message("Invalid Price Entry");
			}
		}

		if (!error) {

			cout << " Quantity on hand: ";
			is >> quantityOnhand;

			if (is.fail()) {
				error = true;
				is.setstate(std::ios::failbit);
				m_Err.message("Invalid Quantity Entry");
			}
		}

		if (!error) {

			cout << " Quantity needed: ";
			is >> quantityNeeded;

			if (is.fail()) {
				error = true;
				is.setstate(std::ios::failbit);
				m_Err.message("Invalid Quantity Needed Entry");
			}

		}

		if (!error) {
			*this = Good(SKU, name, unit, quantityOnhand, taxable, price, quantityNeeded);
			this->m_good_Type = type;
			is.ignore(1000, '\n');
		}

		return is;
	}

	

	std::ostream& operator<<(std::ostream& os, const iGood& rhs) {

		rhs.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, iGood& rhs) {

		rhs.read(is);
		return is;
	}

	double operator+=(double& total, const iGood& rhs) {

		return (total + rhs.total_cost());
	}
}
