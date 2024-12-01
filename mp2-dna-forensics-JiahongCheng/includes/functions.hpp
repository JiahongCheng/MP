#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"


std::vector<std::string> Header(const std::string& file);
std::vector<std::vector<std::string>> GetPeople(const std::string& file);
int Max(const std::string& str, const std::string& str2);
std::string Match(const std::string& file, const std::string& dna);

#endif