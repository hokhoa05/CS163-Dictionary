#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict("../data/eng-vie/Data.txt");
	std::vector<Word*> search = data->searchWithDefinition("mot cach phi chinh tri");
	for (auto x : search) {
		std::cout << x->data << "\n";
	}
	delete data;
	mainMenu();
	return 0;
}