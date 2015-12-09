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
