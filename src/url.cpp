#include "url.h"

Url::Url() {
	port = "80";
	path = "/";
}

Url Url::parse(std::string str) {
	Url url;
	int dot, pth;

	dot = str.find(':');

	if (dot != std::string::npos) {
		url.protocol = str.substr(0, dot);
		while (str[dot + 1] == '/') {
			++dot;
		}
		str = str.substr(dot + 1);
	}

	dot = str.find(':');
	pth = str.find('/');

	// port, path and domain
	if (dot != std::string::npos && pth != std::string::npos && dot < pth) {
		url.domain = str.substr(0, dot);
		url.port = str.substr(dot + 1, pth - dot - 1);
		url.path = str.substr(pth);
	}
	// only port
	else if (dot != std::string::npos && pth == std::string::npos) {
		url.domain = str.substr(0, dot);
		url.port = str.substr(dot + 1);
	}
	// only path
	else if (pth != std::string::npos) {
		url.domain = str.substr(0, pth);
		url.path = str.substr(pth);
	}
	// only domain
	else {
		url.domain = str;
	}

	return url;
}
