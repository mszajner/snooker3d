
/** @file Timer.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CTimer.
 *
 *  Plik zawiera interfejs klasy CTimer.
 *
 */ 

#pragma once

/** @brief Klasa obs³uguj¹ca czasomierz systemowy wysokiej precyzji.
 */
class CTimer {

	private:
		/** @brief Czêstotliwoœæ czasomierza systemowego. */
		LARGE_INTEGER m_Frequency;
		/** @brief Aktualny stan licznik czasomierza. */
		LARGE_INTEGER m_Current;
		/** @brief Poprzedni stan licznik czasomierza. */
		LARGE_INTEGER m_Previous;

	public:
		/** @brief Konstruktor domyœlny. */
		CTimer(void);

	public:
		/** @brief Funkcja zwraca czas jaki up³yn¹³ od poprzedniego wywo³ania tej funkcji.
		 *  @retval Funkcja zwraca czas w sekundach.
		 */
		float Get(void);

};
