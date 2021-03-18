#include "pch.h"
#include "CThread.h"
CThread::CThread()
{
	m_bExit = FALSE;						// FALSE:�߳�ֹͣ״̬;TRUE:�߳�����״̬
	m_dwParam = 0;							// ����==0
	m_hThread = NULL;						// �߳̾��Ϊ��
}

CThread::~CThread()
{
	if (!m_bExit)
	{
		Stop();								// ͨ���������Լ��ķ�������ֹͣ����
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
		::WaitForSingleObject(m_hThread, INFINITE);  // �ȴ��߳�m_hThread�߳�ִ�����,INFINITE��ʾ���󱻴����ź�֮�󣬸ú����Ż᷵��
		CloseHandle(m_hThread);			
		m_hThread = NULL;
	}
}

void CThread::SetThreadData(DWORD dwParam)	// ��������ʱ���øú���,������Ǵ��ڶ����ָ��
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
	ASSERT(pThis);							// ��pThisΪ0,���򽫵�����Ϣ����ͣ(һ�����ڵ���)					
	while (!pThis->m_bExit)					// FALSE����������״̬  
	{
		pThis->Run();						/* ���н���,�������������;���ɼ̳���CThread�������ȥ����run()����ִ�о��������,
											��ʵ��CThraed���ͨ����,����������õ��Ǹ���ĺ�����ִ�е�������ĺ���*/
	}
	pThis->m_bExit = TRUE;					/* �߳̽�����ʱ���ǲ���Ӧ�������̵߳�״̬ΪTRUE��,��֤�߳��˳���ʱ��,m_bExit�ض���TRUE,�������ƺ�û��Ҳ��*/									   
	return TRUE;							
}

void CThread::Run()
{
	Sleep(100);
}