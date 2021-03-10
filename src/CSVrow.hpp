//////////////////////////////////////////////////////////////////////////////////////////////////
// CSVrow class
// Description: class to parse data in table form from CSV-like files. The 
// Reference: http://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c 
// Modified by Daniel Santiago-Gonzalez (Feb/2021)
// Compile with: g++ -c -o CSVrow.o CSVrow.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class CSVrow
{
public:
  CSVrow(char delimiter=',');
  std::string const& operator[](std::size_t index) const;
  // std::istream& operator>>(std::istream& str);

  std::size_t size() const;
  void readNextRow(std::ifstream& fstr);
private:
  std::vector<std::string>    m_data;
  char delimiter;
};
