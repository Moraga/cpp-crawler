#include <regex>
#include "htmlparser.h"
#include "price.h"
#include "tools.h"

struct PriceFinder: public HTMLParser {
	std::string title;
	Node* name;
	float price;
	std::string url;
	std::vector<std::string*> links;
	std::vector<Price*> prices;
	std::vector<Price*> installments;
	void parse_element(ElementNode*);
	void parse_text(TextNode*);
	void find();
	void analyze();
	void applyInstallments();
	void applyProximity();
	void applyRoadmap();
	void applyUniqueness();
	void applyRepetitions();
	void applyMerge();
	void applyHelpers();
	void applyJSONValues();
	void decision();
};
