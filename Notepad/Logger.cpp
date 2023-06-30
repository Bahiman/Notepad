#include "Logger.h"
#include<fstream>
#include <iostream>
#include<stdexcept>

void Logger::LOG(std::string_view message)
{
	std::cout << message << std::endl;
	static int m_counter = 0;
	std::string m_path = "./log.txt";
	if (!std::filesystem::exists(m_path))
		throw std::runtime_error("The file was not found!");
	std::fstream file_stream(m_path, std::ios::app);
	if (!file_stream.good())
		throw std::runtime_error("The file couldn't be opened!");
	std::time_t curr_time = std::time(nullptr);
	std::string new_time = std::ctime(&curr_time);
	new_time.erase(new_time.find_last_not_of("\n") + 1);
	file_stream << new_time << ' ' << m_counter << '\n' << message << '\n' << std::endl;
	m_counter++;
}
