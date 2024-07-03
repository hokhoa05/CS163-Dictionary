#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Word* s1 = new Word("abcdef");
	Word* s2 = new Word("abc");
	Word* s3 = new Word("afg");
	Trie<Word*>* trie = new Trie<Word*>(PRINTABLE, nullptr);
	trie->insert(s1->data, s1);
	trie->insert(s2->data, s2);
	trie->insert(s3->data, s3);
	std::vector<Word*> result = trie->searchByKey("abcd");
	for (Word* x : result) {
		std::cout << x->data << '\n';
	}
	delete s1;
	s1 = nullptr;
	delete s2;
	s2 = nullptr;
	delete s3;
	s3 = nullptr;
	delete trie;
	mainMenu();
	return 0;
}