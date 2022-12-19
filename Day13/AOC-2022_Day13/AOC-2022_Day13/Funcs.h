#pragma once
#include <string>

enum Winner {
	FIRSTARG,
	SECONDARG
};

int CheckPair(const std::pair<std::string, std::string>& pair);

bool LeftvRight(std::vector<std::string> left, std::vector<std::string> right, bool recursiveCall = false);

Winner ListvList(std::string list1, std::string list2, bool recursiveCall = false);

Winner ListvInt(std::string list, int integer);