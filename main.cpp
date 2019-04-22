#include <iostream>
#include <sstream>
#include "skipList.h";

using namespace std;

int main()
{
	skipList l;

	for (size_t i = 0; i < 50; i++)
	{
		l.insert(i);
	}

	l.print();
}