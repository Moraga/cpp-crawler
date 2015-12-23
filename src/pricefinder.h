#include <regex>
#include "htmlparser.h"
#include "tools.h"

struct PriceFinder: public HTMLParser {
	static std::regex regex;
	void parse_text(TextNode*);
};
