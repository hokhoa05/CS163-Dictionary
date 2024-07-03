#pragma once
#include <fstream>
#include <sstream>
#include "Trie.h"

struct Word;
struct Definition;

void loadWordsToTrie(const std::string& filename, Trie<Word*>*& trie);



struct Word {
	bool isFavorite; //Check if Word is in favorite list
	std::string data; //The word
	std::vector<Definition*> defs; 
	/*
		Definitions of the word, a word can be linked to several of definitions.
		Using pointer.
	*/
	
	Word(const std::string &str); // Constructor
	~Word(); // Destructor
};

struct Definition {
	std::string data; //The definition
	Word *word;
	/*
		A definition is linked to a word.
		Using pointer.
	*/
	Definition(const std::string& str); // Constructor
	~Definition(); // Destructor
};