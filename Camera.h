
/** @file Camera.h
 *  @author Miros≥aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag≥Ûwkowy klasy CCamera i CCameraPosition.
 *
 *  Plik zawiera definicjÍ klasy CCamera i CCameraPosition.
 *
 */ 

#pragma once

#include "Vector.h"
#include "Ball.h"

/**
 *  Klasa zawiera pola jednoznacznie opisujπce po≥oøenie kamery w przestrzeni 3D.
 *  Dodatkowo zawiera funkcje do odczytu i zapisu po≥oøenie z/do pliku, oraz wykonywania
 *  przesuniÍcia do nowej pozycji.
 *  
 *  @brief Klasa reprezentujπca po≥oøenie kamery.
 */
class CCameraPosition {

	public:
		/** @brief Pozycja na osi OX kamery. */
		float m_X;
		/** @brief Ostatni przyrost po≥oøenia kamery na osi OX. */
		float m_dX;
		/** @brief Pozycja na osi OY kamery. */
		float m_Y;
		/** @brief Ostatni przyrost po≥oøenia kamery na osi OY. */
		float m_dY;
		/** @brief Pozycja na osi OZ kamery. */
		float m_Z;
		/** @brief Ostatni przyrost po≥oøenia kamery na osi OZ. */
		float m_dZ;
		/** @brief Kπt nachylenia kamery do do≥u (wokÛ≥ osi OX). */
		float m_Alpha;
		/** @brief Ostatni przyrost kπt nachylenia kamery do do≥u (wokÛ≥ osi OX). */
		float m_dAlpha;
		/** @brief Kπt obrotu kamery wzglÍdem osi OZ. */
		float m_Beta;
		/** @brief Ostatni przyrost kπta obrotu kamery wzglÍdem osi OZ. */
		float m_dBeta;
		/** @brief Kπt perspektywy kamery. */
		float m_FOV;
		/** @brief Ostatni przyrost kπta perspektywy kamery. */
		float m_dFOV;

	public:
		/** @brief Konstruktor domyúlny. */
		CCameraPosition(void);

		/** @brief Konstruktor kopiujπcy. 
		 *  @param[in] Position èrÛd≥owa pozycja kamery.
		 */
		CCameraPosition(const CCameraPosition &Position);

		/** @brief Konstruktor z inicjalizacjπ ustawieÒ. 
		 *  @param[in] X WspÛ≥rzÍdna po≥oøenia X.
		 *  @param[in] Y WspÛ≥rzÍdna po≥oøenia Y.
		 *  @param[in] Z WspÛ≥rzÍdna po≥oøenia Z.
		 *  @param[in] Alpha Kπt obrotu wzglÍdem osi X.
		 *  @param[in] Beta Kπt obrotu wzglÍdem osi Z.
		 *  @param[in] FOV Kπt perspektywy.
		 */
		CCameraPosition(float X, float Y, float Z, float Alpha, float Beta, float FOV);

	public:
		/**
		 *  Funkcja odczytuje pozycjÍ kamery z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    X 0
		 *    Y 1
		 *    ...
		 *    ALPHA 30
		 *  END
		 *  </pre>
		 *
		 *  @brief Funkcja odczytujπca po≥oøenie kamery z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje pozycjÍ kamery do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisujπca po≥oøenie kamery do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype≥nienie tabulacja przed kaødπ liniπ.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja przesuwajπca po≥oøenie do po≥oøenia docelowego przez czas Time.
		 *  @param[in] Time Czas przesuniÍcia.
		 *  @param[in] Position Po≥oøenie docelowe.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		void MoveTo(float Time, const CCameraPosition &Position);

	public:
		/** @brief Funkcja zwraca po≥oøenie kamery na osi OX. 
		 *  @retval Funkcja zwraca po≥oøenie kamery na osi OX.
		 */
		float GetX(void) const { return m_X; };

		/** @brief Funkcja zwraca po≥oøenie kamery na osi OY. 
		 *  @retval Funkcja zwraca po≥oøenie kamery na osi OY.
		 */
		float GetY(void) const { return m_Y; };

		/** @brief Funkcja zwraca po≥oøenie kamery na osi OZ. 
		 *  @retval Funkcja zwraca po≥oøenie kamery na osi OZ.
		 */
		float GetZ(void) const { return m_Z; };

		/** @brief Funkcja zwraca kπt nachylenia kamery do do≥u (wzglÍdem osi OX). 
		 *  @retval Funkcja zwraca kπt nachylenia kamery do do≥u (wzglÍdem osi OX).
		 */
		float GetAlpha(void) const { return m_Alpha; };

		/** @brief Funkcja zwraca kπt obrotu kamery wzglÍdem osi OZ. 
		 *  @retval Funkcja zwraca kπt obrotu kamery wzglÍdem osi OZ.
		 */
		float GetBeta(void) const { return m_Beta; };

		/** @brief Funkcja zwraca kπt perspektywy kamery. 
		 *  @retval Funkcja zwraca kπt perspektywy kamery.
		 */
		float GetFOV(void) const { return m_FOV; };

		/** @brief Funkcja zwraca pozycjÍ kamery jako wektor. 
		 *  @retval Funkcja zwraca pozycjÍ kamery jako wektor.
		 */
		CVector GetVector(void) const { return CVector(m_X, m_Y, m_Z); };

	public:
		/** @brief Funkcja ustawia pozycjÍ kamery na osi OX.
		 */
		void SetX(float X) { m_X = X; };

		/** @brief Funkcja ustawia pozycjÍ kamery na osi OY.
		 */
		void SetY(float Y) { m_Y = Y; };

		/** @brief Funkcja ustawia pozycjÍ kamery na osi OZ.
		 */
		void SetZ(float Z) { m_Z = Z; };

		/** @brief Funkcja ustawia kπt nachylenia kamery do do≥u (wzglÍdem osi OX).
		 */
		void SetAlpha(float Alpha) { m_Alpha = Alpha; };

		/** @brief Funkcja ustawia kπt obrotu kamery wzglÍdem osi OZ.
		 */
		void SetBeta(float Beta) { m_Beta = Beta; };

		/** @brief Funkcja ustawia perpektywÍ kamery.
		 */
		void SetFOV(float FOV) { m_FOV = FOV; };

	public:
		/** @brief Operator przypisania. 
		 *  @param[in] Position èrÛd≥owa pozycja kamery. 
		 *  @retval Operator zwraca referencjÍ do tego po≥oøenia.
		 */
		CCameraPosition& operator=(const CCameraPosition &Position);

};

/** 
 *  Klasa zawiera pola opisujπce kamerÍ i jej po≥oøenie w przestrzeni.
 *  Klasa udostÍpnia szereg funkcji do przesuwania i obrotÛw kamery 
 *  w przestrzeni, zapisu i odczytu do/z pliku, etc.
 *
 *  @brief Klasa reprezentujπca kamerÍ.
 */
class CCamera {

	private:
		/** @brief Indeks bili na ktÛrπ ma spojrzeÊ kamera. */
		int m_BallIndex;
		/** @brief Bliøsza p≥aszczyzna obcinania perspektywy. */
		float m_Near;
		/** @brief Daleka p≥aszczyzna obcinania perspektywy. */
		float m_Far;
		/** @brief WspÛ≥czynnik przesuwania kamery. */
		float m_MoveFactor;
		/** @brief WspÛ≥czynnik obrotu kamery. */
		float m_RollFactor;
		/** @brief WspÛ≥czynnik obrotu kamery wokÛ≥ sto≥u. */
		float m_FlyFactor;
		/** @brief Minimalne wartoúci po≥oøenia kamery. */
		CCameraPosition m_Min;
		/** @brief Maksymalne wartoúci po≥oøenia kamery. */
		CCameraPosition m_Max;
		/** @brief Po≥oøenie docelowe kamery. */
		CCameraPosition m_Target;
		/** @brief Aktualne po≥oøenie kamery. */
		CCameraPosition m_Position;
		/** @brief Tablica po≥oøeÒ kamery. */
		CArray<CCameraPosition,CCameraPosition&> m_Positions;

	private:
		/** @brief Uaktualnia perspektywÍ.
		 */
		void UpdatePerspective(void);

	public:
		/** @brief Konstruktor domyúlny.
		 */
		CCamera(void);

	public:
		/**
		 *  Funkcja odczytuje kamerÍ z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    POSITION
		 *    ...
		 *  END
		 *  </pre>
		 *
		 *  @brief Funkcja odczytujπca kamerÍ z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje kamerÍ do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisujπca kamerÍ do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype≥nienie tabulacja przed kaødπ liniπ.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja przesuwajπca kamerÍ do pozycji docelowej.
		 *  @param[in] Time Czas przesuwania.
		 */
		void Run(float Time);

	public:
		/** @brief Funkcja ≥adujπca pozycjÍ kamery z wczeúniej zapisanych.
		 *  @param[in] Index Numer pozycji.
		 */
		void LoadPosition(int Index);

		/** @brief Funkcja zapamiÍtujπca pozycjÍ kamery.
		 *  @param[in] Index Numer pozycji pod ktÛrπ zapisaÊ aktualnπ pozycjÍ.
		 */
		void StorePosition(int Index);

	public:
		/** @brief Funkcja ≥adujπca kamerÍ z pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku tekstowego.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Load(const CString FileName);

		/** @brief Funkcja zapisujπca kamerÍ do pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku tekstowego.
		 *  @retval Zwraca wartoúÊ rÛønπ od zera jeúli operacja powiod≥a siÍ.
		 */
		int Save(const CString FileName);

	public:
		/** @brief Funkcja przesuwa kamerÍ do przodu rÛwnolegle do p≥aszczyzny (X,Y).
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveForward(float Factor);

		/** @brief Funkcja przesuwa kamerÍ do ty≥u rÛwnolegle do p≥aszczyzny (X,Y).
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveBackward(float Factor);

	public:
		/** @brief Funkcja przesuwa kamerÍ do przodu zgodnie z widokiem.
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveIn(float Factor);

		/** @brief Funkcja przesuwa kamerÍ do ty≥u zgodnie z widokiem.
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveOut(float Factor);

	public:
		/** @brief Funkcja przesuwa kamerÍ do gÛry rÛwnolegle do osi OZ.
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveUp(float Factor);

		/** @brief Funkcja przesuwa kamerÍ do do≥u rÛwnolegle do osi OZ.
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveDown(float Factor);

		/** @brief Funkcja przesuwa kamerÍ w lewo rÛwnolegle do p≥aszczyzny (X,Y).
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveLeft(float Factor);

		/** @brief Funkcja przesuwa kamerÍ w prawo rÛwnolegle do p≥aszczyzny (X,Y).
		 *  @param[in] Factor WspÛ≥czynnik przesuniÍcia.
		 */
		void MoveRight(float Factor);

	public:
		/** @brief Funkcja wykonuje powiÍkszenie obrazu kamery.
		 *  @param[in] Factor WspÛ≥czynnik powiÍkszenia.
		 */
		void ZoomIn(float Factor);

		/** @brief Funkcja wykonuje pomniejszenie obrazu kamery.
		 *  @param[in] Factor WspÛ≥czynnik pomniejszenia.
		 */
		void ZoomOut(float Factor);

	public:
		/** @brief Funkcja obraca kamerÍ do gÛry wzglÍdem osi OX.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 */
		void RollUp(float Factor);

		/** @brief Funkcja obraca kamerÍ do do≥u wzglÍdem osi OX.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 */
		void RollDown(float Factor);

		/** @brief Funkcja obraca kamerÍ w lewo wzglÍdem osi OZ.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 */
		void RollLeft(float Factor);

		/** @brief Funkcja obraca kamerÍ w prawo wzglÍdem osi OZ.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 */
		void RollRight(float Factor);

	public:
		/** @brief Funkcja obraca kamerÍ do gÛry dooko≥a punktu.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 *  @param[in] Point Punkt wokÛ≥ ktÛrego kamera obraca siÍ.
		 */
		void AroundUp(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamerÍ do do≥u dooko≥a punktu.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 *  @param[in] Point Punkt wokÛ≥ ktÛrego kamera obraca siÍ.
		 */
		void AroundDown(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamerÍ w lewo dooko≥a punktu.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 *  @param[in] Point Punkt wokÛ≥ ktÛrego kamera obraca siÍ.
		 */
		void AroundLeft(float Factor, const CVector &Point);

		/** @brief Funkcja obraca kamerÍ w prawo dooko≥a punktu.
		 *  @param[in] Factor WspÛ≥czynnik obrotu.
		 *  @param[in] Point Punkt wokÛ≥ ktÛrego kamera obraca siÍ.
		 */
		void AroundRight(float Factor, const CVector &Point);

	public:
		/** @brief Funkcja kieruje kamere na punkt o podanych wspÛ≥rzÍdnych.
		 *  @param[in] Point Punkt na ktÛry kamera ma siÍ skierowaÊ.
		 */
		void LookAt(const CVector &Point);

	public:
		/** @brief Funkcja zwraca bliøszy prostokπt obcinania perspektywy.
		 *  @retval Funkcja zwraca bliøszy prostokπt obcinania perspektywy.
		 */
		float GetNear(void) const { return m_Near; };

		/** @brief Funkcja zwraca dalszy prostokπt obcinania perspektywy.
		 *  @retval Funkcja zwraca dalszy prostokπt obcinania perspektywy.
		 */
		float GetFar(void) const { return m_Far; };

		/** @brief Funkcja zwraca aktualnπ pozycjÍ kamery.
		 *  @retval Funkcja zwraca aktualnπ pozycjÍ kamery.
		 */
		const CCameraPosition& GetPosition(void) const { return m_Position; };

		/** @brief Funkcja zwraca wspÛ≥czynnik przesuwania kamery.
		 *  @retval Funkcja zwraca wspÛ≥czynnik przesuwania kamery.
		 */
		float GetMoveFactor(void) { return m_MoveFactor; };

		/** @brief Funkcja zwraca wspÛ≥czynnik obracania kamery.
		 *  @retval Funkcja zwraca wspÛ≥czynnik obracania kamery.
		 */
		float GetRollFactor(void) { return m_RollFactor; };

		/** @brief Funkcja zwraca wspÛ≥czynnik lotu kamery wokÛ≥ sto≥u.
		 *  @retval Funkcja zwraca wspÛ≥czynnik lotu kamery wokÛ≥ sto≥u.
		 */
		float GetFlyFactor(void) { return m_FlyFactor; };
/*
		const CCameraPosition& GetMin(void) const { return m_Min; };
		const CCameraPosition& GetMax(void) const { return m_Max; };
*/
	public:
		/** @brief Funkcja kieruje kamere na bile o podanym indeksie.
		 *  @param[in] BallIndex Indeks bili na ktÛrπ kamera ma siÍ obrÛciÊ.
		 */
		void SetBall(int BallIndex);

		/** @brief Funkcja ustawia pozycjÍ docelowπ kamery.
		 *  @param[in] Position Pozycja docelowa kamery.
		 */
		void SetPosition(const CCameraPosition &Position);

		/** @brief Funkcja ustawia wspÛ≥czynnik przesuwania kamery.
		 *  @param[in] MoveFactor Nowy wspÛ≥czynnik przesuwania kamery.
		 */
		void SetMoveFactor(float MoveFactor) { m_MoveFactor = MoveFactor; };

		/** @brief Funkcja ustawia wspÛ≥czynnik obracania kamery.
		 *  @param[in] RollFactor Nowy wspÛ≥czynnik obracania kamery.
		 */
		void SetRollFactor(float RollFactor) { m_RollFactor = RollFactor; };

		/** @brief Funkcja ustawia wspÛ≥czynnik lotu kamery wokÛ≥ sto≥u.
		 *  @param[in] FlyFactor Nowy wspÛ≥czynnik lotu kamery wokÛ≥ sto≥u.
		 */
		void SetFlyFactor(float FlyFactor) { m_FlyFactor = FlyFactor; };

	public:
		/** @brief Funkcja obraca kamerÍ dooko≥a sto≥u.
		 *  @param[in] Time Czas miÍdzy jednπ a drugπ klatkπ.
		 */
		void FlyAround(float Time);

};
