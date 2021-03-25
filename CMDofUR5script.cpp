#include "pch.h"
#include "CMDofUR5script.h"

char * CMDofUR5script::CMDPowerOn(unsigned int &n)
{
	// 格式化好需要的命令
	char *cmdPowerOn = "power on\n";					// C风格字符串---null结尾
	n = strlen(cmdPowerOn) + 1;							// strlen不计算null,因此需要给null也申请一个字节的空间
	char * pcmdAddress = new char[n];					// n就是格式化后的命令真正需要的长度
	/*将命令中的不带null的字符都拷贝到pcmdAddress位置,因为pcmdAddress仍有剩余,根据函数特性,会自动补null*/
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
