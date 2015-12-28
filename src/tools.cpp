#include "tools.h"

void replace(std::string& str, const std::string& from, const std::string& to) {
	size_t pos = 0;
	while ((pos = str.find(from, pos)) != std::string::npos) {
		str.replace(pos, from.length(), to);
		pos += to.length();
	}
};

std::string trim(const std::string& str) {
	return remove_spaces(ltrim(rtrim(str)));
};

std::string ltrim(const std::string& str) {
	static const std::regex re("^\\s+");
	return std::regex_replace(str, re, "");
}

std::string rtrim(const std::string& str) {
	static const std::regex re("\\s+$");
	return std::regex_replace(str, re, "");
};

std::string remove_spaces(const std::string& str) {
	static const std::regex re("\\s{2,}");
	return std::regex_replace(str, re, " ");
};
