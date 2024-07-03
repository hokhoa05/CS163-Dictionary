#include<string>
#include<vector>
#include<iostream>
#include "Structures.h"
Word::Word(const std::string& str) {
	data = str;
}

Word::~Word() {
	std::cerr << "Deleted Word\n";
}

Definition::Definition(const std::string& str) {
	data = str;
}

Definition::~Definition() {
	delete word;
	word = nullptr;
	std::cerr << "Deleted Definition\n";
}

void loadWordsToTrie(const std::string& filename, Trie<Word*>*& trie) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Cannot open: " << filename << '\n';
        return;
    }

    std::string line;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string wordName; // Declare new word
        iss >> wordName;
        Word* word = new Word(wordName); 

        std::string definitionName; //Declare new definition
        Definition* definitions;
        while (iss >> definitionName) {
            definitions = new Definition(definitionName); 
            word->defs.push_back(definitions);
        }
        trie->insert(word->data, word); // Insert word to trie
    }
    infile.close();
}