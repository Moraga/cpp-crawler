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
	std::vector<Node*> siblings();
	Node* prev();
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
	static std::string ignore[];
	std::vector<Attribute*> attributes;
	std::vector<TextNode*> textNodes;
	ElementNode(std::string);
	~ElementNode();
	std::string getAttribute(std::string);
	void setAttribute(std::string, std::string);
	ElementNode* createNode(std::string);
	TextNode* createTextNode(std::string);
	bool isUnique();
	bool parsable();
	std::string outerHTML();
	std::string innerHTML();
};
