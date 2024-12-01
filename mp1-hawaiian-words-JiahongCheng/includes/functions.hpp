#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
#include <iostream>

// Your function declarations should go in this header file.
std::string ConvertToHawaiianWord(std::string input);
bool IsConsonants(char c);
std::string CaseA(char after, bool& increment);
std::string CaseE(char after, bool& increment);
std::string CaseI(char after, bool& increment);
std::string CaseO(char after, bool& increment);
std::string CaseU(char after, bool& increment);
std::string CaseW(char before);
std::string RemoveDash(const std::string& output);
std::string Convert(std::string input);
void AddOne(bool& increment, unsigned int& i);
std::string SpciealCase(std::string input);
#endif