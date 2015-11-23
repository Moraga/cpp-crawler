#include <iostream>
#include "node.h"


int main() {
	ElementNode html("html"),
			body("body");

	html.setAttribute("lang", "pt");
	html.appendChild(body);

	std::cout << html.outerHTML() << std::endl;
}
