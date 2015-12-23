#include <iostream>
#include <vector>
#include <regex>
#include "node.h"
#include "tools.h"
#include "url.h"
#include "http.h"
#include "pricefinder.h"

int main() {
	// get website content
	http h;
	std::string str = h.fetch("www.submarino.com.br");

	// uses the price finder
	PriceFinder pf;
	pf.parse(str);
}
