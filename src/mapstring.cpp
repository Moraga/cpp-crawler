#include "mapstring.h"

void mapstring(std::string str) {
	std::string all =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789.";

	std::string key = "";
	std::string val = "";

	char qut = '\0';

	for (char& chr: str) {
		// quoted text
		if (qut != '\0') {
			if (chr == qut) {
				qut = '\0';
			}
			else {
				val += chr;
			}
		}
		// searching quotes
		else if (chr == '"' || chr == '\'') {
			qut = chr;
		}
		// data captured
		else if (chr == ',' || chr == ']' || chr == '}' || chr == ';') {
			if (!key.empty()) {
				//std::cout << key << " => " << val << std::endl;
			}
			key = "";
			val = "";
		}
		// content end
		else if (chr == '{' || chr == '[') {
			key = "";
			val = "";
		}
		// key or value pure
		else if (all.find(chr) != std::string::npos) {
			val += chr;
		}
	}
}
