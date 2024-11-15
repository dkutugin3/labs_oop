#include <set>
#include <string>
#include <iostream>
std::string removeVowels(const std::string& input) {
    std::set<char> vowels = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
    std::string result;
    for (char c : input) {
        if (vowels.count(c) == 0) {
            result += c;
        }
    }
    return result;
}