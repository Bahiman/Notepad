#pragma once
#include <string>
#include<filesystem>
#include<unordered_set>



class File
{
protected:
	inline static const std::unordered_set<std::string> textFileExtensions = { ".txt", ".cpp", ".h", ".hpp", ".c", ".java" };
	inline static std::filesystem::path m_path = "./log.txt";
public:
	static void updatePath(std::string_view path);
	static bool isTextFile();
	static bool is_good();
};