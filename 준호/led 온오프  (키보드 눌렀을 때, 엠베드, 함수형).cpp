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

// Blinking rate in milliseconds
Thread thread;
Serial pc(SERIAL_TX,SERIAL_RX);

char num=0;

int time_rate=500;

bool flag=false;

int main()
{
    pc.baud(115200);
        
    while (true) {
			led_control();
    }
}

void led_control() {
	
		if(pc.readable()){
			 num = pc.getc();
			 if(num =='A'){
						led3 =!led3;
			 }
		}
}
