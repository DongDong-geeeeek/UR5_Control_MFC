#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
	
	
public:
	/*ʹ��Ĭ�Ϲ��캯������������*/
	Client();

	/* 
	 * ����Socket,������Ĭ�ϲ���
	 * �����ɹ�����TRUE,���򷵻�FALSE
	 * ����FALSEʱ,�������ر������
	 */ 
	BOOL CreatSocket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
	
	/*
	 * ���û�е�۵�ַ��Ϣ
	 */
	void SetRobortAddress(SOCKADDR_IN * address);

	/* 
	 * ���ӵ���е��
	 * ���ӳɹ�����TRUE,���򷵻�FALSE
	 * ����ʧ�ܲ���ر��׽��ֺ������
	 */
	BOOL ConnectToRobort();
	
	// ��������(��δд����ʵ��)
	int Send(const char *buf, int len);
	
	// ��������(��δд����ʵ��)
	int Recv(char *buf, int howmany);

public:
	SOCKADDR_IN m_addressData;// ��е�۵�ַ��Ϣ
	SOCKET m_socket;	// �׽���Socket
	BOOL m_flag;		// false ��ʾSocket��Ч,True��ʾSocket��Ч
	BOOL m_conSucc;		// ��ʶʱ�����ӳɹ�

	HANDLE m_hThread;	// �߳̾��
};

