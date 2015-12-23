#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "node.h"
#include "tools.h"

struct HTMLParser {
	ElementNode* document;
	void parse(const std::string);
	virtual void parse_element(ElementNode*);
	virtual void parse_text(TextNode*);
	virtual ~HTMLParser() {}
};
