
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
