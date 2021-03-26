#include "Common.h"
#include "pch.h"
BOOL WinSockInit()
{
	// һ��������ⲢУ��汾
	WORD wVersion = MAKEWORD(2, 2);
	WSADATA wsaMsg;
	int iResWsaStart = WSAStartup(wVersion, &wsaMsg);
	CString tipMsg;

	if (0 != iResWsaStart)
	{
		switch (iResWsaStart)
		{
		case WSASYSNOTREADY:
			tipMsg.Format(_T("�������ʧ��,���������Ի��⻷������.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAVERNOTSUPPORTED:
			tipMsg.Format(_T("�������ʧ��,Socket�汾�Ų�ƥ��.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEINPROGRESS:
			tipMsg.Format(_T("�������ʧ��,��������,���������.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEPROCLIM:
			tipMsg.Format(_T("�������ʧ��,��ص�һЩ����Ҫ�������Ϊ���������ṩ��Դ.\n"));
			AfxMessageBox(tipMsg);
			break;
		case WSAEFAULT:
			tipMsg.Format(_T("�������ʧ��,WSAStartup�ڶ�������Ϊ��Ч��ָ��.\n"));
			AfxMessageBox(tipMsg);
			break;
		}
		return FALSE;
	}

	// У��汾��
	if (2 != HIBYTE(wsaMsg.wVersion) || 2 != LOBYTE(wsaMsg.wVersion))
	{
		tipMsg.Format(_T("ϵͳ�ṩ�������汾��ƥ�䣡\n"));
		AfxMessageBox(tipMsg);

		WSACleanup();
		return FALSE;
	}

	return TRUE;
}
