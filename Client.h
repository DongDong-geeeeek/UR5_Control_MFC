#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class Client
{
	/*ʹ��Ĭ�Ϲ��캯������������*/
	Client();
	// ������Ԫ��
	friend class CCtrlURobotDlg;
public:

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
	 * ����ʧ�ܻ�ر��׽���,���������ر������
	 */
	BOOL ConnectToRobort();
	
	// ��������(��δд����ʵ��)
	int Send(SOCKET s, const char *buf, int len, int flags);
	
	// ��������(��δд����ʵ��)
	int Recv(SOCKET s, char *buf, int len, int flags);
	
	/* 
	 * �ر�Socket�׽���
	 * �رճɹ�����TRUE,���򷵻�FALSE
	 */
	BOOL CloseSocket();

public:
	SOCKADDR_IN m_addressData;// ��е�۵�ַ��Ϣ
	SOCKET m_socket;	// �׽���Socket
	CString tipMsg;		// ������ʾ�ַ���
	BOOL m_flag;		// false ��ʾSocket��Ч,True��ʾSocket��Ч
};

