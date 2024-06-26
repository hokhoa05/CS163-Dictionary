#pragma once

struct Word;
struct Definition;
struct Word {
	bool isFavorite;
	std::string data;
	std::vector<Definition*> defs;
	Word(const std::string &str);
	~Word();
};

struct Definition {
	std::string data;
	Word *word;
	Definition(const std::string& str);
	~Definition();
};