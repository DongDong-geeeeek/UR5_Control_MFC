/*
 *	1.CMDofUR5script类主要是对UR脚本的封装
 *	2.类方法返回的是复合机械臂要求的字符串命令
 *  3.使用方法:	先调用本类中的方法获取到希望的命令
 *	4.			然后调用Client中的Send()方法发送命令
 */
#pragma once
class CMDofUR5script
{
	/*
	 *	1.调用PowerOn函数后,需要调用Client中的Send函数
	 *	2.Client在对话框类中,因此可以对话框的回调函数中进行调用
	 *	3.那或许在可以调用工具函数时,返回的是已经格式化好的命令
	 *	4.再手动去调用Send既可(我觉得这样可能更加灵活一点)
	 */


	/*
	 *	1. 返回值为接收格式化后的命令的地址
	 *	2. 注意: 格式化后的命令为ASCII码的多字编码形式(C风格的字符串)
	 *	3. 参数为一个无符号整型的引用,用于保存结果命令字符串的长度
	 *	4. 因为在调用Send时,需要给出howmany参数,因此本函数的参数1就是为howmany服务的
	 */
public:
	char * CMDPowerOn(unsigned int &n);
	//下电
	char * CMDPowerOff(unsigned int &n);
};

