//
// Created by hsh on 2023/2/27.
//

#ifndef OMEGA7_COM_CATHETER_KINEMETIC_H
#define OMEGA7_COM_CATHETER_KINEMETIC_H


//鞘管运动学类及变量类型声明

#include "Eigen/Core"
#include "Eigen/SVD"

//单个鞘管常数参数结构体
typedef struct qC_
{
    float l0;			//鞘管弯曲段原始长度（mm）
    float D;			//鞘管外径（mm）
    float d;			//鞘管内径（mm）
    float dF;			//控弯牵引丝固定点直径（mm）
    float E;			//杨氏模量
    float EI;			//抗弯强度
}Catheter_Const_Param_t;

//单个鞘管操纵（驱动）空间参数结构体
typedef struct qS_
{
    float phi;			//旋转角度（rad）
    float z;			//轴向位移（mm）
    float x;			//牵引丝缩短长度（mm）

    //向量转换为结构体
    qS_ convertFromVector(const Eigen::Matrix<float, 3, 1> &vector)
    {
        phi = vector(0, 0);
        z = vector(1, 0);
        x = vector(2, 0);
        return *this;
    }
    //结构体转换为向量
    Eigen::Matrix<float, 3, 1> convert2Vector(void)
    {
        Eigen::Matrix<float, 3, 1> vector;
        vector(0, 0) = phi;
        vector(1, 0) = z;
        vector(2, 0) = x;
        return vector;
    }
}Catheter_Steer_Param_t;

//单段鞘管（重合部分为同一段）几何空间结构体
typedef struct qG_
{
    float d;			//直线段长度（mm）
    float theta;		//旋转角度（rad）
    float l;			//圆弧段弧长（mm）
    float kappa;		//曲率（mm^-1）
    float rho;			//曲率半径（mm）

    //向量转换为结构体
    qG_ convertFromVector(const Eigen::Matrix<float, 4, 1> &vector)
    {
        d = vector(0, 0);
        theta = vector(1, 0);
        l = vector(2, 0);
        kappa = vector(3, 0);
        return *this;
    }
    //结构体转换为向量
    Eigen::Matrix<float, 4, 1> convert2Vector(void)
    {
        Eigen::Matrix<float, 4, 1> vector;
        vector(0, 0) = d;
        vector(1, 0) = theta;
        vector(2, 0) = l;
        vector(3, 0) = kappa;
        return vector;
    }
}Catheter_Geometry_Param_t;

//两级鞘管常数参数结构体
typedef struct qC
{
    Catheter_Const_Param_t m;			//大鞘常数参数
    Catheter_Const_Param_t n;			//小鞘常数参数
}Catheter_Const_Param_Group_t;

//两级鞘管操纵（驱动）空间参数结构体
typedef struct qS
{
    Catheter_Steer_Param_t m;			//大鞘操纵/驱动空间参数
    Catheter_Steer_Param_t n;			//小鞘操纵/驱动空间参数

    //向量转换为结构体
    qS convertFromVector(const Eigen::Matrix<float, 6, 1> &vector)
    {
        m.convertFromVector(vector.block(0, 0, 3, 1));
        n.convertFromVector(vector.block(3, 0, 3, 1));
        return *this;
    }
    //结构体转换为向量
    Eigen::Matrix<float, 6, 1> convert2Vector(void)
    {
        Eigen::Matrix<float, 6, 1> vector;
        vector.block(0, 0, 3, 1) = m.convert2Vector();
        vector.block(3, 0, 3, 1) = n.convert2Vector();
        return vector;
    }
}Catheter_Steer_Param_Group_t;

//两级鞘管几何空间参数结构体
typedef struct qG
{
    Catheter_Geometry_Param_t a;		//A段几何空间参数
    Catheter_Geometry_Param_t b;		//B段几何空间参数

    //向量转换为结构体
    qG convertFromVector(const Eigen::Matrix<float, 8, 1> &vector)
    {
        a.convertFromVector(vector.block(0, 0, 4, 1));
        b.convertFromVector(vector.block(4, 0, 4, 1));
        return *this;
    }
    //结构体转换为向量
    Eigen::Matrix<float, 8, 1> convert2Vector(void)
    {
        Eigen::Matrix<float, 8, 1> vector;
        vector.block(0, 0, 4, 1) = a.convert2Vector();
        vector.block(4, 0, 4, 1) = b.convert2Vector();
        return vector;
    }
}Catheter_Geometry_Param_Group_t;

//鞘管工作空间参数结构体
typedef struct ws
{
    Eigen::Matrix<float, 4, 4> T;		//齐次变换矩阵
    Eigen::Matrix<float, 3, 1> P;		//末端位置向量（mm）
    Eigen::Matrix<float, 3, 3> R;		//旋转矩阵
    Eigen::Matrix<float, 3, 1> rz;		//末端姿态向量
}Catheter_Workspace_t;

//鞘管工作空间微分参数结构体
typedef struct diff_ws
{
    Eigen::Matrix<float, 3, 1> v;		//末端速度向量（mm/s）
    Eigen::Matrix<float, 3, 1> omega;	//末端角速度向量

    //向量转换为结构体
    diff_ws convertFromVector(const Eigen::Matrix<float, 6, 1> &vector)
    {
        v = vector.block(0, 0, 3, 1);
        omega = vector.block(3, 0, 3, 1);
        return *this;
    }
    //结构体转换为向量
    Eigen::Matrix<float, 6, 1> convert2Vector(void)
    {
        Eigen::Matrix<float, 6, 1> vector;
        vector.block(0, 0, 3, 1) = v;
        vector.block(3, 0, 3, 1) = omega;
        return vector;
    }
}Catheter_Workspace_Diff_t;

//操纵/驱动空间雅可比
typedef Eigen::Matrix<float, 6, 6> Catheter_Jacob_Steer_t;

//几何空间雅可比
typedef Eigen::Matrix<float, 6, 8> Catheter_Jacob_Geometry_t;

//鞘管运动学类
class Catheter_Kinemetic
{
public:
    //构造函数
    Catheter_Kinemetic(void);
    Catheter_Kinemetic(Catheter_Const_Param_Group_t qC);

    //操纵/驱动空间向几何空间映射
    Catheter_Geometry_Param_Group_t spaticalMap_qSteer2qGeometry(Catheter_Steer_Param_Group_t qS);
    //几何空间向操纵/驱动空间映射
    Catheter_Steer_Param_Group_t spaticalMap_qGeometry2qSteer(Catheter_Geometry_Param_Group_t qG);

    //正运动学：操纵/驱动空间->工作空间
    Catheter_Workspace_t fkine_qSteer2Workspace(Catheter_Steer_Param_Group_t qS);
    //正运动学：几何空间->工作空间
    Catheter_Workspace_t fkine_qGeometry2Workspace(Catheter_Geometry_Param_Group_t qG);

    //微分运动学：操纵/驱动空间雅可比
    Catheter_Jacob_Steer_t jacob_qSteer(Catheter_Steer_Param_Group_t qS);
    //微分运动学：几何空间雅可比
    Catheter_Jacob_Geometry_t jacob_qGeometry(Catheter_Geometry_Param_Group_t qG);

    //准静态逆运动学
    Catheter_Steer_Param_Group_t ikine_QuasiStatic_V2dqSteer(Catheter_Steer_Param_Group_t qS,
                                                             Catheter_Workspace_Diff_t V);

    //单段圆弧几何参数正运动学
    Eigen::Matrix<float, 4, 4> fkine_Single_qGeometry2Workspace(Catheter_Geometry_Param_t qG_);

    //访问参数结构体
    Catheter_Steer_Param_Group_t getSteerParam() {return qS;}
    Catheter_Steer_Param_Group_t getSteerVelocityParam() {return dqS;}
    Catheter_Geometry_Param_Group_t getGeometryParam() {return qG;}
    Catheter_Workspace_t getWorkspaceParam() {return workspace;}
    Catheter_Workspace_Diff_t getVelocityParam() {return V;}
    Catheter_Jacob_Steer_t getJacobSteer() {return JS;}

private:
    Catheter_Const_Param_Group_t qC;				//常数参数
    Catheter_Steer_Param_Group_t qS;				//操纵/驱动空间参数
    Catheter_Steer_Param_Group_t dqS;				//操纵/驱动空间参数变化率
    Catheter_Geometry_Param_Group_t qG;				//几何空间参数
    Catheter_Geometry_Param_Group_t dqG;			//几何空间参数变化率
    Catheter_Workspace_t workspace;					//工作空间参数
    Catheter_Workspace_Diff_t V;					//工作空间参数
    Catheter_Jacob_Steer_t JS;						//操纵/驱动空间雅可比
    Catheter_Jacob_Geometry_t JG;					//几何空间雅可比

    float alpha;									//空间映射计算中间变量α
    float beta;										//空间映射计算中间变量β

    Eigen::Matrix<float, 3, 1> skewSymmetricMat2Vector(Eigen::Matrix<float, 3, 3> mat);
};

#endif //OMEGA7_COM_CATHETER_KINEMETIC_H
