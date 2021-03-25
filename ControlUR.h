#pragma once
/*
 *	1.ControlUR类主要是对UR脚本的封装
 *  2.目的是可以通过调用C++的类方法实现对UR的控制
 *	3.上电、下电、移动等
 */
class ControlUR
{
	/*
	 *	1.调用PowerOn函数时,可以调用到Client中的Send函数
	 *	2.Client在对话框类中,因此可以对话框的回调函数中进行调用
	 *	3.那或许可以调用工具函数时,返回的是已经格式化好的命令
	 *	4.再手动去调用Send既可(我觉得这样可能更加灵活一点)
	 */
	void PowerOn();
	//下电
	void PowerOff();
};

