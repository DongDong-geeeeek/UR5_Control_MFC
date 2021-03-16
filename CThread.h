#include<afxwin.h>
#pragma once
// Thread线程类
// 一个Thread类是对这个线程的操作处理以及其应该拥有的数据的集合
// 成员方法:	1)线程启动			2)线程停止		3)设置线程的参数	   
//			4)获取线程的参数		5)线程处理函数   6)运行线程
// 数据变量:	1)线程句柄			2)退出标志位		3)线程参数
// 创建一个线程类基于CWinThread
class CThread
{
public:
	CThread();
	~CThread();

	//创建一个线程         立即去执行线程处理函数
	//获得其线程句柄    存进类的成员变量m_hThread
	//设置线程退出状态 FALSE
	void Startup();								// 线程的启动

	//设置线程退出状态 TRUE
	//等待线程处理完毕后,归还句柄资源给系统
	//设置句柄为NULL
	void Stop();								// 线程的停止

public:
	virtual void SetThreadData(DWORD dwParam);	// 设置线程的参数
	virtual DWORD GetThreadData();				// 获得线程的参数
	void Run();							

public:
	static DWORD ThreadProc(LPVOID pParam);		// 备注:线程处理函数必须是静态函数

public:	
	HANDLE  m_hThread;							
	BOOL m_bExit;								
	DWORD m_dwParam;							// 线程参数变量，一般用来存储串口对象的指针
};

