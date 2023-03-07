#ifndef KINEMETIC_WIDGET_H
#define KINEMETIC_WIDGET_H

#include <QtCore>
#include <QWidget>

#include "catheter_kinemetic.h"
#include "QPlot3D.h"

class Kinemetic_Widget : public QWidget
{
    Q_OBJECT


private:
    QPlot3D plot;                           //鞘管3D图像
    QPlot3D plot_xz;                        //鞘管3D图像正视图
    QPlot3D plot_xy;                        //鞘管3D图像俯视图
    QPlot3D plot_yz;                        //鞘管3D图像侧视图
    QPlot3D *p_plot[4] = {&plot, &plot_xz, &plot_xy, &plot_yz};
    QCurve3D catheter_a;                    //鞘管A段
    QCurve3D catheter_b;                    //鞘管B段

    //控制组件
    //m_rotate, m_bend, m_stretch, n_rotate, n_bend, n_stretch
    QLabel *pLabel_steer_control[6];
    QSlider *pSlider_steer_control[6];
    QDoubleSpinBox *pSpinBox_steer_control[6];

    QPushButton *pButton_workspace[6][2];
    QTextBrowser *pText_JS_singular_value;


public:
    Kinemetic_Widget(QWidget *parent = nullptr);

    void plotInit(void);
    void plotCatheter(Catheter_Geometry_Param_Group_t qG);

public slots:
    void runSimulation(void);

signals:

    void signal_qSmphi(const float data);
    void signal_qSmx(const float data);
    void signal_qSmz(const float data);
    void signal_qSnphi(const float data);
    void signal_qSnx(const float data);
    void signal_qSnz(const float data);

public:
    Catheter_Kinemetic kine;                //鞘管运动学类

    Catheter_Steer_Param_Group_t qS;		//操纵/驱动空间参数
    Catheter_Steer_Param_Group_t dqS;		//操纵/驱动空间参数
    Catheter_Geometry_Param_Group_t qG;		//几何空间参数
    Catheter_Workspace_t workspace;			//工作空间参数
    Catheter_Workspace_Diff_t V;			//工作空间速度/角速度参数
    Catheter_Jacob_Steer_t JS;              //操纵空间雅可比


};
#endif // KINEMETIC_WIDGET_H
