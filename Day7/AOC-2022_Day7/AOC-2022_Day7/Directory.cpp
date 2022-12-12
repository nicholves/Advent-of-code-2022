#include "Directory.h"

void Directory::addSubdir(Directory* dir) {
	m_subDirs.push_back(dir);
}

int Directory::getTotalSize() const {
	int totalOfSubdirs = 0;
	for (Directory* dir : m_subDirs) {
		totalOfSubdirs += dir->getTotalSize();
	}

	return totalOfSubdirs + getSizeOfFiles();
}

int Directory::getSizeOfFiles() const {
	int total = 0;

	for (std::pair<std::string, int> file : m_files) {
		total += file.second;
	}
	return total;
}

void Directory::setSizeOfFile(std::string filename, int size) {
	m_files.insert(std::pair<std::string, int>(filename, size));
}

std::string Directory::getPath() const {
	return m_path;
}

void Directory::setPath(std::string path) {
	m_path = path;
}

std::vector<Directory*> Directory::getSubdirs() {
	return m_subDirs;
}

std::string Directory::getDirName() const {
	if (m_path == "/")
		return "/";

	std::string tempstring = m_path;

	tempstring = tempstring.substr(0, tempstring.size() - 1);

	return tempstring.substr(tempstring.find_last_of('/') + 1);
}