/*
 * RCC.h
 *
 *  Created on: 14.01.2017
 *      Author: Przemek
 */

#ifndef RCC_H_
#define RCC_H_

// Dostepne opcje ustawienia taktowania:
// dla M0:
// HSE_8MHZ_SYSCLK_48MHZ_M0
// dla M3:
// HSE_8MHZ_SYSCLK_72MHZ_M4


/*
 * \brief Inicjalizacja zegara systemowego zgodnie z makrem z pliku pliku konfiguracyjnego.
 */
void RCC_init( void );

#endif /* RCC_H_ */
