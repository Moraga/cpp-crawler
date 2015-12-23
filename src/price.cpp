#include "price.h"

Price::Price(float value, TextNode* textNode) {
	this->value = value;
	this->textNode = textNode;
	nodeName = &textNode->parentNode->nodeName;
};

int Price::distance(Price* other) {
	return textNode->parentNode->proximity(other->textNode->parentNode);
};

bool Price::different(Price* other) {
	return true;
};

void Price::print() {

};
