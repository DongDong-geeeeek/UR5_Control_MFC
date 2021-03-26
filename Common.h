#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


/*打开网络库并校验版本*/
BOOL WinSockInit();

/*
 *	1.功能 :显示ASCII码流到某个编辑框
 *	2.参数1:pEdit	编辑框指针
 *	3.参数2:buf		待显数据地址
 *	4.参数3:howmany	待显数据量,以字节为单位
 */ 
void DispASCIIToEdit(CEdit *pEdit, unsigned char* buf, int howmany);

/*
 *	1.功能 :获取编辑框中的字符串后并转化为可以机械臂可以认识的命令格式
 *	2.参数1:pEdit	编辑框指针
 *  3.返回 :格式化好的命令字符串指针
 *	4.注意 :不需要其他的参数,因为我们的数据来源是编辑框
 *			返回的是在堆上申请的内存空间,因此使用完之后
 *			务必需要进行delete[] 释放内存空间
 */
char* GetStringFromEdit(CEdit *pEdit, int &iLen);