//
// Created by hsh on 2023/3/4.
//

#include "omega_com.h"
#include <QDebug>
#include <QThread>

Omega7_Communicator::Omega7_Communicator(QObject *parent) {
    memset(pose, 0, sizeof(double)*6);
    t0 = 0; t1 = 0;
    freq = 0;
    done = 0;
    encNum = 7;
    grip = 0;

    QObject::connect(&this->timer, SIGNAL(QTimer::timeout), this, SLOT(Omega7_Communicator::loop), Qt::UniqueConnection);

    timer.start(1);
}

Omega7_Communicator::~Omega7_Communicator() noexcept {

    this->timer.deleteLater();

}

void Omega7_Communicator::continueQueryPose() {
    // required to access joint angles
    dhdEnableExpertMode ();

    // open the first available device
    if (dhdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
        dhdSleep (2.0);
        return;
    }

    // identify device
    printf ("%s device detected\n\n", dhdGetSystemName());

    // emulate button on supported devices
    dhdEmulateButton (DHD_ON);

    // display instructions
    printf ("press BUTTON to enable virtual spring\n");
    printf ("         'q' to quit\n\n");

    // enable force
    dhdEnableForce (DHD_ON);


    // haptic loop
    while (!done) {

        // retrieve joint angles
        if (dhdGetPositionAndOrientationDeg(&pose[0], &pose[1], &pose[2], &pose[3], &pose[4], &pose[5]) < DHD_NO_ERROR) {
            printf ("error: cannot get joint angles (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // compute force to apply
        if (spring) {
            fx = - K * pose[0];
            fy = - K * pose[1];
            fz = - K * pose[2];
        }
        else fx = fy = fz = 0.0;

        // retrieve joint angles
        if (dhdGetDeltaJointAngles (&j0, &j1, &j2) < DHD_NO_ERROR) {
            printf ("error: cannot get joint angles (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // compute jacobian
        if (dhdDeltaJointAnglesToJacobian (j0, j1, j2, J) < DHD_NO_ERROR) {
            printf ("error: cannot compute jacobian (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // compute joint torques required for gravity compensation
        if (dhdDeltaGravityJointTorques (j0, j1, j2, &g0, &g1, &g2) < DHD_NO_ERROR) {
            printf ("error: cannot compute gravity compensation joint torques (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // compute joint torques Q = ((J)T) * F
        MatTranspose (J, Jt);
        q0 = Jt[0][0]*fx + Jt[0][1]*fy + Jt[0][2]*fz;
        q1 = Jt[1][0]*fx + Jt[1][1]*fy + Jt[1][2]*fz;
        q2 = Jt[2][0]*fx + Jt[2][1]*fy + Jt[2][2]*fz;

        // combine gravity compensation and requested force
        q0 += g0;
        q1 += g1;
        q2 += g2;

        // apply joint torques
        if ((sat = dhdSetDeltaJointTorques (q0, q1, q2)) < DHD_NO_ERROR) {
            printf ("error: cannot set joint torques (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // display refresh rate and position at 10Hz
        t1 = dhdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // retrieve information to display
            freq = dhdGetComFreq ();
            t0   = t1;

            // write down position
            if (dhdGetPositionAndOrientationDeg(&pose[0], &pose[1], &pose[2], &pose[3], &pose[4], &pose[5]) < 0) {
                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            if (sat == DHD_MOTOR_SATURATED) printf ("[*] ");
            else                            printf ("[-] ");
            printf ("q = (%+0.03f, %+0.03f, %+0.03f) [Nm]  |  freq = %0.02f [kHz]   px = %+0.03f, py = %+0.03f, pz = %+0.03f, oa = %+0.03f, ob = %+0.03f, og = %+0.03f    \n", q0, q1, q2, freq, pose[0], pose[1], pose[2], pose[3], pose[4], pose[5]);

            // user input
            if (dhdGetButtonMask()) spring = true;
            else                    spring = false;
        }
    }

    // close the connection
    dhdClose ();
    emit finishWork();
}

void Omega7_Communicator::stopQueryPose() {
    this->done = 1;
}

void Omega7_Communicator::loop() {
    emit sendData(pose);
}