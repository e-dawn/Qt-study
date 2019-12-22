#include "adc.h"

static int adc_fd = -1;

int init_ADdevice(void)
{
        if((adc_fd=open(ADC_DEV, O_RDWR))<0){
                printf("Error opening %s adc device\n", ADC_DEV);
                return 0;
        }
        return 1;
}

int GetADresult(int channel)
{
        int PRESCALE=0XFF;
        int data=ADC_WRITE(channel, PRESCALE);
        write(adc_fd, &data, sizeof(data));
        read(adc_fd, &data, sizeof(data));
        return data;
}

float get_value(int i)
{
        return ((float)GetADresult(i))/1024.0;
}

void close_adc()
{
    close(adc_fd);
}
