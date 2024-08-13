#include<iostream>
#include<string>
#include<vector>
#include "Data-Structures/Static.h"
#include "Data-Structures/Structures.h"
#include "Data-Structures/Trie.h"
#include "UI/menu.h"

int main() {
	Dict* data = new Dict(EMOJI_FILE);

	data->hiswords->saveWordListToFile(HISTORY_FILE);
	data->hiswords->clearHistory();
	delete data;
	return 0;
}