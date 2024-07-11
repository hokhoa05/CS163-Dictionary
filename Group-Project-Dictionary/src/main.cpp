#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict(EMOJI_FILE);
	//Definition* def = data->getRandomWord();
	//std::cout << def->word->data << "\t" << def->data;
	mainMenu(data);
	delete data;
	return 0;
}