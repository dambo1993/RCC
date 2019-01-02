/*
 * rcc_settings.h
 *
 *  Created on: 27.05.2018
 *      Author: Przemek
 */

#ifndef LIBS_CONFIG_RCC_SETTINGS_H_
#define LIBS_CONFIG_RCC_SETTINGS_H_

/** \addtogroup rcc_settings
 *  @{
 */

/**
 * \brief Plik "systemowy" zalezny od plaftormy na jaka piszemy
 */
#define RCC_SYSTEM_INCLUDE 		"stm32f0xx.h"

/**
 * \brief Wybor aktywnego ustawienia zegara.
 */
#define RCC_MODE HSE_8MHZ_SYSCLK_48MHZ

/**
 * \brief Ilosc obiegow petli oczekujacej na uruchomienie sie HSE
 */
#define HSE_STARTUP_TIMEOUT 1000000

/** @}*/

#endif /* LIBS_CONFIG_RCC_SETTINGS_H_ */
