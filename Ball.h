
/** @file Ball.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy reprezentuj�cej bil� CBall.
 *
 *  Plik zawiera definicj� klasy CBall reprezentuj�c� pojedyncz� bil�
 *  oraz dodatkowe typy potrzebne do opisania bili.
 *
 */ 

#pragma once

#include "Vector.h"
#include "Triangle.h"

/** @brief Typ wyliczeniowy definiuj�cy typ bili: 
 *         bia�a, czerwona i kolorowa.
 */
typedef enum {
	/** @brief Bia�a bila.
	 */
	btWhite = 0,

	/** @brief Czerwona bila.
	 */
	btRed = 1,

	/** @brief Kolorowa bila.
	 */
	btColor = 2,
} CBallType;

/** 
 *  Klasa opisuje pojedyncz� bil�. Zawiera niezb�dne pola do opisu wygl�du, 
 *  fizyki i stanu w grze bili. Klasa udost�pnia szereg metod niezb�dnych
 *  do przeprowadzenia symulacji fizyki, etc.
 *
 *  @brief Klasa reprezentuj�ca bil�.
 */
class CBall {

	public:
		/** @brief Liczba punkt�w przypisana do bili. */
		int m_Score;
		/** @brief Typ bili. */
		CBallType m_Type;
		/** @brief Flaga identyfikuj�ca czy bila bierze udzia� w symulacji. */
		int m_Simulate;
		/** @brief Flaga identyfikuj�ca czy bila bierze udzia� w renderowaniu. */
		int m_Render;
		/** @brief Flaga identyfikuj�ca czy bila zostala wbita. */
		int m_KnockedIn;
		/** @brief Flaga identyfikujaca czy bila wysokczyla poza stol. */
		int m_OutOfBoard;
		/** @brief Promie� bili. */
		float m_Ray;
		/** @brief Masa bili. */
		float m_Mass;
		/** @brief Aktualnie przebyta droga przez bile. */
		float m_Track;
		/** @brief Poprzednia przebyta droga przez bile. */
		float m_TrackPrevious;
		/** @brief Kolor bili. */
		float m_Color[4];
		/** @brief Aktualna pozycja bili. */
		CVector m_Position;
		/** @brief Poprzednia pozycja bili. */
		CVector m_PositionPrevious;
		/** @brief Oryginalna pozycja bili. */
		CVector m_PositionOriginal;
		/** @brief Pr�dko�� bili. */
		CVector m_Velocity;
		/** @brief Wektor kierunkowy (normalny) predko�ci bili. */
		CVector m_VelocityNormal;
		/** @brief Wektor obrotu bili. */
		CVector m_Rotate;
		/** @brief Si�a przyk�adana do bili. */
		CVector m_Force;
		/** @brief Tr�jk�t, po kt�rym porusza si� bila. */
		const CTriangle *m_Triangle;

	public:
		/**
		 *  Domy�lny konstruktor inicjalizuj�cy domy�lne ustawienia bili.
		 *
		 *  @brief Konstruktor domy�lny. 
		 */
		CBall(void);

		/** @brief Konstruktor kopiuj�cy.
		 *  @param[in] Ball Bila �r�d�owa
		 */
		CBall(const CBall &Ball);

	public:
		/**
		 *  Funkcja odczytuje bile z pliku tekstowego w formacie:
		 *  <pre>
		 *  BEGIN
		 *    SCORE 1
		 *    KNOCKED_IN 0
		 *    ...
		 *  END
		 *  </pre>
		 *
		 *  @brief Funkcja odczytuj�ca bil� z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje bil� do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisuj�ca bil� do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacj� przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja dodaje si�� do bili.
		 *  @param[in] Force Wektor si�y, kt�r� chcemy przy�o�y� do bili.
		 */
		void AddForce(const CVector &Force);

		/** @brief Funkcja dodaje si�� tarcia do bili.
		 */
		void AddFrictionForce(void);

		/** @brief Funkcja dodaje si�� grawitacji do bili.
		 */
		void AddGravityForce(void);

		/**
		 *  Funkcja aplikuje si�� do bili zgodnie z prawami fizyki.
		 *  Pr�dko�� jest wyznaczana zgodnie ze wzorem:
		 *  <pre>V(i+1) = V(i) + (F/M) * T</pre> gdzie 
		 *  V(i+1) - nowa pr�dko��, V(i) - poprzednia pr�dko��,
		 *  F - si�a przy�o�ona do bili, M - masa bili, T - czas.
		 *
		 *  @brief Funkcja przyk�ada si�� do bili w czasie Time.
		 *  @param[in] Time Czas symulacji (przy�o�enia si�y).
		 */
		void ApplyForce(float Time);

		/**
		 *  Funkcja aplikuje pr�dko�� do bili, czyli przesuwa bil�
		 *  z zadan� pr�dko�ci� w podanym czasie zgodnie z prawami
		 *  fizyki. Nowa pr�dko�� jest wyznaczana w oparciu o wz�r:
		 *  <pre>P(i+1) = P(i) + V*T</pre> gdzie P(i+1) - nowa pozycja,
		 *  P(i) - poprzednia pozycja, V - pr�dko��, T - czas.
		 *  Funkcja dodatkowo zlicza przebyt� drog� przez bil�
		 *  dodaj�c d�ugo�� przesuni�cie do zmiennej m_Track.
		 *  Zmienna ta, jest potrzebna przy wyznaczaniu k�ta
		 *  obrotu bili.
		 *
		 *  @brief Funkcja symuluj�ca przesuni�cie si� bili.
		 *  @param[in] Time Czas symulacji (ruchu bili).
		 */
		void Simulate(float Time);

		/**
		 *  Funkcja przywraca poprzedni� pozycj� bili z przed ostatniego wywo�ania
		 *  metody Simulate. Funkcja jest potrzebna podczas przeprowadzania symulacji.
		 *
		 *  @brief Funkcja przywraca pozycje bili do stanu z przed ostatniego wywo�ania 
		 *         funkcji Simulate.
		 */
		void Restore(void);

		/**
		 *  Funkcja przywraca oryginalne ustawienia bili - pozycj�, flagi, itd.
		 *  Jest niezb�dna do poprawnej inicjalizacji gry.
		 *
		 *  @brief Funkcja przywraca pozycje bili do stanu oryginlnego.
		 */
		void Reset(void);

		/**
		 *  Funkcja wyznacza nowy wektor obrotu bili. Wektor obrotu bili
		 *  jest wynikiem wektorowego mno�enia pr�dko�ci i normalnej powierzchni
		 *  poziomej. Wektor obrotu jest nast�pnie u�ywany przy renderowaniu bili.
		 *
		 *  @brief Funkcja wyznacza nowy wektor obrotu bili.
		 */
		void Rotate(void);

		/**
		 *  Funkcja zatrzymuje bil�. Zeruje wektor pr�dko�ci i si�y.
		 *
		 *  @brief Funkcja zatrzymuj�ca bil�.
		 */
		void Stop(void);

	public:
		/** @brief Funkcja sprawdzaj�ca czy bila si� toczy.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li bila jeszcze si� toczy.
		 */
		int IsMoving(void) const { return !m_Velocity.IsZero(0.05f); };

		/** @brief Funkcja zwracaj�ca liczb� punkt�w.
		 *  @retval Funkcja zwraca liczb� punkt�w przypisan� do bili.
		 */
		int GetScore(void) const { return m_Score; };

		/** @brief Funkcja zwracaj�ca typ bili.
		 *  @retval Funkcja zwraca typ bili (btWhite, btRed, btColor).
		 */
		CBallType GetType(void) const { return m_Type; };

		/** @brief Funkcja zwracaj�ca czy symulacja bili jest w��czona.
		 *  @retval Funkcja zwraca liczb� r�na od zera je�li symulacja bili jest w��czona.
		 */
		int GetSimulate(void) const { return m_Simulate; };

		/** @brief Funkcja zwracaj�ca czy bila ma by� renderowana.
		 *  @retval Funkcja zwraca liczb� r�na od zera je�li renderowanie bili jest w��czone.
		 */
		int GetRender(void) const { return m_Render; };

		/** @brief Funkcja zwracaj�ca czy bila zosta�a wbita.
		 *  @retval Funkcja zwraca liczb� r�na od zera je�li bila zosta�a wbita do do�ka.
		 */
		int GetKnockedIn(void) const { return m_KnockedIn; };

		/** @brief Funkcja zwracaj�ca promie� bili.
		 *  @retval Funkcja zwraca promie� bili.
		 */
		float GetRay(void) const { return m_Ray; };

		/** @brief Funkcja zwracaj�ca mas� bili.
		 *  @retval Funkcja zwraca mas� bili.
		 */
		float GetMass(void) const { return m_Mass; };

		/** @brief Funkcja zwracaj�ca drog� przebyt� przez bil�.
		 *  @retval Funkcja zwraca drog� przebyt� przez bil�.
		 */
		float GetTrack(void) const { return m_Track; };

		/** @brief Funkcja zwracaj�ca kolor bili.
		 *  @retval Funkcja zwraca tablic� czteroelementow� z kolorem bili.
		 */
		const float* GetColor(void) const { return m_Color; };

		/** @brief Funkcja zwracaj�ca pozycj� bili.
		 *  @retval Funkcja zwraca wektor pozycji bili.
		 */
		const CVector& GetPosition(void) const { return m_Position; };

		/** @brief Funkcja zwracaj�ca wektor obrotu bili.
		 *  @retval Funkcja zwraca wektor obrotu bili.
		 */
		const CVector& GetRotate(void) const { return m_Rotate; };

		/**
		 *  Funkcja sprawdza czy pozycja bili znajduje si� w podanym tr�jk�cie.
		 *  Je�li podano wska�nik pusty, to funkcja testuje tr�jk�t wskazywany
		 *  przez wska�nik m_Triangle. Je�li punkt nale�y do tr�jk�ta, zapami�tuje
		 *  nowy wska�nik w zmiennej m_Triangle.
		 * 
		 *  @brief Funkcja sprawdzaj�ca czy bila toczy si� po tr�jk�cie.
		 *  @param[in] Triangle Badany tr�jk�t. Je�li podany zostanie pusty wska�nik
		 *                      funkcja sprawdzi tr�jk�t zapami�tany w bili.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li bila toczy si� po tr�jk�cie.
		 *  @warning Je�li bila toczy si� po podanym tr�jk�cie, to wska�nik 
		 *           do tego tr�jk�ta zostanie zapami�tany w bili.
		 */
		int IsInTriangle(const CTriangle *Triangle = NULL);

	public:
		/**
		 *  Funkcja szuka kolizji z drug� bil�. Najpierw wyznaczana jest relatywna
		 *  pr�dko�� mi�dzy bilami. Nast�pnie tworzona jest p�prosta o pocz�tku
		 *  w punkcie (poprzednim) bili i kierunku r�wnoleg�ym z wektorem wzgl�dnej
		 *  pr�dko�ci. Badamy odleg�o�� podanej bili (Ball) od tej p�prostej i je�eli
		 *  odleg�o�� jest mniejsza od sumy promieni bil, to nast�pi zderzenie.
		 *  Wykrycie punktu kolizji jest reazliowane przez podzielenie ca�ego czasu
		 *  symulacji na 150 cz�ci. Nast�pnie w ka�dej cz�ci sprawdzana jest odleg�o��
		 *  mi�dzy �rodkami bil i je�li jest mniejsza od sumy promieni bil, to nast�pi�a
		 *  kolizja. Zapami�tywany jest czas kolizji w parametrze Time i zwracana jest
		 *  warto�� r�na od zera.
		 *
		 *  @brief Funkcja szukaj�ca kolizji z drug� bil� w podanym czasie.
		 *  @param[in] FullTime Czas trwania ostatniej klatki.
		 *  @param[out] Time Czas kolizji.
		 *  @param[in] Ball Sprawdzana bila.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li bile zderz� si� w czasie Time.
		 */
		int FindCollision(float FullTime, float &Time, const CBall &Ball) const;

		/**
		 *  Funkcja szuka kolizji z podanym tr�jk�tem. Najpierw sprawdzana jest pr�dko��
		 *  bili, czy w og�le si� ona toczy. Nast�pnie wyznaczany jest iloczyn skalarny
		 *  wektora normalnego pr�dko�ci i normalnej tr�jk�ta. Je�li wynik jest r�wny
		 *  zero, to wektory s� prostopad�e i nigdy nie dojdzie do zderzenia.
		 *  Nast�pnie sprawdzane jest po�o�enie bili wzgl�dem tr�jk�ta. Je�li bila znajduje
		 *  si� za tr�jk�tem, to wtedy r�wnie� nie dojdzie do zderzenia. Nast�pnie wyznaczany
		 *  jest czas do punktu kolizji. Je�eli czas jest wi�kszy od czasu trwania klatki,
		 *  lub jest wi�kszy od czasu Time, to nie bierzemy pod uwag� tego zderzenia.
		 *  Nastepnie przesuwamy �rodek bili do tego czasu i sprawdzamy czy punkt le�y 
		 *  wewn�trz tr�jk�ta. Je�eli le�y, tzn. �e dojdzie do zderzenia. Zapami�tywany
		 *  jest czas zderzenia w zmiennej Time.
		 *
		 *  @brief Funkcja szukaj�ca kolizji z tr�jk�tem w podanym czasie.
		 *  @param[in] FullTime Czas trwania ostatniej kolizji.
		 *  @param[out] Time Czas kolizji.
		 *  @param[in] Triangle Sprawdzany tr�jk�t.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li bila zderzy si� z tr�jk�tem w czasie Time.
		 */
		int FindCollision(float FullTime, float &Time, const CTriangle &Triangle) const;

	public:
		/**
		 *  Funkcja wyznacza nowe wektory pr�dko�ci bil. Najpierw wyznaczany jest o� ��cz�ca �rodki
		 *  bil, nast�pnie wyznaczane s� nowe wektory cz�stkowe pr�dko�ci dla obydwu bil. Nastepnie 
		 *  zgodnie z zasad� zachowania p�du przekazywany jest p�d z jednej bili do drugiej na podstawie
		 *  mas bil. Nowe wektory pr�dko�ci s� zapami�tywane w bilach. Na koniec wywo�ywana jest metoda
		 *  Rotate dla ka�dej z bil, aby wyznaczy� nowy wektor obrotu dla ka�dej bili.
		 *
		 *  @brief Funkcja dokonuje odbicia bil.
		 *  @param[in,out] Ball Bila od kt�rej odbija si� bila.
		 */
		void Reflect(CBall &Ball);

		/**
		 *  Funkcja wyznacza nowy wektor pr�dko�ci bili po odbiciu od tr�jk�ta. Najpierw sprawdzany jest
		 *  tr�jk�t. Je�li jest do�kiem, bila jest zatrzymywana, ustawiana jest flaga wbicia bili, 
		 *  wy��czane s� flagi symulacji i renderowania. Nast�pnie sprawdzamy czy symulacja bili jest 
		 *  w��czona i tr�jk�t jest tr�jk�tem odbijaj�cym. Zapami�tywana jest d�ugo�� wektora pr�dko�ci
		 *  po czym wyznaczany jest nowy wektor pr�dko�ci na podstawie wektora normalnego tr�jk�ta.
		 *  Nowy wektor jest przemna�any przez zapami�tan� d�ugo�� wektora pr�dko�ci pomniejszon� o 5%
		 *  spowodowane odbiciem - poch�oni�ciem cz�ci energii bili przez band�.
		 *
		 *  @brief Funkcja dokonuje odbicia bili od tr�jk�ta.
		 *  @param[in] Triangle Tr�jk�t, od kt�rego bila si� odbija.
		 */
		void Reflect(const CTriangle &Triangle);

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Ball Bila �r�d�owa.
		 *  @retval Funkcja zwraca referencj� do tej bili.
		 */
		CBall& operator=(const CBall &Ball);

};
