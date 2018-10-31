
/** @file Billard.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy billarda CBillard.
 *
 *  Plik zawiera definicj� klasy CBillard. Plik zawiera dodatkowo
 *  typy danych potrzebne do stworzenia tej klasy.
 *
 */ 

#pragma once

#include "afxtempl.h"
#include "Ball.h"
#include "Triangle.h"
#include "Player.h"

/** @brief Dynamiczna tablica bil oparta o CArray.
 */
typedef CArray<CBall,CBall&> CBalls;

/** @brief Dynamiczna tablica tr�jk�t�w oparta o CArray.
 */
typedef CArray<CTriangle,CTriangle&> CTriangles;

/** @brief Dynamiczna tablica graczy oparta o CArray.
 */
typedef CArray<CPlayer,CPlayer&> CPlayers;

/** @brief Maksymalna si�a uderzenia bia�ej bili.
 */
#define MAX_FORCE  2000.0f

/** @brief Typ wyliczeniowy definiuj�cy stan gry billarda:
 *         pocz�tek gry, obserwacja sto�u, ustawianie bia�ej bili,
 *         celowanie, strza�, koniec gry.
 */
typedef enum {
	/** @brief Pocz�tek gry, prezentacja menu i obr�t kamery dooko�a sto�u.
	 */
	bsStart,

	/** @brief Gracz obserwuje st�.
	 */
	bsView,

	/** @brief Gracz ustawia bia�a bil�.
	 */
	bsBallInHand,

	/** @brief Gracz celuje.
	 */
	bsAim,

	/** @brief Gracz wykona� strza� (trwa symulacja).
	 */
	bsShot,

	/** @brief Gra zako�czona.
	 */
	bsOver
} CBillardState;

/** 
 *  Klasa zawiera tablice graczy, bil i tr�jk�t�w potrzebnych do przeprowadzenia
 *  symulacji i gry. Udost�pnia metody niezb�dne do rozpocz�cia, i obs�ugi gry,
 *  do wczytywania i zapisywania stanu gry, obs�ugi klawiatury, myszki itd.
 *
 *  @brief Klasa reprezentuj�ca gr�.
 */
class CBillard {

	public:
		/** @brief Stan gry. */
		CBillardState m_State;
		/** @brief Flaga aktywno�ci symulacji. */
		int m_Running;
		/** @brief Pauza symulacji. */
		int m_Pause;
		/** @brief Flaga pierwszej kolizji bil. */
		int m_Collision;
		/** @brief Liczba bil kolorowych. */
		int m_ColorCount;
		/** @brief Liczba bil kolorowych pozostaj�cych na stole. */
		int m_ColorLeftCount;
		/** @brief Liczba bil czerwonych. */
		int m_RedCount;
		/** @brief Liczba bil czerwonych pozostaj�cych na stole. */
		int m_RedLeftCount;
		/** @brief Indeks gracza rozgrywaj�cego w tablicy. Je�li -1, to gra treningowa. */
		int m_StrikerIndex;
		/** @brief Tablica graczy. */
		CPlayers m_Players;
		/** @brief Indeks bia�ej bili w tablicy. Je�li -1, to brakuje bia�ej bili. */
		int m_WhiteIndex;
		/** @brief Tablica z bilami. */
		CBalls m_Balls;
		/** @brief Tablica z tr�jk�tami. */
		CTriangles m_Triangles;
		/** brief Sila uderzenia. */
		float m_Force;

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CBillard(void);

	public:
		/**
		 *  Funkcja odczytuje gr� z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    STATE 1
		 *    STRIKER_INDEX 0
		 *    ...
		 *  END
		 *  </pre>
		 *
		 *	@brief Funkcja odczytuj�ca ca�� gr� z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje gr� do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *	@brief Funkcja zapisuj�ca ca�� gr� do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/**
		 *  Funkcja inicjalizuje now� gr�. Parametr Players zawiera tablic� z graczami.
		 *  Je�li tablica jest pusta, to gra jest treningowa. Funkcja ustawia szereg
		 *  zmiennych i bil. Nast�pnie przechodzi do widoku i �aduje czwart� predefiniowan�
		 *  pozycj� kamery.
		 *
		 *  @brief Funkcja rozpoczyna now� gr�.
		 *  @param[in] Players Tablica z graczami.
		 */
		void NewGame(const CPlayers &Players);

		/** @brief Funkcja �aduj�ca ca�� gr� z pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku, z kt�rego nale�y wczyta� gr�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int LoadGame(const CString FileName);

		/** @brief Funkcja zapisuj�ca ca�� gr� do pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku, do kt�rego nale�y zapisa� gr�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int SaveGame(const CString FileName);

	public:
		/** @brief Funkcja wykonuj�ca symulacj� (ruch) bil, obs�ug� klawiatury, 
		 *         myszki i kamery.
		 *  @param[in] Time Czas kt�ry up�yn�� od poprzedniego wywo�ania funkcji.
		 */
		void Run(float Time);

		/** @brief Funkcja przetwarzaj�ca klawiatur�, myszk�.
		 *  @param[in] Time Czas kt�ry up�yn�� od poprzedniego wywo�ania funkcji.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void ProcessControls(float Time);

		/** @brief Funkcja przechodzi do kolejnego stanu gry.
		 */
		void NextState(void);

		/** @brief Funkcja przechodzi do poprzedniego stanu gry.
		 */
		void PreviousState(void);

		/** @brief Funkcja ustawiaj�ca stan gry.
		 *  @param[in] State Nowy stan gry.
		 */
		void SetState(CBillardState State);

	public:
		/** @brief Funkcja wywo�ywana przy rozpocz�ciu symulacji.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void OnStart(void);

		/** @brief Funkcja wywo�ywana przy zako�czeniu symulacji.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void OnStop(void);

		/** @brief Funkcja wywo�ywana przy wpadni�ciu bili do kieszeni.
		 *  @param[in] Ball Referencja do bili, kt�ra w�a�nie wpad�a.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void OnKnockIn(CBall &Ball);

		/** @brief Funkcja wywo�ywana przy zderzeniu dw�ch bil.
		 *  @param[in] Ball1 Referencja do pierwszej bili zderzaj�cej.
		 *  @param[in] Ball2 Referencja do drugiej bili zderzaj�cej.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void OnCollision(CBall &Ball1, CBall &Ball2);

	public:
		/** @brief Funkcja przyk�adaj�ca si�y do bil.
		 *  @param[in] Time Czas przy�o�enia si�y.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li jeszcze jaka� bila si� toczy.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		int ApplyForces(float Time);

		/** @brief Funkcja przesuwaj�ca bile.
		 *  @param[in] Time Czas przesuni�cia.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void Simulate(float Time);

		/** @brief Funkcja cofaj�ca bile.
		 *  @param[in] Index Indeks bili, kt�r� chcemy cofn��, je�li -1, to cofa wszyskie bile.
		 *  @warning Funkcja jest wywo�ywana przez funkcj� Run.
		 */
		void Restore(int Index = -1);

		/** @brief Funkcja przywracaj�ca oryginalne po�o�enia bil.
		 *  @param[in] Index Indeks bili, kt�r� chcemy przywr�ci�, je�li -1, to przywraca wszyskie bile.
		 */
		void Reset(int Index = -1);

		/** @brief Funkcja zatrzymuj�ca bile.
		 *  @param[in] Index Indeks bili, kt�r� chcemy zatrzyma�, je�li -1, to zatrzymuje wszyskie bile.
		 */
		void Stop(int Index = -1);

	public:
		/** @brief Funkcja szukaj�ca tr�jk�ta po kt�rym bila si� toczy.
		 *  @param[in] Ball Referencja do bili, dla kt�rej chcemy znale�� nowy tr�jk�t.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li uda�o si� znale�� tr�jk�t.
		 *  @warning Funkcja modyfikuje odpowiednio bil� zapami�tuj�c wska�nik do nowo znalezionego tr�jk�ta.
		 */
		int FindTriangle(CBall &Ball);

		/** @brief Funkcja szukaj�ca kolizje mi�dzy bilami.
		 *  @param[in] FullTime Czas symulacji.
		 *  @param[out] Time Czas do zderzenia dw�ch bil.
		 *  @param[out] Ball1 Indeks pierwszej zderzaj�cej si� bili.
		 *  @param[out] Ball2 Indeks drugiej zderzaj�cej si� bili.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li uda�o si� znale�� kolizj�.
		 */
		int FindBallsCollision(float FullTime, float &Time, int &Ball1, int &Ball2);

		/** @brief Funkcja szukaj�ca kolizje mi�dzy bil� a tr�jk�tem (band�, do�kiem, etc.).
		 *  @param[in] FullTime Czas symulacji.
		 *  @param[out] Time Czas do zderzenia bili z band�.
		 *  @param[out] Ball Indeks bili kolizyjnej.
		 *  @param[out] Triangle Indeks tr�jk�ta kolizyjnego.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li uda�o si� znale�� kolizj�.
		 */
		int FindTriangleCollision(float FullTime, float &Time, int &Ball, int &Triangle);

};
