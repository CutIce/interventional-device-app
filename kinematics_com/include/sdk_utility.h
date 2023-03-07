//
// Created by hsh on 2023/2/26.
//

#ifndef OMEGA7_COM_SDK_UTILITY_H
#define OMEGA7_COM_SDK_UTILITY_H

#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINCES
#include <math.h>

#include "drdc.h"
#include "dhdc.h"

#include "Eigen/Eigen"
using namespace Eigen;


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

bool openDevice();
int GetEncoderNumber();
int GetJointAngles();


// examples:
int autocenter();
int autoinit();
int center();
int encoders();
int gravity();
int jacobian();
int mirror();
int multithread();
int segment();
int sensor();
int viscosity();
int wrist();

#endif //OMEGA7_COM_SDK_UTILITY_H
