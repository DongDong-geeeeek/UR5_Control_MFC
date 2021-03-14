#include "pch.h"
#include "Client.h"


Client::Client()
{
	m_flag = FALSE;
}

BOOL Client::CreatSocket(int af, int type, int protocol)
{
	m_socket = socket(af, type, protocol);

	if (INVALID_SOCKET == m_socket)
	{
		tipMsg.Format(_T("�����ͻ���Socketʧ�ܣ��������Ϊ%d\n"), WSAGetLastError());
		AfxMessageBox(tipMsg);

		return FALSE;
	}

	m_flag = TRUE;
	return TRUE;
}

VOID Client::SetRobortAddress(SOCKADDR_IN * address)
{
	m_addressData.sin_addr = address->sin_addr;
	m_addressData.sin_family = address->sin_family;
	m_addressData.sin_port = address->sin_port;
}

BOOL Client::ConnectToRobort()
{
	int a = connect(m_socket, (struct sockaddr *)&m_addressData, sizeof(m_addressData));
	if (SOCKET_ERROR == a)
	{
		tipMsg.Format(_T("���ӵ���е��ʧ�ܣ��������Ϊ %d\n"), WSAGetLastError());
		AfxMessageBox(tipMsg);
		// �ر��׽���
		CloseSocket();
		return FALSE;
	}

	return TRUE;
}

int Client::Send(SOCKET s, const char * buf, int len, int flags)
{
	return 0;
}

int Client::Recv(SOCKET s, char * buf, int len, int flags)
{
	return 0;
}

BOOL Client::CloseSocket()
{
	// �ȹرն��׽����շ�����
	if (0!= shutdown(m_socket, 2))
	{
		tipMsg.Format(_T("shutdown����ִ��ʧ��,�������Ϊ %d"),WSAGetLastError());
		AfxMessageBox(tipMsg);
		return FALSE;
	}
	// ���ͷ��׽���
	if (0!= closesocket(m_socket))
	{
		tipMsg.Format(_T("win32API closesocket����ִ��ʧ��,�������Ϊ %d"), WSAGetLastError());
		AfxMessageBox(tipMsg);
		return FALSE;
	}
	m_flag = FALSE;

	return TRUE;
}
