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

/*
 * 1.��ΪClient�ĳ�Ա����
 * 2.���͵�Socket����ֻ����Client�ڲ���Socket
 * 3.API ����send��flags����ʹ��Ĭ�ϵ�0, �Լ�Client::Send()�ĵ���
 * 4.����1����Ҫ���͵����ݵ�ַ
 * 4.����2��howmany��ʾ��Ҫ���͵�������,��λ���ֽ���
 * 5.����ֵ���ѷ���������int
 */
int Client::Send(const char * buf, int howmany)
{
	/*ͬ1400�ֽڽ��бȽ�,���С��1400,ֱ��һ�η���; �������1400,�ֶ�η���*/
	if (howmany <= 1400)
	{
		int ret = 0;
		while (ret < howmany)							// �����жϱ��η����Ƿ�����
		{
			int iResSend = send(m_socket, buf + ret, howmany - ret, 0);
			if (iResSend == SOCKET_ERROR)				// ��ʾ���ͳ��ִ���
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					continue;
				}
				else
				{
					return -1; // �������ݳ���
				}
			}
			else
			{
				ret += iResSend;						// �ѷ���ret�ֽڵ�����
			}
		}


		return ret;
	}
	else
	{
		int times = howmany / 1400;			// �ȷ���times��1400�ֽڵ�����
		int remainder = howmany % 1400;		// �ٷ���1��remainder�ֽڵ�����

		int sumOfSend = 0;
		for (int i = 0; i < times; i++)
		{
			// send()
			int ret = 0;
			while (ret < 1400)
			{
				int iResSend = send(m_socket, buf + i * 1400 + ret, 1400 - ret, 0);
				if (iResSend == SOCKET_ERROR)				
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						continue;
					}
					else
					{
						return -1;// �������ݳ���
					}
				}
				else
				{
					ret += iResSend;						
				}
			}

			sumOfSend += ret;
		}
		
		if (remainder > 0)
		{
			// send()
			int ret = 0;
			while (ret < remainder)
			{
				int iResSend = send(m_socket, buf + times * 1400 + ret, remainder - ret, 0);
				if (iResSend == SOCKET_ERROR)
				{
					if (WSAGetLastError() == WSAEWOULDBLOCK)
					{
						continue;
					}
					else
					{
						return -1;// �������ݳ���
					}
				}
				else
				{
					ret += iResSend;
				}
			}

			sumOfSend += ret;
		}

		return sumOfSend;
	}
}

/*	
	ʹ��recvѭ����������
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

