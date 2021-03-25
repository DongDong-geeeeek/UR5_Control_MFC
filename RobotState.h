/*
 *	ע��:
 *	1. ��RobotStateר���ڴӻ�е��30003�˿ڵ����ݽ���
 *	2. ʵ���һ�е��Ϊ3.10�汾�����,�����ݰ���С��ͬ,������ʽһ��
 *	3. ������,����Ҫ��ȡ���ݰ��Ĵ�С,����ʳ�Ա���������Ƿ��ʷ���
 */
#pragma once
#include "ConvertTools.h"

// �ؽڵ�Ŀ��λ�ýṹ��
struct st_q_target_pos
{
	double q_target_1;
	double q_target_2;
	double q_target_3;
	double q_target_4;
	double q_target_5;
	double q_target_6;
};
// �ؽڵ�Ŀ���ٶ�
struct st_qd_target_vel
{
	double qd_target_1;
	double qd_target_2;
	double qd_target_3;
	double qd_target_4;
	double qd_target_5;
	double qd_target_6;
};
// �ؽڵ�Ŀ����ٶ�
struct st_qdd_target_acc
{
	double qdd_target_1;
	double qdd_target_2;
	double qdd_target_3;
	double qdd_target_4;
	double qdd_target_5;
	double qdd_target_6;
};
// �ؽڵ�ʵ��λ��_�ṹ��
struct st_q_actual_pos
{
	double q_actual_1;
	double q_actual_2;
	double q_actual_3;
	double q_actual_4;
	double q_actual_5;
	double q_actual_6;
};
// �ؽ�ʵ���ٶ�
struct st_qd_actual_vel
{
	double qd_actual_1;
	double qd_actual_2;
	double qd_actual_3;
	double qd_actual_4;
	double qd_actual_5;
	double qd_actual_6;
};
// �ѿ�������ϵ�й��ߵ�ʵ������
struct st_tool_actual_pos
{
	double tl_actual_p_x;		// x����
	double tl_actual_p_y;		// y����
	double tl_actual_p_z;		// z����
	double tl_actual_P_rx;
	double tl_actual_p_ry;
	double tl_actual_p_rz;
};
// �ѿ�������ϵ��TCP��ʵ���ٶ�
struct st_tcp_actual_vel
{
	double tcp_actual_v_x;
	double tcp_actual_v_y;
	double tcp_actual_v_z;
	double tcp_actual_v_rx;
	double tcp_actual_v_ry;
	double tcp_actual_v_rz;
};
// �ѿ�������ϵ�й��ߵ�Ŀ������Tool vector target
struct st_tool_target_pos
{
	double tl_target_p_x;
	double tl_target_p_y;
	double tl_target_p_z;
	double tl_target_p_rx;
	double tl_target_p_ry;
	double tl_target_p_rz;
};
// �ѿ�������ϵ��TCP��Ŀ���ٶ�TCP speed target
struct st_tcp_target_vel
{
	double tcp_target_v_x;
	double tcp_target_v_y;
	double tcp_target_v_z;
	double tcp_target_v_rx;
	double tcp_target_v_ry;
	double tcp_target_v_rz;
};
// �ؽڿ���ģʽ
struct st_JointControlMode
{
	double ControlMode_J1;
	double ControlMode_J2;
	double ControlMode_J3;
	double ControlMode_J4;
	double ControlMode_J5;
	double ControlMode_J6;
};
// �ⲿλ��
struct st_ElbowPos
{
	double ElbowPos_1;
	double ElbowPos_2;
	double ElbowPos_3;
};
// �ⲿ�ٶ�
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
	int m_iPackageSize;					// �洢���ݰ��Ĵ�С,�����������

private:
	int RS_GetPackageSize();			// ���ݰ���С����ֻ�������ڲ�ʹ��

private:
	ConvertTools m_cTool;				// ConvertTools���Ա����
	char *p_aRobotData;					// ָ��PackageData�ĵ�ַָ��
};