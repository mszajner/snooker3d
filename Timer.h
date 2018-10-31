
/** @file Timer.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CTimer.
 *
 *  Plik zawiera interfejs klasy CTimer.
 *
 */ 

#pragma once

/** @brief Klasa obs�uguj�ca czasomierz systemowy wysokiej precyzji.
 */
class CTimer {

	private:
		/** @brief Cz�stotliwo�� czasomierza systemowego. */
		LARGE_INTEGER m_Frequency;
		/** @brief Aktualny stan licznik czasomierza. */
		LARGE_INTEGER m_Current;
		/** @brief Poprzedni stan licznik czasomierza. */
		LARGE_INTEGER m_Previous;

	public:
		/** @brief Konstruktor domy�lny. */
		CTimer(void);

	public:
		/** @brief Funkcja zwraca czas jaki up�yn�� od poprzedniego wywo�ania tej funkcji.
		 *  @retval Funkcja zwraca czas w sekundach.
		 */
		float Get(void);

};
