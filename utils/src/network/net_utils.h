#pragma once
#include "global.h"
#include "safe_data.h"

#include <string_view>

#include <WinSock2.h>

namespace park18::network
{
	void startup(WSAData& wsaData);
	void cleanup();

	safe_data::safe_socket<> make_socket();

	void connect();

	void bind(std::string_view ip, ushort);

	void listen(size_t type = PF_INET);

	safe_data::safe_socket<> accept();
}
