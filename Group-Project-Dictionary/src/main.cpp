#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict(ENG_VIE_FILE);
	Definition* def = data->getRandomWord();
	std::cout << def->word->data << "\t" << def->data;
	delete data;
	//mainMenu();
	return 0;
}