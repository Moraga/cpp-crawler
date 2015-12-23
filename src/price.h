#include <iostream>
#include "node.h"

struct Price {
	float value;
	TextNode* textNode;
	std::string* nodeName;
	float rank = 1;
	int proximity = 0;
	int installments = 0;
	int siblings = 0;
	int repetitions = 0;
	Price(float, TextNode*);
	int distance(Price*);
	bool different(Price*);
	void print();
};
