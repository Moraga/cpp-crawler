#include <iostream>
#include "node.h"


int main() {
	ElementNode html("html"),
			body("body");

	html.setAttribute("lang", "pt");
	html.appendChild(body);

	body.createTextNode("text text");


	std::cout << html.outerHTML() << std::endl;
}
