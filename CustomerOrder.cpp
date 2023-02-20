// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}


	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities ut;
		bool more;
		size_t pos = 0;
		try {
			m_name = ut.extractToken(str, pos, more);
			m_product = ut.extractToken(str, pos, more);
			m_cntItem = std::count(str.begin(), str.end(), ut.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(ut.extractToken(str, pos, more));
			}
			m_widthField = m_widthField > ut.getFieldWidth() ? m_widthField : ut.getFieldWidth();
		}
		catch (const char* msg) {
			std::cout << msg;
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder&) {
		throw "ERROR: Cannot make copies.";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;
		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0;
		src.m_lstItem = nullptr;
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}
		return*this;
	}

	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_isFilled == false) {
				return false;
			}
		}
		return true;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool result = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (m_lstItem[i]->m_isFilled == false) {
					result = false;
				}
			}
		}
		
		return result;
	}


	void CustomerOrder::fillItem(Station& station, std::ostream& os) {

		bool valid = true;
		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&](Item* item) {
			if (station.getItemName() == item->m_itemName && valid && item->m_isFilled == false) {
				if (station.getQuantity() > 0) {

					station.updateQuantity();
					item->m_serialNumber = station.getNextSerialNumber();
					item->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << std::endl;
					valid = false;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << item->m_itemName << "]" << std::endl;
				}
			}
			});
	}

	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::left << std::setw(m_widthField + 1) << std::setfill(' ') << m_lstItem[i]->m_itemName << "  - ";
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "TO BE FILLED" << std::endl;
			}
		}
	}
}