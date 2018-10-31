
/** @file Ball.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy reprezentuj¹cej bilê CBall.
 *
 *  Plik zawiera definicjê klasy CBall reprezentuj¹c¹ pojedyncz¹ bilê
 *  oraz dodatkowe typy potrzebne do opisania bili.
 *
 */ 

#pragma once

#include "Vector.h"
#include "Triangle.h"

/** @brief Typ wyliczeniowy definiuj¹cy typ bili: 
 *         bia³a, czerwona i kolorowa.
 */
typedef enum {
	/** @brief Bia³a bila.
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
 *  Klasa opisuje pojedyncz¹ bilê. Zawiera niezbêdne pola do opisu wygl¹du, 
 *  fizyki i stanu w grze bili. Klasa udostêpnia szereg metod niezbêdnych
 *  do przeprowadzenia symulacji fizyki, etc.
 *
 *  @brief Klasa reprezentuj¹ca bilê.
 */
class CBall {

	public:
		/** @brief Liczba punktów przypisana do bili. */
		int m_Score;
		/** @brief Typ bili. */
		CBallType m_Type;
		/** @brief Flaga identyfikuj¹ca czy bila bierze udzia³ w symulacji. */
		int m_Simulate;
		/** @brief Flaga identyfikuj¹ca czy bila bierze udzia³ w renderowaniu. */
		int m_Render;
		/** @brief Flaga identyfikuj¹ca czy bila zostala wbita. */
		int m_KnockedIn;
		/** @brief Flaga identyfikujaca czy bila wysokczyla poza stol. */
		int m_OutOfBoard;
		/** @brief Promieñ bili. */
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
		/** @brief Prêdkoœæ bili. */
		CVector m_Velocity;
		/** @brief Wektor kierunkowy (normalny) predkoœci bili. */
		CVector m_VelocityNormal;
		/** @brief Wektor obrotu bili. */
		CVector m_Rotate;
		/** @brief Si³a przyk³adana do bili. */
		CVector m_Force;
		/** @brief Trójk¹t, po którym porusza siê bila. */
		const CTriangle *m_Triangle;

	public:
		/**
		 *  Domyœlny konstruktor inicjalizuj¹cy domyœlne ustawienia bili.
		 *
		 *  @brief Konstruktor domyœlny. 
		 */
		CBall(void);

		/** @brief Konstruktor kopiuj¹cy.
		 *  @param[in] Ball Bila Ÿród³owa
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
		 *  @brief Funkcja odczytuj¹ca bilê z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Read(FILE *File);

		/**
		 *  Funkcja zapisuje bilê do pliku tekstowego zgodnie z 
		 *  formatem odczytu funkcji Read.
		 *
		 *  @brief Funkcja zapisuj¹ca bilê do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype³nienie tabulacj¹ przed ka¿d¹ lini¹.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja dodaje si³ê do bili.
		 *  @param[in] Force Wektor si³y, któr¹ chcemy przy³o¿yæ do bili.
		 */
		void AddForce(const CVector &Force);

		/** @brief Funkcja dodaje si³ê tarcia do bili.
		 */
		void AddFrictionForce(void);

		/** @brief Funkcja dodaje si³ê grawitacji do bili.
		 */
		void AddGravityForce(void);

		/**
		 *  Funkcja aplikuje si³ê do bili zgodnie z prawami fizyki.
		 *  Prêdkoœæ jest wyznaczana zgodnie ze wzorem:
		 *  <pre>V(i+1) = V(i) + (F/M) * T</pre> gdzie 
		 *  V(i+1) - nowa prêdkoœæ, V(i) - poprzednia prêdkoœæ,
		 *  F - si³a przy³o¿ona do bili, M - masa bili, T - czas.
		 *
		 *  @brief Funkcja przyk³ada si³ê do bili w czasie Time.
		 *  @param[in] Time Czas symulacji (przy³o¿enia si³y).
		 */
		void ApplyForce(float Time);

		/**
		 *  Funkcja aplikuje prêdkoœæ do bili, czyli przesuwa bilê
		 *  z zadan¹ prêdkoœci¹ w podanym czasie zgodnie z prawami
		 *  fizyki. Nowa prêdkoœæ jest wyznaczana w oparciu o wzór:
		 *  <pre>P(i+1) = P(i) + V*T</pre> gdzie P(i+1) - nowa pozycja,
		 *  P(i) - poprzednia pozycja, V - prêdkoœæ, T - czas.
		 *  Funkcja dodatkowo zlicza przebyt¹ drogê przez bilê
		 *  dodaj¹c d³ugoœæ przesuniêcie do zmiennej m_Track.
		 *  Zmienna ta, jest potrzebna przy wyznaczaniu k¹ta
		 *  obrotu bili.
		 *
		 *  @brief Funkcja symuluj¹ca przesuniêcie siê bili.
		 *  @param[in] Time Czas symulacji (ruchu bili).
		 */
		void Simulate(float Time);

		/**
		 *  Funkcja przywraca poprzedni¹ pozycjê bili z przed ostatniego wywo³ania
		 *  metody Simulate. Funkcja jest potrzebna podczas przeprowadzania symulacji.
		 *
		 *  @brief Funkcja przywraca pozycje bili do stanu z przed ostatniego wywo³ania 
		 *         funkcji Simulate.
		 */
		void Restore(void);

		/**
		 *  Funkcja przywraca oryginalne ustawienia bili - pozycjê, flagi, itd.
		 *  Jest niezbêdna do poprawnej inicjalizacji gry.
		 *
		 *  @brief Funkcja przywraca pozycje bili do stanu oryginlnego.
		 */
		void Reset(void);

		/**
		 *  Funkcja wyznacza nowy wektor obrotu bili. Wektor obrotu bili
		 *  jest wynikiem wektorowego mno¿enia prêdkoœci i normalnej powierzchni
		 *  poziomej. Wektor obrotu jest nastêpnie u¿ywany przy renderowaniu bili.
		 *
		 *  @brief Funkcja wyznacza nowy wektor obrotu bili.
		 */
		void Rotate(void);

		/**
		 *  Funkcja zatrzymuje bilê. Zeruje wektor prêdkoœci i si³y.
		 *
		 *  @brief Funkcja zatrzymuj¹ca bilê.
		 */
		void Stop(void);

	public:
		/** @brief Funkcja sprawdzaj¹ca czy bila siê toczy.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli bila jeszcze siê toczy.
		 */
		int IsMoving(void) const { return !m_Velocity.IsZero(0.05f); };

		/** @brief Funkcja zwracaj¹ca liczbê punktów.
		 *  @retval Funkcja zwraca liczbê punktów przypisan¹ do bili.
		 */
		int GetScore(void) const { return m_Score; };

		/** @brief Funkcja zwracaj¹ca typ bili.
		 *  @retval Funkcja zwraca typ bili (btWhite, btRed, btColor).
		 */
		CBallType GetType(void) const { return m_Type; };

		/** @brief Funkcja zwracaj¹ca czy symulacja bili jest w³¹czona.
		 *  @retval Funkcja zwraca liczbê ró¿na od zera jeœli symulacja bili jest w³¹czona.
		 */
		int GetSimulate(void) const { return m_Simulate; };

		/** @brief Funkcja zwracaj¹ca czy bila ma byæ renderowana.
		 *  @retval Funkcja zwraca liczbê ró¿na od zera jeœli renderowanie bili jest w³¹czone.
		 */
		int GetRender(void) const { return m_Render; };

		/** @brief Funkcja zwracaj¹ca czy bila zosta³a wbita.
		 *  @retval Funkcja zwraca liczbê ró¿na od zera jeœli bila zosta³a wbita do do³ka.
		 */
		int GetKnockedIn(void) const { return m_KnockedIn; };

		/** @brief Funkcja zwracaj¹ca promieñ bili.
		 *  @retval Funkcja zwraca promieñ bili.
		 */
		float GetRay(void) const { return m_Ray; };

		/** @brief Funkcja zwracaj¹ca masê bili.
		 *  @retval Funkcja zwraca masê bili.
		 */
		float GetMass(void) const { return m_Mass; };

		/** @brief Funkcja zwracaj¹ca drogê przebyt¹ przez bilê.
		 *  @retval Funkcja zwraca drogê przebyt¹ przez bilê.
		 */
		float GetTrack(void) const { return m_Track; };

		/** @brief Funkcja zwracaj¹ca kolor bili.
		 *  @retval Funkcja zwraca tablicê czteroelementow¹ z kolorem bili.
		 */
		const float* GetColor(void) const { return m_Color; };

		/** @brief Funkcja zwracaj¹ca pozycjê bili.
		 *  @retval Funkcja zwraca wektor pozycji bili.
		 */
		const CVector& GetPosition(void) const { return m_Position; };

		/** @brief Funkcja zwracaj¹ca wektor obrotu bili.
		 *  @retval Funkcja zwraca wektor obrotu bili.
		 */
		const CVector& GetRotate(void) const { return m_Rotate; };

		/**
		 *  Funkcja sprawdza czy pozycja bili znajduje siê w podanym trójk¹cie.
		 *  Jeœli podano wskaŸnik pusty, to funkcja testuje trójk¹t wskazywany
		 *  przez wskaŸnik m_Triangle. Jeœli punkt nale¿y do trójk¹ta, zapamiêtuje
		 *  nowy wskaŸnik w zmiennej m_Triangle.
		 * 
		 *  @brief Funkcja sprawdzaj¹ca czy bila toczy siê po trójk¹cie.
		 *  @param[in] Triangle Badany trójk¹t. Jeœli podany zostanie pusty wskaŸnik
		 *                      funkcja sprawdzi trójk¹t zapamiêtany w bili.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli bila toczy siê po trójk¹cie.
		 *  @warning Jeœli bila toczy siê po podanym trójk¹cie, to wskaŸnik 
		 *           do tego trójk¹ta zostanie zapamiêtany w bili.
		 */
		int IsInTriangle(const CTriangle *Triangle = NULL);

	public:
		/**
		 *  Funkcja szuka kolizji z drug¹ bil¹. Najpierw wyznaczana jest relatywna
		 *  prêdkoœæ miêdzy bilami. Nastêpnie tworzona jest pó³prosta o pocz¹tku
		 *  w punkcie (poprzednim) bili i kierunku równoleg³ym z wektorem wzglêdnej
		 *  prêdkoœci. Badamy odleg³oœæ podanej bili (Ball) od tej pó³prostej i je¿eli
		 *  odleg³oœæ jest mniejsza od sumy promieni bil, to nast¹pi zderzenie.
		 *  Wykrycie punktu kolizji jest reazliowane przez podzielenie ca³ego czasu
		 *  symulacji na 150 czêœci. Nastêpnie w ka¿dej czêœci sprawdzana jest odleg³oœæ
		 *  miêdzy œrodkami bil i jeœli jest mniejsza od sumy promieni bil, to nast¹pi³a
		 *  kolizja. Zapamiêtywany jest czas kolizji w parametrze Time i zwracana jest
		 *  wartoœæ ró¿na od zera.
		 *
		 *  @brief Funkcja szukaj¹ca kolizji z drug¹ bil¹ w podanym czasie.
		 *  @param[in] FullTime Czas trwania ostatniej klatki.
		 *  @param[out] Time Czas kolizji.
		 *  @param[in] Ball Sprawdzana bila.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli bile zderz¹ siê w czasie Time.
		 */
		int FindCollision(float FullTime, float &Time, const CBall &Ball) const;

		/**
		 *  Funkcja szuka kolizji z podanym trójk¹tem. Najpierw sprawdzana jest prêdkoœæ
		 *  bili, czy w ogóle siê ona toczy. Nastêpnie wyznaczany jest iloczyn skalarny
		 *  wektora normalnego prêdkoœci i normalnej trójk¹ta. Jeœli wynik jest równy
		 *  zero, to wektory s¹ prostopad³e i nigdy nie dojdzie do zderzenia.
		 *  Nastêpnie sprawdzane jest po³o¿enie bili wzglêdem trójk¹ta. Jeœli bila znajduje
		 *  siê za trójk¹tem, to wtedy równie¿ nie dojdzie do zderzenia. Nastêpnie wyznaczany
		 *  jest czas do punktu kolizji. Je¿eli czas jest wiêkszy od czasu trwania klatki,
		 *  lub jest wiêkszy od czasu Time, to nie bierzemy pod uwagê tego zderzenia.
		 *  Nastepnie przesuwamy œrodek bili do tego czasu i sprawdzamy czy punkt le¿y 
		 *  wewn¹trz trójk¹ta. Je¿eli le¿y, tzn. ¿e dojdzie do zderzenia. Zapamiêtywany
		 *  jest czas zderzenia w zmiennej Time.
		 *
		 *  @brief Funkcja szukaj¹ca kolizji z trójk¹tem w podanym czasie.
		 *  @param[in] FullTime Czas trwania ostatniej kolizji.
		 *  @param[out] Time Czas kolizji.
		 *  @param[in] Triangle Sprawdzany trójk¹t.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli bila zderzy siê z trójk¹tem w czasie Time.
		 */
		int FindCollision(float FullTime, float &Time, const CTriangle &Triangle) const;

	public:
		/**
		 *  Funkcja wyznacza nowe wektory prêdkoœci bil. Najpierw wyznaczany jest oœ ³¹cz¹ca œrodki
		 *  bil, nastêpnie wyznaczane s¹ nowe wektory cz¹stkowe prêdkoœci dla obydwu bil. Nastepnie 
		 *  zgodnie z zasad¹ zachowania pêdu przekazywany jest pêd z jednej bili do drugiej na podstawie
		 *  mas bil. Nowe wektory prêdkoœci s¹ zapamiêtywane w bilach. Na koniec wywo³ywana jest metoda
		 *  Rotate dla ka¿dej z bil, aby wyznaczyæ nowy wektor obrotu dla ka¿dej bili.
		 *
		 *  @brief Funkcja dokonuje odbicia bil.
		 *  @param[in,out] Ball Bila od której odbija siê bila.
		 */
		void Reflect(CBall &Ball);

		/**
		 *  Funkcja wyznacza nowy wektor prêdkoœci bili po odbiciu od trójk¹ta. Najpierw sprawdzany jest
		 *  trójk¹t. Jeœli jest do³kiem, bila jest zatrzymywana, ustawiana jest flaga wbicia bili, 
		 *  wy³¹czane s¹ flagi symulacji i renderowania. Nastêpnie sprawdzamy czy symulacja bili jest 
		 *  w³¹czona i trójk¹t jest trójk¹tem odbijaj¹cym. Zapamiêtywana jest d³ugoœæ wektora prêdkoœci
		 *  po czym wyznaczany jest nowy wektor prêdkoœci na podstawie wektora normalnego trójk¹ta.
		 *  Nowy wektor jest przemna¿any przez zapamiêtan¹ d³ugoœæ wektora prêdkoœci pomniejszon¹ o 5%
		 *  spowodowane odbiciem - poch³oniêciem czêœci energii bili przez bandê.
		 *
		 *  @brief Funkcja dokonuje odbicia bili od trójk¹ta.
		 *  @param[in] Triangle Trójk¹t, od którego bila siê odbija.
		 */
		void Reflect(const CTriangle &Triangle);

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Ball Bila Ÿród³owa.
		 *  @retval Funkcja zwraca referencjê do tej bili.
		 */
		CBall& operator=(const CBall &Ball);

};
