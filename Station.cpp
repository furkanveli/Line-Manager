// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <string>
#include <iostream>
#include "Station.h"
#include "Utilities.h"
namespace sdds {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;
	
	Station::Station(const std::string& str) {
		Utilities ut;
		bool more;
		size_t pos = 0;
		size_t endOfName;
		try {
			nameOfItem = ut.extractToken(str, pos, more);

			endOfName = nameOfItem.find_last_not_of(" ");
			nameOfItem = (endOfName == std::string::npos) ? "" : nameOfItem.substr(0, endOfName + 1);

			m_serialNumber = std::stoi(ut.extractToken(str, pos, more));
			currentQuantity = std::stoi(ut.extractToken(str, pos, more));
			m_widthField = m_widthField > ut.getFieldWidth() ? m_widthField : ut.getFieldWidth();
			description = ut.extractToken(str, pos, more);
			id_generator++;
			stationId = id_generator;
		}
		catch (const char* msg) {
			std::cout << msg << std::endl;
		}
	}

	const std::string& Station::getItemName() const {
		return nameOfItem;
	}

	size_t Station::getNextSerialNumber() {		
		return m_serialNumber++;
	}

	size_t Station::getQuantity() const {
		return currentQuantity;
	}

	void Station::updateQuantity() {
		if(currentQuantity > 0)
			currentQuantity--;
	}

	void Station::display(std::ostream& os, bool full) const {
		if (!full) {
			os.setf(std::ios::right);
			os.fill('0');
			os.width(3);
			os << stationId;
			os.unsetf(std::ios::right);
			os << " | ";
			os.setf(std::ios::left);
			os.fill(' ');
			os.width(m_widthField + 1);
			os << nameOfItem;
			os.unsetf(std::ios::left);
			os << " | ";
			os.setf(std::ios::right);
			os.fill('0');
			os.width(6);
			os << m_serialNumber;
			os.unsetf(std::ios::right);
			os << " | ";
			os << std::endl;
		}
		else {
			os.setf(std::ios::right);
			os.fill('0');
			os.width(3);
			os << stationId;
			os.unsetf(std::ios::right);
			os << " | ";
			os.setf(std::ios::left);
			os.fill(' ');
			os.width(m_widthField + 1);
			os << nameOfItem;
			os.unsetf(std::ios::left);
			os << " | ";
			os.setf(std::ios::right);
			os.fill('0');
			os.width(6);
			os << m_serialNumber;
			os.unsetf(std::ios::left);
			os << " | ";
			os.setf(std::ios::right);
			os.fill(' ');
			os.width(4);
			os << currentQuantity;
			os.unsetf(std::ios::right);
			os << " | ";
			os << description;
			os << std::endl;
		}
	}

}