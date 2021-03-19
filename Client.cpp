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

	unsigned long on = 1;
	ioctlsocket(m_socket, FIONBIO, &on);
	return TRUE;
	
	 //socket����Ϊ������ 
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
		if (WSAEWOULDBLOCK == WSAGetLastError())
		{
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

int Client::Send(SOCKET s, const char * buf, int len, int flags)
{
	return 0;
}

/*	ʹ��recvѭ����������
	�������û�н�����,������
	���recv����ʱ��������,��ô������һ��ѭ��,���
	���������͵Ĵ���,��ú�����ǰ��ֹ,������ʾ
*/

int Client::Recv(char * buf, int howmany)
{
	char * chartemp = new char[howmany];
	memset(chartemp, '\0', howmany);

	int ret = 0;
	int temp = 0;
	while (ret < howmany)
	{
		temp = recv(m_socket, chartemp + ret, howmany - ret, 0);
		if (temp == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				continue;
			}
			else if(WSAGetLastError() == WSAENOTSOCK)
			{
				break;
			}
			else
			{
				CString tipMsg = NULL;
				tipMsg.Format(_T("recv��������,�������Ϊ %d\n"), WSAGetLastError());
				AfxMessageBox(tipMsg);
				break;
			}
		}
		ret += temp;
	}

	memcpy(buf, chartemp, ret);

	delete[] chartemp;
	return ret;
}

