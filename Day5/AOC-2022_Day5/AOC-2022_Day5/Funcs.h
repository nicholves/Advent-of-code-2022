#pragma once
#include <string>
#include <stack>
#include <vector>

void ProcessRow(std::string text, std::vector<std::stack<char>*>& stacks);

void ReverseStack(std::stack<char>& stack);

void ProcessCommand(std::vector<std::stack<char>*>& stacks, std::string command);

void ProcessCommandRetainOrder(std::vector<std::stack<char>*>& stacks, std::string command);