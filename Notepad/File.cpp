#include "File.h"
#include<filesystem>
#include<algorithm>
#include<cctype>

void File::updatePath(std::string_view path)
{
	if (!std::filesystem::exists(path))
		throw std::runtime_error("The file doesn't exist(Trying to modify the read path)");
	m_path = path;
}

bool File::isTextFile()
{
	std::string extension = m_path.extension().string();

    // Convert the extension to lowercase
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return std::tolower(c); });
	
	return textFileExtensions.count(extension) > 0;
}

bool File::is_good()
{
	return isTextFile() && std::filesystem::exists(m_path);
}
