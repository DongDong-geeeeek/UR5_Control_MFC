#include "Common.h"
#include "pch.h"
#define LINELENGTH 11
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

/*
 *	1.pEdit��ʾ��Ҫ��ʾ�ı༭���ָ��
 *	2.buf��ʾ��Ҫ��ʾ������(�ַ�����)�ĵ�ַ
 *	3.howmany��ʾ��Ҫ��ʾ���ֽ���,һ���ǽ��յ�����,����ʾ��������
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
		if ((i + 1) % LINELENGTH == 0)		// linelength��ʾ11���ֽڵ�����
		{
			recvText += "\r\n";
		}
	}
	recvText += "\r\n";						// �������ݰ��Ľ�β���ϻ��з�

	CString strDisp = NULL;
	strDisp += lastDisp;					// �����ϴε�����
	strDisp += recvText;					// ���ϱ��ε�����
	pEdit->SetWindowTextW(strDisp);			// ��ʾ���༭��
	
	// �����۽���ĩβ
	int nLength = pEdit->GetWindowTextLengthW();
	pEdit->SetSel(nLength, nLength, FALSE);
	pEdit->SetFocus();

	lastDisp = recvText;
}
