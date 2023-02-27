//鞘管运动学类实现

#include "catheter_kinemetic.h"
#include "Eigen/LU"

/**
 * @brief	默认构造函数
 * @param 	none
 * @retval 	none
 */
Catheter_Kinemetic::Catheter_Kinemetic(void)
{
	//大鞘常数参数
	this->qC.m.l0 = 25;
	this->qC.m.D = 6.3;
	this->qC.m.d = 5.6;
	this->qC.m.dF = 5.8;
	this->qC.m.E = 1;
	this->qC.m.EI = this->qC.m.E * (pow(this->qC.m.D, 4) - pow(this->qC.m.d, 4)) / 64;
	//小鞘常数参数
	this->qC.n.l0 = 75;
	this->qC.n.D = 5.2;
	this->qC.n.d = 3.8;
	this->qC.n.dF = 4;
	this->qC.n.E = 1;
	this->qC.n.EI = this->qC.n.E * (pow(this->qC.n.D, 4) - pow(this->qC.n.d, 4)) / 64;
	
//	printf("大鞘参数\nl0:%.4f, dF:%.4f, EI:%.4f\n", this->qC.m.l0, this->qC.m.dF, this->qC.m.EI);
//	printf("小鞘参数\nl0:%.4f, dF:%.4f, EI:%.4f\n\n", this->qC.n.l0, this->qC.n.dF, this->qC.n.EI);
}

/**
 * @brief	构造函数
 * @param 	qC: 常数参数组，包含大小鞘常数参数
 * @retval 	none
 */
Catheter_Kinemetic::Catheter_Kinemetic(Catheter_Const_Param_Group_t qC)
{
	this->qC = qC;
	
//	printf("大鞘参数\nl0:%.4f, dF:%.4f, EI:%.4f\n", this->qC.m.l0, this->qC.m.dF, this->qC.m.EI);
//	printf("小鞘参数\nl0:%.4f, dF:%.4f, EI:%.4f\n\n", this->qC.n.l0, this->qC.n.dF, this->qC.n.EI);
}

/**
 * @brief	操纵/驱动空间向几何空间映射
 * @param 	qS: 操纵/驱动空间参数组，包含大小鞘操纵/驱动空间参数
 * @retval 	几何空间参数组，包括大小鞘几何空间参数
 */
Catheter_Geometry_Param_Group_t Catheter_Kinemetic::spaticalMap_qSteer2qGeometry(Catheter_Steer_Param_Group_t qS)
{
	this->qS = qS;

	alpha = (qS.n.x*(qC.m.l0-qS.m.x/2))/(qS.m.x*(qS.n.z-qS.m.z-qS.n.x/2+qC.m.l0))
			* ((qC.m.dF*qC.n.EI)/(qC.n.dF*qC.m.EI));
	//A段参数
	qG.a.d = qS.m.z;
	qG.a.l = qC.m.l0 - qS.m.x/2;
    qG.a.l = (qG.a.l > 0) ? qG.a.l : 0;
	if(qS.m.x == 0) //x_m=0, α=inf
	{
		qG.a.theta = qS.n.phi;
		qG.a.kappa = (qS.n.x/((qS.n.z-qS.m.z-qS.n.x/2+qC.m.l0)*qC.n.dF)) * (qC.n.EI/(qC.m.EI+qC.n.EI));
	}
	else
	{
		qG.a.theta = atan2(sin(qS.m.phi)+alpha*sin(qS.n.phi), cos(qS.m.phi)+alpha*cos(qS.n.phi));
		qG.a.kappa = (qS.m.x/((qC.m.l0-qS.m.x/2)*qC.m.dF)) * (qC.m.EI/(qC.m.EI+qC.n.EI))
					 * sqrt(1+pow(alpha, 2)+2*alpha*cos(qS.m.phi-qS.n.phi));
	}
	qG.a.rho = 1/qG.a.kappa;
	//B段参数
	qG.b.d = 0;
	qG.b.theta = qS.n.phi - qG.a.theta;
	qG.b.l = qS.n.z - qS.m.z - abs(qS.n.x/2);
    qG.b.l = (qG.b.l > 0) ? qG.b.l : 0;
//	qG.b.kappa = qS.n.x/((qS.n.z-qS.m.z-abs(qS.n.x/2))*qC.n.dF);
    qG.b.kappa = qS.n.x/(qG.b.l*qC.n.dF);
	qG.b.rho = 1/qG.b.kappa;

	return qG;
}

/**
 * @brief	几何空间向操纵/驱动空间映射
 * @param 	qG: 几何空间参数组，包括大小鞘几何空间参数
 * @retval 	操纵/驱动空间参数组，包含大小鞘操纵/驱动空间参数
 */
Catheter_Steer_Param_Group_t Catheter_Kinemetic::spaticalMap_qGeometry2qSteer(Catheter_Geometry_Param_Group_t qG)
{
	this->qG = qG;

	beta = (qG.b.kappa/qG.a.kappa) * (qG.b.l/(qG.b.l+qC.m.l0)) * (qC.n.EI/(qC.m.EI+qC.n.EI));
	alpha = beta/sqrt(1+pow(beta,2)-2*beta*cos(qG.b.theta));
	//小鞘（n）参数
	qS.n.phi = qG.a.theta + qG.b.theta;
	qS.n.z = qG.a.d + qG.b.l*(1+qC.n.dF*qG.b.kappa/2);
	qS.n.x = qG.b.l*qC.n.dF*qG.b.kappa;
	//大鞘（m）参数
	if(qG.a.kappa == 0 && qG.b.kappa == 0) //ab段曲率均为0，奇异位形，β=inf
	{
		//此时φa可为任意值，保持当前值不变
	}
	else if(qG.a.kappa == 0) //a段（大鞘）曲率为0，β=inf
	{
		qS.m.phi = atan2(-sin(qG.b.theta), -cos(qG.b.theta));
	}
	else //a段（大鞘）曲率不为0
	{
		qS.m.phi = qS.n.phi - atan2(sin(qG.b.theta), cos(qG.b.theta)-beta);
	}
	qS.m.z = qG.a.d;
	if(qG.b.kappa == 0) //b段（小鞘前段）曲率均为0，β=0，α=0
	{
		qS.m.x = qG.b.kappa*qG.a.l*qC.m.dF * ((qC.m.EI+qC.n.EI)/qC.m.EI);
	}
	else if(qG.a.kappa == 0) //a段（大鞘）曲率为0，β=inf，α=1
	{
		alpha = 1;
		qS.m.x = (qG.b.kappa*qG.a.l*qG.b.l*qC.m.dF)/(alpha*(qG.b.l+qC.m.l0)) * (qC.n.EI/qC.m.EI);
	}
	else //ab段曲率均不为0
	{
		qS.m.x = (qG.b.kappa*qG.a.l*qG.b.l*qC.m.dF)/(alpha*(qG.b.l+qC.m.l0)) * (qC.n.EI/qC.m.EI);
	}

	return qS;
}

/**
 * @brief	正运动学——操纵/驱动空间->工作空间
 * @param 	qS: 操纵/驱动空间参数组，包含大小鞘操纵/驱动空间参数
 * @retval 	工作空间参数
 */
Catheter_Workspace_t Catheter_Kinemetic::fkine_qSteer2Workspace(Catheter_Steer_Param_Group_t qS)
{
	this->qS = qS;
	qG = spaticalMap_qSteer2qGeometry(qS);
	workspace = fkine_qGeometry2Workspace(qG);
	return workspace;
}

/**
 * @brief	正运动学（单段，私有函数）——几何空间->工作空间
 * @param 	qG_: 几何空间参数
 * @retval 	齐次变换矩阵
 */
Eigen::Matrix<float, 4, 4> Catheter_Kinemetic::fkine_Single_qGeometry2Workspace(Catheter_Geometry_Param_t qG_)
{
	Eigen::Matrix<float, 4, 4> T_;
	if(qG_.kappa == 0)
	{
		T_ << cos(qG_.theta)*cos(qG_.kappa*qG_.l), -sin(qG_.theta),	cos(qG_.theta)*sin(qG_.kappa*qG_.l), 0,
			  sin(qG_.theta)*cos(qG_.kappa*qG_.l),  cos(qG_.theta),	sin(qG_.theta)*sin(qG_.kappa*qG_.l), 0,
			 -sin(qG_.kappa*qG_.l),					0,			   	cos(qG_.kappa*qG_.l),				 qG_.d+qG_.l,
			  0,									0,			   	0,									 1;
	}
	else
	{
		T_ << cos(qG_.theta)*cos(qG_.kappa*qG_.l), -sin(qG_.theta),	cos(qG_.theta)*sin(qG_.kappa*qG_.l), 2*cos(qG_.theta)*pow(sin(qG_.kappa*qG_.l/2),2)/qG_.kappa,
			  sin(qG_.theta)*cos(qG_.kappa*qG_.l),  cos(qG_.theta),	sin(qG_.theta)*sin(qG_.kappa*qG_.l), 2*sin(qG_.theta)*pow(sin(qG_.kappa*qG_.l/2),2)/qG_.kappa,
			 -sin(qG_.kappa*qG_.l),					0,			   	cos(qG_.kappa*qG_.l),				 qG_.d+sin(qG_.kappa*qG_.l)/qG_.kappa,
			  0,									0,			   	0,									 1;
	}
	return T_;
}

/**
 * @brief	正运动学——几何空间->工作空间
 * @param 	qG: 几何空间参数组，包括大小鞘几何空间参数
 * @retval 	工作空间参数
 */
Catheter_Workspace_t Catheter_Kinemetic::fkine_qGeometry2Workspace(Catheter_Geometry_Param_Group_t qG)
{
	this->qG = qG;

	//分段齐次变换矩阵相乘
	workspace.T = fkine_Single_qGeometry2Workspace(qG.a) * fkine_Single_qGeometry2Workspace(qG.b);
	workspace.P = workspace.T.block(0, 3, 3, 1);
	workspace.R = workspace.T.block(0, 0, 3, 3);
	workspace.rz = workspace.T.block(0, 2, 3, 1) / workspace.T.block(0, 2, 3, 1).norm();

	//完整表达式
	// //旋转矩阵
	// workspace.R(0,0) =	cos(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l)
	// 				   -sin(qG.a.theta)*sin(qG.b.theta)*cos(qG.b.kappa*qG.b.l)
	// 				   -cos(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l);
	// workspace.R(1,0) =	sin(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l)
	// 				   +cos(qG.a.theta)*sin(qG.b.theta)*cos(qG.b.kappa*qG.b.l)
	// 				   -sin(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l);
	// workspace.R(2,0) = -cos(qG.b.theta)*sin(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l) 
	// 				   -cos(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l);
	// workspace.R(0,1) = -sin(qG.a.theta)*cos(qG.b.theta)
	// 				   -cos(qG.a.theta)*sin(qG.b.theta)*cos(qG.a.kappa*qG.a.l);
	// workspace.R(1,1) =  cos(qG.a.theta)*cos(qG.b.theta)
	// 				   -sin(qG.a.theta)*sin(qG.b.theta)*cos(qG.a.kappa*qG.a.l);
	// workspace.R(2,1) =  sin(qG.b.theta)*sin(qG.a.kappa*qG.a.l);
	// workspace.R(0,2) = 	cos(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l)
	// 				   -sin(qG.a.theta)*sin(qG.b.theta)*sin(qG.b.kappa*qG.b.l)
	// 				   +cos(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l);
	// workspace.R(1,2) =	sin(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l)
	// 				   +cos(qG.a.theta)*sin(qG.b.theta)*sin(qG.b.kappa*qG.b.l)
	// 				   +sin(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l);
	// workspace.R(2,2) = -cos(qG.b.theta)*sin(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l) 
	// 				   +cos(qG.a.kappa*qG.a.l)*cos(qG.b.kappa*qG.b.l);
	// //资态向量
	// workspace.rz = workspace.R.block(0, 2, 3, 1) / workspace.R.block(0, 2, 3, 1).norm();
	// //末端坐标
	// workspace.P(0,0) =  qG.b.d*cos(qG.a.theta)*sin(qG.a.kappa*qG.a.l)
	// 				   +2/qG.a.kappa*cos(qG.a.theta)*pow(sin(qG.a.kappa*qG.a.l/2),2)
	// 				   +1/qG.b.kappa*(cos(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l)
	// 				   		-2*sin(qG.a.theta)*sin(qG.b.theta)*pow(sin(qG.b.kappa*qG.b.l/2),2)
	// 						+2*cos(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*pow(sin(qG.b.kappa*qG.b.l/2),2));
	// workspace.P(1,0) =  qG.b.d*sin(qG.a.theta)*sin(qG.a.kappa*qG.a.l)
	// 				   +2/qG.a.kappa*sin(qG.a.theta)*pow(sin(qG.a.kappa*qG.a.l/2),2)
	// 				   +1/qG.b.kappa*(sin(qG.a.theta)*sin(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l)
	// 				   		+2*cos(qG.a.theta)*sin(qG.b.theta)*pow(sin(qG.b.kappa*qG.b.l/2),2)
	// 						+2*sin(qG.a.theta)*cos(qG.b.theta)*cos(qG.a.kappa*qG.a.l)*pow(sin(qG.b.kappa*qG.b.l/2),2));
	// workspace.P(2,0) =  qG.a.d + qG.b.d*cos(qG.a.theta)*cos(qG.a.kappa*qG.a.l) + 1/qG.a.kappa*sin(qG.a.kappa*qG.a.l)
	// 				   +1/qG.b.kappa*(cos(qG.a.kappa*qG.a.l)*sin(qG.b.kappa*qG.b.l)
	// 				   		-2*cos(qG.b.theta)*sin(qG.a.kappa*qG.a.l)*pow(sin(qG.b.kappa*qG.b.l/2),2));
	// //齐次变换矩阵拼接
	// workspace.T.block(0,0,3,3) = workspace.R;
	// workspace.T.block(0,3,3,1) = workspace.P;
	// workspace.T.block(3,0,1,3) << 0, 0, 0;
	// workspace.T(3,3) = 1;

	return workspace;
}

/**
 * @brief	反对称矩阵->向量（私有函数）
 * @param 	mat: 反对称矩阵S(ω)
 * @retval 	反对称矩阵对应向量ω
 */
Eigen::Matrix<float, 3, 1> Catheter_Kinemetic::skewSymmetricMat2Vector(Eigen::Matrix<float, 3, 3> mat)
{
	Eigen::Matrix<float, 3, 1> vector;
	vector << mat(2, 1), mat(0, 2), mat(1, 0);
	return vector;
}

/**
 * @brief	微分运动学——操纵/驱动空间雅可比
 * @param 	qS: 操纵/驱动空间参数组，包含大小鞘操纵/驱动空间参数
 * @retval 	雅可比矩阵
 */
Catheter_Jacob_Steer_t Catheter_Kinemetic::jacob_qSteer(Catheter_Steer_Param_Group_t qS)
{
	this->qS = qS;
	
	Catheter_Workspace_t workspace = fkine_qSteer2Workspace(qS);
	Catheter_Workspace_t workspace_diff = workspace;
	Catheter_Steer_Param_Group_t qS_diff;
	Eigen::Matrix<float, 6, 1> qS_vector = qS.convert2Vector();
	Eigen::Matrix<float, 6, 1> qS_diff_vector = qS_vector;
	float diff_step = 1e-3;

	for(int i = 0; i < 6; i++)
	{
		qS_diff_vector = qS_vector;
		qS_diff_vector(i) += diff_step;
		qS_diff.convertFromVector(qS_diff_vector);
		workspace_diff = fkine_qSteer2Workspace(qS_diff);
		JS.block(0, i, 3, 1) = (workspace_diff.P - workspace.P) / diff_step;
		JS.block(3, i, 3, 1) = skewSymmetricMat2Vector((((workspace_diff.R - workspace.R) / diff_step)
													   * workspace.R.transpose()));
	}

	return JS;
}

/**
 * @brief	微分运动学——几何空间雅可比
 * @param 	qG: 几何空间参数组，包括大小鞘几何空间参数
 * @retval 	雅可比矩阵
 */
Catheter_Jacob_Geometry_t Catheter_Kinemetic::jacob_qGeometry(Catheter_Geometry_Param_Group_t qG)
{
	this->qG = qG;

	Catheter_Workspace_t workspace = fkine_qGeometry2Workspace(qG);
	Catheter_Workspace_t workspace_diff = workspace;
	Catheter_Geometry_Param_Group_t qG_diff;
	Eigen::Matrix<float, 8, 1> qG_vector = qG.convert2Vector();
	Eigen::Matrix<float, 8, 1> qG_diff_vector = qG_vector;
	float diff_step = 1e-3;

	for(int i = 0; i < 8; i++)
	{
		qG_diff_vector = qG_vector;
		qG_diff_vector(i) += diff_step;
		qG_diff.convertFromVector(qG_diff_vector);
		workspace_diff = fkine_qGeometry2Workspace(qG_diff);
		JG.block(0, i, 3, 1) = (workspace_diff.P - workspace.P) / diff_step;
		JG.block(3, i, 3, 1) = skewSymmetricMat2Vector((((workspace_diff.R - workspace.R) / diff_step)
													   * workspace.R.transpose()));
	}

	return JG;
}

/**
 * @brief	准静态逆运动学，根据末端位姿和速度、角速度求操纵/驱动空间参数变化率
 * @param 	ws: 工作空间参数
 * @param 	V: 工作空间速度、姿态角速度
 * @retval 	操纵/驱动空间参数变化率
 */
Catheter_Steer_Param_Group_t Catheter_Kinemetic::ikine_QuasiStatic_V2dqSteer(Catheter_Steer_Param_Group_t qS, 
																			 Catheter_Workspace_Diff_t V)
{
	this->qS = qS;
	this->V = V;

	jacob_qSteer(qS);
	Eigen::Matrix<float, 6, 1> V_vector = V.convert2Vector();
	//速度角速度空间投影矩阵H，将末端速度向有效末端速度投影
	Eigen::Matrix<float, 6, 6> H_velo_project;
	H_velo_project << Eigen::MatrixXf::Identity(3, 3), Eigen::MatrixXf::Zero(3, 3),
					  Eigen::MatrixXf::Zero(3, 3), Eigen::MatrixXf::Identity(3, 3)-workspace.rz*workspace.rz.transpose()/(workspace.rz.transpose()*workspace.rz);
	//有效自由度
	Eigen::Matrix<float, 5, 6> H_effect = H_velo_project.block(0, 0, 5, 6);
	Eigen::Matrix<float, 6, 5> JS_effect = JS.block(0, 1, 6, 5);
	//求解
	Eigen::Matrix<float, 6, 1> dqS_vector;
	dqS_vector.block(1, 0, 5, 1) = (H_effect*JS_effect).lu().solve(H_effect*V_vector);
	dqS_vector(0, 0) = 0;
	dqS.convertFromVector(dqS_vector);

	return dqS;
}
