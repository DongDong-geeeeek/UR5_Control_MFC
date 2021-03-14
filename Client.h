#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
	/*使用默认构造函数和析构函数*/
	Client();
	// 设置友元类
	friend class CCtrlURobotDlg;
public:

	/* 
	 * 创建Socket,并附带默认参数
	 * 创建成功返回TRUE,否则返回FALSE
	 * 返回FALSE时,不主动关闭网络库
	 */ 
	BOOL CreatSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	
	/*
	 * 设置机械臂地址信息
	 */
	void SetRobortAddress(SOCKADDR_IN * address);

	/* 
	 * 连接到机械臂
	 * 连接成功返回TRUE,否则返回FALSE
	 * 连接失败会关闭套接字,但不主动关闭网络库
	 */
	BOOL ConnectToRobort();
	
	// 发送数据(还未写具体实现)
	int Send(SOCKET s, const char *buf, int len, int flags);
	
	// 接受数据(还未写具体实现)
	int Recv(SOCKET s, char *buf, int len, int flags);
	
	/* 
	 * 关闭Socket套接字
	 * 关闭成功返回TRUE,否则返回FALSE
	 */
	BOOL CloseSocket();

public:
	SOCKADDR_IN m_addressData;// 机械臂地址信息
	SOCKET m_socket;	// 套接字Socket
	CString tipMsg;		// 错误提示字符串
	BOOL m_flag;		// false 表示Socket无效,True表示Socket有效
};

