#pragma once

int StringToInt(const std::string& str, int radix);

bool IsSumOverflowed(int a, int b, int radix);

int CharToInt(const char& symbol);

std::string IntToString(int n, int radix);

char IntToChar(int n);

std::string ChangeNumberNotation(int sourceNotation, int destinationNotation, const std::string& value);

bool IsNotationsValid(int sourceNotation, int destinationNotation);

bool IsNotationValid(int notation);