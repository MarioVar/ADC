#include <stm32f30x.h>
float tensione;
float tensione2;
int calibrazione=0;
void main(void){

RCC->AHBENR |= 1<<28;// ABilito BUS CLK degli ADC 1 e 2 perchË sono in coppia
RCC->AHBENR |= 1<<17;
RCC->CFGR2 |=1<<8;//clock diviso per 2
ADC1_2->CCR |= 1<<17;
GPIOA->MODER &= ~ ((unsigned int)3); // INPUT PORTA A

ADC1->CR &= 0xCFFFFFFF; // pongo a 00 gli ultimi bit fi ADVREGEN
ADC1->CR |= 1<<28; //pomgo 01 in ADVREGEN
for(int i=0;i<721;i++);// aspetto 10 micro secondi

ADC1->CR |= 1<<31; //abilito ADCAL
while( (ADC1->CR & 1<<31) == 1<<31);// attesa fine calibrazione
ADC1->CR |= 1;//pongo aden a 1
while( !(ADC1->ISR & 1)== 1);// il bit ADRDY si Ë alzato ed Ë pronto per la conversione
ADC1->SQR1 |=0<<0;
ADC1->SQR1 |= 1<<6;//Pongo nel campo L uno 0
ADC1->SMPR2 |= 7<<18;

while(1){
  if( GPIOA->IDR & 0x1 == 0x1){
    ADC1->CR |= 1<<2;
    while( (ADC1->ISR & 1<<2)==0);// attendo si alzi End Of Conversion

    calibrazione=ADC1->CALFACT;
    tensione =ADC1->DR;
    tensione2=( (tensione*3.3)/4096);
    //metti la printf 
  }
}
}
