#include "pch.h"
#include "RobotState.h"
/*
 *	1.因为Reverse()是对字节进行一个反转,所以进行一次反转就可以了,反转多次反而使的数据不准确
 *	  因此,设置参数BOOL m_flag,用于区分是否是第一次调用函数;如果是TRUE表示第一次,那么应该调
 *	  用Reverse();如果是FALSE表示不是第一次调用,那么不应该在函数中继续调用Reverse();
 *
 *	2.如果接收到的数据不足1116个字节,那么岂不是解析会存在不足
 *    因此设计了RS_UpDateData()方法专门在更新数据的时候,获取数据包大小,并存在成员变量m_iPackageSize中
 *	  这样一来本类中其余的方法在执行之前,判断一下字节数目是否达到1116;如果达到,那么正常转换,否则返回0
 * 
 *  3.RS_GetPackageSize()一般只会执行一次
 */
RobotState::RobotState()
{
	m_iPackageSize = 0;
	p_aRobotData = NULL;
}
void RobotState::RS_UpDateData(char * pChar)
{
	p_aRobotData = pChar;
	m_iPackageSize = RS_GetPackageSize();
}

int RobotState::RS_GetPackageSize()
{
	m_cTool.Reverse(p_aRobotData, 0, 4);
	return m_cTool.BytesToInt(p_aRobotData, 0);
}

double RobotState::RS_GetTime(BOOL b_flag)
{
	if (m_iPackageSize != 1116)
	{
		return 0;
	}

	if (b_flag)
	{
		m_cTool.Reverse(p_aRobotData, 4, 8);
	}
	return m_cTool.BytesToDouble(p_aRobotData, 4);
}

st_q_target_pos RobotState::RS_GetJointTargetPos(BOOL b_flag)
{
	st_q_target_pos st_temp = { 0,0,0,0,0,0 };
	
	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 12 + i * 8, 8);
		}
	}
	st_temp.q_target_1 = m_cTool.BytesToDouble(p_aRobotData, 12);
	st_temp.q_target_2 = m_cTool.BytesToDouble(p_aRobotData, 20);
	st_temp.q_target_3 = m_cTool.BytesToDouble(p_aRobotData, 28);
	st_temp.q_target_4 = m_cTool.BytesToDouble(p_aRobotData, 36);
	st_temp.q_target_5 = m_cTool.BytesToDouble(p_aRobotData, 44);
	st_temp.q_target_6 = m_cTool.BytesToDouble(p_aRobotData, 52);

	return st_temp;
}

st_qd_target_vel RobotState::RS_GetJointTargetVel(BOOL b_flag)
{
	st_qd_target_vel st_temp = { 0,0,0,0,0,0 };
	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 60 + i * 8, 8);
		}
	}
	st_temp.qd_target_1 = m_cTool.BytesToDouble(p_aRobotData, 60);
	st_temp.qd_target_2 = m_cTool.BytesToDouble(p_aRobotData, 68);
	st_temp.qd_target_3 = m_cTool.BytesToDouble(p_aRobotData, 76);
	st_temp.qd_target_4 = m_cTool.BytesToDouble(p_aRobotData, 84);
	st_temp.qd_target_5 = m_cTool.BytesToDouble(p_aRobotData, 92);
	st_temp.qd_target_6 = m_cTool.BytesToDouble(p_aRobotData, 100);

	return st_temp;
}

st_qdd_target_acc RobotState::RS_GetJointTargetAcc(BOOL b_flag)
{
	st_qdd_target_acc st_temp = { 0,0,0,0,0,0 };
	
	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 108 + i * 8, 8);
		}
	}
	st_temp.qdd_target_1 = m_cTool.BytesToDouble(p_aRobotData, 108);
	st_temp.qdd_target_2 = m_cTool.BytesToDouble(p_aRobotData, 116);
	st_temp.qdd_target_3 = m_cTool.BytesToDouble(p_aRobotData, 124);
	st_temp.qdd_target_4 = m_cTool.BytesToDouble(p_aRobotData, 132);
	st_temp.qdd_target_5 = m_cTool.BytesToDouble(p_aRobotData, 140);
	st_temp.qdd_target_6 = m_cTool.BytesToDouble(p_aRobotData, 148);

	return st_temp;
}

st_q_actual_pos RobotState::RS_GetJointActualPos(BOOL b_flag)
{
	st_q_actual_pos st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 252 + i * 8, 8);
		}
	}
	st_temp.q_actual_1 = m_cTool.BytesToDouble(p_aRobotData, 252);
	st_temp.q_actual_2 = m_cTool.BytesToDouble(p_aRobotData, 260);
	st_temp.q_actual_3 = m_cTool.BytesToDouble(p_aRobotData, 268);
	st_temp.q_actual_4 = m_cTool.BytesToDouble(p_aRobotData, 276);
	st_temp.q_actual_5 = m_cTool.BytesToDouble(p_aRobotData, 284);
	st_temp.q_actual_6 = m_cTool.BytesToDouble(p_aRobotData, 292);

	return st_temp;
}

st_qd_actual_vel RobotState::RS_GetJointActualVel(BOOL b_flag)
{
	st_qd_actual_vel st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 300 + i * 8, 8);
		}
	}
	st_temp.qd_actual_1 = m_cTool.BytesToDouble(p_aRobotData, 300);
	st_temp.qd_actual_2 = m_cTool.BytesToDouble(p_aRobotData, 308);
	st_temp.qd_actual_3 = m_cTool.BytesToDouble(p_aRobotData, 316);
	st_temp.qd_actual_4 = m_cTool.BytesToDouble(p_aRobotData, 324);
	st_temp.qd_actual_5 = m_cTool.BytesToDouble(p_aRobotData, 332);
	st_temp.qd_actual_6 = m_cTool.BytesToDouble(p_aRobotData, 340);

	return st_temp;
}

st_tool_actual_pos RobotState::RS_GetToolActualPos(BOOL b_flag)
{
	st_tool_actual_pos st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 444 + i * 8, 8);
		}
	}
	st_temp.tl_actual_p_x = m_cTool.BytesToDouble(p_aRobotData, 444);
	st_temp.tl_actual_p_y = m_cTool.BytesToDouble(p_aRobotData, 452);
	st_temp.tl_actual_p_z = m_cTool.BytesToDouble(p_aRobotData, 460);
	st_temp.tl_actual_P_rx = m_cTool.BytesToDouble(p_aRobotData, 468);
	st_temp.tl_actual_p_ry = m_cTool.BytesToDouble(p_aRobotData, 476);
	st_temp.tl_actual_p_rz = m_cTool.BytesToDouble(p_aRobotData, 484);

	return st_temp;
}

st_tcp_actual_vel RobotState::RS_GetTcpActualVel(BOOL b_flag)
{
	st_tcp_actual_vel st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 492 + i * 8, 8);
		}
	}
	st_temp.tcp_actual_v_x = m_cTool.BytesToDouble(p_aRobotData, 492);
	st_temp.tcp_actual_v_y = m_cTool.BytesToDouble(p_aRobotData, 500);
	st_temp.tcp_actual_v_z = m_cTool.BytesToDouble(p_aRobotData, 508);
	st_temp.tcp_actual_v_rx = m_cTool.BytesToDouble(p_aRobotData, 516);
	st_temp.tcp_actual_v_ry = m_cTool.BytesToDouble(p_aRobotData, 524);
	st_temp.tcp_actual_v_rz = m_cTool.BytesToDouble(p_aRobotData, 532);

	return st_temp;
}

st_tool_target_pos RobotState::RS_GetToolTargetPos(BOOL b_flag)
{
	st_tool_target_pos st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 588 + i * 8, 8);
		}
	}
	st_temp.tl_target_p_x = m_cTool.BytesToDouble(p_aRobotData, 588);
	st_temp.tl_target_p_y = m_cTool.BytesToDouble(p_aRobotData, 596);
	st_temp.tl_target_p_z = m_cTool.BytesToDouble(p_aRobotData, 604);
	st_temp.tl_target_p_rx = m_cTool.BytesToDouble(p_aRobotData, 612);
	st_temp.tl_target_p_ry = m_cTool.BytesToDouble(p_aRobotData, 620);
	st_temp.tl_target_p_rz = m_cTool.BytesToDouble(p_aRobotData, 628);

	return st_temp;
}

st_tcp_target_vel RobotState::RS_GetToolTargetVel(BOOL b_flag)
{
	st_tcp_target_vel st_temp = { 0,0,0,0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 636 + i * 8, 8);
		}
	}
	st_temp.tcp_target_v_x = m_cTool.BytesToDouble(p_aRobotData, 636);
	st_temp.tcp_target_v_y = m_cTool.BytesToDouble(p_aRobotData, 644);
	st_temp.tcp_target_v_z = m_cTool.BytesToDouble(p_aRobotData, 652);
	st_temp.tcp_target_v_rx = m_cTool.BytesToDouble(p_aRobotData, 660);
	st_temp.tcp_target_v_ry = m_cTool.BytesToDouble(p_aRobotData, 668);
	st_temp.tcp_target_v_rz = m_cTool.BytesToDouble(p_aRobotData, 676);

	return st_temp;
}

double RobotState::RS_GetRobotMode(BOOL b_flag)
{
	if (m_iPackageSize != 1116)
	{
		return 0;
	}

	if (b_flag)
	{
		m_cTool.Reverse(p_aRobotData, 756, 8);
	}
	return m_cTool.BytesToDouble(p_aRobotData, 756);
}

st_JointControlMode RobotState::RS_GetJointCtrlMode(BOOL b_flag)
{
	st_JointControlMode st_temp = { 0,0,0,0,0,0 };
	
	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 6; i++)
		{
			m_cTool.Reverse(p_aRobotData, 764 + i * 8, 8);
		}
	}
	st_temp.ControlMode_J1 = m_cTool.BytesToDouble(p_aRobotData, 764);
	st_temp.ControlMode_J2 = m_cTool.BytesToDouble(p_aRobotData, 772);
	st_temp.ControlMode_J3 = m_cTool.BytesToDouble(p_aRobotData, 780);
	st_temp.ControlMode_J4 = m_cTool.BytesToDouble(p_aRobotData, 788);
	st_temp.ControlMode_J5 = m_cTool.BytesToDouble(p_aRobotData, 796);
	st_temp.ControlMode_J6 = m_cTool.BytesToDouble(p_aRobotData, 804);
	
	return st_temp;
}

double RobotState::RS_GetSafetyMode(BOOL b_flag)
{
	if (m_iPackageSize != 1116)
	{
		return 0;
	}

	if (b_flag)
	{
		m_cTool.Reverse(p_aRobotData, 812, 8);
	}
	return m_cTool.BytesToDouble(p_aRobotData, 812);
}

double RobotState::RS_GetProgState(BOOL b_flag)
{
	if (m_iPackageSize != 1116)
	{
		return 0;
	}

	if (b_flag)
	{
		m_cTool.Reverse(p_aRobotData, 1052, 8);
	}
	return m_cTool.BytesToDouble(p_aRobotData, 1052);
}

st_ElbowPos RobotState::RS_GetElbowPos(BOOL b_flag)
{
	st_ElbowPos st_temp = { 0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 3; i++)
		{
			m_cTool.Reverse(p_aRobotData, 1060 + i * 8, 8);
		}
	}
	st_temp.ElbowPos_1 = m_cTool.BytesToDouble(p_aRobotData, 1060);
	st_temp.ElbowPos_2 = m_cTool.BytesToDouble(p_aRobotData, 1068);
	st_temp.ElbowPos_3 = m_cTool.BytesToDouble(p_aRobotData, 1076);

	return st_temp;
}

st_ElbowVel RobotState::RS_GetElbowVel(BOOL b_flag)
{
	st_ElbowVel st_temp = { 0,0,0 };

	if (m_iPackageSize != 1116)
	{
		return st_temp;
	}

	if (b_flag)
	{
		for (int i = 0; i < 3; i++)
		{
			m_cTool.Reverse(p_aRobotData, 1084 + i * 8, 8);
		}
	}
	st_temp.ElbowVel_1 = m_cTool.BytesToDouble(p_aRobotData, 1084);
	st_temp.ElbowVel_2 = m_cTool.BytesToDouble(p_aRobotData, 1092);
	st_temp.ElbowVel_3 = m_cTool.BytesToDouble(p_aRobotData, 1100);

	return st_temp;
}

double RobotState::RS_GetSafetyStatus(BOOL b_flag)
{
	if (m_iPackageSize != 1116)
	{
		return 0;
	}

	if (b_flag)
	{
		m_cTool.Reverse(p_aRobotData, 1108, 8);
	}
	return m_cTool.BytesToDouble(p_aRobotData,1108);
}
