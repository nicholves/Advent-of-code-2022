#pragma once
#include <string>

#include "Directory.h"

void processCD(std::string& currPath, const std::string& commandText);

void processLSData(const std::string& currPath, std::vector<Directory*>& dirs, const std::string& text);

void printFileSystem(const Directory& dir, int depth = 0);

void fillSpace(std::string& space, int n);