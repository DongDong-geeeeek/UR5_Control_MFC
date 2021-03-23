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

/*
 * 1.作为Client的成员方法
 * 2.发送的Socket对象只能是Client内部的Socket
 * 3.API 函数send的flags参数使用默认的0, 以简化Client::Send()的调用
 * 4.参数1是需要发送的数据地址
 * 4.参数2是howmany表示需要发送的数据量,单位是字节数
 * 5.返回值是已发送数据量int
 */
int Client::Send(const char * buf, int howmany)
{
	/*同1400字节进行比较,如果小于1400,直接一次发完; 如果大于1400,分多次发送*/
	if (howmany <= 1400)
	{
		int ret = 0;
		while (ret < howmany)							// 用于判断本次发送是否完整
		{
			int iResSend = send(m_socket, buf + ret, howmany - ret, 0);
			if (iResSend == SOCKET_ERROR)				// 表示发送出现错误
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					continue;
				}
				else
				{
					return -1; // 发送数据出错
				}
			}
			else
			{
				ret += iResSend;						// 已发送ret字节的数据
			}
		}


		return ret;
	}
	else
	{
		int times = howmany / 1400;			// 先发送times次1400字节的数据
		int remainder = howmany % 1400;		// 再发送1次remainder字节的数据

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
						return -1;// 发送数据出错
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
						return -1;// 发送数据出错
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
	使用recv循环接收数据
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

