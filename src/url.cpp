#include "url.h"

Url::Url(std::string str) {
	int sep = str.find(':');
	int bar = str.find('/');

	// protocol
	if (sep != std::string::npos && (bar == std::string::npos || sep < bar)) {
		protocol = str.substr(0, sep);
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
		domain = str.substr(0, sep);
		port = str.substr(sep + 1, bar - sep - 1);
		path = str.substr(bar);
	}
	// only port
	else if (sep != std::string::npos && bar == std::string::npos) {
		domain = str.substr(0, sep);
		port = str.substr(bar + 1);
	}
	// only path
	else if (bar != std::string::npos) {
		domain = str.substr(0, bar);
		path = str.substr(bar);
	}
	// only domain
	else {
		domain = str;
	}
}

void Url::print() {
	std::cout <<
			"\nprotocol: " << protocol <<
			"\ndomain: " << domain <<
			"\nport: " << port <<
			"\npath: " << path <<
			std::endl;
}
