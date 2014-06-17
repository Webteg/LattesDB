/*
 * trienode.h
 *
 *  Created on: Jun 16, 2014
 *      Author: marcos
 */

#ifndef TRIENODE_H_
#define TRIENODE_H_
#include <map>
#include <iterator>
#include <cstdlib>
#include <vector>

namespace std {

class Trienode {
	map<char, Trienode*> children;
	unsigned long int item;
public:
	Trienode() {
		item = 0;
	}
	unsigned long int getItem() {
		return item;
	}
	void putItem(unsigned long int t) {
		item = t;
	}
	Trienode* getChild(char c) {
		map<char, Trienode*>::iterator it = children.find(c);
		if (it != children.end())
			return it->second;
		else
			return NULL;
	}

	vector<Trienode*> getChildren() {
		vector<Trienode*> ret;
		map<char, Trienode*>::iterator it = children.begin();
		while (it != children.end()) {
			ret.push_back(it->second);
			it++;
		}
		return ret;
	}

	vector<pair<char, Trienode*> > getEdges() {
		vector<pair<char, Trienode*> > ret;
		map<char, Trienode*>::iterator it = children.begin();
		while (it != children.end()) {
			ret.push_back(*it);
			it++;
		}
		return ret;
	}

	void putChild(char c, Trienode* node) {
		children[c] = node;
	}

	bool isLeaf() {
		return children.empty();
	}

	bool isEmpty() {
		return item == 0;
	}

	virtual ~Trienode() {

	}
};

} /* namespace std */

#endif /* TRIENODE_H_ */
