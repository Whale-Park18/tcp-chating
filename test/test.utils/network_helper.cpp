#include <filesystem>
#include <thread>

#include <Windows.h>

constexpr char* TEST_CLIENT_NAME = (char*)"test.client.exe";
constexpr char* TEST_SERVER_NAME = (char*)"test.server.exe";

void execute_test_client()
{
	if (std::filesystem::exists(TEST_CLIENT_NAME) == false)
	{
		return;
	}

	system(TEST_CLIENT_NAME);
}

void execute_test_server()
{
	if (std::filesystem::exists(TEST_SERVER_NAME) == false)
	{
		return;
	}

	std::thread thread([]() {system(TEST_SERVER_NAME); });
	thread.detach();
}