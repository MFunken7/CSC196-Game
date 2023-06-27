#include "FileIO.h"

namespace kiko
{
	std::string getFilePath()
	{
		return std::filesystem::current_path().string();
	}
}