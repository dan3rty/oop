#pragma once

int StringToInt(const std::string& str, int radix);

int CharToInt(const char& symbol);

std::string IntToString(int n, int radix);

std::string numberConversion(const std::string& sourceNotation, const std::string& destinationNotation, const std::string& value);