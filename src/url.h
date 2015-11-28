#include <string>

struct Url {
	std::string protocol;
	std::string domain;
	std::string port;
	std::string path;
	Url();
	static Url parse(std::string);
};
