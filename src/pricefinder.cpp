#include "pricefinder.h"

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

void PriceFinder::find() {
	analyze();
	//check_installments();
};

void PriceFinder::analyze() {
	static const std::regex reInstallment("(\\d+)\\s*[Xx]");
	static const std::regex reSave("([0-9]+[0-9,]*)\\s*%");

	for (Price* price: options) {
		std::smatch matches;
		std::string content = price->content();
		// is an installment
		if (std::regex_search(content, matches, reInstallment)) {
			Price* installment = new Price(*price);
			// calculates the total value
			installment->value *= stoi(matches[1]);
			// price loses rank
			price->rank *= 0.9;
			installments.push_back(installment);
		}
		// is an installment with save
		else if (std::regex_search(content, matches, reSave)) {

		}
	}
};

void PriceFinder::check_installments() {
	for (Price* installment: installments) {
		std::cout << installment->nodeName();
	}
};
