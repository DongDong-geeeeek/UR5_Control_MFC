#include<afxwin.h>
#pragma once
// Thread�߳���
// һ��Thread���Ƕ�����̵߳Ĳ��������Լ���Ӧ��ӵ�е����ݵļ���
// ��Ա����:	1)�߳�����			2)�߳�ֹͣ		3)�����̵߳Ĳ���	   
//			4)��ȡ�̵߳Ĳ���		5)�̴߳�����   6)�����߳�
// ���ݱ���:	1)�߳̾��			2)�˳���־λ		3)�̲߳���
// ����һ���߳������CWinThread
class CThread
{
public:
	CThread();
	~CThread();

	//����һ���߳�         ����ȥִ���̴߳�����
	//������߳̾��    �����ĳ�Ա����m_hThread
	//�����߳��˳�״̬ FALSE
	void Startup();								// �̵߳�����

	//�����߳��˳�״̬ TRUE
	//�ȴ��̴߳�����Ϻ�,�黹�����Դ��ϵͳ
	//���þ��ΪNULL
	void Stop();								// �̵߳�ֹͣ

public:
	virtual void SetThreadData(DWORD dwParam);	// �����̵߳Ĳ���
	virtual DWORD GetThreadData();				// ����̵߳Ĳ���
	void Run();							

public:
	static DWORD ThreadProc(LPVOID pParam);		// ��ע:�̴߳����������Ǿ�̬����

public:	
	HANDLE  m_hThread;							
	BOOL m_bExit;								
	DWORD m_dwParam;							// �̲߳���������һ�������洢���ڶ����ָ��
};

