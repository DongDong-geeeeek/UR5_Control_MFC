#pragma once
#include "stdint.h"
/*
 *	1.ConvertTools 类本质上是一个方法工具族
 *	2.暂时没有成员变量,只有成员方法
 *	3.主要实现的大端存储到小端存储、Bytes到int\double\float\uint64_t\uint32_t等类型的数值抓换
 */
class ConvertTools
{
public:
	/*	功能 :反转数组中的howmany个连续字节
	   	参数1:char* 数组名---数据的起始地址
		参数2:int   反转起始字节:相对于数组起始地址的偏移量
		参数3:int   反转长度
		例如:
		数组array[8] = [0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18];
		需要反转的是0x13, 0x14, 0x15, 0x16这4个字节
		期待的结果是 array[8] = [0x11, 0x12, 0x16, 0x15, 0x14, 0x13, 0x17, 0x18];
		那么参数1: Res = array; 参数2: start = 2; 参数3: houmany = 4;
	*/
	void Reverse(char * Res, int start, int howmany);
	/*
		功能 :将4个字节转换为int
		参数1:char*--- 数组名\数据的起始地址
		参数2:int  --- 待转换的4个字节中的第一个字节相对于数组头的偏移量
		例如:
		数组Res = [0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18]
		若待转换的字节是0x13,0x14,0x15,0x16
		那么参数start = 2
		因为是转换为int 所以默认是转换4个字节,因此不需要这个长度参数了
	*/
	int BytesToInt(const char * Res, int start);
	/*注释请参考BytesToInt*/
	float BytesToFloat(const char * Res, int start);
	/*注释请参考BytesToInt*/
	double BytesToDouble(const char * Res, int start);
	/*uin32_t 也即 unsigned int*/
	uint32_t BytesToUint32_t(const char * Res, int start);
	/*注释请参考BytesToInt*/
	uint64_t BytesToUint64_t(const char * Res, int start);

public:
};

