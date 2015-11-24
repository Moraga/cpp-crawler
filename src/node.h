#include <string>
#include <vector>
#include <iostream>

struct Node {
	std::string nodeName;
	std::string nodeType;
	std::string value;
	Node* parentNode;
	std::vector<Node*> childNodes;
	virtual ~Node();
	void appendChild(Node&);
};

struct Attribute {
	std::string name;
	std::string value;
	Attribute(std::string, std::string);
};

struct ElementNode: public Node {
	static std::string unique[];
	std::vector<Attribute*> attributes;
	ElementNode(std::string);
	~ElementNode();
	void setAttribute(std::string, std::string);
	void createTextNode(std::string);
	bool isUnique();
	std::string outerHTML();
	std::string innerHTML();
};

struct TextNode: public Node {
	TextNode(std::string);
};
