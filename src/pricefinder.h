#include <regex>
#include "htmlparser.h"
#include "price.h"
#include "tools.h"

struct PriceFinder: public HTMLParser {
	std::vector<Price*> options;
	static std::regex regex;
	void parse_text(TextNode*);
};
