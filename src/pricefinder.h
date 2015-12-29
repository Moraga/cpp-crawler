#include <regex>
#include "htmlparser.h"
#include "price.h"
#include "tools.h"

struct PriceFinder: public HTMLParser {
	std::vector<Price*> options;
	std::vector<Price*> installments;
	void parse_text(TextNode*);
	void find();
	void check_installments();
	void analyze();
};
