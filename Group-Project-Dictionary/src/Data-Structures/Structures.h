#pragma once
#include "Trie.h"
struct Word;
struct Definition;
struct Word {
	double cnt;
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
	double cnt;
	std::string data; //The definition
	Word *word;
	/*
		A definition is linked to a word.
		Using pointer.
	*/
	Definition(const std::string& str); // Constructor
	~Definition(); // Destructor
};

int editDistance(const std::string& a, const std::string& b); //dp edit distance
std::vector<std::string> split(const std::string& a, const char& key); 
/*
	split string a by charater key into pieces
	return vector<string>
	example: 
	split("Ho Nguyen Dang Khoa", ' ') -> vector<string>{"Ho", "Nguyen", "Dang", "Khoa"} 
*/
std::string normalize(const std::string& a); //
/*
* return a normalized string of a (use lowercase latin characters and numbers)
* example:
* normalize("Kho*&AD") -> "khoad"
*/
struct Dict {
	Dict();
	~Dict();
	Trie<Word*>* trieDef = nullptr;
	/*
		Trie of words create definition
	*/
	Trie<Word*>* trieWord = nullptr;
	/*
		Trie of words
	*/
	std::vector<Definition*> allDefs;
	/*
		vector of all of definition
	*/
	std::vector<Word*> allWords;
	/*
		vector of all of words
	*/
	Definition* addDefinition(const std::string &d);
	/*
		add a definition into Dictionary and words create definition into trie
		return a *definition
	*/
	Word* addWord(const std::string &w);
	/*
		add a word into Dictionary and trie
		return a *word
	*/
	void addWordAndDef(const std::string& w, const std::string& d);
	/*
		add a word with a definition into Dictionary
		(use addDefinition and addWord to add)
	*/
	std::vector<Word*> searchWithDefinition(const std::string &def);
	/*
		return vector<Word*> have definition def
	*/
};