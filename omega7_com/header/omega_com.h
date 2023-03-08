//
// Created by hsh on 2023/2/23.
//

#ifndef OMEGA7_COM_OMEGA_COM_H
#define OMEGA7_COM_OMEGA_COM_H

#include <QObject>
#include <QTimer>
#include "sdk/drdc.h"
#include "sdk/dhdc.h"
#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <Eigen/Eigen>
using namespace Eigen;

#define REFRESH_INTERVAL 0.1
#define REFRESH_INTERVAL  0.1   // sec
#define KP    100.0
#define KVP    10.0
#define MAXF    4.0
#define KR      0.3
#define KWR     0.02
#define MAXT    0.1
#define KG    100.0
#define KVG     5.0
#define MAXG    1.0

#define DEFAULT_K_SLAVE   500.0
#define DEFAULT_K_BOX     500.0
#define SLAVE_BOX_SIZE      0.06
#define MIN_SCALE           0.2
#define MAX_SCALE           5.0

#define MIN(a,b) ((a)<(b))?(a):(b)
#define MAX(a,b) ((a)>(b))?(a):(b)

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const double K = 60;

inline void
MatTranspose (const double a[3][3],
              double       m[3][3])
{
    m[0][0] = a[0][0];  m[0][1] = a[1][0];  m[0][2] = a[2][0];
    m[1][0] = a[0][1];  m[1][1] = a[1][1];  m[1][2] = a[2][1];
    m[2][0] = a[0][2];  m[2][1] = a[1][2];  m[2][2] = a[2][2];
}


class Omega7_Communicator: public QObject {
    Q_OBJECT

    int done;
    int encNum;
    int sat;
    int spring;
    double pose[6];
    double grip;
    double force[3];
    double freq;
    double fx, fy, fz;
    double j0, j1, j2;
    double g0, g1, g2;
    double q0, q1, q2;
    double J[3][3];
    double Jt[3][3];
    double t0;
    double t1;

public:
    explicit Omega7_Communicator(QObject *parent = nullptr);
    ~Omega7_Communicator();

signals:
    void sendData(double* pose);
    void finishWork();

public slots:
    void continueQueryPose();
    void stopQueryPose();
    void loop();


public:
    QTimer timer;
};


#endif //OMEGA7_COM_OMEGA_COM_H
