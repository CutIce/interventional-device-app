#include <QApplication>
#include <QPushButton>
#include "sdk_utility.h"


int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();

    int encNumber = 0;
    double px, py, pz;
    double oa, ob, og;
    double fx, fy, fz;
    double freq = 0.0;
    double t1, t0 = dhdGetTime();
    bool   spring = false;
    int    done   = 0;
    int    sat;

    dhdEnableExpertMode();
    if (dhdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
        dhdSleep (2.0);
        return -1;
    }

    // identify device
    printf ("%s device detected\n\n", dhdGetSystemName());

    printf ("%s device detected\n\n", dhdGetSystemName());


    dhdEmulateButton (DHD_ON);
    dhdEnableForce(DHD_ON);

    while (!done) {
        t1 = dhdGetTime();
        if ((t1 - t0) > REFRESH_INTERVAL) {
            if (dhdGetPositionAndOrientationDeg(&px, &py, &pz, &oa, &ob, &og) < 0) {
                printf("Error: %s\n", dhdErrorGetLastStr());
                done = 1;
            }

            freq = dhdGetComFreq();
            t0 = t1;
            printf("px : %f, py : %f, pz : %f, oa : %f, ob : %f, og : %f \n", px, py, pz, oa, ob, og);
        }
    }

//    jacobian();


// required to access joint angles
//    dhdEnableExpertMode ();
//
//    // open the first available device
//    if (dhdOpen () < 0) {
//        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
//        dhdSleep (2.0);
//        return -1;
//    }
//
//    // identify device
//    printf ("%s device detected\n\n", dhdGetSystemName());
//
//    // emulate button on supported devices
//    dhdEmulateButton (DHD_ON);
//    // enable force
//    dhdEnableForce (DHD_ON);
//
//    // haptic loop
//    while (!done) {
//        // display refresh rate and position at 10Hz
//        t1 = dhdGetTime ();
//        if ((t1-t0) > REFRESH_INTERVAL) {
//
//            // retrieve information to display
//            freq = dhdGetComFreq ();
//            t0   = t1;
//
//            // write down position
//            if (dhdGetPositionAndOrientationDeg(&px, &py, &pz, &oa, &ob, &og) < 0) {
//                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
//                done = 1;
//            }
//            if (sat == DHD_MOTOR_SATURATED) printf ("[*] ");
//            else                            printf ("[-] ");
//            if (spring) printf(" sp ");
//            else printf(" xsp ");
////            printf ("q = (%+0.03f, %+0.03f, %+0.03f) [Nm]  |  f = %0.02f [kHz]   px = %+0.03f, py = %+0.03f, pz = %+0.03f, oa = %+0.03f, ob = %+0.03f, og = %+0.03f    \r", q0, q1, q2, freq, px, py, pz, oa, ob, og);
//            printf ("f = %0.02f [kHz]   px = %+0.03f, py = %+0.03f, pz = %+0.03f, oa = %+0.03f, ob = %+0.03f, og = %+0.03f    \r", freq, px, py, pz, oa, ob, og);
//
//            // user input
//            if (dhdGetButtonMask()) spring = true;
//            else                    spring = false;
//            if (dhdKbHit() && dhdKbGet() == 'q') done = 1;
//        }
//    }
//    // close the connection
//    dhdClose ();
//
//    // happily exit
//    printf ("\ndone.\n");
    return 0;


//    return 0;

//    autocenter();
//    encoders();



    return QApplication::exec();
}
