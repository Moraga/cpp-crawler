#ifndef _WIN32

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "url.h"

#define SIZE 1000000

struct http {
	int sock;
	struct sockaddr_in server;
	bool conn(std::string, int);
	bool write(std::string);
	std::string read();
	std::string fetch(std::string);
};

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
	write("GET "+ u.path +" HTTP/1.1\r\nHost: "+ u.domain +"\r\n\r\n");
	return read();
};

#endif

#ifdef _WIN32

#include <string>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include "url.h"
#include "node.h"

#define SIZE 1000000

#pragma comment(lib,"ws2_32.lib")

int http (std::string url) {
	Url u;

	u = Url::parse(url);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cout << "WSAStartup failed.\n";
        return 1;
    }
    SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct hostent *host;
    host = gethostbyname(u.domain.c_str());
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(80);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        std::cout << "Could not connect";
        return 1;
    }
    std::cout << "Connected.\n";

    std::string head = "GET "+ u.path +" HTTP/1.1\r\nHost: " + u.domain + "\r\nConnection: close\r\n\r\n";
    send(Socket, head.c_str(), head.length(), 0);

    char buffer[SIZE];
    int total = 0;
    memset(buffer, 0, SIZE);

    int brecv;
    while ((brecv = recv(Socket, buffer + total, SIZE - 1, 0)) > 0) {
        total += brecv;
    }

    buffer[total] = '\0';
    closesocket(Socket);
    WSACleanup();

    std::string buff(buffer, strlen(buffer));

    ElementNode* node = parsehtml(buff);

    std::cout << node->nodeName;

    return 0;
}

#endif
