#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"

int main() {
	//parsehtml();

	//std::cout << document.nodeName << std::endl;

	ElementNode* node = parsehtml("<html lang=pt><body>test</body></html>");

	std::cout << node->outerHTML() << "\n";

	std::cout << node->childNodes[0]->childNodes[0]->nodeName << "\n";

	//std::cout << "Ok!\n" << ;

}
