/*
 * trie.h
 *
 *  Created on: Jun 16, 2014
 *      Author: marcos
 */

#ifndef TRIE_H_
#define TRIE_H_
#include "trienode.h"
#include <vector>
#include <stack>
#include <fstream>
#include <utility>

using namespace std;

class Trie {
	Trienode *root;
	unsigned int size;
	static const int SIZE_ULINT = sizeof(unsigned long int);
	static const int SIZE_UINT = sizeof(unsigned int);
public:
	Trie() {
		root = new Trienode();
		size = 0;
	}
	void insert(string key, unsigned long int t) {
		unsigned int k = 0;
		Trienode *x = root;
		while (!x->isLeaf() && k < key.size()) {
			char c = key[k++];
			Trienode* y = x->getChild(c);
			if (y == NULL) {
				y = new Trienode();
				x->putChild(c, y);
			}
			x = y;
		}
		while (k < key.size()) {
			Trienode* y = new Trienode();
			x->putChild(key[k++], y);
			x = y;
		}
		if (x->isEmpty()) {
			x->putItem(t);
			size++;
		}
	}

	unsigned long int get(string key) {
		unsigned int i = 0;
		Trienode* x = root;
		while (i < key.size()) {
			x = x->getChild(key[i++]);
			if (x == NULL) {
				return 0;
			}
		}
		return x->getItem();
	}

	vector<unsigned long int> getPrefix(string key) {
		vector<unsigned long int> v;
		unsigned int i = 0;
		Trienode* x = root;
		while (i < key.size()) {
			if (x == NULL) {
				return v;
			}
			x = x->getChild(key[i++]);
		}
		if (x == NULL) {
			return v;
		}
		stack<Trienode*> s;
		s.push(x);
		while (!s.empty()) {
			x = s.top();
			s.pop();
			if (!x->isEmpty()) {
				v.push_back(x->getItem());
			}
			vector<Trienode*> nodes = x->getChildren();
			for (unsigned int i = 0; i < nodes.size(); i++) {
				s.push(nodes[i]);
			}
		}
		return v;
	}

	void write(string file_name) {
		fstream file(file_name.c_str(), ios::out | ios::binary);
		file.write((char*) &size, sizeof(size));
		stack<pair<string, Trienode*> > s;
		s.push(make_pair("", root));
		while (!s.empty()) {
			pair<string, Trienode*> p = s.top();
			Trienode* x = p.second;
			string key = p.first;
			s.pop();
			if (!x->isEmpty()) {
				unsigned int str_size = key.size();
				unsigned long int item = x->getItem();
				file.write((char*) &item, sizeof(item));
				file.write((char*) &str_size, sizeof(str_size));
				file.write(key.c_str(), key.size());
			}
			vector<pair<char, Trienode*> > edges = x->getEdges();
			for (unsigned int i = 0; i < edges.size(); i++) {
				s.push(make_pair(key + edges[i].first, edges[i].second));
			}
		}
		file.close();
	}

	void read(string file_name) {
		fstream file(file_name.c_str(), ios::in | ios::binary);
		if (file.is_open()) {
			unsigned int file_size;
			char buffer[512];
			file.read((char*) &file_size, sizeof(file_size));
			for (unsigned int i = 0; i < file_size; i++) {
				unsigned long int item;
				unsigned int str_size;
				file.read((char*) &item, sizeof(item));
				file.read((char*) &str_size, sizeof(str_size));
				file.read(buffer, str_size);
				buffer[str_size] = '\0';
				string key = string(buffer);
				insert(key, item);
			}
		}
		file.close();
	}

	virtual ~Trie() {
		stack<Trienode*> s;
		Trienode* x = root;
		s.push(x);
		while (!s.empty()) {
			x = s.top();
			s.pop();
			vector<Trienode*> nodes = x->getChildren();
			delete x;
			for (unsigned int i = 0; i < nodes.size(); i++) {
				s.push(nodes[i]);
			}
		}
	}
};

#endif /* TRIE_H_ */
