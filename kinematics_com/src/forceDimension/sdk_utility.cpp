//
// Created by hsh on 2023/2/26.
//

#include "sdk_utility.h"

bool openDevice() {
    if (drdOpen() < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr ());
        return false;
    }
    printf("Open Device.\n");

    if (!drdIsSupported()) {
        printf("Unsupported device\n");
        printf("existing...\n");
        drdClose();
        return false;
    }
    printf("%s haptic device detection\n\n", dhdGetSystemName());

    return true;
}

int GetEncoderNumber() {
    int encCount = 0;
    switch (dhdGetSystemType()) {
        case DHD_DEVICE_DELTA3:
        case DHD_DEVICE_OMEGA3:
        case DHD_DEVICE_FALCON:
            encCount = 3;
            break;
        case DHD_DEVICE_OMEGA33:
        case DHD_DEVICE_OMEGA33_LEFT:
            encCount = 6;
            break;
        case DHD_DEVICE_OMEGA331:
        case DHD_DEVICE_OMEGA331_LEFT:
            encCount = 7;
            break;
        case DHD_DEVICE_CONTROLLER:
        case DHD_DEVICE_CONTROLLER_HR:
            encCount = 8;
            break;
        default:
            encCount = 8;
            break;
    }
    return encCount;
}

int GetJointAngles(int* enc, int encNum) {
    if (dhdGetEnc(enc, -1) < 0) {
        printf ("error: cannot read encoders (%s)\n", dhdErrorGetLastStr ());
        return 0;
    }
    return 1;
}




// sdk examples:
int autocenter() {
    double px, py, pz;
    double fx, fy, fz;
    double freq   = 0.0;
    double t1,t0  = dhdGetTime ();
    int    done   = 0;

    // center of workspace
    double nullPose[DHD_MAX_DOF] = { 0.0, 0.0, 0.0,  // base  (translations)
                                     0.0, 0.0, 0.0,  // wrist (rotations)
                                     0.0 };          // gripper

    // message
    printf ("Force Dimension - Auto Center Gravity %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // open the first available device
    if (drdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }

    // print out device identifier
    if (!drdIsSupported ()) {
        printf ("unsupported device\n");
        printf ("exiting...\n");
        dhdSleep (2.0);
        drdClose ();
        return -1;
    }
    printf ("%s haptic device detected\n\n", dhdGetSystemName ());

    // perform auto-initialization
    if (!drdIsInitialized () && drdAutoInit () < 0) {
        printf ("error: auto-initialization failed (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }
    else if (drdStart () < 0) {
        printf ("error: regulation thread failed to start (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }

    // move to center
    drdMoveTo (nullPose);

    // stop regulation thread (but leaves forces on)
    drdStop (true);

    // display instructions
    printf ("press 'q' to quit\n");
    printf ("      'c' to re-center end-effector (all axis)\n");
    printf ("      'p' to re-center position only\n");
    printf ("      'r' to re-center rotation only\n");
    printf ("      'g' to close gripper only\n\n");

    // haptic loop
    while (!done) {

        // apply zero force
        if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) < DHD_NO_ERROR) {
            printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr ());
            done = 1;
        }

        // display refresh rate and position at 10Hz
        t1 = dhdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // retrieve information to display
            freq = dhdGetComFreq ();
            t0   = t1;

            // write down position
            if (dhdGetPosition (&px, &py, &pz) < 0) {
                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            if (dhdGetForce (&fx, &fy, &fz) < 0) {
                printf ("error: cannot read force (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            printf ("p (%+0.03f %+0.03f %+0.03f) m  |  f (%+0.01f %+0.01f %+0.01f) N  |  freq [%0.02f kHz]       \r", px, py, pz, fx, fy, fz, freq);

            // user input
            if (dhdKbHit ()) {
                switch (dhdKbGet ()) {
                    case 'q': done = 1; break;
                    case 'c':
                        drdRegulatePos  (true);
                        drdRegulateRot  (true);
                        drdRegulateGrip (true);
                        drdStart();
                        drdMoveTo (nullPose);
                        drdStop(true);
                        break;
                    case 'p':
                        drdRegulatePos  (true);
                        drdRegulateRot  (false);
                        drdRegulateGrip (false);
                        drdStart();
                        drdMoveToPos (0.0, 0.0, 0.0);
                        drdStop(true);
                        break;
                    case 'r':
                        drdRegulatePos  (false);
                        drdRegulateRot  (true);
                        drdRegulateGrip (false);
                        drdStart();
                        drdMoveToRot (0.0, 0.0, 0.0);
                        drdStop(true);
                        break;
                    case 'g':
                        drdRegulatePos  (false);
                        drdRegulateRot  (false);
                        drdRegulateGrip (true);
                        drdStart();
                        drdMoveToGrip (0.0);
                        drdStop(true);
                        break;
                }
            }
        }
    }

    // close the connection
    printf ("cleaning up...                                                           \n");
    drdClose ();

    // happily exit
    printf ("\ndone.\n");


    return 0;
}


int autoinit() {
    double px, py, pz;
    double fx, fy, fz;
    double freq   = 0.0;
    double t1,t0  = dhdGetTime ();
    int    done   = 0;

    // message
    printf ("Force Dimension - Automatic Initialization %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // required to change asynchronous operation mode
    dhdEnableExpertMode ();

    // open the first available device
    if (drdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }

    // print out device identifier
    if (!drdIsSupported()) {
        printf ("unsupported device\n");
        printf ("exiting...\n");
        dhdSleep (2.0);
        drdClose ();
        return -1;
    }
    printf ("%s haptic device detected\n\n", dhdGetSystemName());

    // perform auto-initialization
    printf ("initializing...\r");
    fflush (stdout);
    if (drdAutoInit () < 0) {
        printf ("error: auto-initialization failed (%s)\n", dhdErrorGetLastStr ());
        drdClose ();
        dhdSleep (2.0);
        return -1;
    }

    // perform initialization check (optional)
    printf ("checking initialization...\r");
    fflush (stdout);
    if (drdCheckInit () < 0) {
        printf ("error: device initialization check failed (%s)\n", dhdErrorGetLastStr ());
        drdClose ();
        dhdSleep (2.0);
        return -1;
    }

    // report success
    printf ("device successfully initialized\n\n");

    // stop regulation (and leave force enabled)
    drdStop (true);

    // display instructions
    printf ("press 'q' to quit\n\n");

    // haptic loop
    while (!done) {

        // apply zero force
        if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) < DHD_NO_ERROR) {
            printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // display refresh rate and position at 10Hz
        t1 = dhdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // update timestamp
            t0 = t1;

            // retrieve information to display
            freq = dhdGetComFreq ();

            // write down position
            if (dhdGetPosition (&px, &py, &pz) < 0) {
                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            if (dhdGetForce (&fx, &fy, &fz) < 0) {
                printf ("error: cannot read force (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            printf ("p (%+0.03f %+0.03f %+0.03f) m  |  f (%+0.01f %+0.01f %+0.01f) N  |  freq [%0.02f kHz]       \r", px, py, pz, fx, fy, fz, freq);

            // user input
            if (dhdKbHit() && dhdKbGet() == 'q') done = 1;
        }
    }

    // close the connection
    printf ("cleaning up...                                                           \n");
    drdClose ();

    // happily exit
    printf ("\ndone.\n");


    return 0;
}


int center() {
    double p[DHD_MAX_DOF];
    double r[3][3];
    double v[DHD_MAX_DOF];
    double f[DHD_MAX_DOF];
    double normf, normt;
    int    done  = 0;
    double t0    = dhdGetTime ();
    double t1    = t0;
    bool   base  = false;
    bool   wrist = false;
    bool   grip  = false;
    int    count = 0;
    int    res;

    // Eigen objects (mapped to the arrays above)
    Map<Vector3d> position(&p[0], 3);
    Map<Vector3d> force   (&f[0], 3);
    Map<Vector3d> torque  (&f[3], 3);
    Map<Vector3d> velpos  (&v[0], 3);
    Map<Vector3d> velrot  (&v[3], 3);
    Matrix3d center;
    Matrix3d rotation;

    // center of workspace
    center.setIdentity ();                           // rotation (matrix)
    double nullPose[DHD_MAX_DOF] = { 0.0, 0.0, 0.0,  // translation
                                     0.0, 0.0, 0.0,  // rotation (joint angles)
                                     0.0 };          // gripper

    // message
    printf ("Force Dimension - Constant Centering Example %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // open the first available device
    if (drdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }

    // print out device identifier
    if (!drdIsSupported ()) {
        printf ("unsupported device\n");
        printf ("exiting...\n");
        dhdSleep (2.0);
        drdClose ();
        return -1;
    }
    printf ("%s haptic device detected\n\n", dhdGetSystemName ());

    // perform auto-initialization
    if (!drdIsInitialized () && drdAutoInit () < 0) {
        printf ("error: auto-initialization failed (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }
    else if (drdStart () < 0) {
        printf ("error: regulation thread failed to start (%s)\n", dhdErrorGetLastStr ());
        dhdSleep (2.0);
        return -1;
    }

    // move to center
    drdMoveTo (nullPose);

    // request a null force (only gravity compensation will be applied)
    // this will only apply to unregulated axis
    drdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0,  // force
                                         0.0, 0.0, 0.0,  // torque
                                         0.0);           // gripper force

    // disable all axis regulation (but leave regulation thread running)
    drdRegulatePos  (base);
    drdRegulateRot  (wrist);
    drdRegulateGrip (grip);

    // display instructions
    printf ("press 'q' to quit\n");
    printf ("      'b' to free/hold base (translations)\n");
    printf ("      'w' to free/hold wrist (rotations)\n");
    printf ("      'g' to free/hold gripper\n\n");

    // display output header
    printf ("BASE  |  ");
    if (dhdHasActiveWrist ()) printf ("WRIST |  ");
    if (dhdHasGripper ())     printf ("GRIP  |  ");
    printf ("regulation  |  local   \n");
    printf ("---------");
    if (dhdHasActiveWrist ()) printf ("---------");
    if (dhdHasGripper ())     printf ("---------");
    printf ("-----------------------\n");

    // haptic loop
    while (!done) {

        // synchronize with regulation thread
        drdWaitForTick ();

        // get position/orientation/gripper and update Eigen rotation matrix
        drdGetPositionAndOrientation (&(p[0]), &(p[1]), &(p[2]),
                                      &(p[3]), &(p[4]), &(p[5]),
                                      &(p[6]), r);
        for (int i=0; i<3; i++) rotation.row(i) = Vector3d::Map(&r[i][0], 3);

        // get position/orientation/gripper velocity
        drdGetVelocity (&(v[0]), &(v[1]), &(v[2]),
                        &(v[3]), &(v[4]), &(v[5]),
                        &(v[6]));

        // compute base centering force
        force = - KP * position;

        // compute wrist centering torque
        AngleAxisd deltaRotation (rotation.transpose() * center);
        torque = rotation * (KR * deltaRotation.angle() * deltaRotation.axis());

        // compute gripper centering force
        f[6]  = - KG * (p[6] - 0.015);

        // scale force to a pre-defined ceiling
        if ((normf = force.norm()) > MAXF) force *= MAXF/normf;

        // scale torque to a pre-defined ceiling
        if ((normt = torque.norm()) > MAXT) torque *= MAXT/normt;

        // scale gripper force to a pre-defined ceiling
        if (f[6] >  MAXG) f[6] =  MAXG;
        if (f[6] < -MAXG) f[6] = -MAXG;

        // add damping
        force  -= KVP * velpos;
        torque -= KWR * velrot;
        f[6]   -= KVG * v[6];

        // apply centering force with damping
        res = drdSetForceAndTorqueAndGripperForce (f[0], f[1], f[2],  // force
                                                   f[3], f[4], f[5],  // torque
                                                   f[6]);             // gripper force
        if (res < DHD_NO_ERROR) {
            printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr ());
            done = 1;
        }

        // local loop refresh rate
        count++;

        // display refresh rate and position at 10Hz
        t1 = drdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // retrieve/compute information to display
            double freq = (double)count/(t1-t0)*1e-3;
            count = 0;
            t0 = t1;

            // print status
            if (base)    printf ("HOLD  |  ");
            else         printf ("free  |  ");
            if (dhdHasActiveWrist ()) {
                if (wrist) printf ("HOLD  |  ");
                else       printf ("free  |  ");
            }
            if (dhdHasGripper()) {
                if( grip)  printf ("HOLD  |  ");
                else       printf ("free  |  ");
            }
            printf ("  %0.2f kHz  |  %0.02f kHz       \r", dhdGetComFreq (), freq);

            // user input
            if (dhdKbHit ()) {
                switch (dhdKbGet ()) {
                    case 'q': done = 1; break;
                    case 'b':
                        base = !base;
                        drdRegulatePos  (base);
                        break;
                    case 'w':
                        wrist = !wrist;
                        drdRegulateRot  (wrist);
                        break;
                    case 'g':
                        grip = !grip;
                        drdRegulateGrip (grip);
                        break;
                }
            }
        }
    }

    // stop regulation
    drdStop ();

    // close the connection
    printf ("cleaning up...                                                           \n");
    drdClose ();

    // happily exit
    printf ("\ndone.\n");


    return 0;
}


int encoders() {
    int i;
    int done = 0;
    int enc[DHD_MAX_DOF];
    int encCount;

    // message
    printf ("Force Dimension - Encoder Reading Example %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // open the first available device
    if (dhdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
        dhdSleep (2.0);
        return -1;
    }

    // identify device
    printf ("%s device detected\n\n", dhdGetSystemName());

    // identify number of encoders to report based on device type
    switch (dhdGetSystemType ()) {
        case DHD_DEVICE_DELTA3:
        case DHD_DEVICE_OMEGA3:
        case DHD_DEVICE_FALCON:
            encCount = 3;
            break;
        case DHD_DEVICE_OMEGA33:
        case DHD_DEVICE_OMEGA33_LEFT:
            encCount = 6;
            break;
        case DHD_DEVICE_OMEGA331:
        case DHD_DEVICE_OMEGA331_LEFT:
            encCount = 7;
            break;
        case DHD_DEVICE_CONTROLLER:
        case DHD_DEVICE_CONTROLLER_HR:
        default:
            encCount = 8;
            break;
    }

    // display instructions
    printf ("press 'q' to quit\n\n");
    printf ("encoder values:\n");

    // configure device
    dhdEnableExpertMode();

    // haptic loop
    while (!done) {

        // apply zero force for convenience
        dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

        // read all available encoders
        if (dhdGetEnc (enc) < 0) {
            printf ("error: cannot read encoders (%s)\n", dhdErrorGetLastStr ());
            done = 1;
        }

        // print out encoders according to system type
        for (i=0; i<encCount; i++) printf ("%06d ", enc[i]);
        printf ("          \r");

        // check for exit condition
        if (dhdKbHit() && dhdKbGet() == 'q') done = 1;
    }

    // close the connection
    dhdClose ();

    // happily exit
    printf ("\ndone.\n");
    return 0;
}


int gravity() {
    double px, py, pz;
    double fx, fy, fz;
    double t1,t0  = dhdGetTime ();
    int    done   = 0;

    // message
    printf ("Force Dimension - Gravity Compensation Example %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // open the first available device
    if (dhdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
        dhdSleep (2.0);
        return -1;
    }

    // identify device
    printf ("%s device detected\n\n", dhdGetSystemName());

    // display instructions
    printf ("press 'q' to quit\n\n");

    // enable force
    dhdEnableForce (DHD_ON);

    // haptic loop
    while (!done) {

        // apply zero force
        if (dhdSetForceAndTorqueAndGripperForce (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0) < DHD_NO_ERROR) {
            printf ("error: cannot set force (%s)\n", dhdErrorGetLastStr());
            done = 1;
        }

        // display refresh rate and position at 10Hz
        t1 = dhdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // update timestamp
            t0 = t1;

            // retrieve position
            if (dhdGetPosition (&px, &py, &pz) < DHD_NO_ERROR) {
                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }

            // retrieve force
            if (dhdGetForce (&fx, &fy, &fz) < DHD_NO_ERROR) {
                printf ("error: cannot read force (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }

            // display status
            printf ("p (%+0.03f %+0.03f %+0.03f) m  |  f (%+0.01f %+0.01f %+0.01f) N  |  freq %0.02f kHz\r", px, py, pz, fx, fy, fz, dhdGetComFreq());

            // user input
            if (dhdKbHit() && dhdKbGet() == 'q') done = 1;
        }
    }

    // close the connection
    dhdClose ();

    // happily exit
    printf ("\ndone.\n");
    return 0;
}

inline void
MatTranspose (const double a[3][3],
              double       m[3][3])
{
    m[0][0] = a[0][0];  m[0][1] = a[1][0];  m[0][2] = a[2][0];
    m[1][0] = a[0][1];  m[1][1] = a[1][1];  m[1][2] = a[2][1];
    m[2][0] = a[0][2];  m[2][1] = a[1][2];  m[2][2] = a[2][2];
}

int jacobian() {
    const double K = 60;

    double px, py, pz;
    double oa, ob, og;
    double fx, fy, fz;
    double j0, j1, j2;
    double g0, g1, g2;
    double q0, q1, q2;
    double J[3][3];
    double Jt[3][3];
    double freq   = 0.0;
    double t1,t0  = dhdGetTime ();
    bool   spring = false;
    int    done   = 0;
    int    sat;

    // message
    printf ("Force Dimension - Jacobian Usage Example %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // required to access joint angles
    dhdEnableExpertMode ();

    // open the first available device
    if (dhdOpen () < 0) {
        printf ("error: cannot open device (%s)\n", dhdErrorGetLastStr());
        dhdSleep (2.0);
        return -1;
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

//        // retrieve joint angles
//        if (dhdGetPositionAndOrientationDeg(&px, &py, &pz, &oa, &ob, &og) < DHD_NO_ERROR) {
//            printf ("error: cannot get joint angles (%s)\n", dhdErrorGetLastStr());
//            done = 1;
//        }
//
//        // compute force to apply
//        if (spring) {
//            fx = - K * px;
//            fy = - K * py;
//            fz = - K * pz;
//        }
//        else fx = fy = fz = 0.0;
//
//        // retrieve joint angles
//        if (dhdGetDeltaJointAngles (&j0, &j1, &j2) < DHD_NO_ERROR) {
//            printf ("error: cannot get joint angles (%s)\n", dhdErrorGetLastStr());
//            done = 1;
//        }
//
//        // compute jacobian
//        if (dhdDeltaJointAnglesToJacobian (j0, j1, j2, J) < DHD_NO_ERROR) {
//            printf ("error: cannot compute jacobian (%s)\n", dhdErrorGetLastStr());
//            done = 1;
//        }
//
//        // compute joint torques required for gravity compensation
//        if (dhdDeltaGravityJointTorques (j0, j1, j2, &g0, &g1, &g2) < DHD_NO_ERROR) {
//            printf ("error: cannot compute gravity compensation joint torques (%s)\n", dhdErrorGetLastStr());
//            done = 1;
//        }
//
//        // compute joint torques Q = ((J)T) * F
//        MatTranspose (J, Jt);
//        q0 = Jt[0][0]*fx + Jt[0][1]*fy + Jt[0][2]*fz;
//        q1 = Jt[1][0]*fx + Jt[1][1]*fy + Jt[1][2]*fz;
//        q2 = Jt[2][0]*fx + Jt[2][1]*fy + Jt[2][2]*fz;
//
//        // combine gravity compensation and requested force
//        q0 += g0;
//        q1 += g1;
//        q2 += g2;
//
//        // apply joint torques
//        if ((sat = dhdSetDeltaJointTorques (q0, q1, q2)) < DHD_NO_ERROR) {
//            printf ("error: cannot set joint torques (%s)\n", dhdErrorGetLastStr());
//            done = 1;
//        }

        // display refresh rate and position at 10Hz
        t1 = dhdGetTime ();
        if ((t1-t0) > REFRESH_INTERVAL) {

            // retrieve information to display
            freq = dhdGetComFreq ();
            t0   = t1;

            // write down position
            if (dhdGetPositionAndOrientationDeg(&px, &py, &pz, &oa, &ob, &og) < 0) {
                printf ("error: cannot read position (%s)\n", dhdErrorGetLastStr());
                done = 1;
            }
            if (sat == DHD_MOTOR_SATURATED) printf ("[*] ");
            else                            printf ("[-] ");
            if (spring) printf(" sp ");
            else printf(" xsp ");
            printf ("q = (%+0.03f, %+0.03f, %+0.03f) [Nm]  |  f = %0.02f [kHz]   px = %+0.03f, py = %+0.03f, pz = %+0.03f, oa = %+0.03f, ob = %+0.03f, og = %+0.03f    \r", q0, q1, q2, freq, px, py, pz, oa, ob, og);

            // user input
            if (dhdGetButtonMask()) spring = true;
            else                    spring = false;
            if (dhdKbHit() && dhdKbGet() == 'q') done = 1;
        }
    }

    // close the connection
    dhdClose ();

    // happily exit
    printf ("\ndone.\n");
    return 0;
}


int mirror() {
    double mx0, my0, mz0;
    double mx, my, mz;
    double sx0, sy0, sz0;
    double sx, sy, sz;
    double tx, ty, tz;
    double fx, fy, fz;
    double time;
    double refTime = dhdGetTime ();
    double Kslave = DEFAULT_K_SLAVE;
    double Kbox   = DEFAULT_K_BOX;
    double scale   = 1.0;
    bool   engaged = false;
    int    done    = 0;
    int    master, slave;


    // message
    printf ("Force Dimension - Master Slave Example %s\n", dhdGetSDKVersionStr());
    printf ("Copyright (C) 2001-2022 Force Dimension\n");
    printf ("All Rights Reserved.\n\n");

    // open and initialize 2 devices
    for (int dev=0; dev<2; dev++) {

        // open device
        if (drdOpenID (dev) < 0) {
            printf ("error: not enough devices found\n");
            dhdSleep (2.0);
            for (int j=0; j<=dev; j++) drdClose (j);
            return -1;
        }

        // exclude some device types that have not been fully tested with 'mirror'
        bool incompatible = false;
        switch (dhdGetSystemType ()) {
            case DHD_DEVICE_SIGMA331:
            case DHD_DEVICE_SIGMA331_LEFT:
                incompatible = true;
                break;
        }

        // check that device is supported
        if (incompatible || !drdIsSupported()) {
            printf ("error: unsupported device (%s)\n", dhdGetSystemName(dev));
            dhdSleep (2.0);
            for (int j=0; j<=dev; j++) drdClose (j);
            return -1;
        }

        // initialize Falcon by hand if necessary
        if (!drdIsInitialized() && dhdGetSystemType() == DHD_DEVICE_FALCON) {
            printf ("please initialize Falcon device...\r"); fflush(stdout);
            while (!drdIsInitialized()) dhdSetForce (0.0, 0.0, 0.0);
            printf ("                                  \r");
            dhdSleep (0.5);
        }

        // initialize if necessary
        if (!drdIsInitialized (dev) && (drdAutoInit (dev) < 0)) {
            printf ("error: initialization failed (%s)\n", dhdErrorGetLastStr ());
            dhdSleep (2.0);
            for (int j=0; j<=dev; j++) drdClose (j);
            return -1;
        }

        // start robot control loop
        if (drdStart (dev) < 0) {
            printf ("error: control loop failed to start properly (%s)\n", dhdErrorGetLastStr ());
            dhdSleep (2.0);
            for (int j=0; j<=dev; j++) drdClose (j);
            return -1;
        }
    }

    // default role assignment
    master = 0;
    slave  = 1;

    // prefer Falcon as master
    if (dhdGetSystemType (0) != DHD_DEVICE_FALCON && dhdGetSystemType (1) == DHD_DEVICE_FALCON) {
        master = 1;
        slave  = 0;
    }

    // give preference to omega.3 as slave
    if (dhdGetSystemType (0) == DHD_DEVICE_OMEGA3 && dhdGetSystemType (1) != DHD_DEVICE_OMEGA3) {
        master = 1;
        slave  = 0;
    }

    // if a device is virtual, make it the master
    if (dhdGetComMode (1) == DHD_COM_MODE_VIRTUAL) {
        master = 1;
        slave  = 0;
    }

    dhdEmulateButton(DHD_ON, master);

    ushort mastersn, slavesn;
    dhdGetSerialNumber (&mastersn, master);
    dhdGetSerialNumber (&slavesn, slave);
    printf ("%s haptic device [sn: %04d] as master\n", dhdGetSystemName(master), mastersn);
    printf ("%s haptic device [sn: %04d] as slave\n", dhdGetSystemName(slave), slavesn);

    // display instructions
    printf ("\n");
    printf ("press 's' to decrease scaling factor\n");
    printf ("      'S' to increase scaling factor\n");
    printf ("      'k' to decrease virtual stiffness\n");
    printf ("      'K' to increase virtual stiffness\n");
    printf ("      'q' to quit\n\n");

    // center both devices
    drdMoveToPos (0.0, 0.0, 0.0, false, master);
    drdMoveToPos (0.0, 0.0, 0.0, true,  slave);
    while (drdIsMoving (master) || drdIsMoving (slave)) drdWaitForTick (master);

    // initialize slave target position to current position
    drdGetPositionAndOrientation (&tx, &ty, &tz, NULL, NULL, NULL, NULL, NULL, slave);

    // stop regulation on master, stop motion filters on slave
    drdStop (true, master);
    dhdSetForce (0.0, 0.0, 0.0, master);
    drdEnableFilter (false, slave);

    // master slave loop
    while (!done) {

        // detect button press
        if (!engaged && dhdGetButtonMask(master) != 0x00) {

            // store start position
            dhdGetPosition (&mx0, &my0, &mz0, master);
            dhdGetPosition (&sx0, &sy0, &sz0, slave);

            // enable slave control
            engaged = true;
        }

            // detect button release, disable slave control
        else if (engaged && dhdGetButtonMask(master) == 0x00) engaged = false;

        // if slave control is enabled, move the slave to match the master movement
        if (engaged) {

            // get master position
            dhdGetPosition (&mx, &my, &mz, master);

            // compute target slave position
            tx = sx0 + scale*(mx - mx0);
            ty = sy0 + scale*(my - my0);
            tz = sz0 + scale*(mz - mz0);

            // send slave to target position
            drdTrackPos (tx, ty, tz, slave);
        }

        // apply forces if slave control is enabled
        if (engaged) {

            // get current actual slave position
            drdGetPositionAndOrientation (&sx, &sy, &sz, NULL, NULL, NULL, NULL, NULL, slave);

            // compute force from slave regulation
            fx = -Kslave * (tx-sx);
            fy = -Kslave * (ty-sy);
            fz = -Kslave * (tz-sz);

            // add force from virtual authorized workspace
            if (sx >  SLAVE_BOX_SIZE/2.0) fx += -Kbox * (sx -  SLAVE_BOX_SIZE/2.0) / scale;
            if (sx < -SLAVE_BOX_SIZE/2.0) fx += -Kbox * (sx - -SLAVE_BOX_SIZE/2.0) / scale;
            if (sy >  SLAVE_BOX_SIZE/2.0) fy += -Kbox * (sy -  SLAVE_BOX_SIZE/2.0) / scale;
            if (sy < -SLAVE_BOX_SIZE/2.0) fy += -Kbox * (sy - -SLAVE_BOX_SIZE/2.0) / scale;
            if (sz >  SLAVE_BOX_SIZE/2.0) fz += -Kbox * (sz -  SLAVE_BOX_SIZE/2.0) / scale;
            if (sz < -SLAVE_BOX_SIZE/2.0) fz += -Kbox * (sz - -SLAVE_BOX_SIZE/2.0) / scale;
        }

            // otherwise, only apply gravity compensation
        else fx = fy = fz = 0.0;

        // apply force to master
        dhdSetForce (fx, fy, fz, master);

        // print stats and check for exit condition
        time = dhdGetTime ();
        if (time-refTime > 0.04) {
            printf ("[%c] scale = %0.03f | K = %04d | master %0.02f kHz | slave %0.02f kHz            \r",
                    (engaged ? '*' : ' '), scale, (int)Kslave, dhdGetComFreq (master), drdGetCtrlFreq (slave));
            refTime = time;
            if (!drdIsRunning (slave)) done = -1;
            if (dhdKbHit ()){
                switch (dhdKbGet ()) {
                    case 'q': done = 1;   break;
                    case 'k': Kslave -= 100.0; break;
                    case 'K': Kslave += 100.0; break;
                    case 's': if (!engaged) scale = MAX(MIN_SCALE, scale-0.1); break;
                    case 'S': if (!engaged) scale = MIN(MAX_SCALE, scale+0.1); break;
                }
            }
        }
    }

    // report exit cause
    printf ("                                                                           \r");
    if (done == -1) printf ("\nregulation finished abnormally on slave device\n");
    else            printf ("\nexiting on user request\n");

    // close the connection
    drdClose (slave);
    drdClose (master);

    // exit
    printf ("\ndone.\n");
    return 0;
}


int multithread() {
    return 0;
}


int segment() {
    return 0;
}


int sensor() {
    return 0;
}


int viscosity() {
    return 0;
}

int wrist() {
    return 0;
}