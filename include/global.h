#pragma once

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WIN32_LEAN_AND_MEAN // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

//*********************************************
// Built-in header(c)
//*********************************************
#include <Windows.h>	// Windows API
#include <WinSock2.h>	// Windows socket

//*********************************************
// Built-in header(c++)
//*********************************************

//*********************************************
// Custom header(c++)
//*********************************************
#include "basic_type.h"	// custom 

//*********************************************
// header lib/dll link
//*********************************************
#pragma comment(lib, "ws2_32.lib")	// WinSock2.h