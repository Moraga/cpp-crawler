#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "tools.h"

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
	std::string content(float=0);
	virtual std::string text();
	int proximity(Node*);
	int searchInside(Node*, int=0);
	int searchOutside(Node*, int=0);
	std::vector<Node*> closest(const std::string&, int=1);
	std::vector<Node*> closestInside(const std::string&, int=1);
	std::vector<Node*> closestOutside(const std::string&, int=1);
protected:
	std::vector<Node*> trash;
};

struct Attribute: public Node {
	Attribute(const std::string, const std::string);
};

struct TextNode: public Node {
	TextNode(const std::string);
	std::string text();
};

struct ElementNode: public Node {
	static std::string unique[];
	static std::string ignore[];
	std::vector<Attribute*> attributes;
	std::vector<TextNode*> textNodes;
	ElementNode(const std::string);
	~ElementNode();
	std::string getAttribute(const std::string);
	void setAttribute(const std::string, const std::string);
	ElementNode* createElementNode(const std::string);
	TextNode* createTextNode(const std::string);
	bool isUnique();
	bool parsable();
	std::string outerHTML();
	std::string innerHTML();
};
