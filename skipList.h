#pragma once

#include <string>
#include <vector>

struct skipNode
{
	int key;
	std::vector<skipNode*> forward;

	skipNode(int k, int level);
};


class skipList
{
public:
	skipList();
	~skipList();

	void print();
	skipNode* find(int key);
	void insert(int key);
	skipNode* deleteNode(int key);

private:

	int maxLevel;

	skipNode* head;
	skipNode* tail;

	int randomLevel();
	int nodeLevel(const std::vector<skipNode*> p);
};