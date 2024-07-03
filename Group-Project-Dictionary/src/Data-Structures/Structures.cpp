#include<string>
#include<vector>
#include<iostream>
#include<math.h>
#include<algorithm>
#include "Static.h"
#include "Trie.h"
#include "Structures.h"
Word::Word(const std::string& str) {
	cnt = 0;
	data = str;
	isFavorite = 0;
}

Word::~Word() {
	std::cerr << "Deleted Word\n";
}

Definition::Definition(const std::string& str) {
	cnt = 0;
	data = str;
	word = nullptr;
}

Definition::~Definition() {
	std::cerr << "Deleted Definition\n";
}

Dict::Dict() {
	trieWord = new Trie<Word*>(PRINTABLE, nullptr);
	trieDef = new Trie<Word*>(PRINTABLE, nullptr);
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
				if (a[i - 1] == b[j - 1])
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
std::string normalize(const std::string& a) {
	std::string result = "";
	for (char x : a) {
		if (('a' <= x) && (x <= 'z'))
			result += x;
		if (('A' <= x) && (x <= 'Z'))
			result += char(x - 'A' + 'a');
		if (('0' <= x) && (x <= '9'))
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
		if ((int)listDef.size() == 10000)
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
		tmp = new Word(s);
		trieWord->insert(s, tmp);
	}
	allWords.push_back(tmp);
	return tmp;
}

void Dict::addWordAndDef(const std::string& w, const std::string& d) {
	Word* word = addWord(w);
	Definition* def = addDefinition(d);
	word->defs.push_back(def);
	def->word = word;
}