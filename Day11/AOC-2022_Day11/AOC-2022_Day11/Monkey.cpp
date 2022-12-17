#include "Monkey.h"
#include <assert.h>
#include <limits>
#include <cmath>

Monkey::Monkey(const std::queue<uint64_t>& items, const std::string& operation, uint64_t divisibleBy, unsigned int ifTrueMonkey, unsigned int ifFalseMonkey) :
	m_items(items),
	m_operation(operation),
	m_divisibleBy(divisibleBy),
	m_ifTrueMonkey(ifTrueMonkey),
	m_ifFalseMonkey(ifFalseMonkey) 
{
}

void Monkey::AddItem(uint64_t itemValue) {
	m_items.push(itemValue);
}

void Monkey::TakeTurn(std::vector<Monkey>& monkeys, uint64_t bigMod, int part) {
	while (m_items.size() != 0) {
		ProcessItem(monkeys, bigMod, part);
	}
}

void Monkey::ProcessItem(std::vector<Monkey>& monkeys, uint64_t bigMod, int part) {
	// grab first item in items queue
	uint64_t itemVal = m_items.front();
	m_items.pop();

	// set up terms of math operations
	std::string firstTerm = m_operation.substr(0, m_operation.find(' '));
	std::string secondTerm = m_operation.substr(m_operation.find_last_of(' ') + 1);

	char operatorChar = m_operation[m_operation.find(' ') + 1];

	uint64_t firstVal, secondVal;
	// compute values for operation
	if (firstTerm == "old")
		firstVal = itemVal;
	else
		firstVal = uint64_t(stoll(firstTerm));

	if (secondTerm == "old")
		secondVal = itemVal;
	else
		secondVal = uint64_t(stoll(secondTerm));


	uint64_t newVal = PerformOperation(firstVal, operatorChar, secondVal);

	if (part == 1) {
		newVal = newVal / 3;
	}

	bool test = newVal % m_divisibleBy == 0;

	if (bigMod != 0) {
		newVal %= bigMod;
	}

	if (test) {
		monkeys[m_ifTrueMonkey].AddItem(newVal);
	}
	else {
		monkeys[m_ifFalseMonkey].AddItem(newVal);
	}

	m_inspects++;
}

uint64_t Monkey::PerformOperation(uint64_t firstTerm, char operatorChar, uint64_t secondTerm) {
	if (operatorChar == '+') {
		return firstTerm + secondTerm;
	}

	else if (operatorChar == '-') {
		return firstTerm - secondTerm;
	}

	else if (operatorChar == '*') {
		return firstTerm * secondTerm;
	}

	assert(0); // unreachable
	return -1;
}

Monkey CreateMonkey(std::string monkeyText[7]) {
	std::queue<uint64_t> startingItems;

	// get starting items
	startingItems.push(stoi(monkeyText[1].substr(monkeyText[1].find(": ") + 2)));
	int lastPos = 0;
	while (monkeyText[1].find(',', lastPos) != std::string::npos) {
		size_t index = monkeyText[1].find(',', lastPos) + 2;

		startingItems.push(stoi(monkeyText[1].substr(index)));
		lastPos = index;
	}

	std::string operation = monkeyText[2].substr(monkeyText[2].find("= ") + 2);

	uint64_t divisibleTestNum = stoi(monkeyText[3].substr(monkeyText[3].find("by ") + 3));

	unsigned int ifTrueMonkey, ifFalseMonkey;

	ifTrueMonkey = stoi(monkeyText[4].substr(monkeyText[4].find("monkey ") + 7));
	ifFalseMonkey = stoi(monkeyText[5].substr(monkeyText[5].find("monkey ") + 7));

	return Monkey(startingItems, operation, divisibleTestNum, ifTrueMonkey, ifFalseMonkey);
}