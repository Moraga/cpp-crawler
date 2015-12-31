#pragma once

#include <iostream>
#include <string>

struct Url {
	std::string protocol;
	std::string domain;
	std::string port;
	std::string path = "/";
	Url(std::string);
	void print();
};
