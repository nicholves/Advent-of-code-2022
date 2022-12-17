#pragma once
#include <string>
#include <queue>
#include <vector>
#include <limits>

class Monkey {
public:
	Monkey(const std::queue<uint64_t>& items, const std::string& operation, uint64_t divisibleBy, unsigned int ifTrueMonkey, unsigned int ifFalseMonkey);

	void AddItem(uint64_t itemValue);

	void TakeTurn(std::vector<Monkey>& monkeys, uint64_t bigMod = 0, int part = 1);

	inline uint64_t getInspects() { return m_inspects; }

	inline uint64_t getDivBy() { return m_divisibleBy; }

private:
	void ProcessItem(std::vector<Monkey>& monkeys, uint64_t bigMod, int part = 1);

	uint64_t PerformOperation(uint64_t firstTerm, char operatorChar, uint64_t secondTerm);

	std::string m_operation;

	unsigned int m_ifTrueMonkey;
	unsigned int m_ifFalseMonkey;
	
	uint64_t m_divisibleBy;
	uint64_t m_inspects = 0; // nums can get big in part 2

	std::queue<uint64_t> m_items;
};

Monkey CreateMonkey(std::string monkeyText[7]);