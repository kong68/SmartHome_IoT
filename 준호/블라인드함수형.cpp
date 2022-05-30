#include "mbed.h"
#include "Servo.h"

Servo blind(D3);                					// 서보모터 변수 선언 > 블라인드
AnalogIn cds_sensor(A0);        					// 조도센서 변수 선언

Serial pc(SERIAL_TX,SERIAL_RX);						// 시리얼통신

int flag = 0;															// 블라인드 상태를 저장하는 변수, 현재 닫혀있음


void blind_control() {
		// blind.calibrate(0.0005, 45);		   // Default 회전반경
		// blind.calibrate(0.001, 90);       // 서보모터 회전반경 확장
    
    
    //blind.write(0.5f);						// 블라인드 기본 상태 설정 (닫힘)
     
		//조도센서 밝기 읽어오기
		pc.printf("cds_sensor value -->> %f \n", cds_sensor.read());    // 시리얼모니터 출력
		wait(0.2);
		
		if (cds_sensor > 0.5f)          // 1. 주변이 어두우면
		{
				if(flag == 0) {             // 2. 블라인드가 닫혀있으면
						blind.write(1.0f);      // 블라인드 오픈
						flag = 1;               // 오픈 상태 저장
				}
		}
		else 
		{                         			// 1. 주변이 밝으면
				if(flag == 1) {             // 2. 블라인드가 열려 있으면
						blind.write(0.5f);      // 블라인드 클로즈
						flag = 0;               // 클로즈 상태 저장
				}
		}
}

int main()  {
    pc.baud(115200);
    
    // blind.calibrate(0.0005, 45);   // Default 회전반경
    blind.calibrate(0.001, 90);       // 서보모터 회전반경 확장
    
    
    blind.write(0.5f);								// 블라인드 기본 상태 설정 (닫힘)
    
    while(true) {
			blind_control();
    }
     
}
