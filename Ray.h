
/** @file Ray.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CRay.
 *
 *  Plik zawiera interfejs klasy CRay.
 *
 */ 

#pragma once

#include "Vector.h"

/**
 *  Klasa opisuje p�prost� w przestrzeni. Wykorzystywana jest przy wykrywaniu
 *  kolizji mi�dzy bilami oraz przy wykrywaniu czy kij nie przechodzi przez bil�.
 *
 *  @brief Klasa reprezentuj�ca p�prost� w przestrzeni.
 */
class CRay {

	public:
		/** @brief Punkt pocz�tkowy p�prostej. */
		CVector m_Point;
		/** @brief Wektor kierunkowy p�prostej. */
		CVector m_Direction;

	public:
		/** @brief Konstruktor domy�lny. */
		CRay(void);

		/** @brief Konstrukor tworz�cy p�prost� z dw�ch punkt�w.
		 *  @param[in] Point1 Punkt wyznaczaj�cy kierunek p�prostej.
		 *  @param[in] Point2 Punkt pocz�tkowy p�prostej.
		 */
		CRay(const CVector &Point1, const CVector &Point2);

		/** @brief Konstruktor kopiuj�cy.
		 *  @param[in] Ray P�prosta �r�d�owa.
		 */
		CRay(const CRay &Ray);
	
	public:
		/** @brief Funkcja odwracaj�ca kierunek p�prostej.
		 */
		void Negative(void);

	public:
		/** @brief Funkcja ustawiaj�ca parametry p�prostej.
		 *  @param[in] Point Punkt pocz�tkowy p�prostej.
		 *  @param[in] Direction Wektor kierunkowy p�prostej.
		 *  Funkcja dodatkowo normalizuje wektor kierunkowy p�prostej.
		 */
		void Set(const CVector &Point, const CVector &Direction);

		/** @brief Funkcja ustawiaj�ca punkt pocz�tkowy p�prostej.
		 *  @param[in] Point Punkt pocz�tkowy p�prostej.
		 */
		void SetPoint(const CVector &Point);

		/** @brief Funkcja ustawiaj�ca wektor kierunkowy p�prostej.
		 *  @param[in] Direction Nowy wektor kierunkowy p�prostej.
		 *  Funkcja dodatkowo normalizuje wektor kierunkowy p�prostej.
		 */
		void SetDirection(const CVector &Direction);
	
	public:
		/** @brief Funkcja wyznacza najbli�sze punkty na dw�ch p�prostych.
		 *  @param[in] Ray Druga p�prosta.
		 *  @param[out] Point1 Punkt znajduj�cy si� na pierwszej p�prostej.
		 *  @param[out] Point2 Punkt znajduj�cy si� na drugiej p�prostej (Ray).
		 */
		void AdjacentPoints(const CRay &Ray, CVector &Point1, CVector &Point2) const;

		/** @brief Sprawdza czy dwa punkty le�� po tej samej stronie p�prostej.
		 *  @param[in] Point1 Pierwszy badany punkt.
		 *  @param[in] Point2 Drugi badany punkt.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li oba punkty 
		 *          znajduj� si� po tej samej stronie p�prostej.
		 */
		int AreAtSameSide(const CVector &Point1, const CVector &Point2) const;
	
	public:
		/** @brief Funkcja wyznacza odleg�o�� mi�dzy dwoma p�prostymi.
		 *  @param[in] Ray Druga p�prosta.
		 *  @retval Funkcja zwraca odleg�o�� mi�dzy dwoma p�prostymi, a je�li si�
		 *          przecinaj� to zwraca 0.
		 */
		float Distance(const CRay &Ray) const;

		/** @brief Funkcja wyznacza odleg�o�� punktu od p�prostej.
		 *  @param[in] Point Badany punkt.
		 *  @retval Funkcja zwraca odleg�o�� punktu od p�prostej.
		 */
		float Distance(const CVector &Point) const;
	
	public:
		/** @brief Operator odwracania p�prostej.
		 *  @retval Operator zwraca p�prost� o odwr�conym wektorze kierunkowym.
		 */
		CRay operator-(void) const;

};
