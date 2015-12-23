#include "tools.h"

std::string replace(const std::string& str, const std::string& from, const std::string& to) {
	std::string ret = str;
	size_t pos = 0;
	while ((pos = ret.find(from, pos)) != std::string::npos) {
		ret.replace(pos, from.length(), to);
		pos += to.length();
	}
	return ret;
};
