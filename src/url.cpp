#include "url.h"

Url::Url() {
	path = "/";
}

Url Url::parse(std::string str) {
	Url url;
	int sep, bar;

	sep = str.find(':');
	bar = str.find('/');

	// protocol
	if (sep != std::string::npos && (bar == std::string::npos || sep < bar)) {
		url.protocol = str.substr(0, sep);
	}
	else {
		sep = -1;
	}

	// remove initial bars
	while (str[sep + 1] == '/') {
		++sep;
	}
	str = str.substr(sep + 1);

	// search again
	sep = str.find(':');
	bar = str.find('/');

	// port, path and domain
	if (sep != std::string::npos && bar != std::string::npos && sep < bar) {
		url.domain = str.substr(0, sep);
		url.port = str.substr(sep + 1, bar - sep - 1);
		url.path = str.substr(bar);
	}
	// only port
	else if (sep != std::string::npos && bar == std::string::npos) {
		url.domain = str.substr(0, sep);
		url.port = str.substr(bar + 1);
	}
	// only path
	else if (bar != std::string::npos) {
		url.domain = str.substr(0, bar);
		url.path = str.substr(bar);
	}
	// only domain
	else {
		url.domain = str;
	}

	return url;
}

void Url::print() {
	std::cout <<
			"\nprotocol: " << protocol <<
			"\ndomain: " << domain <<
			"\nport: " << port <<
			"\npath: " << path <<
			std::endl;
}
