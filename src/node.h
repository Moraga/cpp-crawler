#pragma once

#include <string>
#include <vector>
#include <iostream>

struct Node {
	std::string nodeName;
	std::string nodeType;
	std::string name;
	std::string value;
	Node* parentNode;
	std::vector<Node*> childNodes;
	virtual ~Node();
	void appendChild(Node&);
protected:
	std::vector<Node*> trash;
};

struct Attribute: public Node {
	Attribute(std::string, std::string);
};

struct TextNode: public Node {
	TextNode(std::string);
};

struct ElementNode: public Node {
	static std::string unique[];
	std::vector<Attribute*> attributes;
	std::vector<TextNode*> textNodes;
	ElementNode(std::string);
	~ElementNode();
	void setAttribute(std::string, std::string);
	ElementNode* createNode(std::string);
	void createTextNode(std::string);
	bool isUnique();
	std::string outerHTML();
	std::string innerHTML();
};
