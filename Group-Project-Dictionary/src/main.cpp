#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict(ENG_ENG_FILE);
	std::vector<Word*> result = data->searchWithDefinition("fruit");
	for (auto x : result)
		std::cout << x->data << '\n';
	delete data;
	//mainMenu();
	return 0;
}