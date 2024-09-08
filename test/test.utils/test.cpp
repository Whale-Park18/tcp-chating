#include "utils_global.h"

/// <summary>
/// 테스트 진행시, 유의사항
/// - test.server 프로그램 실행
/// - test.client 프로그램
/// </summary>

extern void execute_test_client();
extern void execute_test_server();

namespace utils
{
	//*********************************************************
	// network base 
	//*********************************************************
	TEST(network, startup)
	{
		WSADATA wsaData = { 0 };
		ASSERT_EQ(park18::network::startup(wsaData), 0);
	}

	TEST(network, socket)
	{
		park18::safe_data::safe_socket sock = park18::network::socket();
		ASSERT_NE(sock.get(), INVALID_SOCKET);
	}

	//*********************************************************
	// network server
	//*********************************************************
	TEST(network, bind)
	{
		park18::safe_data::safe_socket sock = park18::network::socket();
		int result = park18::network::bind(sock, "127.0.0.1", 30701);

		ASSERT_NE(result, SOCKET_ERROR);
	}

	TEST(network, listen)
	{
		park18::safe_data::safe_socket sock = park18::network::socket();
		park18::network::bind(sock, "127.0.0.1", 30701);
		int result = park18::network::listen(sock, 10);

		ASSERT_NE(result, SOCKET_ERROR);
	}

	TEST(network, accept)
	{
		park18::safe_data::safe_socket listenSock = park18::network::socket();
		park18::network::bind(listenSock, "127.0.0.1", 30701);
		park18::network::listen(listenSock, 10);

		// execute test client
		execute_test_client();

		sockaddr_in acceptAddress = { 0 };
		park18::safe_data::safe_socket acceptSock = park18::network::accept(listenSock, acceptAddress);

		ASSERT_NE(acceptSock.get(), INVALID_SOCKET);
	}

	//*********************************************************
	// network client 
	//*********************************************************
	TEST(network, connect)
	{
		// execute test server
		execute_test_server();

		park18::safe_data::safe_socket sock = park18::network::socket();
		int result = park18::network::connect(sock, "127.0.0.1", 30701);

		ASSERT_NE(result, SOCKET_ERROR);
	}

	//*********************************************************
	// network address helper
	//*********************************************************
	TEST(network, set_sockaddr)
	{
		sockaddr_in address = { 0 };
		park18::network::set_sockaddr(address, "127.0.0.1", 30701);

		char ip[MAX_PATH] = { 0 };
		inet_ntop(address.sin_family, &address.sin_addr.S_un.S_addr, ip, _countof(ip));
		park18::ushort port = ntohs(address.sin_port);

		ASSERT_STREQ(ip, "127.0.0.1");
		ASSERT_EQ(port, 30701);
	}

	TEST(network, transform_to_sockaddr)
	{
		park18::network::socket_info socketInfo = { };
		socketInfo.familyType = static_cast<park18::network::family_type>(PF_INET);
		socketInfo.socketType = static_cast<park18::network::socket_type>(SOCK_STREAM);
		socketInfo.protocol = 0;
		socketInfo.port = 30701;
		std::strcpy(socketInfo.ip, "127.0.0.1");

		sockaddr_in address = park18::network::transform_to_sockaddr(socketInfo);

		char ip[MAX_PATH] = { 0 };
		inet_ntop(address.sin_family, &address.sin_addr.S_un.S_addr, ip, _countof(ip));
		park18::ushort port = ntohs(address.sin_port);

		ASSERT_STREQ(ip, "127.0.0.1");
		ASSERT_EQ(port, 30701);
	}

	TEST(network, get_socket_info)
	{
		park18::safe_data::safe_socket sock = park18::network::socket();
		park18::network::bind(sock, "127.0.0.1", 30701);

		auto maybeSocketInfo = park18::network::get_socket_info(sock);
		ASSERT_TRUE(maybeSocketInfo.has_value());

		sockaddr_in address = park18::network::transform_to_sockaddr(maybeSocketInfo.value());

		char ip[MAX_PATH] = { 0 };
		inet_ntop(address.sin_family, &address.sin_addr.S_un.S_addr, ip, _countof(ip));
		park18::ushort port = ntohs(address.sin_port);

		ASSERT_STREQ(ip, "127.0.0.1");
		ASSERT_EQ(port, 30701);
	}
}