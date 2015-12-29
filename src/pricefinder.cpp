#include "pricefinder.h"

void PriceFinder::parse_element(ElementNode* elem) {
	if ("title" == elem->nodeName) {
		if (title.empty())
			title = elem->text();
	}
	else if ("meta" == elem->nodeName) {
		std::string prop = elem->getAttribute("property");
		if ("og:title" == prop)
			title = elem->getAttribute("content");
		else if ("og:url" == prop && url.empty())
			url = elem->getAttribute("content");
	}
	else if ("link" == elem->nodeName) {
		if ("canonical" == elem->getAttribute("rel"))
			url = elem->getAttribute("href");
	}
	else if ("a" == elem->nodeName) {
		std::string href = elem->getAttribute("href");
		if (!href.empty() && href.at(0) != '#' && (href.find(":") == std::string::npos || href.find("http") == 0))
			links.push_back(&href);
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
			prices.push_back(price);
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
	static const std::regex reDiscount("(\\d+)%.*desconto");
	static const std::regex reFees("com\\s+juros");
	static const std::regex reSave("([0-9]+[0-9,]*)\\s*%");

	for (Price* price: prices) {
		std::smatch matches;
		std::string content = price->content();
		// is an installment
		if (std::regex_search(content, matches, reInstallment)) {
			Price* installment = new Price(*price);
			// calculates the total value
			installment->value *= stoi(matches[1]);
			// cash discount
			if (matches[1] == "1" && std::regex_search(content, matches, reDiscount)) {
				installment->value /= 1 - stof(matches[1]) / 100;
			}
			// rates and fees
			else if (std::regex_search(content, reFees)) {
				installment->value *= .98;
			}
			// price loses rank
			price->rank *= 0.9;
			installments.push_back(installment);
		}
		// is an installment with save
		else if (std::regex_search(content, matches, reSave)) {
			// possibilities for installment
			// opt 1
			Price* installment1 = new Price(*price);
			installment1->value *= stof(matches[1]) / 100 + 1;
			installments.push_back(installment1);
			// opt 2
			Price* installment2 = new Price(*price);
			installment2->value = installment2->value / stof(matches[1]) * 100 + installment2->value;
			installments.push_back(installment2);
		}
	}
};

void PriceFinder::applyInstallments() {
	for (Price* installment: installments) {
		std::cout << installment->nodeName();
	}
};

void PriceFinder::applyProximity() {
	int closer = 0, further = 0;

	for (Price* price: prices) {
		price->proximity = name->proximity(price->textNode->parentNode);
		if (further < price->proximity)
			further = price->proximity;
		if (closer == 0 || closer > price->proximity)
			closer = price->proximity;
	}

	if (further != closer) {
		for (Price* price: prices) {
			price->rank += installments.size()
					* ((further - price->proximity) / (further - closer))
					* ((price->installments + 1) / (installments.size() + 1));
		}
	}
};

void PriceFinder::applyRoadmap() {

};

void PriceFinder::applyUniqueness() {

};

void PriceFinder::applyRepetitions() {

};

void PriceFinder::applyMerge() {

};

void PriceFinder::applyHelpers() {

};

void PriceFinder::applyJSONValues() {

};

void PriceFinder::decision() {

};
