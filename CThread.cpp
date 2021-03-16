#include "pch.h"
#include "CThread.h"
CThread::CThread()
{
	m_bExit = FALSE;						// FALSE:线程停止状态;TRUE:线程运行状态
	m_dwParam = 0;							// 参数==0
	m_hThread = NULL;						// 线程句柄为空
}

CThread::~CThread()
{
	if (!m_bExit)
	{
		Stop();								// 通过调用类自己的方法进行停止进程
	}
}

void CThread::Startup()
{
	DWORD dwThreadID;						
	m_hThread = ::CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, this, 0, &dwThreadID);
	ASSERT(m_hThread);
	m_bExit = FALSE;						
}

void CThread::Stop()
{
	if (m_hThread)							
	{
		m_bExit = true;					
		::WaitForSingleObject(m_hThread, INFINITE);  // 等待线程m_hThread线程执行完毕,INFINITE表示对象被触发信号之后，该函数才会返回
		CloseHandle(m_hThread);			
		m_hThread = NULL;
	}
}

void CThread::SetThreadData(DWORD dwParam)	// 启动串口时调用该函数,传入的是串口对象的指针
{
	if (m_dwParam != dwParam)				
		m_dwParam = dwParam;
}

DWORD CThread::GetThreadData()
{
	return m_dwParam;
}

DWORD CThread::ThreadProc(LPVOID pParam)	
{
	CThread *pThis = (CThread*)pParam;		
	ASSERT(pThis);							// 若pThis为0,程序将弹出消息并暂停(一般用于调试)					
	while (!pThis->m_bExit)					// FALSE代表处于运行状态  
	{
		pThis->Run();						/* 运行进程,将运行任务抽象;可由继承自CThread类的子类去重载run()函数执行具体的任务,
											以实现CThraed类的通用性,可是这里调用的是父类的函数，执行的是子类的函数*/
	}
	pThis->m_bExit = TRUE;					/* 线程结束的时候是不是应该设置线程的状态为TRUE呢,保证线程退出的时候,m_bExit必定是TRUE,在这里似乎没有也可*/									   
	return TRUE;							
}

void CThread::Run()
{
	Sleep(100);
}