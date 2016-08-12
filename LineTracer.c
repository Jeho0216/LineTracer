/*
프로그램 명 : 라인트레이서
작성자 : 이제호
작성일 : 2016.08
*/

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>

#define MotorA 0	//Motor 1,2 A Phase
#define MotorB 1	//Motor 1,2 B Phase

void portInit(void){	//Port Initalize.
	DDRA = 0xFF;		//Output IR value.
	DDRE = 0xFF;		//Output Motor control signal.
	DDRD = 0x00;		//Input IR value.
}

int main(void){
	unsigned char Sensor = 0;		//Storing IR value.

	portInit();
	
	while(1){
		Sensor = (~PIND) & 0x0F;	//Reading IR Sensor.
		//Use D0 ~ D3
		//Blackline = 1, Whiteline = 0.
		/*
		sensor	value	black line position
		0001	1		Left
		0011	3		Left
		0110	6		Middle
		1100	12(C)	Right
		1000	8		Right
		*/
		switch(Sensor){
			case 1 :		//Turn left
			break;
			case 3 :		//Turn left
			break;
			case 6 :		//Straight
			break;
			case 12 :		//Turn Right
			break;
			case 8 :		//Turn Right
			break;
		}
	}
}