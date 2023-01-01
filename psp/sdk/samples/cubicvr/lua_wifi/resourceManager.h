#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <stdlib.h>
#include <string.h>
#include <string>

extern std::string	baseContentDirectoryPath;

void 				ResourceSetHomeDirectory(std::string dir);
std::string 		ResourceFilename(std::string resourceFilename);

#endif