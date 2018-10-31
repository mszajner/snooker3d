
/** @file Triangle.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CTriangle.
 *
 *  Plik zawiera interfejs klasy CTriangle.
 *
 */ 

#pragma once

#include "Vector.h"

/** @brief Klasa reprezentuj�ca tr�jk�t w przestrzeni.
 */
class CTriangle {

	public:
		/** @brief Flaga identyfikuj�ca czy tr�jk�t jest do�kiem. */
		int m_Hole;
		/** @brief Flaga identyfikuj�ca czy tr�jk�t potrafi odbi� bil�. */
		int m_Reflect;
		/** @brief Wierzcho�ek A. */
		CVector m_A;
		/** @brief Wierzcho�ek B. */
		CVector m_B;
		/** @brief Wierzcho�ek C. */
		CVector m_C;
		/** @brief Wektor normalny do tego tr�jk�ta. */
		CVector m_N;

	public:
		/** @brief Konstruktor domy�lny. */
		CTriangle(void);

		/** @brief Konstruktor kopiuj�cy.
		 *  @param[in] Triangle Tr�jk�t �r�d�owy.
		 */
		CTriangle(const CTriangle &Triangle);

		/** @brief Konstruktor ustawiaj�cy wierzcho�ki.
		 *  @param[in] A Wierzcho�ek A.
		 *  @param[in] B Wierzcho�ek B.
		 *  @param[in] C Wierzcho�ek C.
		 *  Konstruktor po ustawieniu wierzcho�k�w automatycznie oblicza
		 *  wektor normalny do tego tr�jk�ta.
		 */
		CTriangle(const CVector &A, const CVector &B, const CVector &C);

	public:
		/** @brief Funkcja odczytuj�ca tr�jk�t z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj�ca tr�jk�t do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja ustawiaj�ca wierzcho�ki.
		 *  @param[in] A Wierzcho�ek A.
		 *  @param[in] B Wierzcho�ek B.
		 *  @param[in] C Wierzcho�ek C.
		 *  Funkcja po ustawieniu wierzcho�k�w automatycznie oblicza
		 *  wektor normalny do tego tr�jk�ta.
		 */
		void Set(const CVector &A, const CVector &B, const CVector &C);

		/** @brief Funkcja ustawiaj�ca wierzcho�ek A.
		 *  @param[in] A Wierzcho�ek A.
		 *  Funkcja po ustawieniu wierzcho�ka automatycznie oblicza
		 *  wektor normalny do tego tr�jk�ta.
		 */
		void SetA(const CVector &A);

		/** @brief Funkcja ustawiaj�ca wierzcho�ek B.
		 *  @param[in] B Wierzcho�ek B.
		 *  Funkcja po ustawieniu wierzcho�ka automatycznie oblicza
		 *  wektor normalny do tego tr�jk�ta.
		 */
		void SetB(const CVector &B);

		/** @brief Funkcja ustawiaj�ca wierzcho�ek C.
		 *  @param[in] C Wierzcho�ek C.
		 *  Funkcja po ustawieniu wierzcho�ka automatycznie oblicza
		 *  wektor normalny do tego tr�jk�ta.
		 */
		void SetC(const CVector &C);

		/** @brief Funkcja wyznaczaj�ca na nowo wektor normalny.
		 */
		void SetN(void);

	public:
		/** @brief Funkcja sprawdzaj�ca czy dany punkt znajduje si� wewn�trz tr�jk�ta.
		 *  @param[in] Point Badany punkt.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li punkt le�y wewn�trz tr�jk�ta.
		 */
		int Contains(const CVector &Point) const;

		/** @brief Funkcja zwracaj�ca flag� czy tr�jk�t jest tr�jk�tem odbijaj�cym.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li tr�jk�t jest odbijaj�cy.
		 */
		int GetReflect(void) const { return m_Reflect; };

		/** @brief Funkcja zwracaj�ca flag� czy tr�jk�t jest do�kiem.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li tr�jk�t jest do�kiem.
		 */
		int GetHole(void) const { return m_Hole; };

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Triangle Tr�jk�t �r�d�owy.
		 *  @retval Funkcja zwraca referencj� do tego tr�jk�ta.
		 */
		CTriangle& operator=(const CTriangle &Triangle);

};
