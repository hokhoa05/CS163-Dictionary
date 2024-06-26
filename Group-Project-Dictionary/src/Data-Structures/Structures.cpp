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