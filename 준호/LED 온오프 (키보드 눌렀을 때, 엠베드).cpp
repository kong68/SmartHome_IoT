/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
 
 
#include "mbed.h"
#include "platform/mbed_thread.h"
#include "rtos.h"
#define BLINKING_RATE_MS                                                    500

//PWM 기능 이용
PwmOut led3(D6);        

int i =0;
//int 1Hz_cnt=0;


// Blinking rate in milliseconds
Thread thread;
Serial pc(SERIAL_TX,SERIAL_RX);

char num=0;

int time_rate=500;

bool flag=false;


// LED 점멸 함수
//void led_thread() {
//    PwmOut led3(D6); 
//    while (true) {
//        led3 =!led3;
//        thread_sleep_for(time_rate);
//    }
//}


int main()
{
    pc.baud(115200);
        
    while (true) {
        if(pc.readable()){
           num = pc.getc();
           if(num =='A'){
                led3 =!led3;
           }
        }
    }
}
