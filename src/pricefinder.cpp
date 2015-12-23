#include "pricefinder.h"

std::regex PriceFinder::regex("\\d+(\\.\\d{3})*,\\d{2}(?![0-9 ]*[a-z%])|\\$\\s*[0-9]+[0-9.,]+");

void PriceFinder::parse_text(TextNode* textNode) {
	std::smatch matches;
	// tries to find a price
	if (std::regex_search(textNode->value, matches, regex)) {
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
			Price* price = new Price(value, textNode);
			options.push_back(price);
		} catch (std::exception& e) {}
	}
	else {

	}
};
