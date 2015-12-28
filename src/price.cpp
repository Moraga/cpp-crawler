#include "price.h"

Price::Price(float value, std::string match, TextNode* textNode) {
	this->value = value;
	this->match = match;
	this->textNode = textNode;
	nodeName = &textNode->parentNode->nodeName;
};

std::string Price::content() {
	return textNode->content(match.length() * 1.5);
};

int Price::distance(Price* other) {
	return textNode->parentNode->proximity(other->textNode->parentNode);
};

bool Price::different(Price* other) {
	return true;
};

void Price::print() {

};
