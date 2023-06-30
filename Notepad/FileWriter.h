#pragma once
#include <string>
#include "File.h"

class FileWriter : public File
{
 public:
	static void write(std::string_view data);
	static void clear();
};