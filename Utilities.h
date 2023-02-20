// Name: Furkan Veli Ozalp
// Seneca Student ID: 157580200
// Seneca email: fvozalp@myseneca.ca
// Date of completion: 2022-07-02
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef UTILITIES
#define UTILITIES
#include <string>
namespace sdds {
	class Utilities {
	private:
		size_t m_widthField = 1;
	public:
		static char m_delimiter;

		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

	};
}


#endif // !UTILITIES

