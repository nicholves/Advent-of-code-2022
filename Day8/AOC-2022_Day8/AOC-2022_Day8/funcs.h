#pragma once

char GetFromTree(const char* arr, size_t row, size_t col, size_t colsize);

void SetInTree(char* arr, size_t row, size_t col, char c, size_t colsize);

int GetNumVisibleTrees(const char* arr, size_t rows, size_t cols);

bool TreeIsVisible(const char* arr, int y, int x, size_t rows, size_t cols);

int GetBestScenicScore(const char* arr, size_t rows, size_t cols);

int GetScenicScore(const char* arr, int y, int x, size_t rows, size_t cols);