#include "stm32f4xx.h"

int main(void)
{
	void seta700ms(TIM_TypeDef* tim);
	void seta200ms(TIM_TypeDef* tim);
	void esperaTimer (void);

  RCC->AHB1ENR=0x00000087;  // inicializa o clock;
  GPIOC->MODER=0X00005555;

  RCC->APB2ENR|=0x20000;  // inicializa o clock do TIMER10;
  TIM10->CR1|=0x0005;  // habilita a contagem do TIMER10;

  seta700ms(TIM10);


  while (1)
  {
	  GPIOC->ODR = 0x01;
	  seta700ms(TIM10);
	  esperaTimer();
	  GPIOC->ODR = 0x03;
	  seta200ms(TIM10);
	  esperaTimer();
	  GPIOC->ODR = 0x04;
	  seta700ms(TIM10);
	  esperaTimer();
  }
}

void esperaTimer (void){
	char naoEstourou(TIM_TypeDef* tim);
	void limpaEstouro(TIM_TypeDef* tim);

	while(naoEstourou(TIM10));
	limpaEstouro(TIM10);
}

void seta700ms(TIM_TypeDef* tim) {
	tim->PSC=1999;
	tim->ARR=5599;
}

void seta200ms(TIM_TypeDef* tim) {
	tim->PSC=1999;
	tim->ARR=1599;
}

void limpaEstouro(TIM_TypeDef* tim) {
	tim->SR&=~(0x0001);
}

char estourou(TIM_TypeDef* tim) {
	return (tim->SR & 0x0001) == 0x0001;
}

char naoEstourou(TIM_TypeDef* tim) {
	return (tim->SR & 0x0001) == 0x0000;
}
