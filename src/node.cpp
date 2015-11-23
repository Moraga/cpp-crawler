#include "node.h"

Node::~Node() {};

void Node::appendChild(Node& node) {
	childNodes.push_back(&node);
};

Attribute::Attribute(std::string name, std::string value) {
	this->name = name;
	this->value = value;
};

ElementNode::ElementNode(std::string nodeName) {
	this->nodeName = nodeName;
};

void ElementNode::setAttribute(std::string name, std::string value) {
	Attribute* attribute = new Attribute(name, value);
	attributes.push_back(attribute);
};

std::string ElementNode::outerHTML() {
	std::string ret = "<" + nodeName;

	for (unsigned i = 0; i < attributes.size(); ++i) {
		ret += " " + attributes[i]->name + "=\""+ attributes[i]->value  + "\"";
	}

	ret += ">";

	ret += innerHTML();

	ret += "</" + nodeName + ">";

	return ret;
};

std::string ElementNode::innerHTML() {
	std::string ret = "";

	for (unsigned i = 0; i < childNodes.size(); ++i) {
		ElementNode* node = dynamic_cast<ElementNode*>(childNodes[i]);
		if (node != nullptr) {
			ret += node->outerHTML();
		}
	}

	return ret;
};

ElementNode::~ElementNode() {
	for (unsigned i = attributes.size(); i--;) {
		delete attributes[i];
	}
};
