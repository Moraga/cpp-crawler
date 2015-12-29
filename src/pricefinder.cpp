#include "pricefinder.h"

void PriceFinder::parse_element(ElementNode* elem) {
	if ("title" == elem->nodeName) {
		if (name.empty())
			name = elem->text();
	}
	else if ("meta" == elem->nodeName) {
		std::string prop = elem->getAttribute("property");
		if ("og:title" == prop) {
			name = elem->getAttribute("content");
		}
		else if ("og:url" == prop && url.empty()) {
			url = elem->getAttribute("content");
		}
	}
	else if ("link" == elem->nodeName) {
		if ("canonical" == elem->getAttribute("rel"))
			url = elem->getAttribute("href");
	}
	else if ("a" == elem->nodeName) {
		std::string href = elem->getAttribute("href");
		if (href.at(0) != '#' && (href.find(":") == std::string::npos || href.find("http") == 0)) {
			links.push_back(&href);
		}
	}
};

void PriceFinder::parse_text(TextNode* textNode) {
	static const std::regex rePrice("\\d+(\\.\\d{3})*,\\d{2}(?![0-9 ]*[a-z%])|\\$\\s*[0-9]+[0-9.,]+");

	std::smatch matches;
	//  find product price
	if (std::regex_search(textNode->value, matches, rePrice)) {
		// gets the first price found
		std::string text_price = matches[0];
		// remove leftover characters
		replace(text_price, ".", "");
		replace(text_price, ",", ".");
		replace(text_price, "$", "");
		replace(text_price, " ", "");
		// creates a price object
		try {
			float value = std::stof(text_price);
			Price* price = new Price(value, matches[0], textNode);
			options.push_back(price);
		} catch (std::exception& e) {}
	}
	// find product name
	else {

	}
};

void PriceFinder::analyze() {
	static const std::regex reInstallment("(\\d+)\\s*[Xx]");
	static const std::regex reSave("([0-9]+[0-9,]*)\\s*%");

	for (Price* price: options) {
		std::string content = price->content();
		std::smatch matches;
		// is an installment
		if (std::regex_search(content, matches, reInstallment)) {

		}
		// is an installment with save
		else if (std::regex_search(content, matches, reSave)) {

		}
	}
};
