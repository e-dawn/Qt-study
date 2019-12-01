#ifndef LED_CTL_H
#define LED_CTL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>


int init_led();
void change_led(int value);
void led_close();

#endif // LED_CTL_H
