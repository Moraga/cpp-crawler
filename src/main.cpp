#include <iostream>
#include "node.h"


int main() {
	ElementNode html("html"),
			body("body");

	html.setAttribute("lang", "pt");
	html.appendChild(body);

	body.createTextNode("text text");

	ElementNode input("input");
	input.setAttribute("type", "text");
	body.appendChild(input);

	ElementNode p("p");
	p.createTextNode("paragraph");
	body.appendChild(p);


	std::cout << html.outerHTML() << std::endl;
}
