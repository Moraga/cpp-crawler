#include "node.h"

Node::~Node() {};

void Node::appendChild(Node& node) {
	node.parentNode = this;
	childNodes.push_back(&node);
};

Attribute::Attribute(std::string name, std::string value) {
	this->name = name;
	this->value = value;
};

TextNode::TextNode(std::string value) {
	this->value = value;
};

std::string ElementNode::unique[] = {
		"area", "base", "col", "command", "embed", "hr", "img", "input",
		"keygen", "link", "meta", "param", "source", "track", "wbr"
};

std::string ElementNode::ignore[] = {"script", "style"};

ElementNode::ElementNode(std::string nodeName) {
	this->nodeName = nodeName;
};

void ElementNode::setAttribute(std::string name, std::string value) {
	Attribute* attribute = new Attribute(name, value);
	attributes.push_back(attribute);
	trash.push_back(attribute);
};

ElementNode* ElementNode::createNode(std::string nodeName) {
	ElementNode* node = new ElementNode(nodeName);
	trash.push_back(node);
	appendChild(*node);
	return node;
};

void ElementNode::createTextNode(std::string value) {
	TextNode* textNode = new TextNode(value);
	textNodes.push_back(textNode);
	trash.push_back(textNode);
	appendChild(*textNode);
};

bool ElementNode::isUnique() {
	for (std::string name: ElementNode::unique) {
		if (name == nodeName)
			return true;
	}
	return false;
};

bool ElementNode::parsable() {
	for (std::string name: ElementNode::ignore) {
		if (name == nodeName)
			return false;
	}
	return true;
};

std::string ElementNode::outerHTML() {
	std::string ret = "<" + nodeName;
	for (unsigned i = 0; i < attributes.size(); ++i) {
		ret += " " + attributes[i]->name + "=\""+ attributes[i]->value  + "\"";
	}
	ret += ">";
	if (!isUnique()) {
		ret += innerHTML();
		ret += "</" + nodeName + ">";
	}
	return ret;
};

std::string ElementNode::innerHTML() {
	std::string ret = "";
	for (unsigned i = 0; i < childNodes.size(); ++i) {
		ElementNode* node = dynamic_cast<ElementNode*>(childNodes[i]);
		if (node != nullptr) {
			ret += node->outerHTML();
		}
		else {
			ret += childNodes[i]->value;
		}
	}
	return ret;
};

ElementNode::~ElementNode() {
	for (unsigned i = trash.size(); i--;) {
		delete trash[i];
	}
};
