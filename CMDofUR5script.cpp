#include "pch.h"
#include "CMDofUR5script.h"

char * CMDofUR5script::CMDPowerOn(unsigned int &n)
{
	// ��ʽ������Ҫ������
	char *cmdPowerOn = "power on\n";					// C����ַ���---null��β
	n = strlen(cmdPowerOn) + 1;							// strlen������null,�����Ҫ��nullҲ����һ���ֽڵĿռ�
	char * pcmdAddress = new char[n];					// n���Ǹ�ʽ���������������Ҫ�ĳ���
	/*�������еĲ���null���ַ���������pcmdAddressλ��,��ΪpcmdAddress����ʣ��,���ݺ�������,���Զ���null*/
	strncpy_s(pcmdAddress, n, cmdPowerOn, n - 1);		
	return pcmdAddress;
}

char * CMDofUR5script::CMDPowerOff(unsigned int &n)
{
	char * cmdPowerOff = "power off\n";
	n = strlen(cmdPowerOff) + 1;
	char *pcmdAddress = new char[n];
	strncpy_s(pcmdAddress, n, cmdPowerOff, n - 1);
	return pcmdAddress;
}
