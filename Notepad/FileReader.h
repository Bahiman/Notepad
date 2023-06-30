#pragma once
#include <string>
#include"File.h"

class FileReader : public File
{
private:
	inline static std::string m_file_contents = "";
public:
	static void updateContents();
	static const std::string& getContents();
	static bool changed(std::string_view old_data);
};