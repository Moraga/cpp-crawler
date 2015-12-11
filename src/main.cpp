#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"
#include "url.h"
#include "http.h"
#include "htmlparser.h"

int main() {
	// getting content
	http h;
	std::string str = h.fetch("www.uol.com.br");

	// parsing the content
	HTMLParser parser;
	parser.parse(str);
}
