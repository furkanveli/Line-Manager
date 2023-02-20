// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef STATION
#define STATION

namespace sdds {
	class Station {
	private:
		int stationId;
		std::string nameOfItem;
		std::string description;
		unsigned int m_serialNumber;
		unsigned int currentQuantity;
	public:
		
		static size_t m_widthField;
		static size_t id_generator;

		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}


#endif // !STATION


