#include "FileWriter.h"
#include<fstream>
#include <iostream>

void FileWriter::write(std::string_view data)
{
	if (!is_good())
		throw std::runtime_error("The file is not good(trying to write)");

	std::ofstream stream(m_path, std::ios::trunc);
	
	if (!stream.good())
	{
		std::cerr << std::strerror(errno) << std::endl;
		throw std::runtime_error("The stream couldn't be opened(tring to write)");
	}

	stream << data;
}

void FileWriter::clear()
{
	if (!is_good())
		throw std::runtime_error("The file is not good(trying to write)");
	std::fstream stream(m_path, std::ios::trunc);

	if (!stream.good())
		throw std::runtime_error("The stream couldn't be opened(tring to write)");
}
