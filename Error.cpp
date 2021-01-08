#include <iostream>
#include <cstring>
#include <string>
#include "Error.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;

namespace aid
{
	Error::Error(const char* errorMessage )
	{
		if (errorMessage == nullptr || (errorMessage[0] == '\0'))
		{
			m_Message = nullptr;
		}
		else
		{
			m_Message = new char[strlen(errorMessage) + 1];
			strcpy(m_Message, errorMessage);
		}
	}

	Error::~Error()
	{
		clear();
	}

	void Error::clear()
	{
		delete[] this->m_Message;
		this->m_Message = nullptr;
	}

	bool Error::isClear() const
	{
		if(m_Message == nullptr){return true;}else{return false;}
	}

	void Error::message(const char* str)
	{
		clear();

		if ((str == nullptr) || (str[0] == '\0') ) {

			this->m_Message = nullptr;
		}
		else
		{
			this->m_Message = new char[strlen(str) + 1];
			strcpy(m_Message, str);
		}
		
	}

	const char* Error::message() const
	{
		if (this->m_Message == false) 
		{
			return nullptr;
		}
		else 
		{
			return this->m_Message;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Error& error)
	{
		if (!error.isClear())
		{
			os << error.message();
		}
		return os;
	}
}
