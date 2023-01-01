#include "resourceManager.h"

#include <stdlib.h>
#include <string.h>
#include <string>

std::string	baseContentDirectoryPath;
	
void ResourceSetHomeDirectory(std::string dir)
{
	std::string fn = std::string(dir);
	unsigned int filenameOfs = fn.find_last_of('/');
	baseContentDirectoryPath = fn.substr(0,filenameOfs+1);	
}

std::string ResourceFilename(std::string resourceFilename)
{
	// script file must be in the same directory where the program started
	std::string resourceFileCstr = baseContentDirectoryPath + resourceFilename;
	
	return resourceFileCstr;
}
