#include "http.h"

bool http::conn(std::string host, int port) {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		return false;
	if (inet_addr(host.c_str()) == -1) {
		struct hostent* he;
		struct in_addr** addr_list;
		he = gethostbyname(host.c_str());
		if (!he)
			return false;
		addr_list = (struct in_addr**) he->h_addr_list;
		for (int i = 0; addr_list[i] != 0; i++) {
			server.sin_addr = *addr_list[i];
			break;
		}
	}
	else {
		server.sin_addr.s_addr = inet_addr(host.c_str());
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if (connect(sock, (struct sockaddr*) &server, sizeof(server)) < 0)
		return false;
	return true;
};

bool http::write(std::string data) {
	if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
		return false;
	}
	return true;
};

std::string http::read() {
	char buffer[SIZE];
	int brecv, total = 0;
	memset(buffer, 0, SIZE);
	while ((brecv = recv(sock, buffer + total, SIZE - 1, 0)) > 0) {
		total += brecv;
	}
	return std::string(buffer, strlen(buffer));
};

std::string http::fetch(std::string url) {
	Url u = Url::parse(url);
	conn(u.domain, 80);
	write("GET "+ u.path +" HTTP/1.0\r\nHost: "+ u.domain +"\r\n\r\n");
	return read();
};
