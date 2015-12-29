#include "node.h"

Node::~Node() {};

void Node::appendChild(Node& node) {
	node.parentNode = this;
	childNodes.push_back(&node);
};

std::vector<Node*> Node::siblings() {
	std::vector<Node*> siblings;
	for (Node* node: parentNode->childNodes)
		if (node != this)
			siblings.push_back(node);
	return siblings;
};

Node* Node::prev() {
	Node* prev = nullptr;
	for (Node* node: parentNode->childNodes)
		if (node == this)
			break;
		else
			prev = node;
	return prev;
};

std::string Node::content(float maxLength) {
	Node* node = this;

	// short and closured tags
	for (unsigned i = 4; node && i--; node = node->parentNode) {
		if ("td" == node->nodeName) {
			for (unsigned j = 4; node && j--; node = node->parentNode) {
				if ("tr" == node->nodeName) {
					return node->text();
				}
			}
		}
	}

	// max length and up the tree
	if (maxLength > 0) {
		node = this;
		for (unsigned tries = 4; node && tries--; node = node->parentNode) {
			std::string text = trim(node->text());
			if (text.length() > maxLength) {
				if (text.length() > maxLength * 5)
					break;
				return text;
			}
		}
	}

	return text();
};

std::string Node::text() {
	std::string text = "";
	for (Node* childNode: childNodes)
		text += " " + childNode->text();
	return text.substr(1);
};

int Node::proximity(Node* node) {
	int distance = searchInside(node);
	return distance != 0 ? distance: searchOutside(node);
};

int Node::searchInside(Node* node, int depth) {
	int size = childNodes.size();

	// siblings
	for (unsigned i = size; --i; )
		if (childNodes[i] == node)
			return i + depth;

	// depth search
	for (unsigned i = 0; i < size; i++) {
		int distance = childNodes[i]->searchInside(node, i + 1 + depth);
		if (distance > 0)
			return distance;
	}

	return 0;
};

int Node::searchOutside(Node* node, int depth) {
	if (parentNode) {
		std::vector<Node*> childNodes = parentNode->childNodes;
		int size = childNodes.size();
		int position = size;

		// find this position on parent node
		for (; --position; )
			if (childNodes[position] == this)
				break;

		// navigate through the siblings
		for (int j = 0, k = position * -1; j < size; ++j, ++k) {
			// prevent repeat this node
			if (k != 0) {
				if (childNodes[j] == node)
					return std::abs(k) + depth;
				else {
					int distance = childNodes[j]->searchInside(node, std::abs(k) + 1 + depth);
					if (distance > 0)
						return distance;
				}
			}
		}

		// up the tree
		return parentNode->searchOutside(node, position + 1 + depth);
	}

	return 0;
};

std::vector<Node*> Node::closest(const std::string& nodeName, int size) {
	std::vector<Node*> nodes = closestInside(nodeName, size);
	size -= nodes.size();
	if (size > 0) {
		std::vector<Node*> temp = closestOutside(nodeName, size);
		if (temp.size() > 0) {
			nodes.reserve(nodes.size() + std::distance(temp.begin(), temp.end()));
			nodes.insert(nodes.end(), temp.begin(), temp.end());
		}
	}
	return nodes;
};

std::vector<Node*> Node::closestInside(const std::string& nodeName, int size) {
	std::vector<Node*> nodes;
	for (Node* node: childNodes) {
		// sibling
		if (node->nodeName == nodeName) {
			nodes.push_back(node);
			if (--size == 0)
				break;
		}
		std::vector<Node*> temp = node->closestInside(nodeName, size);
		if (temp.size() > 0) {
			nodes.reserve(nodes.size() + std::distance(temp.begin(), temp.end()));
			nodes.insert(nodes.end(), temp.begin(), temp.end());
			size -= temp.size();
			if (size < 1)
				break;
		}
	}
	return nodes;
};

std::vector<Node*> Node::closestOutside(const std::string& nodeName, int size) {
	std::vector<Node*> nodes;

	if (parentNode) {
		std::vector<Node*> siblings;
		int position = 0;

		// get this position and siblings
		for (unsigned i = 0; i < parentNode->childNodes.size(); ++i) {
			if (this == parentNode->childNodes[i])
				position = i;
			else
				siblings.push_back(parentNode->childNodes[i]);
		}

		for (unsigned j = 0, k = ++position * -1; j < position; ++j, ++k) {
			if (k != 0) {
				if (parentNode->childNodes[j]->nodeName == nodeName) {
					nodes.push_back(parentNode->childNodes[j]);
					if (--size == 0)
						break;
				}
				std::vector<Node*> temp = parentNode->childNodes[j]->closestInside(nodeName, size);
				if (temp.size() > 0) {
					nodes.reserve(nodes.size() + std::distance(temp.begin(), temp.end()));
					nodes.insert(nodes.end(), temp.begin(), temp.end());
					size -= temp.size();
					if (size < 1)
						break;
				}
			}
		}
	}

	// up the tree
	if (size > 0 && parentNode->parentNode) {
		std::vector<Node*> temp = parentNode->parentNode->closestOutside(nodeName, size);
		if (temp.size() > 0) {
			nodes.reserve(nodes.size() + std::distance(temp.begin(), temp.end()));
			nodes.insert(nodes.end(), temp.begin(), temp.end());
		}
	}

	return nodes;
};

Attribute::Attribute(const std::string name, const std::string value) {
	this->name = name;
	this->value = value;
};

TextNode::TextNode(const std::string value) {
	this->value = value;
};

std::string TextNode::text() {
	return value;
};

std::string ElementNode::unique[] = {
		"area", "base", "col", "command", "embed", "hr", "img", "input",
		"keygen", "link", "meta", "param", "source", "track", "wbr"
};

std::string ElementNode::ignore[] = {"script", "style"};

ElementNode::ElementNode(const std::string nodeName) {
	this->nodeName = nodeName;
};

std::string ElementNode::getAttribute(const std::string name) {
	for (unsigned i = 0; i < attributes.size(); ++i)
		if (name == attributes[i]->name)
			return attributes[i]->value;
	return "";
};

void ElementNode::setAttribute(const std::string name, const std::string value) {
	Attribute* attribute = new Attribute(name, value);
	attributes.push_back(attribute);
	trash.push_back(attribute);
};

ElementNode* ElementNode::createElementNode(const std::string nodeName) {
	ElementNode* node = new ElementNode(nodeName);
	trash.push_back(node);
	appendChild(*node);
	return node;
};

TextNode* ElementNode::createTextNode(const std::string value) {
	TextNode* textNode = new TextNode(value);
	textNodes.push_back(textNode);
	trash.push_back(textNode);
	appendChild(*textNode);
	return textNode;
};

bool ElementNode::isUnique() {
	for (std::string name: ElementNode::unique)
		if (name == nodeName)
			return true;
	return false;
};

bool ElementNode::parsable() {
	for (std::string name: ElementNode::ignore)
		if (name == nodeName)
			return false;
	return true;
};

std::string ElementNode::outerHTML() {
	std::string ret = "<" + nodeName;
	for (Attribute* attribute: attributes)
		ret += " " + attribute->name + "=\""+ attribute->value  + "\"";
	ret += ">";
	if (!isUnique()) {
		ret += innerHTML();
		ret += "</" + nodeName + ">";
	}
	return ret;
};

std::string ElementNode::innerHTML() {
	std::string ret = "";
	for (Node* node: childNodes) {
		ElementNode* elem = dynamic_cast<ElementNode*>(node);
		ret += elem ? elem->outerHTML() : node->value;
	}
	return ret;
};

ElementNode::~ElementNode() {
	for (unsigned i = trash.size(); i--;)
		delete trash[i];
};
