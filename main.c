

/**
 *
 * main.c
 */
#define REG volatile unsigned long int *

volatile unsigned long int * GPIOHBCTL = 0x400FE06C;
volatile unsigned long int * RCGCTIMER = 0x400FE604;
volatile unsigned long int * RCGCGPIO = 0x400FE608;

#define TIMER0_BASE  0x40030000


#define FB(offest) (TIMER0_BASE+offest)

REG GPTMCFG = FB(0x000);//
REG GPTMCTL = FB(0x00C);//
REG GPTMTAMR = FB(0x004);//
REG GPTMICR = FB(0x024);//
REG GPTMRIS = FB(0x01C);//
REG  GPTMTAILR=FB(0x028);

#define F_BASE  0x4005D000

#define OFS(offest) (F_BASE+offest)
REG GPIODEN_F = OFS(0x51C);
REG GPIODATA_F =  OFS(0x3FC);//
REG GPIOAFSEL_F =  OFS(0x420);
REG GPIODIRF =  OFS(0x400);
int main(){

 *GPIOHBCTL |= (1<<5);
//configure gpio portf blue led PF2
*RCGCGPIO |= (1<<5); //enable clk on portf
*GPIOAFSEL_F &= ~(1<<1);//disable alternate fn
*GPIODIRF |= (1<<1);//configure as output
*GPIODEN_F|=(1<<1);
*GPIODATA_F = (1<<1);//set to high
//periodic mode configuration
*RCGCTIMER |=(1<<0);//timer clk for timer module
*GPTMCTL &= ~(1<<0);//dis timer
*GPTMCFG|= 0x00000000;
*GPTMTAMR|=(0x2<<0);//h5tar periodic
*GPTMTAMR &= ~(1<<4);//dir down
*GPTMTAILR = 0x00f42400; //16 000 000
*GPTMCTL |= (1<<0);//enable timer
while(1){

    if((*GPTMRIS&&0x00000001)){
        *GPTMICR |=(1<<0);
        *GPIODATA_F ^= (1<<1);

    }
}
return 0;

}
/*
 * #define REG volatile unsigned long int *
//volatile unsigned long int * RCC = 0x400FE060;
volatile unsigned long int * GPIOHBCTL = 0x400FE06C;
volatile unsigned long int * RCGCGPIO = 0x400FE608;
volatile unsigned long int * GPIODIRF = 0x4005D400;
//******************
volatile unsigned long int * RCGCTIMER = 0x400FE604;
#define TIMER0_BASE  0x40030000
#define FB(offest) TIMER0_BASE+offest
REG GPTMCFG = FB(0x000);//
REG GPTMCTL = FB(0x00C);//
REG GPTMTAMR = FB(0x004);//
REG GPTMICR = FB(0x024);//
REG GPTMRIS = FB(0x01C);//
REG  GPTMTAILR=FB(0x028);//

#define F_BASE  0x4005D000
#define FB(offest) F_BASE+offest
#define PIN 2
REG GPIOAFSEL_F = 0x4005D420;//
//REG GPIODR8R_F = F_BASE + 0x508;
REG GPIODEN_F = FB(0x51C);
REG GPIODATA_F = 0x4005D3FC;
int main(void)
{//zbtna internal clk

    *GPIOHBCTL |= (1<<5);//5dt al address bta3 APB
    *RCGCGPIO |= (1<<5);//clk port f enable
    *GPIODIRF |= (1<<PIN);//direction_f
    *GPIOAFSEL_F &= ~(1<<PIN);//a5trna GPIO
    //*GPIODR8R_F |= (1<<PIN);//CURRENT
    *GPIODEN_F |= (1<<PIN);
    *GPIODATA_F = (1<<PIN);
    //periodic mode configuration
    *RCGCTIMER |=(1<<0);
    *GPTMCTL &= ~(1<<0);
    *GPTMCFG=0x00000000;
    *GPTMTAMR|=(0x2<<0);
    *GPTMTAMR &= ~(1<<4);
    *GPTMTAILR = 0x00f42400; //16 000 000
    *GPTMCTL |= (1<<0);
    while(1){
        if((*GPTMRIS&0x00000001)==1){
            *GPTMICR |=(1<<0);
            *GPIODATA_F ^= (1<<2);
        }
        }
    return 0;
}
 */





