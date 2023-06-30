#include "FileReader.h"
#include <filesystem>
#include <fstream>
	
void FileReader::updateContents()
{
	if (!is_good())
		throw std::runtime_error("The file is not good(trying to update contents)");

	std::ifstream stream(m_path);
	
	if (!stream.good())
		throw std::runtime_error(std::string("The stream couldn't be opened(trying to update contents)[") + std::strerror(errno));

	std::string temp;

	// this is a very regular ass comment that I am just doing cuz my mom

	m_file_contents.clear();

	while (std::getline(stream,temp))
	{
		m_file_contents += temp;
		m_file_contents += '\n';
	}
}

const std::string& FileReader::getContents()
{
	return m_file_contents;
}

bool FileReader::changed(std::string_view old_data)
{
	return getContents() == old_data;
	// oh yay makeda and also set the fuck down t sereis I am here to spill the real tea we a re atring to get through me for spotting number one but you inida you lose so bad things that you have doen when we have only just 
}
