#pragma once
#include <string>
#include<filesystem>

class Logger
{
public:
	static void LOG(std::string_view message);
};