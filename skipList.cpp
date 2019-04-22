#include <iostream>
#include "skiplist.h"
#include <random>
#include <time.h>

using namespace std;

skipNode::skipNode(int k, int level): key(k)
{
	for (int i = 0; i < level; ++i)
	{
		forward.emplace_back(nullptr);
	}
}

skipList::skipList():maxLevel(6)
{
	constexpr int min = numeric_limits<int>::min();
	head = new skipNode(min, maxLevel);

	constexpr int max = numeric_limits<int>::max();
	tail = new skipNode(max, maxLevel);

	for (size_t i = 0; i < head->forward.size(); ++i)
	{
		head->forward[i] = tail;
	}
}

skipList::~skipList() {
	delete head;
	delete tail;
}

int skipList::randomLevel()
{
	int level = 1;
	time_t seed = time(NULL);
	static default_random_engine e(seed);
	static uniform_int_distribution<int> u(0, 1);
	while (u(e) && level < maxLevel)
	{
		level++;
	}
	return level;
}

int skipList::nodeLevel(const std::vector<skipNode*> p) 
{
	int nlevel = 1;
	constexpr int max = numeric_limits<int>::max();

	if (p[0]->key == max)
	{
		return nlevel;
	}

	for (size_t i = 0; i < p.size(); i++)
	{
		if (p[i] != nullptr && p[i]->key != max) 
		{
			++nlevel;
		}
		else
		{
			break;
		}
	}

	return nlevel; 
}

void skipList::print()
{
	skipNode* tmp = head;
	int lineLen = 1; 

	cout << "{";

	while (tmp->forward[0] != nullptr)
	{
		cout << "Key: " << tmp->forward[0]->key
			 << ", Level: " << nodeLevel(tmp->forward);

		tmp = tmp->forward[0];

		if (tmp->forward[0] != nullptr) cout << ":";

		if (++lineLen % 2 == 0) cout << "\n";
	}

	cout << "}\n";
}

skipNode* skipList::find(int key) 
{
	skipNode* x = head;
	int nLevel = nodeLevel(head->forward);

	for (size_t i = nLevel; i-- > 0;)
	{
		while (x->forward[i] != nullptr && x->forward[i]->key < key)
		{
			x = x->forward[i];
		}
	}
	x = x->forward[0];

	if (x->key == key)
	{
		return x;
	}
	else
	{
		return nullptr;
	}
}

void skipList::insert(int key)
{
	skipNode* x = nullptr;
	x = find(key);
	if (x)
	{
		return;
	}

	vector<skipNode*> update(head->forward);
	int nLevel = nodeLevel(head->forward);
	x = head;

	for (int i = nLevel; i-- > 0;)
	{
		while (x->forward[i] != nullptr && x->forward[i]->key < key)
		{
			x = x->forward[i];
		}
		update[i] = x;
	}
	x = x->forward[0];

	int newNodeLevel = 1; 
	if (x->key != key) 
	{
		newNodeLevel = randomLevel();
		int nLevel = nodeLevel(update);

		if (newNodeLevel > nLevel) {
			for (int i = nLevel + 1; i < newNodeLevel; i++)
			{
				update[i] = head;
			}
		}
		x = new skipNode(key, newNodeLevel);
	}

	for (size_t i = 0; i < newNodeLevel; ++i)
	{
		x->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = x;
	}
}
