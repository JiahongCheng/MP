#include "functions.hpp"
#include <string>

// Your function definitions should go in this source file.
std::string ConvertToHawaiianWord(std::string input) {
    std::string word = input;
    std::string valid_word;
    std::string lower_word;
    for (unsigned int i = 0; i < input.size(); i++) {
        lower_word += tolower(input[i]);
    }

    for (unsigned int i = 0; i < lower_word.size(); i++) {
        char c = lower_word[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' ||
            c == 'n' || c == 'w' || c == ' ' || c == '\'') {
                valid_word += c;
            } else {
                return (input + " contains a character not a part of the Hawaiian language.");
            }
    }
    std::string output = Convert(valid_word);
    std::string final_output = SpciealCase(output);
    const std::string& new_string = RemoveDash(final_output);
    return new_string;
}

std::string Convert(std::string input) {
    std::string output;
    for (unsigned int i = 0; i < input.size(); i++) {
        char current = input.at(i);
        char after = ' ';
        char before = ' ';
        bool increment = false;
        if (i > 0) {
            before = input.at(i - 1);
        }
        if (i < input.size() - 1) {
            after = input.at(i + 1);
        }
        if (i == 0 && current == 'w') {
            output += current;
        } else if (current == 'w') {
            output += CaseW(before);
        }
        if (IsConsonants(current)) {
            output += current;
        } if (current == 'a') {
            output += CaseA(after, increment);
            AddOne(increment, i);
        } else if (current == 'e') {
            output += CaseE(after, increment);
            AddOne(increment, i);
        } else if (current == 'i') {
            output += CaseI(after, increment);
            AddOne(increment, i);
        } else if (current == 'o') {
            output += CaseO(after, increment);
            AddOne(increment, i);
        } else if (current == 'u') {
            output += CaseU(after, increment);
            AddOne(increment, i);
        } else if (current == ' ' || current == '\'') {
            output += current;
        }
    }
    return output;
}

void AddOne(bool& increment, unsigned int& i) {
    if (increment) {
        i++;
        increment = false;
    }
}

std::string SpciealCase(std::string input) {
    std::string output;
    for (unsigned int i = 0; i < input.size(); i++) {
        char current = input.at(i);
        char space = ' ';
        char dot = '\'';
        char before = ' ';
        if (i > 0) {
            before = input.at(i - 1);
        }
        if (current == space || current == dot) {
            if (before == '-') {
                output.pop_back();
            } 
        }
        output += current;
    }
    return output;
}

bool IsConsonants(char c) {
    return (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n');
}

std::string CaseA(char after, bool& increment) {
    if (after == 'i' || after == 'e') {
        increment = true;
        return "eye-";
    } 
    if (after == 'o' || after == 'u') {
        increment = true;
        return "ow-";
    } 
    return "ah-";
}

std::string CaseE(char after, bool& increment) {
    if (after == 'i') {
        increment = true;
        return "ay-";
    } 
    if (after == 'u') {
        increment = true;
        return "eh-oo-";
    } 
    return "eh-";
}
std::string CaseI(char after, bool& increment) {
    if (after == 'u') {
        increment = true;
        return "ew-";
    } 
    return "ee-";
}
std::string CaseO(char after, bool& increment) {
    if (after == 'u') {
        increment = true;
        return "ow-";
    } 
    if (after == 'i') {
        increment = true;
        return "oy-";
    }
    return "oh-";
}
std::string CaseU(char after, bool& increment) {
    if (after == 'i') {
        increment = true;
        return "ooey-";
    } 
    return "oo-";
}
std::string CaseW(char before) {
    if (before == 'i' || before == 'e') {
        return "v";
    }
    return "w";
}
std::string RemoveDash(const std::string& output) {
    unsigned int index = output.find_last_of('-');
    return output.substr(0, index);
}