#pragma once
#include "pch.h"
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")


/*������ⲢУ��汾*/
BOOL WinSockInit();

/*
 *	1.���� :��ʾASCII������ĳ���༭��
 *	2.����1:pEdit	�༭��ָ��
 *	3.����2:buf		�������ݵ�ַ
 *	4.����3:howmany	����������,���ֽ�Ϊ��λ
 */ 
void DispASCIIToEdit(CEdit *pEdit, unsigned char* buf, int howmany);

/*
 *	1.���� :��ȡ�༭���е��ַ�����ת��Ϊ���Ի�е�ۿ�����ʶ�������ʽ
 *	2.����1:pEdit	�༭��ָ��
 *  3.���� :��ʽ���õ������ַ���ָ��
 *	4.ע�� :����Ҫ�����Ĳ���,��Ϊ���ǵ�������Դ�Ǳ༭��
 *			���ص����ڶ���������ڴ�ռ�,���ʹ����֮��
 *			�����Ҫ����delete[] �ͷ��ڴ�ռ�
 */
char* GetStringFromEdit(CEdit *pEdit, int &iLen);