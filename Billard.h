
/** @file Billard.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy billarda CBillard.
 *
 *  Plik zawiera definicjê klasy CBillard. Plik zawiera dodatkowo
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

/** @brief Dynamiczna tablica trójk¹tów oparta o CArray.
 */
typedef CArray<CTriangle,CTriangle&> CTriangles;

/** @brief Dynamiczna tablica graczy oparta o CArray.
 */
typedef CArray<CPlayer,CPlayer&> CPlayers;

/** @brief Maksymalna si³a uderzenia bia³ej bili.
 */
#define MAX_FORCE  2000.0f

/** @brief Typ wyliczeniowy definiuj¹cy stan gry billarda:
 *         pocz¹tek gry, obserwacja sto³u, ustawianie bia³ej bili,
 *         celowanie, strza³, koniec gry.
 */
typedef enum {
	/** @brief Pocz¹tek gry, prezentacja menu i obrót kamery dooko³a sto³u.
	 */
	bsStart,

	/** @brief Gracz obserwuje stó³.
	 */
	bsView,

	/** @brief Gracz ustawia bia³a bilê.
	 */
	bsBallInHand,

	/** @brief Gracz celuje.
	 */
	bsAim,

	/** @brief Gracz wykona³ strza³ (trwa symulacja).
	 */
	bsShot,

	/** @brief Gra zakoñczona.
	 */
	bsOver
} CBillardState;

/** 
 *  Klasa zawiera tablice graczy, bil i trójk¹tów potrzebnych do przeprowadzenia
 *  symulacji i gry. Udostêpnia metody niezbêdne do rozpoczêcia, i obs³ugi gry,
 *  do wczytywania i zapisywania stanu gry, obs³ugi klawiatury, myszki itd.
 *
 *  @brief Klasa reprezentuj¹ca grê.
 */
class CBillard {

	public:
		/** @brief Stan gry. */
		CBillardState m_State;
		/** @brief Flaga aktywnoœci symulacji. */
		int m_Running;
		/** @brief Pauza symulacji. */
		int m_Pause;
		/** @brief Flaga pierwszej kolizji bil. */
		int m_Collision;
		/** @brief Liczba bil kolorowych. */
		int m_ColorCount;
		/** @brief Liczba bil kolorowych pozostaj¹cych na stole. */
		int m_ColorLeftCount;
		/** @brief Liczba bil czerwonych. */
		int m_RedCount;
		/** @brief Liczba bil czerwonych pozostaj¹cych na stole. */
		int m_RedLeftCount;
		/** @brief Indeks gracza rozgrywaj¹cego w tablicy. Jeœli -1, to gra treningowa. */
		int m_StrikerIndex;
		/** @brief Tablica graczy. */
		CPlayers m_Players;
		/** @brief Indeks bia³ej bili w tablicy. Jeœli -1, to brakuje bia³ej bili. */
		int m_WhiteIndex;
		/** @brief Tablica z bilami. */
		CBalls m_Balls;
		/** @brief Tablica z trójk¹tami. */
		CTriangles m_Triangles;
		/** brief Sila uderzenia. */
		float m_Force;

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CBillard(void);

	public:
		/**
		 *  Funkcja odczytuje grê z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    STATE 1
		 *    STRIKER_INDEX 0
		 *    ...
		 *  END
		 *  </pre>
		 *
		 *	@brief Funkcja odczytuj¹ca ca³¹ grê z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje grê do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *	@brief Funkcja zapisuj¹ca ca³¹ grê do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype³nienie tabulacja przed ka¿d¹ lini¹.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/**
		 *  Funkcja inicjalizuje now¹ grê. Parametr Players zawiera tablicê z graczami.
		 *  Jeœli tablica jest pusta, to gra jest treningowa. Funkcja ustawia szereg
		 *  zmiennych i bil. Nastêpnie przechodzi do widoku i ³aduje czwart¹ predefiniowan¹
		 *  pozycjê kamery.
		 *
		 *  @brief Funkcja rozpoczyna now¹ grê.
		 *  @param[in] Players Tablica z graczami.
		 */
		void NewGame(const CPlayers &Players);

		/** @brief Funkcja ³aduj¹ca ca³¹ grê z pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku, z którego nale¿y wczytaæ grê.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int LoadGame(const CString FileName);

		/** @brief Funkcja zapisuj¹ca ca³¹ grê do pliku tekstowego.
		 *  @param[in] FileName Nazwa pliku, do którego nale¿y zapisaæ grê.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int SaveGame(const CString FileName);

	public:
		/** @brief Funkcja wykonuj¹ca symulacjê (ruch) bil, obs³ugê klawiatury, 
		 *         myszki i kamery.
		 *  @param[in] Time Czas który up³yn¹³ od poprzedniego wywo³ania funkcji.
		 */
		void Run(float Time);

		/** @brief Funkcja przetwarzaj¹ca klawiaturê, myszkê.
		 *  @param[in] Time Czas który up³yn¹³ od poprzedniego wywo³ania funkcji.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void ProcessControls(float Time);

		/** @brief Funkcja przechodzi do kolejnego stanu gry.
		 */
		void NextState(void);

		/** @brief Funkcja przechodzi do poprzedniego stanu gry.
		 */
		void PreviousState(void);

		/** @brief Funkcja ustawiaj¹ca stan gry.
		 *  @param[in] State Nowy stan gry.
		 */
		void SetState(CBillardState State);

	public:
		/** @brief Funkcja wywo³ywana przy rozpoczêciu symulacji.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void OnStart(void);

		/** @brief Funkcja wywo³ywana przy zakoñczeniu symulacji.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void OnStop(void);

		/** @brief Funkcja wywo³ywana przy wpadniêciu bili do kieszeni.
		 *  @param[in] Ball Referencja do bili, która w³aœnie wpad³a.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void OnKnockIn(CBall &Ball);

		/** @brief Funkcja wywo³ywana przy zderzeniu dwóch bil.
		 *  @param[in] Ball1 Referencja do pierwszej bili zderzaj¹cej.
		 *  @param[in] Ball2 Referencja do drugiej bili zderzaj¹cej.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void OnCollision(CBall &Ball1, CBall &Ball2);

	public:
		/** @brief Funkcja przyk³adaj¹ca si³y do bil.
		 *  @param[in] Time Czas przy³o¿enia si³y.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli jeszcze jakaœ bila siê toczy.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		int ApplyForces(float Time);

		/** @brief Funkcja przesuwaj¹ca bile.
		 *  @param[in] Time Czas przesuniêcia.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void Simulate(float Time);

		/** @brief Funkcja cofaj¹ca bile.
		 *  @param[in] Index Indeks bili, któr¹ chcemy cofn¹æ, jeœli -1, to cofa wszyskie bile.
		 *  @warning Funkcja jest wywo³ywana przez funkcjê Run.
		 */
		void Restore(int Index = -1);

		/** @brief Funkcja przywracaj¹ca oryginalne po³o¿enia bil.
		 *  @param[in] Index Indeks bili, któr¹ chcemy przywróciæ, jeœli -1, to przywraca wszyskie bile.
		 */
		void Reset(int Index = -1);

		/** @brief Funkcja zatrzymuj¹ca bile.
		 *  @param[in] Index Indeks bili, któr¹ chcemy zatrzymaæ, jeœli -1, to zatrzymuje wszyskie bile.
		 */
		void Stop(int Index = -1);

	public:
		/** @brief Funkcja szukaj¹ca trójk¹ta po którym bila siê toczy.
		 *  @param[in] Ball Referencja do bili, dla której chcemy znaleŸæ nowy trójk¹t.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli uda³o siê znaleŸæ trójk¹t.
		 *  @warning Funkcja modyfikuje odpowiednio bilê zapamiêtuj¹c wskaŸnik do nowo znalezionego trójk¹ta.
		 */
		int FindTriangle(CBall &Ball);

		/** @brief Funkcja szukaj¹ca kolizje miêdzy bilami.
		 *  @param[in] FullTime Czas symulacji.
		 *  @param[out] Time Czas do zderzenia dwóch bil.
		 *  @param[out] Ball1 Indeks pierwszej zderzaj¹cej siê bili.
		 *  @param[out] Ball2 Indeks drugiej zderzaj¹cej siê bili.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli uda³o siê znaleŸæ kolizjê.
		 */
		int FindBallsCollision(float FullTime, float &Time, int &Ball1, int &Ball2);

		/** @brief Funkcja szukaj¹ca kolizje miêdzy bil¹ a trójk¹tem (band¹, do³kiem, etc.).
		 *  @param[in] FullTime Czas symulacji.
		 *  @param[out] Time Czas do zderzenia bili z band¹.
		 *  @param[out] Ball Indeks bili kolizyjnej.
		 *  @param[out] Triangle Indeks trójk¹ta kolizyjnego.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli uda³o siê znaleŸæ kolizjê.
		 */
		int FindTriangleCollision(float FullTime, float &Time, int &Ball, int &Triangle);

};
