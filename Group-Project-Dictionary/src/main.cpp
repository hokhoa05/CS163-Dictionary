#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict(EMOJI_FILE);
	data->history.addWordToHistory()
	mainMenu(data);
	delete data;
	return 0;
}