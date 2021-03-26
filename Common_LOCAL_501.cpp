#include "Common.h"
#include "pch.h"
#define LINELENGTH 11
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

/*
 *	1.pEdit表示需要显示的编辑框的指针
 *	2.buf表示需要显示的数据(字符数组)的地址
 *	3.howmany表示需要显示的字节数,一般是接收到多少,就显示多少数据
 */
void DispASCIIToEdit(CEdit *pEdit,unsigned char* buf, int howmany)
{
	static CString lastDisp = NULL;
	CString recvText = NULL;

	CString recvTemp = NULL;
	for (int i = 0; i < howmany; i++)
	{
		recvTemp.Empty();
		recvTemp.Format(_T("%02X\t"), buf[i]);
		recvText.Append(recvTemp);
		if ((i + 1) % LINELENGTH == 0)		// linelength显示11个字节的数据
		{
			recvText += "\r\n";
		}
	}
	recvText += "\r\n";						// 整个数据包的结尾加上换行符

	CString strDisp = NULL;
	strDisp += lastDisp;					// 加上上次的数据
	strDisp += recvText;					// 加上本次的数据
	pEdit->SetWindowTextW(strDisp);			// 显示到编辑框
	
	// 将光标聚焦于末尾
	int nLength = pEdit->GetWindowTextLengthW();
	pEdit->SetSel(nLength, nLength, FALSE);
	pEdit->SetFocus();

	lastDisp = recvText;
}
