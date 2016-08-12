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

void Motor_1(int phase){		//Left Motor
	if(phase == MotorB)	PORTE |= 0x01;
	else				PORTE |= 0x02;
}
void Motor_2(int phase){		//Right Motor
	if(phase == MotorB)	PORTE |= 0x04;
	else				PORTE |= 0x08;
}

void Motor_stop(void){
	PORTE = 0x00;
	_delay_us(5);
}

int main(void){
	unsigned char Sensor = 0;		//Storing IR value.

	portInit();
	
	while(1){
		Sensor = (~PIND) & 0x0F;	//Reading IR Sensor.
		PORTA = Sensor;				//Output IR Sensor value.(use LED)
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
			Motor_stop();
			Motor_1(MotorB);
			break;
			
			case 3 :		//Turn left
			Motor_stop();
			Motor_1(MotorB);
			break;
			
			case 6 :		//Straight
			Motor_stop();
			Motor_1(MotorB);
			Motor_2(MotorB);
			break;
			
			case 12 :		//Turn Right
			Motor_stop();
			Motor_2(MotorB);
			break;
			case 8 :		//Turn Right
			Motor_stop();
			Motor_2(MotorB);
			break;
			
			default :
			Motor_stop();
			Motor_1(MotorB);
			Motor_2(MotorB);
			break;
		}
	}
}