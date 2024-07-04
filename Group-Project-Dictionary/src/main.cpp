#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict();
	data->addWordAndDef("love", "To make an emotion to someone");
	data->addWordAndDef("eating", "To eat something");
	data->addWordAndDef("apple", "A red fruit to eat");

	std::vector<Word*> v = data->searchWithDefinition("A red fruit to eat");
	for (auto s : v)
		std::cout << s->data << '\n';
	delete data;
	mainMenu();
	return 0;
}