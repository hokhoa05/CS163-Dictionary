#pragma once
#include "Trie.h"

struct Word;
struct Definition;
struct History;



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
* normalize("Kho  AD") -> "khoad" 
*/
bool isPrintable(char x);
/*
	return True if x is in PRINTABLE
	else return False
*/
struct Dict {
	Dict(const std::string& _dir);
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
	std::string dir; //direction to data folder
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
	void loadWordlistFromfile(const std::string& filename);
	/*
		load a wordlist to dictionary by filename
	*/

	struct History
	{
		std::vector<std::string>& wordlist;
		void saveWordListToFile(const std::string& HISTORY_FILE) const;
		void addWordToHistory(const std::string& word) const
		{
			wordlist.insert(wordlist.begin(), word);
		}
		void loadWordListFromFile(const std::string& HISTORY_FILE) const;
		void viewHistory(const std::string& HISTORY_FILE) const;
		void clearHistory() const
		{
			wordlist.clear();
		}
	}history;
	bool deleteDefinition(Definition* def);
	/*
		delete a definition
	*/
	bool deleteWord(Word* word);
	/*
		delete a word
	*/
	Definition* getRandomWord();
	/*
		return a random definition with a word.
	*/
	std::vector<Word*> searchByKey(const std::string& prefix) const;
	/*
		return 
	*/
	bool addFavorite(Word*& word);
	/*
		return true if add successfully, false if cannot open file
	*/

	bool editDefinition(Word* word, Definition* oldDef, const std::string& newDef);
	/*
		return true if edit successfully, false if not
	*/
	std::vector<std::string> viewFavorite();
	/*
		read all words in favorite list, push in a vector and return it
	*/
	bool deleteFavorite(Word*& word);
	/*
		read words in favorite list, check if it is the one to be deleted, change isFavorite and rewrite new list
	*/
	std::vector<std::string> defGuessWord(); 
	/*
		return a vector with 5 strings:
		first string is a definition
		second string is true word for the definition
		next 3 strings are wrong
	*/
	std::vector<std::string> wordGuessDef();
	/*
		return a vector with 5 strings:
		first string is a word
		second string is true definition for the word
		next 3 strings are wrong
	*/
	void resetDataFiles();
	/*
		call resetDataFiles() to reset all the data and reset the Data.txt from Backup.txt
	*/
	void saveData();
};
void resetData(Dict*& data);
/*
	call resetData(data) to reset the data
*/
struct History {
	History();
	~History();

	std::vector<Word*> wordlist;

	void saveWordListToFile(const std::string& HISTORY_FILE) const;
	void addWordToHistory(Word* word);
	void static loadWordListFromFile(const std::string& HISTORY_FILE);
	void clearHistory();

	
	void static overwriteFile(const std::string& sourceFilePath, const std::string& destFilePath);
};


