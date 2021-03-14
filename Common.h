#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


/*打开网络库并校验版本*/
BOOL WinSockInit();
