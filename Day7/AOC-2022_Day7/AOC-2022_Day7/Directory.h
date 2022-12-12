#pragma once

#include <string>
#include <vector>
#include <map>

class Directory {
public:
	void addSubdir(Directory* dir);

	int getTotalSize() const;

	int getSizeOfFiles() const;

	void setSizeOfFile(std::string fileName, int size);

	std::string getPath() const;

	void setPath(std::string path);

	std::vector<Directory*> getSubdirs();

	std::string getDirName() const;

	inline std::map<std::string, int> getFiles() const { return m_files; }

	inline std::vector<Directory*> getSubDirs() const { return m_subDirs; }

private:

	std::string m_path;

	std::vector<Directory*> m_subDirs;

	std::map<std::string, int> m_files;
};