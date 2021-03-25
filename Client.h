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
	
	/*
	 * 1.��ΪClient�ĳ�Ա����
	 * 2.���͵�Socket����ֻ����Client�ڲ���Socket
	 * 3.API ����send��flags����ʹ��Ĭ�ϵ�0, �Լ�Client::Send()�ĵ���
	 * 4.����1����Ҫ���͵����ݵ�ַ
	 * 5.����2��howmany��ʾ��Ҫ���͵�������,��λ���ֽ���
	 * 6.����ֵ���ѷ���������int
     */
	int Send(const char *buf, int len);
	
	/*
	 * ʹ��recvѭ����������
	 * �������û�н�����,������
	 * ���recv����ʱ��������,��ô������һ��ѭ��,���
	 * ���������͵Ĵ���,��ú�����ǰ��ֹ,������ʾ
	 */
	int Recv(char *buf, int howmany);

public:
	SOCKADDR_IN m_addressData;// ��е�۵�ַ��Ϣ
	SOCKET m_socket;	// �׽���Socket
	BOOL m_flag;		// false ��ʾSocket��Ч,True��ʾSocket��Ч
	BOOL m_conSucc;		// ��ʶʱ�����ӳɹ�
	HANDLE m_hThread;	// �߳̾��
};

