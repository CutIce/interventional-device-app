//
// Created by hsh on 2023/3/5.
//

#ifndef OMEGA7_COM_KINE_SHOW_H
#define OMEGA7_COM_KINE_SHOW_H

#include <QWidget>
#include "QPlot3D.h"
#include <QtCore>


QT_BEGIN_NAMESPACE
namespace Ui { class kine_show; }
QT_END_NAMESPACE

class Kinematic_Displayer : public QWidget {
    Q_OBJECT

private:
    Ui::kine_show *ui;

    QPlot3D plot;
    QPlot3D plot_xz;
    QPlot3D plot_xy;
    QPlot3D plot_yz;
    QPlot3D *p_plot[4] = {&plot, &plot_xz, &plot_xy, &plot_yz};
    QCurve3D catheter_a;
    QCurve3D catheter_b;

    QLabel *pLabel_steer_control[6];
    QSlider *pSlider_steer_control[6];
    QDoubleSpinBox *pSpinBox_steer_control[6];

    QPushButton *pButtun_workspace[6][2];
    QTextBrowser *Text_JS_singular_value;

public:
    explicit Kinematic_Displayer(QWidget *parent = nullptr);

    void plotInit(void);
    void plotCatheter(void);

    ~Kinematic_Displayer() override;
};


#endif //OMEGA7_COM_KINE_SHOW_H
