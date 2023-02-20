// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Utilities.h"
#include <iostream>
#include <string>
namespace sdds {
	const std::string trimmables = " \n\f\v\r\t";

	char Utilities::m_delimiter = ',';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

		
		size_t delimiterIndex = (str.find(getDelimiter(), next_pos));
		std::string token = str.substr(next_pos, delimiterIndex - next_pos);
		token.erase(0, token.find_first_not_of(trimmables));
		token.erase(token.find_last_not_of(trimmables) + 1);
		if (delimiterIndex == next_pos)
		{
			more = false;
			throw "   ERROR: No token.";
		}

		next_pos = delimiterIndex + 1;

		setFieldWidth(std::max(m_widthField, token.size()));
		more = delimiterIndex != std::string::npos;

		return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
	
}