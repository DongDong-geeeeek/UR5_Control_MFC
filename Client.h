#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
	
	
public:
	/*使用默认构造函数和析构函数*/
	Client();

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
	 * 连接失败不会关闭套接字和网络库
	 */
	BOOL ConnectToRobort();
	
	/*
	 * 1.作为Client的成员方法
	 * 2.发送的Socket对象只能是Client内部的Socket
	 * 3.API 函数send的flags参数使用默认的0, 以简化Client::Send()的调用
	 * 4.参数1是需要发送的数据地址
	 * 5.参数2是howmany表示需要发送的数据量,单位是字节数
	 * 6.返回值是已发送数据量int
     */
	int Send(const char *buf, int len);
	
	/*
	 * 使用recv循环接收数据
	 * 如果数据没有接收完,不返回
	 * 如果recv接收时发生阻塞,那么继续下一次循环,如果
	 * 是其他类型的错误,则该函数提前终止,做出提示
	 */
	int Recv(char *buf, int howmany);

public:
	SOCKADDR_IN m_addressData;// 机械臂地址信息
	SOCKET m_socket;	// 套接字Socket
	BOOL m_flag;		// false 表示Socket无效,True表示Socket有效
	BOOL m_conSucc;		// 标识时候连接成功
	HANDLE m_hThread;	// 线程句柄
};

