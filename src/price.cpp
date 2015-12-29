#include "price.h"

Price::Price(float value, std::string match, TextNode* textNode) {
	this->value = value;
	this->match = match;
	this->textNode = textNode;
};

Price::Price(Price& price) {
	value = price.value;
	match = price.match;
	textNode = price.textNode;
};

const std::string& Price::nodeName() {
	return textNode->parentNode->nodeName;
};

std::string Price::content() {
	return textNode->parentNode->content(match.length() * 1.5);
};

int Price::distance(Price* other) {
	return textNode->parentNode->proximity(other->textNode->parentNode);
};

bool Price::different(Price* other) {
	return true;
};

void Price::print() {

};
