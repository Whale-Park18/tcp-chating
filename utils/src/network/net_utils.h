#pragma once
#include "global.h"
#include "safe_data.h"

#include <string>
#include <string_view>
#include <optional>

namespace park18::network
{
	enum class family_type
	{
		IPv4 = AF_INET,
		IPv6 = AF_INET6,
		__max__,
	};

	enum class socket_type
	{
		tcp = SOCK_STREAM,
		udp = SOCK_DGRAM,
		__max__,
	};

	struct socket_info
	{
		family_type familyType;
		socket_type socketType;
		int			protocol;

		char		ip[MAX_PATH];
		ushort		port;
	};

	int startup(WSAData& wsaData);
	int cleanup();

	/// <summary>
	/// ::socket() 와퍼 함수
	/// </summary>
	/// <param name="ipType">인터넷 주소 타입(IPv4, IPv6)</param>
	/// <param name="socketType">소켓 타입(tcp, udp)</param>
	safe_data::safe_socket<> socket(family_type ipType = family_type::IPv4, socket_type socketType = socket_type::tcp);

	/// <summary>
	/// ::connect() 와퍼 함수
	/// </summary>
	/// <param name="sock">소켓</param>
	/// <param name="ip">ip 주소</param>
	/// <param name="port">port 번호</param>
	int connect(SOCKET sock, std::string_view ip, ushort port);

	/// <summary>
	/// ::bind() 와퍼 함수
	/// </summary>
	/// <param name="sock">소켓</param>
	/// <param name="ip">ip 주소</param>
	/// <param name="port">port 번호</param>
	int bind(SOCKET sock, std::string_view ip, ushort port);

	/// <summary>
	/// ::listen() 와퍼 함수
	/// </summary>
	/// <param name="sock">소켓</param>
	/// <param name="queue_size">lisetn 큐 크기</param>
	int listen(SOCKET sock, int queue_size);

	/// <summary>
	/// ::accept() 와퍼 함수
	/// </summary>
	safe_data::safe_socket<> accept(SOCKET sock, sockaddr_in& address);

	/// <summary>
	/// sockaddr_in 구조체 설정 함수
	/// </summary>
	void set_sockaddr(sockaddr_in& address, std::string_view ip, ushort port);

	/// <summary>
	/// socket_info 구조체를 sockaddr_in으로 변경하는 함수
	/// </summary>
	sockaddr_in transform_to_sockaddr(const socket_info& socketInfo);

	/// <summary>
	/// 소켓의 정보(패밀리, 소켓 타입, ip, port 등)를 반환하는 함수
	/// </summary>
	std::optional<socket_info> get_socket_info(SOCKET sock);
}
