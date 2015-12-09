#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"
#include "url.h"
#include "http.h"

int main() {
	http h;
	std::cout << h.fetch("www.uol.com.br");

	std::string content =
			"<html lang = pt>"
			"<body>"
			"<p class='paragraph'>p content</p>"
			"</body>";

	//ElementNode* node = parsehtml(content);
	//std::cout << node->outerHTML() << "\n";

	//Url::parse("www.one.com").print();
	//Url::parse("//www.two.com").print();
	//Url::parse("http://www.three.com").print();
	//Url::parse("http:www.four.com").print();
	//Url::parse("www.five.com:80").print();
	//Url::parse("www.six.com/path").print();
	//Url::parse("http://www.seven.com/path").print();
	//Url::parse("http://www.eight.com:80/path").print();
}
