#include "safe_data.h"

int main()
{
	park18::safe_data::safe_socket listenSock(socket(PF_INET, SOCK_STREAM, 0));
}