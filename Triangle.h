
/** @file Triangle.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CTriangle.
 *
 *  Plik zawiera interfejs klasy CTriangle.
 *
 */ 

#pragma once

#include "Vector.h"

/** @brief Klasa reprezentuj¹ca trójk¹t w przestrzeni.
 */
class CTriangle {

	public:
		/** @brief Flaga identyfikuj¹ca czy trójk¹t jest do³kiem. */
		int m_Hole;
		/** @brief Flaga identyfikuj¹ca czy trójk¹t potrafi odbiæ bilê. */
		int m_Reflect;
		/** @brief Wierzcho³ek A. */
		CVector m_A;
		/** @brief Wierzcho³ek B. */
		CVector m_B;
		/** @brief Wierzcho³ek C. */
		CVector m_C;
		/** @brief Wektor normalny do tego trójk¹ta. */
		CVector m_N;

	public:
		/** @brief Konstruktor domyœlny. */
		CTriangle(void);

		/** @brief Konstruktor kopiuj¹cy.
		 *  @param[in] Triangle Trójk¹t Ÿród³owy.
		 */
		CTriangle(const CTriangle &Triangle);

		/** @brief Konstruktor ustawiaj¹cy wierzcho³ki.
		 *  @param[in] A Wierzcho³ek A.
		 *  @param[in] B Wierzcho³ek B.
		 *  @param[in] C Wierzcho³ek C.
		 *  Konstruktor po ustawieniu wierzcho³ków automatycznie oblicza
		 *  wektor normalny do tego trójk¹ta.
		 */
		CTriangle(const CVector &A, const CVector &B, const CVector &C);

	public:
		/** @brief Funkcja odczytuj¹ca trójk¹t z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj¹ca trójk¹t do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype³nienie tabulacja przed ka¿d¹ lini¹.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja ustawiaj¹ca wierzcho³ki.
		 *  @param[in] A Wierzcho³ek A.
		 *  @param[in] B Wierzcho³ek B.
		 *  @param[in] C Wierzcho³ek C.
		 *  Funkcja po ustawieniu wierzcho³ków automatycznie oblicza
		 *  wektor normalny do tego trójk¹ta.
		 */
		void Set(const CVector &A, const CVector &B, const CVector &C);

		/** @brief Funkcja ustawiaj¹ca wierzcho³ek A.
		 *  @param[in] A Wierzcho³ek A.
		 *  Funkcja po ustawieniu wierzcho³ka automatycznie oblicza
		 *  wektor normalny do tego trójk¹ta.
		 */
		void SetA(const CVector &A);

		/** @brief Funkcja ustawiaj¹ca wierzcho³ek B.
		 *  @param[in] B Wierzcho³ek B.
		 *  Funkcja po ustawieniu wierzcho³ka automatycznie oblicza
		 *  wektor normalny do tego trójk¹ta.
		 */
		void SetB(const CVector &B);

		/** @brief Funkcja ustawiaj¹ca wierzcho³ek C.
		 *  @param[in] C Wierzcho³ek C.
		 *  Funkcja po ustawieniu wierzcho³ka automatycznie oblicza
		 *  wektor normalny do tego trójk¹ta.
		 */
		void SetC(const CVector &C);

		/** @brief Funkcja wyznaczaj¹ca na nowo wektor normalny.
		 */
		void SetN(void);

	public:
		/** @brief Funkcja sprawdzaj¹ca czy dany punkt znajduje siê wewn¹trz trójk¹ta.
		 *  @param[in] Point Badany punkt.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli punkt le¿y wewn¹trz trójk¹ta.
		 */
		int Contains(const CVector &Point) const;

		/** @brief Funkcja zwracaj¹ca flagê czy trójk¹t jest trójk¹tem odbijaj¹cym.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli trójk¹t jest odbijaj¹cy.
		 */
		int GetReflect(void) const { return m_Reflect; };

		/** @brief Funkcja zwracaj¹ca flagê czy trójk¹t jest do³kiem.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli trójk¹t jest do³kiem.
		 */
		int GetHole(void) const { return m_Hole; };

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Triangle Trójk¹t Ÿród³owy.
		 *  @retval Funkcja zwraca referencjê do tego trójk¹ta.
		 */
		CTriangle& operator=(const CTriangle &Triangle);

};
