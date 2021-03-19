#include "pch.h"
#include "Client.h"

/*
 *	1.Client类中不出现提示语句,把提示语句放在对话框
 *	2.Client类抽象的目的是尽量让其内部方法只返回BOOL量
 *	3.Client类内部有一个Socket对象
 *  4.为了防止重复的赋值标识符,所以Client内部不改变标识符,放在外边进行修改
 *	5.确保Client类的方法的参数都很简单,方便调用
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
	
	 //socket设置为非阻塞 
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

/*	使用recv循环接收数据
	如果数据没有接收完,不返回
	如果recv接收时发生阻塞,那么继续下一次循环,如果
	是其他类型的错误,则该函数提前终止,做出提示
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
				tipMsg.Format(_T("recv函数出错,错误代码为 %d\n"), WSAGetLastError());
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

