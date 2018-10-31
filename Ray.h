
/** @file Ray.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CRay.
 *
 *  Plik zawiera interfejs klasy CRay.
 *
 */ 

#pragma once

#include "Vector.h"

/**
 *  Klasa opisuje pó³prost¹ w przestrzeni. Wykorzystywana jest przy wykrywaniu
 *  kolizji miêdzy bilami oraz przy wykrywaniu czy kij nie przechodzi przez bilê.
 *
 *  @brief Klasa reprezentuj¹ca pó³prost¹ w przestrzeni.
 */
class CRay {

	public:
		/** @brief Punkt pocz¹tkowy pó³prostej. */
		CVector m_Point;
		/** @brief Wektor kierunkowy pó³prostej. */
		CVector m_Direction;

	public:
		/** @brief Konstruktor domyœlny. */
		CRay(void);

		/** @brief Konstrukor tworz¹cy pó³prost¹ z dwóch punktów.
		 *  @param[in] Point1 Punkt wyznaczaj¹cy kierunek pó³prostej.
		 *  @param[in] Point2 Punkt pocz¹tkowy pó³prostej.
		 */
		CRay(const CVector &Point1, const CVector &Point2);

		/** @brief Konstruktor kopiuj¹cy.
		 *  @param[in] Ray Pó³prosta Ÿród³owa.
		 */
		CRay(const CRay &Ray);
	
	public:
		/** @brief Funkcja odwracaj¹ca kierunek pó³prostej.
		 */
		void Negative(void);

	public:
		/** @brief Funkcja ustawiaj¹ca parametry pó³prostej.
		 *  @param[in] Point Punkt pocz¹tkowy pó³prostej.
		 *  @param[in] Direction Wektor kierunkowy pó³prostej.
		 *  Funkcja dodatkowo normalizuje wektor kierunkowy pó³prostej.
		 */
		void Set(const CVector &Point, const CVector &Direction);

		/** @brief Funkcja ustawiaj¹ca punkt pocz¹tkowy pó³prostej.
		 *  @param[in] Point Punkt pocz¹tkowy pó³prostej.
		 */
		void SetPoint(const CVector &Point);

		/** @brief Funkcja ustawiaj¹ca wektor kierunkowy pó³prostej.
		 *  @param[in] Direction Nowy wektor kierunkowy pó³prostej.
		 *  Funkcja dodatkowo normalizuje wektor kierunkowy pó³prostej.
		 */
		void SetDirection(const CVector &Direction);
	
	public:
		/** @brief Funkcja wyznacza najbli¿sze punkty na dwóch pó³prostych.
		 *  @param[in] Ray Druga pó³prosta.
		 *  @param[out] Point1 Punkt znajduj¹cy siê na pierwszej pó³prostej.
		 *  @param[out] Point2 Punkt znajduj¹cy siê na drugiej pó³prostej (Ray).
		 */
		void AdjacentPoints(const CRay &Ray, CVector &Point1, CVector &Point2) const;

		/** @brief Sprawdza czy dwa punkty le¿¹ po tej samej stronie pó³prostej.
		 *  @param[in] Point1 Pierwszy badany punkt.
		 *  @param[in] Point2 Drugi badany punkt.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli oba punkty 
		 *          znajduj¹ siê po tej samej stronie pó³prostej.
		 */
		int AreAtSameSide(const CVector &Point1, const CVector &Point2) const;
	
	public:
		/** @brief Funkcja wyznacza odleg³oœæ miêdzy dwoma pó³prostymi.
		 *  @param[in] Ray Druga pó³prosta.
		 *  @retval Funkcja zwraca odleg³oœæ miêdzy dwoma pó³prostymi, a jeœli siê
		 *          przecinaj¹ to zwraca 0.
		 */
		float Distance(const CRay &Ray) const;

		/** @brief Funkcja wyznacza odleg³oœæ punktu od pó³prostej.
		 *  @param[in] Point Badany punkt.
		 *  @retval Funkcja zwraca odleg³oœæ punktu od pó³prostej.
		 */
		float Distance(const CVector &Point) const;
	
	public:
		/** @brief Operator odwracania pó³prostej.
		 *  @retval Operator zwraca pó³prost¹ o odwróconym wektorze kierunkowym.
		 */
		CRay operator-(void) const;

};
