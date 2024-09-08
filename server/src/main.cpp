#include "safe_data.h"
#include "network/net_utils.h"

#include <iostream>

void test_server()
{
	WSADATA wsaData = { 0 };
	park18::network::startup(wsaData);

	park18::safe_data::safe_socket listenSock = park18::network::socket();
	if (park18::network::bind(listenSock, "127.0.0.1", 30701) == SOCKET_ERROR)
	{
		std::cout << "[E] bind - code: " << WSAGetLastError() << std::endl;
	}

	if (park18::network::listen(listenSock, 10) == SOCKET_ERROR)
	{
		std::cout << "[E] listen - code: " << WSAGetLastError() << std::endl;
	}

	sockaddr_in acceptAddress = { 0 };
	park18::safe_data::safe_socket acceptSock = park18::network::accept(listenSock, acceptAddress);
}

int main()
{
	test_server();
}