#include "dcm_motor.h"

static int dcm_fd = -1;
char *DCM_DEV="/dev/dcm/0raw";
int factor = DCM_TCNTB0/1024;

bool start_dcmotor()
{
    if((dcm_fd=open(DCM_DEV, O_WRONLY))<0){
            printf("Error opening %s device\n", DCM_DEV);
            return 0;
    }
    return 1;
}

void changeV_dcmotor(int setpwm)
{
    ioctl(dcm_fd, DCM_IOCTRL_SETPWM, (setpwm * factor));
}

void stop_dcmotor()
{
    close(dcm_fd);
}
