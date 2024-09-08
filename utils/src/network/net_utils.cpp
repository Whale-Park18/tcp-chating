#include "net_utils.h"

#include <iostream>

int park18::network::startup(WSAData& wsaData)
{
	return WSAStartup(MAKEWORD(2,2), &wsaData);
}

int park18::network::cleanup()
{
	return ::WSACleanup();
}

park18::safe_data::safe_socket<> park18::network::socket(family_type ipType , socket_type socketType)
{
	return park18::safe_data::safe_socket<>(::socket(static_cast<int>(ipType), static_cast<int>(socketType), 0));
}

int park18::network::connect(SOCKET sock, std::string_view ip, ushort port)
{
	sockaddr_in address = { 0 };
	set_sockaddr(address, ip, port);

	return ::connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}

int park18::network::bind(SOCKET sock, std::string_view ip, ushort port)
{
	sockaddr_in address = { 0 };
	set_sockaddr(address, ip, port);
	
	return ::bind(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address));
}

int park18::network::listen(SOCKET sock, int queue_size)
{
	return ::listen(sock, queue_size);
}

park18::safe_data::safe_socket<> park18::network::accept(SOCKET sock, sockaddr_in& address)
{
	int addressSize = sizeof(address);

	return park18::safe_data::safe_socket<>(::accept(sock, reinterpret_cast<sockaddr*>(&address), &addressSize));
}

void park18::network::set_sockaddr(sockaddr_in& address, std::string_view ip, ushort port)
{
	address.sin_family = PF_INET;
	address.sin_port   = htons(port);
	inet_pton(address.sin_family, ip.data(), reinterpret_cast<void*>(&address.sin_addr.S_un.S_addr));
}

sockaddr_in park18::network::transform_to_sockaddr(const socket_info& socketInfo)
{
	sockaddr_in address = { 0 };
	address.sin_family = static_cast<int>(socketInfo.familyType);
	address.sin_port   = ::htons(socketInfo.port);
	inet_pton(address.sin_family, socketInfo.ip, reinterpret_cast<void*>(&address.sin_addr.S_un.S_addr));

	return address;
}

std::optional<park18::network::socket_info> park18::network::get_socket_info(SOCKET sock)
{
	// sockaddr 정보 획득
	sockaddr_storage addressStorage = { 0 };
	int addressSize = sizeof(addressStorage);
	if (getsockname(sock, reinterpret_cast<sockaddr*>(&addressStorage), &addressSize) == SOCKET_ERROR)
	{
		return std::nullopt;
	}

	// socket type 획득
	int optionValue = 0;
	int optionSize = sizeof(optionValue);
	if (getsockopt(sock, SOL_SOCKET, SO_TYPE, reinterpret_cast<char*>(&optionValue), &optionSize) == SOCKET_ERROR)
	{
		return std::nullopt;
	}

	// sockaddr_in 구조체로 변환
	sockaddr_in* address = reinterpret_cast<sockaddr_in*>(&addressStorage);

	// socket_info 구조체로 바인딩
	socket_info socketInfo;
	socketInfo.familyType = static_cast<family_type>(address->sin_family);
	socketInfo.socketType = static_cast<socket_type>(optionValue);
	socketInfo.port		  = ntohs(address->sin_port);
	inet_ntop(address->sin_family, &address->sin_addr.S_un.S_addr, socketInfo.ip, _countof(socketInfo.ip));

	return socketInfo;
}
