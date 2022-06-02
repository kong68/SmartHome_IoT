/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "Servo.h"
#include "platform/mbed_thread.h"
Timer timer;  //시간 세기 위해서 필요

Servo blind(D12);                                    // 서보모터 변수 선언 > 블라인드
AnalogIn cds_sensor(A1);                            // 조도센서 변수 선언

AnalogIn ain(A0) ; // 적외선 센서
DigitalOut led1(D2); // Digital Out Pin
DigitalOut led2(D3);
DigitalOut led3(D4);
DigitalOut led4(D5);
DigitalOut pb(D7);

//PwmOut pb(D7);  //부저
//PwmOut led1(D2);  //LED1
//PwmOut led2(D3);  //LED2
//PwmOut led3(D4);  //LED3
//PwmOut led4(D5);  //led4




int i =0;   //적외선 센서값 변수
int a = 0;  //시간 세는 변수
    
int blind_flag = 0;                                                           // 블라인드 상태를 저장하는 변수, 현재 닫혀있음

Ticker flipper;
Serial pc(SERIAL_TX,SERIAL_RX);


    
void time_count(){
    timer.start();  //타이머 스타트
    printf("Hello mbed!!\n");
    timer.stop();  //타이머 스탑
    a = timer.read();  //값 읽어오기
    printf("timer read ---> %d\n", a); //확인을 위해 출력
    
    
    }
    
    

    

    
    
void LED_ON(){
    
         i = ain.read_u16();  //적외선 값 받아오기
         pc.printf("%d\r\n", i);  //확인을 위해 출력
    
        if (i<10700){  //적외선과 가장 가까운곳 ex) 거실

            led1.write(0.0f); //LED꺼짐
            led2.write(0.05f); //LED 살짝 어두움
            led3.write(1.0f); //LED 밝음
            
            if (i<10600){
                led2.write(0.0f); //LED 꺼짐
                
                }
            }
        else if (i>=10700&&i<10900){  // 중간 ex) 복도
            led1.write(0.05f); //LED 살짝 어두움 
            led2.write(1.0f);  //LED 밝음
            led3.write(0.0f);  //LED 꺼짐
            }
        else if (i>=10900&& i<11100){   //적외선과 가장 먼곳 ex) 신발장
            led1.write(1.0f); //LED 밝음
            led2.write(0.0f);  //LED 꺼짐
            led3.write(0.0f);  //LED 꺼짐
            }
            
        else if (i> 11100){ // 아무도 안서있음 불꺼짐
            led1.write(0.0f); //LED 밝음
            led2.write(0.0f);  //LED 꺼짐
            led3.write(0.0f);  //LED 꺼짐
            }
        }
    
    


void blind_control() {
        // blind.calibrate(0.0005, 45);        // Default 회전반경
        // blind.calibrate(0.001, 90);       // 서보모터 회전반경 확장
    
    
    //blind.write(0.5f);                        // 블라인드 기본 상태 설정 (닫힘)
     
        //조도센서 밝기 읽어오기
        pc.printf("cds_sensor value -->> %f \n", cds_sensor.read());    // 시리얼모니터 출력
        //wait(0.2);
        
        if (cds_sensor.read() > 0.7f)          // 1. 주변이 어두우면
        {
                if(blind_flag == 0) {             // 2. 블라인드가 닫혀있으면
                        blind.write(1.0f);      // 블라인드 오픈
                        blind_flag = 1;               // 오픈 상태 저장
                }
        }
        else 
        {                                   // 1. 주변이 밝으면
                if(blind_flag == 1) {             // 2. 블라인드가 열려 있으면
                        blind.write(0.5f);      // 블라인드 클로즈
                        blind_flag = 0;               // 클로즈 상태 저장
                }
        }
}
    

int main()
{
    pc.baud(115200);
    //led1.period(1.0f);      
    //led2.period(1.0f);
    //led3.period(1.0f);
    //led4.period(1.0f);      // 1 second period
    //flipper.attach(&flip,0.01f); //100Hz로 타이머를 설정한다
    blind.calibrate(0.001, 90);       // 서보모터 회전반경 확장
    blind.write(0.5f);                              // 블라인드 기본 상태 설정 (닫힘)
    while(1){
        
        //danger_buzer();
        LED_ON();
        blind_control();

    }
}
