#include<string>
#include<utility>
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<chrono>
#include<random>

#include "Static.h"
#include "Trie.h"
#include "Structures.h"

Word::Word(const std::string& str) {
	cnt = 0;
	data = str;
	isFavorite = 0;
}

Word::~Word() {
	//std::cerr << "Deleted Word\n";
}

Definition::Definition(const std::string& str) {
	cnt = 0;
	data = str;
	word = nullptr;
}

Definition::~Definition() {
	//std::cerr << "Deleted Definition\n";
}


Dict::Dict(const std::string &dir) {
	trieWord = new Trie<Word*>(PRINTABLE, nullptr);
	trieDef = new Trie<Word*>(PRINTABLE, nullptr);
	loadWordlistFromfile(dir);
	hiswords = new History();
}
Dict::~Dict() {
	trieDef->clear();
	trieWord->clear();
	for (auto def : allDefs)
	{
		delete def;
		def = nullptr;
	}
	allWords.clear();
	allDefs.clear();
	delete trieWord;
	trieWord = nullptr;
	delete trieDef;
	trieDef = nullptr;
	delete hiswords;
	hiswords = nullptr;
}

int editDistance(const std::string& a, const std::string& b) {
	int n = (int)a.size();
	int m = (int)b.size();
	std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0)
				dp[i][j] = j;
			if (j == 0)
				dp[i][j] = i;
			if ((i != 0) && (j != 0)) {
				if (tolower(a[i - 1]) == tolower(b[j - 1]))
					dp[i][j] = dp[i - 1][j - 1];
				else
					dp[i][j] = std::min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }) + 1;
			}
		}
	}
	return dp[n][m];
}

std::vector<std::string> split(const std::string& a, const char& key) {
	std::vector<std::string> result;
	std::string tmp = "";
	int i = 0;
	while ((i < (int)a.size()) && (a[i] == key))
		++i;
	for (; i < (int)a.size(); i++) {
		if (a[i] == key) {
			result.push_back(tmp);
			tmp = "";
		}
		else {
			tmp += a[i];
		}
	}
	if (tmp != "")
		result.push_back(tmp);
	return result;
}
bool isPrintable(char x) {
	bool ok = 0;
	for (char c : PRINTABLE) {
		ok |= (c == x);
	}
	return ok;
}
std::string normalize(const std::string& a) {
	std::string result = "";
	for (char x : a) {
		if (x == ' ') continue;
		if (('a' <= x) && (x <= 'z'))
			result += x;
		else if (('A' <= x) && (x <= 'Z'))
			result += char(x - 'A' + 'a');
		else if (isPrintable(x))
			result += x;
	}
	return result;
}
std::vector<Word*> Dict::searchWithDefinition(const std::string& def) {
	for (auto s : split(def, ' ')) {
		s = normalize(s);
		Word* tmp = nullptr;
		if (trieDef->find(s, tmp) == success) {
			tmp->cnt += 1;
		}
		else {
			tmp = new Word(s);
			tmp->cnt = 1;
			trieDef->insert(s, tmp);
		}
	}
	trieDef->calc();
	std::sort(allDefs.begin(), allDefs.end(), [](auto a, auto b) {
		return (a->cnt > b->cnt);
	});
	std::vector<Definition*> listDef;
	std::vector<Word*> result;
	for (Definition* d : allDefs) {
		if (d->cnt > 0) {
			listDef.push_back(d);
			d->cnt = ((double)(d->data.size()) - (double)editDistance(def, d->data))/(double)(d->data.size());
		}
		if ((int)listDef.size() == 100)
			break;
	}
	std::sort(listDef.begin(), listDef.end(), [](auto a, auto b) {
		return (a->cnt > b->cnt);
	});
	for (Definition* d : listDef) {
		bool notFound = 1;
		for (Word* w : result) if (w == d->word) {
			notFound = 0;
			break;
		}
		if (notFound) {
			result.push_back(d->word);
		}
		if ((int)result.size() == SEARCH_LIMIT)
			break;
	}
	trieDef->resetCnt();
	for (auto d : allDefs)
		d->cnt = 0;
	return result;
}

Definition* Dict::addDefinition(const std::string& d) {
	Definition* tmp = new Definition(d);
	for (std::string x : split(d, ' ')) {
		x = normalize(x);
		if ((int)x.size() < 3)
			continue;
		Word* tmp1 = nullptr;
		if (trieDef->find(x, tmp1) != success) {
			tmp1 = new Word(x);
			trieDef->insert(x, tmp1);
		}
		tmp1->defs.push_back(tmp);
	}
	allDefs.push_back(tmp);
	return tmp;
}

Word* Dict::addWord(const std::string& w) {
	std::string s = normalize(w);
	Word* tmp = nullptr;
	if (trieWord->find(s, tmp) != success) {
		tmp = new Word(w);
		trieWord->insert(s, tmp);
		allWords.push_back(tmp);
	}
	return tmp;
}

void Dict::addWordAndDef(const std::string& w, const std::string& d) {
	Word* word = addWord(w);
	Definition* def = addDefinition(d);
	word->defs.push_back(def);
	def->word = word;
}
void Dict:: loadWordlistFromfile(const std::string& filename) {
	std::ifstream infile(filename);
	if (!infile.is_open()) {
		std::cerr << "Cannot open: " << filename << '\n';
		return;
	}

	std::string line;
	while (std::getline(infile, line)) {
		std::vector<std::string> str = split(line, '\t');
		if ((int)str.size() < 2)
			continue;
		addWordAndDef(str[0], str[1]);
	}
	infile.close();
}

History::History() {}

History::~History() {
	for (auto word : wordlist) {
		delete word;
	}
}

void History::saveWordlistIntoFile(const std::string& hisfile, std::vector<Word*> search) {
	std::ofstream outfile(hisfile);
	if (!outfile.is_open()) {
		std::cerr << "Cannot open" << hisfile << '\n';
		return;
	}

	for (auto word : search) {
		outfile << word->data;
		for (auto def : word->defs) {
			outfile << '\t' << def->data;
		}
	}

	std::cout << "Saving word into file successfully" << '\n';
	outfile.close();
}

void History::loadWordfromfile(const std::string& hisfile) {
	std::ifstream infile(hisfile);
	if (!infile.is_open()) {
		std::cerr << "Cannot open" << hisfile << '\n';
		return;
	}

	std::string line;
	while (getline(infile, line)) {
		std::istringstream iss(line);
		std::string wordData;
		iss >> wordData;
		Word* newWord = new Word(wordData);

		std::string defData;
		while (iss >> defData) {
			Definition* newDef = new Definition(defData);
			newWord->defs.push_back(newDef);
		}
		this->wordlist.push_back(newWord);
	}

	std::cout << "Loading wordlist from file successfully" << '\n';
	infile.close();
}

bool Dict::deleteDefinition(Definition* def) {
	std::string str = def->data;
	for (std::string x : split(str, ' ')) {
		x = normalize(x);
		if ((int)x.size() < 3)
			continue;
		Word* tmp = nullptr;
		if (trieDef->find(x, tmp) == non_exist) {
			std::cerr << "Error: definition is not exist\n";
			return false;
		}
		if (std::find(tmp->defs.begin(), tmp->defs.end(), def) == tmp->defs.end()) {
			std::cerr << "Error: cannot find definition having the word\n";
			return false;
		}
		tmp->defs.erase(std::find(tmp->defs.begin(), tmp->defs.end(), def));
	}
	def->word->defs.erase(std::find(def->word->defs.begin(), def->word->defs.end(), def));
	allDefs.erase(std::find(allDefs.begin(), allDefs.end(), def));
	delete def;
	def = nullptr;
	return true;
}
bool Dict::deleteWord(Word *word) {
	while (!word->defs.empty()) {
		deleteDefinition(word->defs.back());
	}
	if (std::find(allWords.begin(), allWords.end(), word) == allWords.end()) {
		std::cerr << "Error: Find word in allWords (deleteWord)";
		return false;
	}
	allWords.erase(std::find(allWords.begin(), allWords.end(), word));
	if (trieWord->remove(word->data) != success) {
		std::cerr << "Error: Delete word trie\n";
		return false;
	}
	if (std::find(hiswords->wordlist.begin(), hiswords->wordlist.end(), word) != hiswords->wordlist.end()) {
		hiswords->wordlist.erase(std::find(hiswords->wordlist.begin(), hiswords->wordlist.end(), word));
	}
	delete word;
	word = nullptr;
	return true;
}
Definition* Dict::getRandomWord() {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	Word* word = allWords[std::uniform_int_distribution<int>(0, (int)allWords.size()-1)(rng)];
	Definition* def = word->defs[std::uniform_int_distribution<int>(0, (int)word->defs.size() - 1)(rng)];
	return def;
}
std::vector<Word*> Dict::searchByKey(const std::string& prefix) const {
	std::string x = normalize(prefix);
	std::vector<Word*> results = trieWord->searchByKey(x);
	return results;
}
bool Dict::addFavorite(Word *&word, const std::string& FAVORITE_FILE) {
	std::ofstream outfile(FAVORITE_FILE, std::ios::app); // Open in append mode

	if (!outfile.is_open()) {
		return false;
	}
	if (word->isFavorite == 0) {
		outfile << word->data << '\n';  // Add the word and a newline
		word->isFavorite = true;
		outfile.close();
		return true;
	}
	return false;
}
vector<string> Dict::viewFavorite(const std::string& FAVORITE_FILE) {
	vector<string> fav;
	std::ifstream infile(FAVORITE_FILE);

	if (!infile.is_open()) return fav;
	string temp;
	while (!infile.eof()) {
		getline(infile, temp, '\n');
		fav.push_back(temp);
	}
	infile.close();
	return fav;
}
bool Dict::deleteFavorite(Word*& word, const std::string& FAVORITE_FILE) {
	std::ifstream infile(FAVORITE_FILE);
	string temp;
	vector<string> fav;

	if (!infile.is_open()) return false;

	while (!infile.eof()) {
		getline(infile, temp, '\n');
		if (temp == word->data) {
			word->isFavorite = 0;
		}
		else fav.push_back(temp);
	}
	infile.close();

	std::ofstream outfile(FAVORITE_FILE);
	if (!outfile.is_open()) return false;
	for (string x : fav) {
		outfile << x << endl;
	}
	outfile.close();
	return true;

}
bool Dict::editDefinition(Word* word, Definition* oldDef, const std::string& newDef) {
	if (!deleteDefinition(oldDef)) {
		return false;
	}

	Definition* newDefObj = addDefinition(newDef);
	word->defs.push_back(newDefObj);
	newDefObj->word = word;
	return true;
}

std::vector<std::string> Dict::defGuessWord() {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::vector<std::string> res;
	Word* w = allWords[std::uniform_int_distribution<int>(0, (int)allWords.size() - 1)(rng)];
	Definition* def = w->defs[std::uniform_int_distribution<int>(0, (int)w->defs.size() - 1)(rng)];
	res.push_back(def->data);
	res.push_back(w->data);
	for (int i = 0; i < 3; i++) {
		w = allWords[std::uniform_int_distribution<int>(0, (int)allWords.size() - 1)(rng)];
		bool ok = 1;
		for (auto d : w->defs) if (d == def) {
			ok = 0;
			break;
		}
		if (!ok) {
			i--;
			continue;
		}
		res.push_back(w->data);
	}
	return res;
}

std::vector<std::string> Dict::wordGuessDef() {
	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::vector<std::string> res;
	Word* w = allWords[std::uniform_int_distribution<int>(0, (int)allWords.size() - 1)(rng)];
	Definition* def = w->defs[std::uniform_int_distribution<int>(0, (int)w->defs.size() - 1)(rng)];
	res.push_back(w->data);
	res.push_back(def->data);
	for (int i = 0; i < 3; i++) {
		def = allDefs[std::uniform_int_distribution<int>(0, (int)allDefs.size() - 1)(rng)];
		if (def->word == w) {
			i--;
			continue;
		}
		res.push_back(def->data);
	}
	return res;
}
