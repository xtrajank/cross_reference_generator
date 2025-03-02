#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <regex>
#include <cstring>

const int WRAP_LIMIT = 9; // line limit before wrapping

// case insensitive comparator, will use in map
struct CaseInsensitiveComparator {
    bool operator ()(const std::string& a, const std::string& b) const {
        int result = _stricmp(a.c_str(), b.c_str());
        if (result == 0) return a < b;
        return result < 0;
    }
};

// extract valid tokens from a line
std::vector<std::string> extractTokens(const std::string& line) {
    std::vector<std::string> tokens;
    std::regex wordRegex(R"(\b[a-zA-Z][a-zA-Z'\-]*\b)"); // finds words, must start with a-z or A-Z, can contain alphabet or ' or -
    std::sregex_iterator it(line.begin(), line.end(), wordRegex); // iterate through all matches
    std::sregex_iterator end;
    
    while (it != end) {
        tokens.push_back(it->str());
        it++;
    }

    return tokens;
}

int main(int argc, char* argv[]) {
    std::ifstream file;
    std::istream* input = &std::cin;

    if (argc > 1) {
        file.open(argv[1]);
        if (!file) {
            std::cerr << "Error opening file: " << argv[1] << std::endl;
            return 1;
        }
        input = &file;
    }

    // create the word map
    std::map<std::string, std::map<int, int>, CaseInsensitiveComparator> wordMap;
    std::string line;
    int lineNumber = 0;

    while (std::getline(*input, line)) {
        lineNumber++;
        auto tokens = extractTokens(line);

        for (const auto& word : tokens) {
            wordMap[word][lineNumber]++;
        }
    }

    if (file.is_open()) file.close();

    // finds max word
    size_t maxWordLength = 0;
    for (const auto& entry : wordMap) {
        maxWordLength = std::max(maxWordLength, entry.first.size());
    }

    // formats and outputs
    for (const auto& [word, lines] : wordMap) {
        std::cout << std::left << std::setw(maxWordLength + 1) << word << ": ";

        int count = 0;
        for (auto it = lines.begin(); it != lines.end(); it++) {
            if (count > 0 && count % WRAP_LIMIT == 0) {
                std::cout << "\n" << std::string(maxWordLength + 1, ' ') << ": ";
            }
            std::cout << it->first << ":" << it->second;
            if (std::next(it) != lines.end()) std::cout << ", ";
            count++;
        }
        std::cout << std::endl;
    }

    return 0;
}