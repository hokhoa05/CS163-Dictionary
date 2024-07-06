#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"


int main() {
	Dict* data = new Dict();
	std::string filename = ENG_ENG_FILE;
	data->loadWordlistFromfile(filename);
	std::vector <Word*> search = data->searchWithDefinition("in the act of");
	std::string hisfile = "his.txt";
	data->hiswords->saveWordlistIntoFile(hisfile, search);
	data->hiswords->loadWordfromfile(hisfile);
	delete data;
	return 0;
}