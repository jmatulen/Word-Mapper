#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

// Given a word and a map, return its mapped value
std::string mapWord(std::string word, std::map<char, char>& letterMap) {
    // For each letter in the string, map it to its value
    std::string mappedWord = "";
    char mappedLetter;
    for (auto& letter : word) {
        // if letter is in map, map it to its value
        if (letterMap.find(letter) != letterMap.end()) {
            mappedLetter = letterMap.find(letter)->second;
        } else {
            // if letter is not in map, map it to nothing
            continue;
        }
        mappedWord += mappedLetter;
    }
    return mappedWord;
}

// given a file of words, return a map of words to their mapped values
std::map<std::string, std::vector<std::string>> mapAllWords(std::string fileName, std::map<char, char>& letterMap) {
    std::map<std::string, std::vector<std::string>> wordMap;
    std::ifstream file(fileName);
    std::string word;
    while (file >> word) {
        // map word to its value
        std::string mappedWord = mapWord(word, letterMap);
        // if mapped word is longer than 4 digits, skip it
        if (mappedWord.length() > 4) {
            continue;
        }
        // otherwise, add the word and its mapping to the priority queue
        else if(wordMap.find(mappedWord) != wordMap.end()) {
            wordMap.find(mappedWord)->second.push_back(word);
        } else {
            wordMap.insert(std::make_pair(mappedWord, std::vector<std::string>{word}));
        }
    }
    return wordMap;
}

// given a map of words to mapped values, return the mappings with a certain key length
std::map<std::string, std::vector<std::string>> getFromKeySize(std::map<std::string, std::vector<std::string>>& mappingMap, int keySize) {
    std::map<std::string, std::vector<std::string>> keySizeMap;
    for (auto& mapping : mappingMap) {
        // if the mapped word is the same length as the key size, add it to the map
        if (mapping.first.length() == keySize) {
            keySizeMap.insert(std::make_pair(mapping.first, mapping.second));
        }
    }
    return keySizeMap;
}

// print the mapping map
void printMappingMap(std::map<std::string, std::vector<std::string>>& mappingMap) {
    for (auto& mapping : mappingMap) {
        std::cout << mapping.first << ": ";
        for(int i = 0; i < mapping.second.size(); i++) {
            std::cout << mapping.second[i];
            if (i != mapping.second.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

// output the mapping map to a file
void outputMappings(std::map<std::string, std::vector<std::string>>& mappingMap, std::string fileName) {
    std::ofstream file(fileName);
    for (auto& mapping : mappingMap) {
        file << mapping.first << ":, ";
        for (int i = 0; i < mapping.second.size(); i++) {
            file << mapping.second[i];
            if (i != mapping.second.size() - 1) {
                file << ", ";
            }
        }
        file << std::endl;
    }
}

int main() {
    // letter mappings
    std::map<char, char> letterMap = {
        {'m', '0'},
        {'n', '1'},
        {'t', '2'},
        {'h', '2'},
        {'z', '2'},
        {'b', '3'},
        {'w', '4'},
        {'v', '4'},
        {'k', '4'},
        {'f', '5'},
        {'r', '5'},
        {'j', '6'},
        {'p', '6'},
        {'x', '6'},
        {'s', '7'},
        {'d', '7'},
        {'g', '8'},
        {'q', '8'},
        {'l', '8'},
        {'c', '9'}
    };
    std::map<std::string, std::vector<std::string>> wordMap = mapAllWords("all_words.txt", letterMap);
    std::map<std::string, std::vector<std::string>> singleDigits = getFromKeySize(wordMap, 1);
    std::map<std::string, std::vector<std::string>> doubleDigits = getFromKeySize(wordMap, 2);
    std::map<std::string, std::vector<std::string>> tripleDigits = getFromKeySize(wordMap, 3);
    std::map<std::string, std::vector<std::string>> quadDigits = getFromKeySize(wordMap, 4);
    //printMappingMap(singleDigits);
    //printMappingMap(doubleDigits);
    //printMappingMap(tripleDigits);
    //printMappingMap(quadDigits);
    outputMappings(singleDigits, "single_digits.txt");
    outputMappings(doubleDigits, "double_digits.txt");
    outputMappings(tripleDigits, "triple_digits.txt");
    outputMappings(quadDigits, "quad_digits.txt");
    return 0;
}