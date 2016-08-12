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

void port_Init(void){	//Port Initalize.
	DDRA = 0xFF;		//UART Com port
	DDRE = 0xFF;		//Output Motor control signal.
	DDRD = 0x00;		//Input IR value.
	DDRG = 0xFF;		//Debug LED
}

void UART_Init(void){
	UCSR1A = 0x00;
	UCSR1B = 0x18;		//RX, TX enable
	UCSR1C = 0x06;		//Data bit : 8bit

	UBRR1H = 0;
	UBRR1L = 51;		//baudrate : 19200
						//error : 0.2%
}

unsigned char get_data(void){
	while(!(UCSR1A & 0x80));
	return UDR1;
}

void send_data(unsigned char data){
	while(!(UCSR1A & 0x20));
	UDR1 = data;
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
	unsigned char prevSenesor = 0;	//Previous IR value.
	port_Init();
	
	while(1){
		prevSensor = Sensor;		//Storing Previous IR value.
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
			case 0 :		//On White line.
				Motor_stop();
				break;

			case 1 :		//Turn left
			case 3 :		
			PORTG = 0x02;
			if(previousSensor != Sensor){	//If the black line positions have chaged
				Motor_stop();
				send_data(get_data);
			}
			Motor_1(MotorB);
			break;
			
			case 6 :		//Straight
			PORTG = 0x03;
			if(previousSensor != Sensor){
				Motor_stop();
				send_data(get_data);
			}
			Motor_1(MotorB);
			Motor_2(MotorA);
			break;
			
			case 12 :		//Turn Right
			case 8 :		//Turn Right
			PORTG = 0x01;
			if(previousSensor != Sensor){
				Motor_stop();
				send_data(get_data);
			}
			Motor_2(MotorA);
			break;
			
			default :
			PORTG = 0x03;
			if(previousSensor != Sensor){
				Motor_stop();
				send_data(get_data);
			}
			Motor_1(MotorB);
			Motor_2(MotorA);
			break;
		}
	}
}
//ADD UART Branch