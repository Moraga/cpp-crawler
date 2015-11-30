#include <iostream>
#include <vector>
#include "node.h"
#include "tools.h"
#include "url.h"



#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int x() {

	int sockfd;

	std::string addr = "www.uol.com.br";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) {
		return -1;
	}

	struct sockaddr_in server;

	if (inet_addr(addr.c_str()) == -1) {
		struct hostent *he;
		struct in_addr **addr_list;

		he = gethostbyname(addr.c_str());

		if (he == NULL) {
			return -1;
		}

		addr_list = (struct in_addr**) he->h_addr_list;

		for (unsigned i = 0; addr_list[i] != NULL; ++i) {
			server.sin_addr = *addr_list[i];
		}
	}
	else {
		server.sin_addr.s_addr = inet_addr(addr.c_str());
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		std::cout << "connect failed. error";
		return -1;
	}

	std::string data = "GET / HTTP/1.1\r\nHost: www.uol.com.br\r\n\r\n\r\n";

	send(sockfd, data.c_str(), strlen(data.c_str()), 0);

	std::cout << "data sent.";

	char buffer[5000000];
	int total = 0;
	int brecv;

	while ((brecv = recv(sockfd, buffer + total, sizeof(buffer), 0)) > 0) {
		total += brecv;
	}

	std::cout << buffer << "\n";

	return 0;
}



int main() {
	x();

	std::string content =
			"<html lang = pt>"
			"<body>"
			"<p class='paragraph'>p content</p>"
			"</body>";

	//ElementNode* node = parsehtml(content);
	//std::cout << node->outerHTML() << "\n";

	//Url::parse("www.one.com").print();
	//Url::parse("//www.two.com").print();
	//Url::parse("http://www.three.com").print();
	//Url::parse("http:www.four.com").print();
	//Url::parse("www.five.com:80").print();
	//Url::parse("www.six.com/path").print();
	//Url::parse("http://www.seven.com/path").print();
	//Url::parse("http://www.eight.com:80/path").print();
}
