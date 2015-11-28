#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"
#include "url.h"

int main() {
	std::string content =
			"<html lang = pt>"
			"<body>"
			"<p class='paragraph'>p content</p>"
			"</body>";

	//ElementNode* node = parsehtml(content);
	//std::cout << node->outerHTML() << "\n";

	Url url = Url::parse("http://www.example.com");

	std::cout <<
				"\nprotocol: " << url.protocol <<
				"\ndomain: " << url.domain <<
				"\nport: " << url.port <<
				"\npath: " << url.path <<
				std::endl;
}
