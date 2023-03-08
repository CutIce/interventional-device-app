//
// Created by hsh on 2023/3/6.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "../form/ui_mainwindow.h"


mainwindow::mainwindow(QWidget *parent) :
        QWidget(parent) {
    // 绘制部分构造
    QWidget *widget_plot = new QWidget(this);
    QWidget *widget_steer_control = new QWidget(this);
    QWidget *widget_workspace_control = new QWidget(this);

    QLabel *pLabel_steer_control_title = new QLabel(widget_steer_control);
    pLabel_steer_control_title->setText("驱动空间控制");
    QLabel *pLabel_workspace_control_title = new QLabel(widget_workspace_control);
    pLabel_workspace_control_title->setText("工作空间控制");

    for(int i = 0; i < 6; i++)
    {
        pLabel_steer_control[i] = new QLabel(widget_steer_control);
        pSlider_steer_control[i] = new QSlider(widget_steer_control);
        pSlider_steer_control[i]->setOrientation(Qt::Horizontal);
        pSpinBox_steer_control[i] = new QDoubleSpinBox(widget_steer_control);
        pSpinBox_steer_control[i]->setKeyboardTracking(false);
        connect(pSpinBox_steer_control[i], QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, [=](double value){pSlider_steer_control[i]->setValue(value*100);});
        connect(pSlider_steer_control[i], QOverload<int>::of(&QSlider::valueChanged),
                this, [=](int value){pSpinBox_steer_control[i]->setValue((double)value/100);});
    }
    pLabel_steer_control[0]->setText("大鞘控旋/°");
    pSlider_steer_control[0]->setRange(-18000, 18000);
    pSpinBox_steer_control[0]->setRange(-180, 180);
    pLabel_steer_control[1]->setText("大鞘控弯/mm");
    pSlider_steer_control[1]->setRange(1, 1000);
    pSpinBox_steer_control[1]->setRange(0.01, 10);
    pLabel_steer_control[2]->setText("大鞘平移/mm");
    pSlider_steer_control[2]->setRange(0, 4000);
    pSpinBox_steer_control[2]->setRange(0, 40);
    pLabel_steer_control[3]->setText("小鞘控旋/°");
    pSlider_steer_control[3]->setRange(-18000, 18000);
    pSpinBox_steer_control[3]->setRange(-180, 180);
    pLabel_steer_control[4]->setText("小鞘控弯/mm");
    pSlider_steer_control[4]->setRange(-1200, 1200);
    pSpinBox_steer_control[4]->setRange(-12, 12);
    pLabel_steer_control[5]->setText("小鞘平移/mm");
    pSlider_steer_control[5]->setRange(0, 5000);
    pSpinBox_steer_control[5]->setRange(0, 50);

    QGridLayout *pLayout_steer_control = new QGridLayout(widget_steer_control);
    widget_steer_control->setLayout(pLayout_steer_control);
    for(int i = 0; i < 6; i++)
    {
        pLayout_steer_control->addWidget(pLabel_steer_control[i], 2*i, 0, 1, 3);
        pLayout_steer_control->addWidget(pSlider_steer_control[i], 2*i+1, 0, 1, 3);
        pLayout_steer_control->addWidget(pSpinBox_steer_control[i], 2*i+1, 3, 1, 1);
    }

    //工作空间控制组件
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            pButton_workspace[i][j] = new QPushButton(widget_workspace_control);
        }
    }
    pButton_workspace[0][0]->setText("-x");
    pButton_workspace[0][1]->setText("+x");
    pButton_workspace[1][0]->setText("-y");
    pButton_workspace[1][1]->setText("+y");
    pButton_workspace[2][0]->setText("-z");
    pButton_workspace[2][1]->setText("+z");
    pButton_workspace[3][0]->setText("-rx");
    pButton_workspace[3][1]->setText("+rx");
    pButton_workspace[4][0]->setText("-ry");
    pButton_workspace[4][1]->setText("+ry");
    pButton_workspace[5][0]->setText("-rz");
    pButton_workspace[5][1]->setText("+rz");
    QLabel *pLabel_JS_singular_value = new QLabel(widget_workspace_control);
    pLabel_JS_singular_value->setText("singular value:");
    pText_JS_singular_value = new QTextBrowser(widget_workspace_control);
    QLabel *pLabel_JS_singular_value_hint = new QLabel(widget_workspace_control);
    pLabel_JS_singular_value_hint->setWordWrap(true);
    pLabel_JS_singular_value_hint->setText("(workspace-control avaliable while singular value > 1e-5)");

    QGridLayout *pLayout_workspace_control = new QGridLayout(widget_workspace_control);
    widget_workspace_control->setLayout(pLayout_workspace_control);
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            pLayout_workspace_control->addWidget(pButton_workspace[i][j], i, j, 1, 1);
        }
    }
    pLayout_workspace_control->addWidget(pLabel_JS_singular_value, 6, 0, 1, 2);
    pLayout_workspace_control->addWidget(pText_JS_singular_value, 7, 0, 1, 2);
    pLayout_workspace_control->addWidget(pLabel_JS_singular_value_hint, 8, 0, 1, 2);

    //图窗布局
    QGridLayout *pLayout_plot = new QGridLayout(widget_plot);
    widget_plot->setLayout(pLayout_plot);
    pLayout_plot->addWidget(&plot, 0, 0, 3, 3);
    pLayout_plot->addWidget(&plot_xz, 0, 3, 1, 1);
    pLayout_plot->addWidget(&plot_xy, 1, 3, 1, 1);
    pLayout_plot->addWidget(&plot_yz, 2, 3, 1, 1);

    //页面布局
    QGridLayout *pLayout = new QGridLayout(this);
    this->setLayout(pLayout);
    pLayout->addWidget(widget_plot,                     0, 0, 3, 1);
    pLayout->addWidget(widget_steer_control,            1, 1, 1, 1, Qt::AlignTop);
    pLayout->addWidget(widget_workspace_control,        1, 2, 1, 1, Qt::AlignTop);
    pLayout->addWidget(pLabel_steer_control_title,      0, 1, 1, 1, Qt::AlignBottom|Qt::AlignHCenter);
    pLayout->addWidget(pLabel_workspace_control_title,  0, 2, 1, 1, Qt::AlignBottom|Qt::AlignHCenter);

    //控件尺寸限制
    widget_plot->setMinimumSize(QSize(720, 540));
    widget_steer_control->setMinimumSize(QSize(240, 400));
    widget_steer_control->setMaximumSize(QSize(240, 400));
    widget_workspace_control->setMinimumSize(QSize(180, 420));
    widget_workspace_control->setMaximumSize(QSize(180, 420));
    pLabel_JS_singular_value->setMaximumHeight(20);
    pText_JS_singular_value->setMaximumHeight(30);
    pLabel_JS_singular_value_hint->setMaximumHeight(70);

    this->plotInit();

    //1ms定时器
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(runSimulation()), Qt::UniqueConnection);
    timer.start(20);

    QObject::connect(this, &mainwindow::signal_qSmphi, this->sd, &serial_demo::Drotate);
    QObject::connect(this, &mainwindow::signal_qSmx, this->sd, &serial_demo::Dcurve);
    QObject::connect(this, &mainwindow::signal_qSmz, this->sd, &serial_demo::Dslide);
    QObject::connect(this, &mainwindow::signal_qSnphi, this->sd, &serial_demo::rotate);
    QObject::connect(this, &mainwindow::signal_qSnx, this->sd, &serial_demo::curve);
    QObject::connect(this, &mainwindow::signal_qSnz, this->sd, &serial_demo::slide);

    sd->show();

    // moveToThread
    omega7_communicator->moveToThread(omega_com_thread);
    sd->serial_system.moveToThread(serial_com_thread);

    omega_com_thread->start();
    serial_com_thread->start();
    //
    QObject::connect(this, &mainwindow::beginOmega7Communication, this->omega7_communicator, &Omega7_Communicator::continueQueryPose, Qt::UniqueConnection);
    QObject::connect(this, &mainwindow::stopOmega7Communication, this->omega7_communicator, &Omega7_Communicator::stopQueryPose, Qt::UniqueConnection);


}

mainwindow::~mainwindow() {
    omega_com_thread->quit();
    serial_com_thread->quit();

    omega_com_thread->wait();
    serial_com_thread->wait();
}


void mainwindow::runSimulation() {
    //驱动空间控制
    qS.m.phi = (float)pSlider_steer_control[0]->value()/5730;
    qS.m.x = (float)pSlider_steer_control[1]->value()/100;
    qS.m.z = (float)pSlider_steer_control[2]->value()/100;
    qS.n.phi = (float)pSlider_steer_control[3]->value()/5730;
    qS.n.x = (float)pSlider_steer_control[4]->value()/100;
    qS.n.z = (float)pSlider_steer_control[5]->value()/100;

    //驱动空间数据发送到串口
    emit signal_qSmphi(qS.m.phi);
    emit signal_qSmx(qS.m.x);
    emit signal_qSmz(qS.m.z);
    emit signal_qSnphi(qS.n.phi);
    emit signal_qSnx(qS.n.x);
    emit signal_qSnz(qS.n.z);

    //工作空间控制
    bool workspace_control_flag = false;
    for(int i = 0; i < 3; i++)
    {
        //平动速度
        if(pButton_workspace[i][0]->isDown())
        {
            V.v(i) = -500;
            workspace_control_flag = true;
        }
        else if(pButton_workspace[i][1]->isDown())
        {
            V.v(i) = 500;
            workspace_control_flag = true;
        }
        else
        {
            V.v(i) = 0;
        }
        //姿态角速度
        if(pButton_workspace[i+3][0]->isDown())
        {
            V.omega(i) = -40;
            workspace_control_flag = true;
        }
        else if(pButton_workspace[i+3][1]->isDown())
        {
            V.omega(i) = 40;
            workspace_control_flag = true;
        }
        else
        {
            V.omega(i) = 0;
        }
    }
    //雅可比矩阵&奇异值
    JS = kine.jacob_qSteer(qS);
    Eigen::JacobiSVD<Eigen::MatrixXf> JS_svd(JS, Eigen::ComputeThinU | Eigen::ComputeThinV);
    pText_JS_singular_value->setText(QString::number(JS_svd.singularValues().minCoeff(), 'e', 1));
    //工作空间控制标志为true，进行准静态逆运动学解算
    if(workspace_control_flag)
    {
        dqS = kine.ikine_QuasiStatic_V2dqSteer(qS, V);
        //驱动空间边界限位检测
        bool bound_flag = false;
        if( (pSlider_steer_control[0]->value() == pSlider_steer_control[0]->minimum() && dqS.m.phi < -1) ||
            (pSlider_steer_control[0]->value() == pSlider_steer_control[0]->maximum() && dqS.m.phi > 1) ||
            (pSlider_steer_control[1]->value() == pSlider_steer_control[1]->minimum() && dqS.m.x < -10) ||
            (pSlider_steer_control[1]->value() == pSlider_steer_control[1]->maximum() && dqS.m.x > 10) ||
            (pSlider_steer_control[2]->value() == pSlider_steer_control[2]->minimum() && dqS.m.z < -10) ||
            (pSlider_steer_control[2]->value() == pSlider_steer_control[2]->maximum() && dqS.m.z > 10) ||
            (pSlider_steer_control[3]->value() == pSlider_steer_control[3]->minimum() && dqS.n.phi < -1) ||
            (pSlider_steer_control[3]->value() == pSlider_steer_control[3]->maximum() && dqS.n.phi > 1) ||
            (pSlider_steer_control[4]->value() == pSlider_steer_control[4]->minimum() && dqS.n.x < -10) ||
            (pSlider_steer_control[4]->value() == pSlider_steer_control[4]->maximum() && dqS.n.x > 10) ||
            (pSlider_steer_control[5]->value() == pSlider_steer_control[5]->minimum() && dqS.n.z < -10) ||
            (pSlider_steer_control[5]->value() == pSlider_steer_control[5]->maximum() && dqS.n.z > 10) )
        {
            bound_flag = true;
        }
        //未触发驱动空间边界限位
        if(!bound_flag)
        {
            //奇异位形处理
            if(JS_svd.singularValues().minCoeff() > 1e-5)
            {
                qS.convertFromVector(qS.convert2Vector()+dqS.convert2Vector()*1e-3);
                pSlider_steer_control[0]->setValue(qRound(qS.m.phi*5730));
                pSlider_steer_control[1]->setValue(qRound(qS.m.x*100));
                pSlider_steer_control[2]->setValue(qRound(qS.m.z*100));
                pSlider_steer_control[3]->setValue(qRound(qS.n.phi*5730));
                pSlider_steer_control[4]->setValue(qRound(qS.n.x*100));
                pSlider_steer_control[5]->setValue(qRound(qS.n.z*100));
            }
        }
    }

    qG = kine.spaticalMap_qSteer2qGeometry(qS);
    workspace = kine.fkine_qSteer2Workspace(qS);
    plotCatheter(qG);
}

void mainwindow::plotInit() {
    catheter_a.setColor(QColor(QRgb(0x0D5CAB)));
    catheter_a.setLineWidth(8);
    catheter_b.setColor(QColor(QRgb(0x2A90F6)));
    catheter_b.setLineWidth(5);

    //plot appearance seting
    for(int i = 0; i < 4; i++)
    {
        p_plot[i]->setBackgroundColor(QColor(QRgb(0x303030)));
        p_plot[i]->setShowAzimuthElevation(true);
        p_plot[i]->setShowLegend(false);
        p_plot[i]->xAxis().setRange(QRange(-20, 20, -20 ,20, 0, 30));
        p_plot[i]->yAxis().setRange(QRange(-20, 20, -20 ,20, 0, 30));
        p_plot[i]->zAxis().setRange(QRange(-20, 20, -20 ,20, 0, 30));
        p_plot[i]->setAxisEqual(true);
        p_plot[i]->setShowAxis(false);
        p_plot[i]->setShowAxisBox(false);
        p_plot[i]->setShowGrid(false);
        p_plot[i]->xAxis().setLabelColor(QColor(QRgb(0x9e9e9e)));
        p_plot[i]->yAxis().setLabelColor(QColor(QRgb(0x9e9e9e)));
        p_plot[i]->zAxis().setLabelColor(QColor(QRgb(0x9e9e9e)));
        p_plot[i]->xAxis().setShowCoordinate(true);
        p_plot[i]->yAxis().setShowCoordinate(true);
        p_plot[i]->zAxis().setShowCoordinate(true);
    }
    plot.setElevation(30);
    plot.setAzimuth(-45);
    plot_xz.setElevation(0);
    plot_xz.setAzimuth(0);
    plot_xy.setElevation(89);
    plot_xy.setAzimuth(0);
    plot_yz.setElevation(0);
    plot_yz.setAzimuth(90);
}

void mainwindow::plotCatheter(Catheter_Geometry_Param_Group_t qG) {
    //清空曲线
    catheter_a.clear();
    catheter_b.clear();

    //A段齐次变换矩阵
    Eigen::Matrix<float, 4, 4> Ta = kine.fkine_Single_qGeometry2Workspace(qG.a);

    catheter_a.addData(0, 0, 0);
    catheter_a.addData(0, 0, qG.a.d);
    if(qG.a.kappa != 0)
    {
        //圆弧旋转矩阵
        Eigen::Matrix<float, 3, 3> Ra;
        Ra << -cos(qG.a.theta), 0, -sin(qG.a.theta),
                -sin(qG.a.theta), 0, cos(qG.a.theta),
                0, 1, 0;
        //圆弧圆心位置
        Eigen::Matrix<float, 3, 1> Oa;
        Oa << 1/qG.a.kappa*cos(qG.a.theta), 1/qG.a.kappa*sin(qG.a.theta), qG.a.d;
        //圆弧齐次变换矩阵
        Eigen::Matrix<float, 4, 4> T_curve_a;
        T_curve_a << Ra, Oa, 0, 0, 0, 1;
        //圆弧齐次变换矩阵
        float tha;
        Eigen::Matrix<float, 4, 1> Pa;
        for(int i = 0; i <= 50; i++)
        {
            tha = (float)i/50*qG.a.l*qG.a.kappa;
            Pa << 1/qG.a.kappa*cos(tha), 1/qG.a.kappa*sin(tha), 0, 1;
            Pa = T_curve_a*Pa;
            catheter_a.addData(Pa(0, 0), Pa(1, 0), Pa(2, 0));
        }
    }
    else
    {
        catheter_a.addData(0, 0, qG.a.d);
        catheter_a.addData(0, 0, qG.a.d+qG.a.l);
    }

    if(qG.b.kappa != 0)
    {
        //圆弧旋转矩阵
        Eigen::Matrix<float, 3, 3> Rb;
        Rb << -cos(qG.b.theta), 0, -sin(qG.b.theta),
                -sin(qG.b.theta), 0, cos(qG.b.theta),
                0, 1, 0;
        Rb = Ta.block(0, 0, 3, 3) * Rb;
        //圆弧圆心位置
        Eigen::Matrix<float, 3, 1> Ob;
        Ob << -1/qG.b.kappa, 0, 0;
        Ob = Rb*Ob + Ta.block(0, 3, 3, 1);
        //圆弧齐次变换矩阵
        Eigen::Matrix<float, 4, 4> T_curve_b;
        T_curve_b << Rb, Ob, 0, 0, 0, 1;
        //圆弧参数方程
        float thb;
        Eigen::Matrix<float, 4, 1> Pb;
        for(int i = 0; i <= 50; i++)
        {
            thb = (float)i/50*qG.b.l*qG.b.kappa;
            Pb << 1/qG.b.kappa*cos(thb), 1/qG.b.kappa*sin(thb), 0, 1;
            Pb = T_curve_b*Pb;
            catheter_b.addData(Pb(0, 0), Pb(1, 0), Pb(2, 0));
        }
    }
    else
    {
        Eigen::Matrix<float, 3, 1> Pb0 = Ta.block(0, 3, 3, 1);
        Eigen::Matrix<float, 3, 1> Pb1 = kine.fkine_qGeometry2Workspace(qG).P;
        catheter_b.addData(Pb0(0, 0), Pb0(1, 0), Pb0(2, 0));
        catheter_b.addData(Pb1(0, 0), Pb1(1, 0), Pb1(2, 0));
    }

    for(int i = 0; i < 4; i++)
    {
        p_plot[i]->addCurve(&catheter_a);
        p_plot[i]->addCurve(&catheter_b);
    }
}