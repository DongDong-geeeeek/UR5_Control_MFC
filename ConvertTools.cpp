#include "pch.h"
#include "ConvertTools.h"


void ConvertTools::Reverse(char * resource, int start, int size)
{
	char* temp = new char[size];
	memset(temp, '\0', size);
	char *begin = resource + start;
	char *end = resource + start + size;// 索引默认从0开始,因此最后一个字节不属于目标字节

	int	offset = size;
	
	for (begin; begin < end; begin++)
	{
		// 从temp的末端开始赋值
		temp[offset - 1] = *begin;
		offset--;
	}
	memcpy(resource + start, temp, size);

	delete[]temp;
	return;
}

int ConvertTools::BytesToInt(const char * Res, int start)
{
	int iResult = 0;
	char * pResuChar = (char *)&iResult;
	// i = 0、1、2、3
	for (int i = 0; i < 4; i++)
	{
		pResuChar[i] = *(Res + start + i);
	}
	return iResult;
}

float ConvertTools::BytesToFloat(const char * Res, int start)
{
	float fResult = 0.0;
	char * pResuChar = (char *)&fResult;

	for (int i = 0; i < 4; i++)
	{
		pResuChar[i] = *(Res + start + i);
	}

	return fResult;
}

double ConvertTools::BytesToDouble(const char * Res, int start)
{
	double dResult = 0.0;
	char * pResultChar = (char*)&dResult;

	for (int i = 0; i < 8; i++)
	{
		pResultChar[i] = *(Res + start + i);
	}

	return dResult;
}

uint32_t ConvertTools::BytesToUint32_t(const char * Res, int start)
{
	uint32_t u32_Result = 0;
	char *pu32_ResultChar = (char *)&u32_Result;

	for (int i = 0; i < 8; i++)
	{
		pu32_ResultChar[i] = *(Res + start + i);
	}

	return u32_Result;
}

uint64_t ConvertTools::BytesToUint64_t(const char * Res, int start)
{
	uint64_t u64_Result = 0;
	char * pu64_ResultChar = (char *)&u64_Result;

	for (int i = 0; i < 8; i++)
	{
		pu64_ResultChar[i] = *(Res + start + i);
	}

	return u64_Result;
}
