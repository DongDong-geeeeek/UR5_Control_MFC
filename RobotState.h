/*
 *	注意:
 *	1. 此RobotState专用于从机械臂30003端口的数据解析
 *	2. 实验室机械臂为3.10版本的软件,但数据包大小相同,解析方式一样
 *	3. 在类外,如需要获取数据包的大小,请访问成员变量而不是访问方法
 */
#pragma once
#include "ConvertTools.h"

// 关节的目标位置结构体
struct st_q_target_pos
{
	double q_target_1;
	double q_target_2;
	double q_target_3;
	double q_target_4;
	double q_target_5;
	double q_target_6;
};
// 关节的目标速度
struct st_qd_target_vel
{
	double qd_target_1;
	double qd_target_2;
	double qd_target_3;
	double qd_target_4;
	double qd_target_5;
	double qd_target_6;
};
// 关节的目标加速度
struct st_qdd_target_acc
{
	double qdd_target_1;
	double qdd_target_2;
	double qdd_target_3;
	double qdd_target_4;
	double qdd_target_5;
	double qdd_target_6;
};
// 关节的实际位置_结构体
struct st_q_actual_pos
{
	double q_actual_1;
	double q_actual_2;
	double q_actual_3;
	double q_actual_4;
	double q_actual_5;
	double q_actual_6;
};
// 关节实际速度
struct st_qd_actual_vel
{
	double qd_actual_1;
	double qd_actual_2;
	double qd_actual_3;
	double qd_actual_4;
	double qd_actual_5;
	double qd_actual_6;
};
// 笛卡尔坐标系中工具的实际坐标
struct st_tool_actual_pos
{
	double tl_actual_p_x;		// x坐标
	double tl_actual_p_y;		// y坐标
	double tl_actual_p_z;		// z坐标
	double tl_actual_P_rx;
	double tl_actual_p_ry;
	double tl_actual_p_rz;
};
// 笛卡尔坐标系中TCP的实际速度
struct st_tcp_actual_vel
{
	double tcp_actual_v_x;
	double tcp_actual_v_y;
	double tcp_actual_v_z;
	double tcp_actual_v_rx;
	double tcp_actual_v_ry;
	double tcp_actual_v_rz;
};
// 笛卡尔坐标系中工具的目标坐标Tool vector target
struct st_tool_target_pos
{
	double tl_target_p_x;
	double tl_target_p_y;
	double tl_target_p_z;
	double tl_target_p_rx;
	double tl_target_p_ry;
	double tl_target_p_rz;
};
// 笛卡尔坐标系中TCP的目标速度TCP speed target
struct st_tcp_target_vel
{
	double tcp_target_v_x;
	double tcp_target_v_y;
	double tcp_target_v_z;
	double tcp_target_v_rx;
	double tcp_target_v_ry;
	double tcp_target_v_rz;
};
// 关节控制模式
struct st_JointControlMode
{
	double ControlMode_J1;
	double ControlMode_J2;
	double ControlMode_J3;
	double ControlMode_J4;
	double ControlMode_J5;
	double ControlMode_J6;
};
// 肘部位置
struct st_ElbowPos
{
	double ElbowPos_1;
	double ElbowPos_2;
	double ElbowPos_3;
};
// 肘部速度
struct st_ElbowVel
{
	double ElbowVel_1;
	double ElbowVel_2;
	double ElbowVel_3;
};

class RobotState
{
public:
	RobotState();
	void RS_UpDateData(char * pChar);
	double RS_GetTime(BOOL b_flag);

	st_q_target_pos RS_GetJointTargetPos(BOOL b_flag);
	st_qd_target_vel RS_GetJointTargetVel(BOOL b_flag);
	st_qdd_target_acc RS_GetJointTargetAcc(BOOL b_flag);

	st_q_actual_pos RS_GetJointActualPos(BOOL b_flag);
	st_qd_actual_vel RS_GetJointActualVel(BOOL b_flag);

	st_tool_actual_pos RS_GetToolActualPos(BOOL b_flag);
	st_tcp_actual_vel RS_GetTcpActualVel(BOOL b_flag);
	st_tool_target_pos RS_GetToolTargetPos(BOOL b_flag);
	st_tcp_target_vel RS_GetToolTargetVel(BOOL b_flag);

	double RS_GetRobotMode(BOOL b_flag);
	st_JointControlMode RS_GetJointCtrlMode(BOOL b_flag);

	double RS_GetSafetyMode(BOOL b_flag);
	double RS_GetProgState(BOOL b_flag);
	st_ElbowPos RS_GetElbowPos(BOOL b_flag);
	st_ElbowVel RS_GetElbowVel(BOOL b_flag);

	double RS_GetSafetyStatus(BOOL b_flag);

public:
	int m_iPackageSize;					// 存储数据包的大小,可在类外访问

private:
	int RS_GetPackageSize();			// 数据包大小方法只能在类内部使用

private:
	ConvertTools m_cTool;				// ConvertTools类成员变量
	char *p_aRobotData;					// 指向PackageData的地址指针
};