#include <regex>
#include "htmlparser.h"
#include "price.h"
#include "tools.h"

struct PriceFinder: public HTMLParser {
	std::string name;
	float price;
	std::string url;
	std::vector<std::string*> links;
	std::vector<Price*> options;
	std::vector<Price*> installments;
	void parse_element(ElementNode*);
	void parse_text(TextNode*);
	void analyze();
};
