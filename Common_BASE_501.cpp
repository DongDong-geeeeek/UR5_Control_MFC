#include "Common.h"
#include "pch.h"
BOOL WinSockInit()
{
	// 一步打开网络库并校验版本
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaMsg;
	int iResWsaStart = WSAStartup(wVersion, &wsaMsg);
	CString tipMsg;

	if (0 != iResWsaStart)
	{
		switch (iResWsaStart)
		{
		case WSASYSNOTREADY:
			tipMsg.Format(_T("打开网络库失败,请重启电脑或检测环境设置.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAVERNOTSUPPORTED:
			tipMsg.Format(_T("打开网络库失败,Socket版本号不匹配.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEINPROGRESS:
			tipMsg.Format(_T("打开网络库失败,程序阻塞,请重启软件.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEPROCLIM:
			tipMsg.Format(_T("打开网络库失败,请关掉一些不必要的软件，为网络运行提供资源.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEFAULT:
			tipMsg.Format(_T("打开网络库失败,WSAStartup第二个参数为无效的指针.\n"));
			AfxMessageBox(tipMsg);
			break;
		}
		return FALSE;
	}

	// 校验版本库
	if (2 != HIBYTE(wsaMsg.wVersion) || 2 != LOBYTE(wsaMsg.wVersion))
	{
		tipMsg.Format(_T("系统提供的网络库版本不匹配！\n"));
		AfxMessageBox(tipMsg);

		WSACleanup();
		return FALSE;
	}

	return TRUE;
}
