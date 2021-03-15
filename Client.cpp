#include "pch.h"
#include "Client.h"

/*
 *	1.Client���в�������ʾ���,����ʾ�����ڶԻ���
 *	2.Client������Ŀ���Ǿ��������ڲ�����ֻ����BOOL��
 *	3.Client���ڲ���һ��Socket����
 *  4.Ϊ�˷�ֹ�ظ��ĸ�ֵ��ʶ��,����Client�ڲ����ı��ʶ��,������߽����޸�
 *	5.ȷ��Client��ķ����Ĳ������ܼ�,�������
 */
Client::Client()
{
	m_flag = FALSE;
	m_conSucc = FALSE;
}

BOOL Client::CreatSocket(int af, int type, int protocol)
{
	m_socket = socket(af, type, protocol);
	if (INVALID_SOCKET == m_socket)
	{
		return FALSE;
	}
	return TRUE;
	/*
	 * socket����Ϊ������
	 * unsigned long on = 1;
	 * ioctlsocket(m_socket, FIONBIO, &on);
	 */
}

VOID Client::SetRobortAddress(SOCKADDR_IN * address)
{
	m_addressData.sin_addr = address->sin_addr;
	m_addressData.sin_family = address->sin_family;
	m_addressData.sin_port = address->sin_port;
}

BOOL Client::ConnectToRobort()
{
	if (SOCKET_ERROR == connect(m_socket, (struct sockaddr *)&m_addressData, sizeof(m_addressData)))
	{
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

