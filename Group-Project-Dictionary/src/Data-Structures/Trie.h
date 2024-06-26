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
template<class DataType>
struct TrieNode {
	DataType data;
	std::vector<TrieNode<DataType>*> pNext;
	TrieNode(const int &numNext, const DataType &data);
	~TrieNode();
};

template<class DataType>
struct Trie {
	int alphaID[256];
	int numNext;
	DataType defaultData;
	TrieNode<DataType>* root;
	Trie(const std::string& str, const DataType& _defaultData);
	~Trie();

	Trie_State insert(const std::string& str, const DataType& data);
	Trie_State find(const std::string& str, DataType& data);
	Trie_State remove(const std::string& str);

	void bfs(TrieNode<DataType>* cur, std::vector<DataType>& result, int searchNumber);
	std::vector<DataType> searchByKey(const std::string& str);
	void deallocate(TrieNode<DataType>*& cur);
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