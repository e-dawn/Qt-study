#ifndef ADC_H
#define ADC_H


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "s3c2410-adc.h"

#define ADC_DEV		"/dev/adc/0raw"


int init_ADdevice(void);
int GetADresult(int channel);
float get_value(int i);
void close_adc();

#endif // ADC_H
