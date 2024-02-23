#pragma once
#include <string>

std::string ReplaceString(const std::string& subject, const std::string& searchString, const std::string& replacementString);

void CopyStreamWithReplacement(std::istream& input, std::ostream& output, const std::string& searchString, const std::string& replacementString);

void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName, const std::string& searchString, const std::string& replaceString);