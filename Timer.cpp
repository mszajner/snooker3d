
/** @file Timer.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CTimer.
 *
 *  Plik zawiera implementacjê klasy CTimer.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Timer.h"

CTimer::CTimer(void)
{
	// pobierz czestotliwosc licznika wysokiej precyzji
	QueryPerformanceFrequency(&m_Frequency);

	// pobierz aktualny stan licznika
	QueryPerformanceCounter(&m_Previous);
}

float CTimer::Get(void)
{
	float Time;

	// pobierz aktualny stan licznika wysokiej precyzji
	QueryPerformanceCounter(&m_Current);

	// wyznacz czas ktory uplynal od poprzedniego wywolania funkcji
	Time = (float)(m_Current.QuadPart - m_Previous.QuadPart) / m_Frequency.QuadPart;
	
	// zapamietaj aktualny czas
	m_Previous = m_Current;

	// zwroc czas, ktory uplynal od poprzedniego wywolania funkcji
	return Time;
}
