/*
 * RCC.c
 *
 *  Created on: 14.01.2017
 *      Author: Przemek
 */

#include "RCC.h"

#include <libs_config/rcc_settings.h>
#include RCC_SYSTEM_INCLUDE


static inline void start_HSE_and_wait_for_ready(void)
{
	uint32_t StartUpCounter = 0, HSEStatus = 0;

	// uruchomienie HSE
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);

	// oczekiwanie na gotowosc HSE
	do
	{
		HSEStatus = RCC->CR & RCC_CR_HSERDY;
		StartUpCounter++;
	} while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
}


static void RCC_init_HSE8MHZ_SYSCLK_48MHZ_M0(void)
{
	start_HSE_and_wait_for_ready();

	// sprawdzenie gotowosci HSE
	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	{
		// mozemy zmienic taktowanie na HSE

		// spowolnienie pamieci flash i wlaczenie buforowania (max komunikacja z FLASH to 24MHz! - niektorzy nie czytaja o tym :/)
		FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;

		// preskaler dla AHB  - domyslnie 1
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		// preskaler dla APB - domyslnie 1
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		// ustawienia PLL
		// PLL mnoznik = HSE * 6 = 48 MHz
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE_PREDIV| RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1 | RCC_CFGR_PLLMUL6);

		// wlaczenie PLL
		RCC->CR |= RCC_CR_PLLON;

		// oczekiwanie na gotowosc PLL
		while((RCC->CR & RCC_CR_PLLRDY) == 0)
		{

		}

		// Wybranie PLL jako zrodla taktowania
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

		// oczekiwanie, az PLL stanie sie zrodlem taktowania
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
		{

		}
	}
	else
	{
		// petla nieskonczona - problem z uruchomieniem zegara - tutaj mozna dodac jakas obsluge
		while(1)
		{

		}
	}
}

void HSE_8MHZ_SYSCLK_72MHZ_M4(void)
{
	start_HSE_and_wait_for_ready();

	// sprawdzanie gotowosci HSE
	if ((RCC->CR & RCC_CR_HSERDY) != RESET)
	{
		// mozemy zmienic taktowanie na HSE

		// spowolnienie pamieci flash i wlaczenie buforowania (max komunikacja z FLASH to 24MHz! - niektorzy nie czytaja o tym :/)
		FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY_1;

		// preskaler dla AHB  - domyslnie 1
		RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

		// preskaler dla APB1 - domyslnie max moze byc 36MHz wiec ustawiamy na 2
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

		// preskaler dla APB2 - 72MHz
		RCC->CFGR |= RCC_CFGR_PPRE1_DIV1;

		// ustawienia PLL
		// PLL mnoznik = HSE * 9 = 72MHz
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMUL));
		RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE_PREDIV| RCC_CFGR_PLLXTPRE_HSE_PREDIV_DIV1 | RCC_CFGR_PLLMUL9 );

		// wlaczenie PLL
		RCC->CR |= RCC_CR_PLLON;

		// oczekiwanie na gotowosc PLL
		while((RCC->CR & RCC_CR_PLLRDY) == 0)
		{

		}

		// Wybranie PLL jako zrodla taktowania
		RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

		// oczekiwanie, az PLL stanie sie zrodlem taktowania
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
		{

		}
	}
	else
	{
		// petla nieskonczona - problem z uruchomieniem zegara - tutaj mozna dodac jakas obsluge
		while(1)
		{

		}
	}
}

/*
 * \brief Inicjalizacja zegara systemowego zgodnie z makrem z pliku pliku konfiguracyjnego.
 */
void RCC_init( void )
{
#if RCC_MODE == HSE_8MHZ_SYSCLK_48MHZ_M0
	RCC_init_HSE8MHZ_SYSCLK_48MHZ_M0();
#elif RCC_MODE == HSE_8MHZ_SYSCLK_72MHZ_M4
	HSE_8MHZ_SYSCLK_72MHZ_M4();
#else
#error "RCC - Nie zdefiniowano ustawienia zegara!"
#endif
}
