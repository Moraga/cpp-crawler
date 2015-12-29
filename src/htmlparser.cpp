#include "htmlparser.h"

void HTMLParser::parse_text(TextNode* textNode) {
	//std::cout << "parsing text" << textNode->value << std::endl;
};

void HTMLParser::parse_element(ElementNode* node) {
	if ("title" == node->nodeName) {
		std::cout << "Title: " << node->innerHTML();
	}
	else if ("link" == node->nodeName) {
		//std::cout << "href: " << node->getAttribute("href");
	}
};

void HTMLParser::parse(const std::string str) {
	ElementNode* elem = new ElementNode("document");

	std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string alnum = alpha + "0123456789";
	std::string aldot = alnum + "-:";
	std::string space = " \r\n\t";
	std::string specs = space + ">";

	std::string dont = "";
	std::string name = "";
	std::string attn = "";
	std::string attv = "";
	std::string text = "";

	char quot = '\0';

	bool onelem = false;
	bool isclos = false;
	bool onname = false;
	bool onattn = false;
	bool onattv = false;
	bool oncomm = false;

	// stacks
	std::vector<ElementNode*> stack;
	std::vector<Attribute> atts;

	stack.push_back(elem);

	char chr;
	char nxt;

	for (unsigned i = 0; i < str.size(); ++i) {
		chr = str[i];

		if (onelem) {
			// tag name
			if (onname) {
				// capturing tag name
				if (alnum.find(chr) != std::string::npos) {
					name += chr;
				}
				else {
					onname = false;
					--i; // back
				}
			}
			// attribute name
			else if (onattn) {
				if (aldot.find(chr) != std::string::npos) {
					attn += chr;
				}
				else {
					onattn = false;
					--i;
				}
			}
			// attribute value
			else if (onattv) {
				if (quot) {
					if (chr == quot) {
						Attribute attr(attn, attv);
						atts.push_back(attr);
						onattv = false;
						attn = "";
						attv = "";
						quot = '\0';
					}
					else {
						attv += chr;
					}
				}
				else if (!attv.empty()) {
					if (specs.find(chr) == std::string::npos) {
						attv += chr;
					}
					else {
						Attribute attr(attn, attv);
						atts.push_back(attr);
						onattv = false;
						attn = "";
						attv = "";
						--i;
					}
				}
				else if (chr == '"' || chr == '\'') {
					quot = chr;
				}
				else if (space.find(chr) == std::string::npos) {
					attv += chr;
				}
			}
			// start attribute value
			else if (chr == '=') {
				onattv = true;
			}
			// attribute name
			else if (alpha.find(chr) != std::string::npos) {
				onattn = true;
				if (!attn.empty()) {
					Attribute attr(attn, attn);
					atts.push_back(attr);
					attn = "";
				}
				attn += chr;
			}
			// closing tag
			else if (chr == '>') {
				if (isclos) {
					for (unsigned j = stack.size(); j--;) {
						if (stack[j]->nodeName == name) {
							parse_element(stack[j]);
							stack.erase(stack.end() - j, stack.end());
							elem = stack[j - 1];
							break;
						}
					}
					isclos = false;
				}
				// creating tag
				else {
					if (!attn.empty()) {
						Attribute attr(attn, attn);
						atts.push_back(attr);
						attn = "";
					}

					// creates the tag
					ElementNode* node = elem->createElementNode(name);
					for (unsigned i = 0; i < atts.size(); ++i) {
						node->setAttribute(atts[i].name, atts[i].value);
					}
					// ignore content of script and style tags
					if (!node->parsable()) {
						elem = node;
						dont = "</" + elem->nodeName;
					}
					// have not close tag
					else if (node->isUnique()) {
						parse_element(node);
					}
					else {
						elem = nullptr;
						elem = node;
						stack.push_back(elem);
					}

				}
				name = "";
				atts.erase(atts.begin(), atts.end());
				onelem = false;
			}
		}
		// comment block
		else if (oncomm) {
			if (chr == '>' && text.substr(text.size() - 2) == "--") {
				oncomm = false;
			}
			text += chr;
		}
		// in script or style tag
		else if (!dont.empty()) {
			if (chr == '>') {
				if ("script" == elem->nodeName) {
					// parse script content
				}
				dont = "";
				text = "";
				continue;
			}
			text += chr;
		}
		// open tag
		else if (chr == '<') {
			nxt = str[i + 1];
			// found comments
			if (nxt == '-' && str[i + 2] == '-') {
				oncomm = true;
			}
			// closing tag
			else if (nxt == '/' && alpha.find(str[i + 2]) != std::string::npos) {
				if (!text.empty()) {
					parse_text(elem->createTextNode(text));
					text = "";
				}
				onelem = true;
				onname = true;
				isclos = true;
				name = str[i + 2];
				i += 2;
			}
			// opening tag
			else if (alpha.find(nxt) != std::string::npos) {
				if (!text.empty()) {
					parse_text(elem->createTextNode(text));
					text = "";
				}
				onelem = true;
				onname = true;
				name = nxt;
				++i;
			}
			else {
				text += chr;
			}
		}
		// capturing text
		else {
			text += chr;
		}
	}

	// missing close tag
	if (!text.empty()) {
		elem->createTextNode(text);
	}

	// self reference
	document = stack[0];
};
