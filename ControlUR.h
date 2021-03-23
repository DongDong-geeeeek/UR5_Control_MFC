#pragma once
/*
 *	1.ControlUR类主要是对UR脚本的封装
 *  2.目的是可以通过调用C++的类方法实现对UR的控制
 *	3.上电、下电、移动等
 */
class ControlUR
{
	//上电
	void PowerOn();
	//下电
	void PowerOff();
};

