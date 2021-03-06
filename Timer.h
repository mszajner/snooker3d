
/** @file Timer.h
 *  @author Mirosław Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nagłówkowy klasy CTimer.
 *
 *  Plik zawiera interfejs klasy CTimer.
 *
 */ 

#pragma once

/** @brief Klasa obsługująca czasomierz systemowy wysokiej precyzji.
 */
class CTimer {

	private:
		/** @brief Częstotliwość czasomierza systemowego. */
		LARGE_INTEGER m_Frequency;
		/** @brief Aktualny stan licznik czasomierza. */
		LARGE_INTEGER m_Current;
		/** @brief Poprzedni stan licznik czasomierza. */
		LARGE_INTEGER m_Previous;

	public:
		/** @brief Konstruktor domyślny. */
		CTimer(void);

	public:
		/** @brief Funkcja zwraca czas jaki upłynął od poprzedniego wywołania tej funkcji.
		 *  @retval Funkcja zwraca czas w sekundach.
		 */
		float Get(void);

};
