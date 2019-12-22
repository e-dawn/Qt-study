#include "led_ctl.h"


unsigned int LEDWORD;
unsigned char LEDCODE[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int init_led()
{
    int led_fd=open("/dev/led/0raw",O_RDWR);
    if (led_fd < 0) {
        printf("####Led device open fail####\n");
        return 0;
    }
    return led_fd;
}

void change_led(int value, int led_fd)
{
    LEDWORD=LEDCODE[value/10]<<8 | LEDCODE[value%10];
    ioctl(led_fd,0x12,LEDWORD);
}

void led_close(int led_fd)
{
    close(led_fd);
}
