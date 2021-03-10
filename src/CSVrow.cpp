#include "CSVrow.hpp"

CSVrow::CSVrow(char delimiter)
{
  // std::cout << "CSVrow constructor" << endl;
  this->delimiter = delimiter;
}


std::size_t CSVrow::size() const
{
  return m_data.size();
}

void CSVrow::readNextRow(std::ifstream& fstr)
{
  std::string         line;
  std::getline(fstr, line);

  std::stringstream   lineStream(line);
  std::string         cell;

  m_data.clear();
  while(std::getline(lineStream, cell, delimiter)) {
    m_data.push_back(cell);
  }
  // This checks for a trailing comma with no data after it.
  if (!lineStream && cell.empty()) {
    // If there was a trailing delimiter then add an empty element.
    m_data.push_back("");
  }
}

std::string const& CSVrow::operator[](std::size_t index) const
{
  return m_data[index];
}
