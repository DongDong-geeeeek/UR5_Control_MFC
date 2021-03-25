#pragma once
#include "stdint.h"
/*
 *	1.ConvertTools �౾������һ������������
 *	2.��ʱû�г�Ա����,ֻ�г�Ա����
 *	3.��Ҫʵ�ֵĴ�˴洢��С�˴洢��Bytes��int\double\float\uint64_t\uint32_t�����͵���ֵץ��
 */
class ConvertTools
{
public:
	/*	���� :��ת�����е�howmany�������ֽ�
	   	����1:char* ������---���ݵ���ʼ��ַ
		����2:int   ��ת��ʼ�ֽ�:�����������ʼ��ַ��ƫ����
		����3:int   ��ת����
		����:
		����array[8] = [0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18];
		��Ҫ��ת����0x13, 0x14, 0x15, 0x16��4���ֽ�
		�ڴ��Ľ���� array[8] = [0x11, 0x12, 0x16, 0x15, 0x14, 0x13, 0x17, 0x18];
		��ô����1: Res = array; ����2: start = 2; ����3: houmany = 4;
	*/
	void Reverse(char * Res, int start, int howmany);
	/*
		���� :��4���ֽ�ת��Ϊint
		����1:char*--- ������\���ݵ���ʼ��ַ
		����2:int  --- ��ת����4���ֽ��еĵ�һ���ֽ����������ͷ��ƫ����
		����:
		����Res = [0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18]
		����ת�����ֽ���0x13,0x14,0x15,0x16
		��ô����start = 2
		��Ϊ��ת��Ϊint ����Ĭ����ת��4���ֽ�,��˲���Ҫ������Ȳ�����
	*/
	int BytesToInt(const char * Res, int start);
	/*ע����ο�BytesToInt*/
	float BytesToFloat(const char * Res, int start);
	/*ע����ο�BytesToInt*/
	double BytesToDouble(const char * Res, int start);
	/*uin32_t Ҳ�� unsigned int*/
	uint32_t BytesToUint32_t(const char * Res, int start);
	/*ע����ο�BytesToInt*/
	uint64_t BytesToUint64_t(const char * Res, int start);

public:
};

