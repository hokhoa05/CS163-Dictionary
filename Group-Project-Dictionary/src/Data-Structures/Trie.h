#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<queue>

#include "Static.h";
enum Trie_State {
	success,
	non_exist,
	invalid_charater,
	duplicated
};
// Node of Trie, a Node has a data and branch to another nodes in Trie.
template<class DataType>
struct TrieNode {
	DataType data;
	std::vector<TrieNode<DataType>*> pNext;
	TrieNode(const int &numNext, const DataType &data);
	~TrieNode();
};

// Trie
template<class DataType>
struct Trie {

	int alphaID[256];//ID of the charater using in trie
	
	int numNext; //Number of branch of each node


	DataType defaultData;	
	/*
		A default data for the type of data that we use in Trie
		If we use a pointer type this should be nullptr
		If we use integer this should be 0
	*/
	
	TrieNode<DataType>* root; //Root node of Trie

	Trie(const std::string& str, const DataType& _defaultData);
	/*
		Constructor
		Initialize Trie: Trie<DataType> trie;
		example: Trie<Word*> *trie;
		trie = new Trie(A string of characters use in trie, nullptr);
		defaultData = nullptr because we use pointer of Word*
	*/
	
	~Trie(); // destructor, use for delete


	Trie_State insert(const std::string& str, const DataType& data);
	/*
		Insert a string into trie, if trie already has exactly the same string before,
		then it will return duplicated
		If insert success it will return success
		else it will return invalid charater.
	*/

	Trie_State find(const std::string& str, DataType& data);
	/*
		Find a string str in trie
		Return success if there is str in trie, assign the data of the string in the trie into data.
		else return non_exist
	*/

	Trie_State remove(const std::string& str);
	/*
		Delete a string str in trie
		Return success if there is str in trie, assign the default data into the data inside the trie. (nullptr)
		else return non_exist
	*/

	void bfs(TrieNode<DataType>* cur, std::vector<DataType>& result, int searchNumber);
	/*
		bfs for searchByKey function.
	*/

	std::vector<DataType> searchByKey(const std::string& str);
	/*
		Using bfs to search, SEARCH_LIMIT is up to 30 strings.
		Search by a prefix str of some string in the trie.
		If exist, return vector has data of the string having prefix str in the trie.
		else return empty vector
	*/

	void deallocate(TrieNode<DataType>*& cur);
	/*
		use for delete entire trie after using.
	*/
};

template<class DataType>
void Trie<DataType>::bfs(TrieNode<DataType>* cur, std::vector<DataType>& result, int searchNumber) {
	std::queue<TrieNode<DataType>*> q;
	q.push(cur);
	while (!q.empty()) {
		TrieNode<DataType>* u = q.front();
		q.pop();
		if (searchNumber == 0)
			continue;
		if (u->data != defaultData) {
			result.push_back(u->data);
			--searchNumber;
		}
		for (int i = 0; i < numNext; i++) if(u->pNext[i] != nullptr) {
			q.push(u->pNext[i]);
		}
	}
}
template<class DataType>
std::vector<DataType> Trie<DataType>::searchByKey(const std::string& str) {
	TrieNode<DataType>* cur = root;
	for (char c : str) {
		int nxt = alphaID[int(c)];
		if (nxt == -1)
			return std::vector<DataType>();
		if (cur->pNext[nxt] == nullptr)
			return std::vector<DataType>();
		cur = cur->pNext[nxt];
	}
	std::vector<DataType> result;
	int searchNumber = SEARCH_LIMIT;
	bfs(cur, result, searchNumber);
	return result;
}

template<class DataType>
TrieNode<DataType>::TrieNode(const int &numNext, const DataType &data) {
	this->data = data;
	this->pNext.resize(numNext);
	for (int i = 0; i < numNext; i++) {
		this->pNext[i] = nullptr;
	}
}

template<class DataType>
TrieNode<DataType>::~TrieNode() {
	std::cerr << "Deleted TrieNode\n";
}

template <class DataType>
Trie<DataType>::Trie(const std::string& str, const DataType& _defaultData)
{
	numNext = (int)str.size();
	memset(alphaID, -1, sizeof(alphaID));
	for (int i = 0; i < numNext; ++i) {
		alphaID[int(str[i])] = i;
	}
	defaultData = _defaultData;
	root = new TrieNode<DataType>(numNext, defaultData);
}

template<class DataType>
Trie<DataType>::~Trie() {
	deallocate(root);
	std::cerr << "Deleted Trie\n";
}

template<class DataType>
void Trie<DataType>::deallocate(TrieNode<DataType>*& cur) {
	if (cur == nullptr)
		return;
	for (int i = 0; i < numNext; i++)
		deallocate(cur->pNext[i]);
	delete cur;
	cur = nullptr;
}

template<class DataType>
Trie_State Trie<DataType>::insert(const std::string& str, const DataType& data) {
	TrieNode<DataType>* cur = root;
	for (char c : str) {
		int nxt = alphaID[int(c)];
		if (nxt == -1) {
			return invalid_charater;
		}
		if (cur->pNext[nxt] == nullptr) {
			cur->pNext[nxt] = new TrieNode<DataType>(numNext, defaultData);
		}
		cur = cur->pNext[nxt];
	}
	if (cur->data == defaultData) {
		cur->data = data;
		return success;
	}
	return duplicated;
}

template<class DataType>
Trie_State Trie<DataType>::find(const std::string& str, DataType& data) {
	TrieNode<DataType>* cur = root;
	for (char c : str) {
		int nxt = alphaID[int(c)];
		if (nxt == -1) {
			return non_exist;
		}
		if (cur->pNext[nxt] == nullptr) {
			return non_exist;
		}
		cur = cur->pNext[nxt];
	}
	if (cur->data == defaultData)
		return non_exist;

	data = cur->data;
	return success;
}

template<class DataType>
Trie_State Trie<DataType>::remove(const std::string& str) {
	TrieNode<DataType>* cur = root;
	for (char c : str) {
		int nxt = alphaID[int(c)];
		if (nxt == -1) {
			return non_exist;
		}
		if (cur->pNext[nxt] == nullptr) {
			return non_exist;
		}
		cur = cur->pNext[nxt];
	}
	if (cur->data == defaultData)
		return non_exist;

	cur->data = defaultData;
	return success;
}