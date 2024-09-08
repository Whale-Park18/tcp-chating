#include "safe_data.h"
#include "network/net_utils.h"

#include <iostream>

void test_client()
{
	WSADATA wsaData = { 0 };
	park18::network::startup(wsaData);

	park18::safe_data::safe_socket connectSock(park18::network::socket());
	if (park18::network::connect(connectSock, "127.0.0.1", 30701) == SOCKET_ERROR)
	{
		std::cout << "[E] connect() - code: " << WSAGetLastError() << std::endl;
	}
}

int main()
{
	test_client();
}