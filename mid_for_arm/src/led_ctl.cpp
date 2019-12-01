#include "led_ctl.h"

int led_fd;
unsigned int LEDWORD;
unsigned char LEDCODE[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int init_led()
{
    led_fd=open("/dev/led/0raw",O_RDWR);
    if (led_fd < 0) {
        printf("####Led device open fail####\n");
        return (0);
    }
    return 1;
}

void change_led(int value)
{
    LEDWORD=LEDCODE[value/10]<<8 | LEDCODE[value%10];
    ioctl(led_fd,0x12,LEDWORD);
}

void led_close()
{
    close(led_fd);
}
