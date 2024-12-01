#include "functions.hpp"
#include "utilities.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <string>

std::vector<std::string> Header(const std::string& file) {
    std::ifstream ifs{file};
    std::string line;
    std::getline(ifs, line);
    return utilities::GetSubstrs(line, ',');
}

std::vector<std::vector<std::string>> GetPeople(const std::string& file) {
    std::ifstream ifs{file};
    std::string second_line;
    std::getline(ifs, second_line);
    std::vector<std::vector<std::string>> people;
    for (std::string line; std::getline(ifs, line); line = "") {
        people.push_back(utilities::GetSubstrs(line, ','));
    }
    return people;
}

int Max(const std::string& str, const std::string& str2) {
    int l = str2.length();
    int count = 0;
    int max = 0;
    for (std::string::size_type i = 0; i <= str.length() - l; i++) {
        if (str.substr(i, l) == str2) {
            count++;
            i += l - 1;
        } else {
            if (max < count) {
                max = count;
            }
            count = 0;
        }
    }
    if (max < count) {
        max = count;
    }
    return max;
}

std::string Match(const std::string& file, const std::string& dna) {
    std::vector<std::string> header = Header(file);
    std::vector<std::vector<std::string>> people = GetPeople(file);
    bool match = true;
    for (std::vector<std::vector<std::string>>::size_type i = 0; i < people.size(); i++) {
        for (std::vector<std::string>::size_type j = 1; j < header.size(); j++) {
            if (std::stoi(people[i][j]) != Max(dna, header[j])) {
                match = false;
                break;
            }
        }
        if (match) {
            return people[i][0];
        }
        match = true;
    }
    return "No match";
}