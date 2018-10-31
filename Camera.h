
/** @file Camera.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CCamera i CCameraPosition.
 *
 *  Plik zawiera definicj� klasy CCamera i CCameraPosition.
 *
 */ 

#pragma once

#include "Vector.h"
#include "Ball.h"

/**
 *  Klasa zawiera pola jednoznacznie opisuj�ce po�o�enie kamery w przestrzeni 3D.
 *  Dodatkowo zawiera funkcje do odczytu i zapisu po�o�enie z/do pliku, oraz wykonywania
 *  przesuni�cia do nowej pozycji.
 *  
 *  @brief Klasa reprezentuj�ca po�o�enie kamery.
 */
class CCameraPosition {

	public:
		/** @brief Pozycja na osi OX kamery. */
		float m_X;
		/** @brief Ostatni przyrost po�o�enia kamery na osi OX. */
		float m_dX;
		/** @brief Pozycja na osi OY kamery. */
		float m_Y;
		/** @brief Ostatni przyrost po�o�enia kamery na osi OY. */
		float m_dY;
		/** @brief Pozycja na osi OZ kamery. */
		float m_Z;
		/** @brief Ostatni przyrost po�o�enia kamery na osi OZ. */
		float m_dZ;
		/** @brief K�t nachylenia kamery do do�u (wok� osi OX). */
		float m_Alpha;
		/** @brief Ostatni przyrost k�t nachylenia kamery do do�u (wok� osi OX). */
		float m_dAlpha;
		/** @brief K�t obrotu kamery wzgl�dem osi OZ. */
		float m_Beta;
		/** @brief Ostatni przyrost k�ta obrotu kamery wzgl�dem osi OZ. */
		float m_dBeta;
		/** @brief K�t perspektywy kamery. */
		float m_FOV;
		/** @brief Ostatni przyrost k�ta perspektywy kamery. */
		float m_dFOV;

	public:
		/** @brief Konstruktor domy�lny. */
		CCameraPosition(void);

		/** @brief Konstruktor kopiuj�cy. 
		 *  @param[in] Position �r�d�owa pozycja kamery.
		 */
		CCameraPosition(const CCameraPosition &Position);

		/** @brief Konstruktor z inicjalizacj� ustawie�. 
		 *  @param[in] X Wsp�rz�dna po�o�enia X.
		 *  @param[in] Y Wsp�rz�dna po�o�enia Y.
		 *  @param[in] Z Wsp�rz�dna po�o�enia Z.
		 *  @param[in] Alpha K�t obrotu wzgl�dem osi X.
		 *  @param[in] Beta K�t obrotu wzgl�dem osi Z.
		 *  @param[in] FOV K�t perspektywy.
		 */
		CCameraPosition(float X, float Y, float Z, float Alpha, float Beta, float FOV);

	public:
		/**
		 *  Funkcja odczytuje pozycj� kamery z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    X 0
		 *    Y 1
		 *    ...
		 *    ALPHA 30
		 *  END
		 *  </pre>
		 *
		 *  @brief Funkcja odczytuj�ca po�o�enie kamery z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje pozycj� kamery do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisuj�ca po�o�enie kamery do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja przesuwaj�ca po�o�enie do po�o�enia docelowego przez czas Time.
		 *  @param[in] Time Czas przesuni�cia.
		 *  @param[in] Position Po�o�enie docelowe.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		void MoveTo(float Time, const CCameraPosition &Position);

	public:
		/** @brief Funkcja zwraca po�o�enie kamery na osi OX. 
		 *  @retval Funkcja zwraca po�o�enie kamery na osi OX.
		 */
		float GetX(void) const { return m_X; };

		/** @brief Funkcja zwraca po�o�enie kamery na osi OY. 
		 *  @retval Funkcja zwraca po�o�enie kamery na osi OY.
		 */
		float GetY(void) const { return m_Y; };

		/** @brief Funkcja zwraca po�o�enie kamery na osi OZ. 
		 *  @retval Funkcja zwraca po�o�enie kamery na osi OZ.
		 */
		float GetZ(void) const { return m_Z; };

		/** @brief Funkcja zwraca k�t nachylenia kamery do do�u (wzgl�dem osi OX). 
		 *  @retval Funkcja zwraca k�t nachylenia kamery do do�u (wzgl�dem osi OX).
		 */
		float GetAlpha(void) const { return m_Alpha; };

		/** @brief Funkcja zwraca k�t obrotu kamery wzgl�dem osi OZ. 
		 *  @retval Funkcja zwraca k�t obrotu kamery wzgl�dem osi OZ.
		 */
		float GetBeta(void) const { return m_Beta; };

		/** @brief Funkcja zwraca k�t perspektywy kamery. 
		 *  @retval Funkcja zwraca k�t perspektywy kamery.
		 */
		float GetFOV(void) const { return m_FOV; };

		/** @brief Funkcja zwraca pozycj� kamery jako wektor. 
		 *  @retval Funkcja zwraca pozycj� kamery jako wektor.
		 */
		CVector GetVector(void) const { return CVector(m_X, m_Y, m_Z); };

	public:
		/** @brief Funkcja ustawia pozycj� kamery na osi OX.
		 */
		void SetX(float X) { m_X = X; };

		/** @brief Funkcja ustawia pozycj� kamery na osi OY.
		 */
		void SetY(float Y) { m_Y = Y; };

		/** @brief Funkcja ustawia pozycj� kamery na osi OZ.
		 */
		void SetZ(float Z) { m_Z = Z; };

		/** @brief Funkcja ustawia k�t nachylenia kamery do do�u (wzgl�dem osi OX).
		 */
		void SetAlpha(float Alpha) { m_Alpha = Alpha; };

		/** @brief Funkcja ustawia k�t obrotu kamery wzgl�dem osi OZ.
		 */
		void SetBeta(float Beta) { m_Beta = Beta; };

		/** @brief Funkcja ustawia perpektyw� kamery.
		 */
		void SetFOV(float FOV) { m_FOV = FOV; };

	public:
		/** @brief Operator przypisania. 
		 *  @param[in] Position �r�d�owa pozycja kamery. 
		 *  @retval Operator zwraca referencj� do tego po�o�enia.
		 */
		CCameraPosition& operator=(const CCameraPosition &Position);

};

/** 
 *  Klasa zawiera pola opisuj�ce kamer� i jej po�o�enie w przestrzeni.
 *  Klasa udost�pnia szereg funkcji do przesuwania i obrot�w kamery 
 *  w przestrzeni, zapisu i odczytu do/z pliku, etc.
 *
 *  @brief Klasa reprezentuj�ca kamer�.
 */
class CCamera {

	private:
		/** @brief Indeks bili na kt�r� ma spojrze� kamera. */
		int m_BallIndex;
		/** @brief Bli�sza p�aszczyzna obcinania perspektywy. */
		float m_Near;
		/** @brief Daleka p�aszczyzna obcinania perspektywy. */
		float m_Far;
		/** @brief Wsp�czynnik przesuwania kamery. */
		float m_MoveFactor;
		/** @brief Wsp�czynnik obrotu kamery. */
		float m_RollFactor;
		/** @brief Wsp�czynnik obrotu kamery wok� sto�u. */
		float m_FlyFactor;
		/** @brief Minimalne warto�ci po�o�enia kamery. */
		CCameraPosition m_Min;
		/** @brief Maksymalne warto�ci po�o�enia kamery. */
		CCameraPosition m_Max;
		/** @brief Po�o�enie docelowe kamery. */
		CCameraPosition m_Target;
		/** @brief Aktualne po�o�enie kamery. */
		CCameraPosition m_Position;
		/** @brief Tablica po�o�e� kamery. */
		CArray<CCameraPosition,CCameraPosition&> m_Positions;

	private:
		/** @brief Uaktualnia perspektyw�.
		 */
		void UpdatePerspective(void);

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CCamera(void);

	public:
		/**
		 *  Funkcja odczytuje kamer� z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    POSITION
		 *    ...
		 *  END
		 *  </pre>
		 *
		 *  @brief Funkcja odczytuj�ca kamer� z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje kamer� do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisuj�ca kamer� do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja przesuwaj�ca kamer� do pozycji docelowej.
		 *  @param[in] Time Czas przesuwania.
		 */
		void Run(float Time);

	public:
		/** @brief Funkcja �aduj�ca pozycj� kamery z wcze�niej zapisanych.
		 *  @param[in] Index Numer pozycji.
		 */
		void LoadPosition(int Index);

		/** @brief Funkcja zapami�tuj�ca pozycj� kamery.
		 *  @param[in] Index Numer pozycji pod kt�r� zapisa� aktualn� pozycj�.
		 */
		void StorePosition(int Index);

	public:
		/** @brief Funkcja �aduj�ca kamer� z pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku tekstowego.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Load(const CString FileName);

		/** @brief Funkcja zapisuj�ca kamer� do pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku tekstowego.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Save(const CString FileName);

	public:
		/** @brief Funkcja przesuwa kamer� do przodu r�wnolegle do p�aszczyzny (X,Y).
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveForward(float Factor);

		/** @brief Funkcja przesuwa kamer� do ty�u r�wnolegle do p�aszczyzny (X,Y).
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveBackward(float Factor);

	public:
		/** @brief Funkcja przesuwa kamer� do przodu zgodnie z widokiem.
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveIn(float Factor);

		/** @brief Funkcja przesuwa kamer� do ty�u zgodnie z widokiem.
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveOut(float Factor);

	public:
		/** @brief Funkcja przesuwa kamer� do g�ry r�wnolegle do osi OZ.
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveUp(float Factor);

		/** @brief Funkcja przesuwa kamer� do do�u r�wnolegle do osi OZ.
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveDown(float Factor);

		/** @brief Funkcja przesuwa kamer� w lewo r�wnolegle do p�aszczyzny (X,Y).
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveLeft(float Factor);

		/** @brief Funkcja przesuwa kamer� w prawo r�wnolegle do p�aszczyzny (X,Y).
		 *  @param[in] Factor Wsp�czynnik przesuni�cia.
		 */
		void MoveRight(float Factor);

	public:
		/** @brief Funkcja wykonuje powi�kszenie obrazu kamery.
		 *  @param[in] Factor Wsp�czynnik powi�kszenia.
		 */
		void ZoomIn(float Factor);

		/** @brief Funkcja wykonuje pomniejszenie obrazu kamery.
		 *  @param[in] Factor Wsp�czynnik pomniejszenia.
		 */
		void ZoomOut(float Factor);

	public:
		/** @brief Funkcja obraca kamer� do g�ry wzgl�dem osi OX.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 */
		void RollUp(float Factor);

		/** @brief Funkcja obraca kamer� do do�u wzgl�dem osi OX.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 */
		void RollDown(float Factor);

		/** @brief Funkcja obraca kamer� w lewo wzgl�dem osi OZ.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 */
		void RollLeft(float Factor);

		/** @brief Funkcja obraca kamer� w prawo wzgl�dem osi OZ.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 */
		void RollRight(float Factor);

	public:
		/** @brief Funkcja obraca kamer� do g�ry dooko�a punktu.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 *  @param[in] Point Punkt wok� kt�rego kamera obraca si�.
		 */
		void AroundUp(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamer� do do�u dooko�a punktu.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 *  @param[in] Point Punkt wok� kt�rego kamera obraca si�.
		 */
		void AroundDown(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamer� w lewo dooko�a punktu.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 *  @param[in] Point Punkt wok� kt�rego kamera obraca si�.
		 */
		void AroundLeft(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamer� w prawo dooko�a punktu.
		 *  @param[in] Factor Wsp�czynnik obrotu.
		 *  @param[in] Point Punkt wok� kt�rego kamera obraca si�.
		 */
		void AroundRight(float Factor, const CVector &Point);

	public:
		/** @brief Funkcja kieruje kamere na punkt o podanych wsp�rz�dnych.
		 *  @param[in] Point Punkt na kt�ry kamera ma si� skierowa�.
		 */
		void LookAt(const CVector &Point);

	public:
		/** @brief Funkcja zwraca bli�szy prostok�t obcinania perspektywy.
		 *  @retval Funkcja zwraca bli�szy prostok�t obcinania perspektywy.
		 */
		float GetNear(void) const { return m_Near; };

		/** @brief Funkcja zwraca dalszy prostok�t obcinania perspektywy.
		 *  @retval Funkcja zwraca dalszy prostok�t obcinania perspektywy.
		 */
		float GetFar(void) const { return m_Far; };

		/** @brief Funkcja zwraca aktualn� pozycj� kamery.
		 *  @retval Funkcja zwraca aktualn� pozycj� kamery.
		 */
		const CCameraPosition& GetPosition(void) const { return m_Position; };

		/** @brief Funkcja zwraca wsp�czynnik przesuwania kamery.
		 *  @retval Funkcja zwraca wsp�czynnik przesuwania kamery.
		 */
		float GetMoveFactor(void) { return m_MoveFactor; };

		/** @brief Funkcja zwraca wsp�czynnik obracania kamery.
		 *  @retval Funkcja zwraca wsp�czynnik obracania kamery.
		 */
		float GetRollFactor(void) { return m_RollFactor; };

		/** @brief Funkcja zwraca wsp�czynnik lotu kamery wok� sto�u.
		 *  @retval Funkcja zwraca wsp�czynnik lotu kamery wok� sto�u.
		 */
		float GetFlyFactor(void) { return m_FlyFactor; };
/*
		const CCameraPosition& GetMin(void) const { return m_Min; };
		const CCameraPosition& GetMax(void) const { return m_Max; };
*/
	public:
		/** @brief Funkcja kieruje kamere na bile o podanym indeksie.
		 *  @param[in] BallIndex Indeks bili na kt�r� kamera ma si� obr�ci�.
		 */
		void SetBall(int BallIndex);

		/** @brief Funkcja ustawia pozycj� docelow� kamery.
		 *  @param[in] Position Pozycja docelowa kamery.
		 */
		void SetPosition(const CCameraPosition &Position);

		/** @brief Funkcja ustawia wsp�czynnik przesuwania kamery.
		 *  @param[in] MoveFactor Nowy wsp�czynnik przesuwania kamery.
		 */
		void SetMoveFactor(float MoveFactor) { m_MoveFactor = MoveFactor; };

		/** @brief Funkcja ustawia wsp�czynnik obracania kamery.
		 *  @param[in] RollFactor Nowy wsp�czynnik obracania kamery.
		 */
		void SetRollFactor(float RollFactor) { m_RollFactor = RollFactor; };

		/** @brief Funkcja ustawia wsp�czynnik lotu kamery wok� sto�u.
		 *  @param[in] FlyFactor Nowy wsp�czynnik lotu kamery wok� sto�u.
		 */
		void SetFlyFactor(float FlyFactor) { m_FlyFactor = FlyFactor; };

	public:
		/** @brief Funkcja obraca kamer� dooko�a sto�u.
		 *  @param[in] Time Czas mi�dzy jedn� a drug� klatk�.
		 */
		void FlyAround(float Time);

};
