#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
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

// given a file of words, return a vector of words and mapping pairs
std::vector<std::pair<std::string, std::string>> mapAllWords(std::string fileName, std::map<char, char>& letterMap) {
    std::vector<std::pair<std::string, std::string>> wordMap;
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
        else {
            wordMap.push_back(std::make_pair(word, mappedWord));
        }
    }
    return wordMap;
}

std::map<std::string, std::vector<std::string>> organizeMappings(std::vector<std::pair<std::string, std::string>>& wordMap) {
    std::map<std::string, std::vector<std::string>> mappingMap;
    for (auto& word : wordMap) {
        // if the mapped word is already in the map, add the word to the vector
        if (mappingMap.find(word.second) != mappingMap.end()) {
            mappingMap.find(word.second)->second.push_back(word.first);
        }
        // if the mapped word is not in the map, add the word to the map and create a vector with the word
        else {
            mappingMap.insert(std::make_pair(word.second, std::vector<std::string>{word.first}));
        }
    }
    return mappingMap;
}

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
        for (auto& word : mapping.second) {
            std::cout << word << std::right << " " << std::setw(4);
        }
        std::cout << std::endl;
    }
}

void outputMappings(std::map<std::string, std::vector<std::string>>& mappingMap, std::string fileName) {
    std::ofstream file(fileName);
    for (auto& mapping : mappingMap) {
        file << mapping.first << ": ";
        for (auto& word : mapping.second) {
            file << word << std::right << " " << std::setw(4);
        }
        file << std::endl;
    }
}


int main() {
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
    std::vector<std::pair<std::string, std::string>> wordMap = mapAllWords("all_words.txt", letterMap);
    std::map<std::string, std::vector<std::string>> mappingMap = organizeMappings(wordMap);
    std::map<std::string, std::vector<std::string>> singleDigits = getFromKeySize(mappingMap, 1);
    std::map<std::string, std::vector<std::string>> doubleDigits = getFromKeySize(mappingMap, 2);
    std::map<std::string, std::vector<std::string>> tripleDigits = getFromKeySize(mappingMap, 3);
    std::map<std::string, std::vector<std::string>> quadDigits = getFromKeySize(mappingMap, 4);
    //printMappingMap(singleDigits);
    //printMappingMap(doubleDigits);
    printMappingMap(tripleDigits);
    //printMappingMap(quadDigits);
    return 0;
}