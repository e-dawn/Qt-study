#ifndef DCM_MOTOR_H
#define DCM_MOTOR_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#define DCM_IOCTRL_SETPWM 			(0x10)
#define DCM_TCNTB0				(16384)


bool start_dcmotor();
void changeV_dcmotor(int setpwm);
void stop_dcmotor();

#endif // DCM_MOTOR_H
