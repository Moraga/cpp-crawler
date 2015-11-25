#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"

int main() {
	std::string content =
			"<html lang = pt>"
			"<body>"
			"<p class='paragraph'>p content</p>"
			"</body>";

	ElementNode* node = parsehtml(content);

	std::cout << node->outerHTML() << "\n";

}
