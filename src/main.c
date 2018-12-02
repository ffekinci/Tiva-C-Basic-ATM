#include <stdint.h>
#include "inc/tm4c123gh6pm.h"


//#define LCD GPIOB
#define RS 1 // PB0
#define RW 2 // PB1
#define EN 4 // PB2
void delayUzun(int n);
void delayKisa(int n);
void LCD_yaz(unsigned char data, unsigned char control);
void LCD_Cmp(unsigned char command);
void LCD_K_Yaz(unsigned char data);
void LCD_Init(void);
void init_port_E(void);
void temizle(void);
void temizle2(void);


int main(){
	init_port_E();
	LCD_Init();
	LCD_Cmp(1);
	LCD_Cmp(0x80);
	delayUzun(500);
	Bas:
	delayUzun(1);

	char dizi[10]={'0','1','2','3','4','5','6','7','8','9'};
	int btn1,btn2,btn3,btn4,btn5,bir=0,iki=0,uc=0,dort=0,bes=0;
	int bas,son;
	char nokta=' ';
	int durum=0,sayac=0,sayac2=0,reset=0;
	while (1){
		delayUzun(1);
		btn1=GPIO_PORTE_DATA_R & 0b00001;
		btn2=GPIO_PORTE_DATA_R & 0b00010;
		btn3=GPIO_PORTE_DATA_R & 0b00100;
		btn4=GPIO_PORTE_DATA_R & 0b01000;
		btn5=GPIO_PORTE_DATA_R & 0b10000;

		delayUzun(10);

		satirdegis(1,12);
		LCD_K_Yaz(dizi[bir]);
		delayUzun(1);
		LCD_K_Yaz(dizi[iki]);
		delayUzun(1);
		LCD_K_Yaz(nokta);
		delayUzun(1);
		LCD_K_Yaz(dizi[dort]);
		delayUzun(1);
		LCD_K_Yaz(dizi[bes]);

		if (btn1 != 0) {
				bir++;
				bir=bir%10;
				durum=1;
				sayac=0;
				delayUzun(40);
			}
		else if(btn2 != 0){
			iki++;
			iki=iki%10;
			durum=1;
			sayac=0;
			delayUzun(40);
		}

		else if(btn3 != 0){

			if(uc==0){
				uc=1;
				nokta='.';
				delayUzun(40);

			}

			else{
								sayac2++;
								delayUzun(40);

								if(sayac2>10){
									satirdegis(2,1);
									Yazibas("RESETLENDI");
									delayUzun(1000);
									temizle();
									nokta=' ';
									goto Bas;

								}
		  }

		}

		else if(btn4 != 0){
			dort++;
			dort=dort%10;
			durum=1;
			sayac=0;
			delayUzun(40);

				}
		else if(btn5 != 0){
			bes++;
			bes=bes%10;
			durum=1;
			sayac=0;
			delayUzun(40);

				}

		else {
//123
				if(durum==1){
					sayac++;
					delayUzun(10);

					if(sayac>100){
						goto hesap;
					}
				}
			}

		delayUzun(10);


	}

	hesap:
	bas = (bir*10)+iki;
	son = (dort*10)+bes;
	int birler,onlar;

	int yirmilik = bas/20; // 99/20=4  ---  99%20=19
	bas = bas % 20;
	if(yirmilik>0){
		if(bas>9){
				birler=bas%10;
				onlar=bas/10;
				satirdegis(1,12);
				LCD_K_Yaz(dizi[onlar]);
				LCD_K_Yaz(dizi[birler]);
			}
			else{
				birler=bas;
				satirdegis(1,12);
				LCD_K_Yaz(' ');
				LCD_K_Yaz(dizi[birler]);

			}
		delayUzun(1);

			LCD_K_Yaz('.');
			LCD_K_Yaz(dizi[dort]);
			LCD_K_Yaz(dizi[bes]);
			delayUzun(1);

			satirdegis(2,1);
			LCD_K_Yaz(dizi[yirmilik]);
			Yazibas("-yirmilik");
			delayUzun(2500);
	}


	temizle();
	delayUzun(1);

	int onluk = bas/10;
	bas = bas % 10;
	if(onluk>0){
		birler=bas;
				satirdegis(1,12);
				LCD_K_Yaz(' ');
				LCD_K_Yaz(dizi[birler]);
			delayUzun(1);

			LCD_K_Yaz('.');
			LCD_K_Yaz(dizi[dort]);
			LCD_K_Yaz(dizi[bes]);
			delayUzun(1);

			satirdegis(2,1);
			LCD_K_Yaz(dizi[onluk]);
			Yazibas("-onluk");
			delayUzun(2500);
	}

	temizle();
	int beslik = bas/5;
	bas = bas % 5;
	if(beslik>0){
		satirdegis(1,12);
				LCD_K_Yaz(' ');
				LCD_K_Yaz(dizi[bas]);
			delayUzun(1);

			LCD_K_Yaz('.');
			LCD_K_Yaz(dizi[dort]);
			LCD_K_Yaz(dizi[bes]);
			delayUzun(1);

			satirdegis(2,1);
			LCD_K_Yaz(dizi[onluk]);
			Yazibas("-beslik");
			delayUzun(2500);
	}

	temizle();
	int birlik = bas/1;
	bas = bas % 1;

	if(birlik>0){
		satirdegis(1,12);
			LCD_K_Yaz(' ');
			LCD_K_Yaz(' ');
			LCD_K_Yaz('.');
			LCD_K_Yaz(dizi[dort]);
			LCD_K_Yaz(dizi[bes]);
			delayUzun(1);

			satirdegis(2,1);
			LCD_K_Yaz(dizi[birlik]);
			Yazibas("-birlik");
			delayUzun(2500);
	}

	temizle();

	int yarimlik = son/50;
	son = son % 50;

	if(yarimlik>0){
		if(son>9){
				birler=son%10;
				onlar=son/10;
				satirdegis(1,14);
				LCD_K_Yaz('.');
				LCD_K_Yaz(dizi[onlar]);
				LCD_K_Yaz(dizi[birler]);
			}
			else{
				satirdegis(1,14);
				LCD_K_Yaz('.');
				LCD_K_Yaz(' ');
				LCD_K_Yaz(dizi[birler]);
			}

			satirdegis(2,1);
			LCD_K_Yaz(dizi[yarimlik]);
			Yazibas("-yarimlik");
			delayUzun(2500);
	}

	temizle();
	int ceyreklik = son/25;
	son = son % 25;

	if(ceyreklik>0){
		if(son>9){
					birler=son%10;
					onlar=son/10;
					satirdegis(1,14);
					LCD_K_Yaz('.');
					LCD_K_Yaz(dizi[onlar]);
					LCD_K_Yaz(dizi[birler]);
				}
				else{
					satirdegis(1,14);
					LCD_K_Yaz('.');
					LCD_K_Yaz(' ');
					LCD_K_Yaz(dizi[birler]);
				}

			satirdegis(2,1);
			LCD_K_Yaz(dizi[ceyreklik]);
			Yazibas("-ceyreklik");
			delayUzun(2500);
	}

	temizle();
	int metelik = son/10;
	son = son % 10;

	if(metelik>0){
		satirdegis(1,14);
			LCD_K_Yaz('.');
			LCD_K_Yaz('0');
			LCD_K_Yaz(dizi[son]);

			satirdegis(2,1);
			LCD_K_Yaz(dizi[metelik]);
			Yazibas("-metelik");
			delayUzun(2500);

			temizle();
			int kurusluk = son;
			satirdegis(1,14);
			LCD_K_Yaz('.');
			LCD_K_Yaz(' ');
			LCD_K_Yaz(' ');
			satirdegis(2,1);
			LCD_K_Yaz(dizi[kurusluk]);
			Yazibas("-kurusluk");
			delayUzun(2500);
	}
	delayUzun(100);
	temizle();
	temizle2();
	goto Bas;


}

void init_port_E() {
volatile unsigned long delay;
SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE; // Port E’nin saati aktifleştir
delay = SYSCTL_RCGC2_R; // Gecikme
GPIO_PORTE_DIR_R |= 0x00; // Port E’nin tüm bitleri cikis olarak ayarla
GPIO_PORTE_DEN_R |= 0xFF; // Tüm Port E için Digital çalışmayı aktifleştir
}

void temizle(){
	satirdegis(2,1);
	Yazibas("                ");
}
void temizle2(){
	satirdegis(1,1);
	Yazibas("                ");
}


void Yazibas( char* s){

        while(*s)
                LCD_K_Yaz(*s++);
}
void satirdegis(char x, char y){

        if(x==1)
                LCD_Cmp(0x80+((y-1)%16));
        else
                LCD_Cmp(0xC0+((y-1)%16));
}

void LCD_Init(void)
{
	SYSCTL_RCGC2_R |= (1<<1);
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0XFF;
	LCD_Cmp(0x28);
	LCD_Cmp(0x06);
	LCD_Cmp(0x01);
	LCD_Cmp(0x0F);

}


void LCD_yaz(unsigned char data, unsigned char control)
{
	data &= 0xF0; // son dort bit data
	control &= 0x0F; // ilk dort bit control
	GPIO_PORTB_DATA_R = data | control;
	GPIO_PORTB_DATA_R = data | control | EN;
	delayKisa(0);
	GPIO_PORTB_DATA_R = data ;

}

void LCD_Cmp(unsigned char command)
{
	LCD_yaz(command & 0xF0,0);
	LCD_yaz(command<<4,0);

	if(command < 4)
	{
		delayUzun(2);
	}
	else
		delayKisa(40);
}
void LCD_K_Yaz(unsigned char data)
{
	LCD_yaz(data & 0xF0,RS);
	LCD_yaz(data <<4,RS);
	delayKisa(40);
}
void delayUzun(int n)
{
	int x,y;
	for(x=0;x<n;x++)
	{
		for(y=0;y<3333;y++)
		{

		}
	}

}
void delayKisa(int n)
{
	int x,y;
		for(x=0;x<n;x++)
		{
			for(y=0;y<3;y++)
			{

			}
		}
}

