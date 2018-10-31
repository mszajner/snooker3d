
/** @file Vector.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CVector.
 *
 *  Plik zawiera interfejs klasy CVector oraz dodatkowe makrodefinicje
 *  u³atwiaj¹ce obliczenia matematyczne.
 *
 */ 

#pragma once

/** @brief Liczba PI u¿ywana w obliczeniach.
 */
#define PI 3.14159265358979323846f

/** @brief Dok³adnoœæ obliczeñ.
 */
#define EPSILON 0.005f

/** @brief Makro zwraca kwadrat podanej liczby.
 */
#define	SQR(x) ((x) * (x))

/** @brief Makro konwertuje k¹t podany w stopniach na k¹t w radianach.
 */
#define	DEGTORAD(x)	(((x) * PI) / 180.0f)

/** @brief Makro konwertuje k¹t podany w radianach na k¹t w stopniach.
 */
#define	RADTODEG(x)	(((x) * 180.0f) / PI)

/** @brief Makro zwraca zero, je¿eli liczba jest bliska zero lub tê liczbê w przeciwnym wypadku.
 */
#define ZERO_CLAMP(x) ((EPSILON > fabs(x)) ? 0.0f : (x))

/** @brief Makro zwraca zero, je¿eli liczba jest bliska zero lub tê liczbê w przeciwnym wypadku.
 */
#define ZERO_CLAMP_EPS(x,eps) ((eps > fabs(x)) ? 0.0f : (x))

/** @brief Makro zwraca czy liczba x jest równa liczbie v z dok³adnoœci¹ EPSILON.
 */
#define FLOAT_EQ(x,v) (((v) - EPSILON) < (x) && (x) < ((v) + EPSILON))

/** @brief Makro zwraca czy liczba x jest równa liczbie v z dok³adnoœci¹ eps.
 */
#define FLOAT_EQ_EPS(x,v,eps) (((v) - eps) < (x) && (x) < ((v) + eps))

/** @brief Makro sprawdza czy x jest z zakresu (min, max) i gdy przekracza to zwraca granice.
 */
#define FLOAT_MID(x,min,max) (((x) >= (min)) ? (((x) <= (max)) ? (x) : (max)) : (min))

/** @brief Makro sprawdza czy x jest wiêksza od min, je¿eli nie, to zwraca min.
 */
#define FLOAT_MIN(x,min)     (((x) >= (min)) ? (x) : (min))

/** @brief Makro sprawdza czy x jest mniejsze od max, je¿eli nie, to zwraca max.
 */
#define FLOAT_MAX(x,max)     (((x) <= (max)) ? (x) : (max))

#include <stdio.h>

/** @brief Klasa reprezentuj¹ca wektor w przestrzeni.
 */
class CVector {

	public:
		/** @brief Wspó³rzêdna X */
		float m_X;
		/** @brief Wspó³rzêdna Y */
		float m_Y;
		/** @brief Wspó³rzêdna Z */
		float m_Z;

	public:
		/** @brief Konstruktor domyœlny */
		CVector(void);

		/** @brief Kontruktor ustawiaj¹cy wspó³rzêdne 
		 *  @param[in] X Wspó³rzêdna X
		 *  @param[in] Y Wspó³rzêdna Y
		 *  @param[in] Z Wspó³rzêdna Z
		 */
		CVector(float X, float Y, float Z);

		/** @brief Konstruktor kopiuj¹cy
		 *  @param[in] Vector Wektor Ÿród³owy
		 */
		CVector(const CVector &Vector);
		
	public:
		/** @brief Funkcja odczytuj¹ca wektor z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj¹ca wektor do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype³nienie tabulacja przed ka¿d¹ lini¹.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja zeruj¹ca wspó³rzêdne wektora.
		 */
		void Zero(void);

		/** @brief Funkcja zeruj¹ca wspó³rzêdne wektora, jeœli s¹ bliskie 0 (z dok³adnoœci¹ EPSILON).
		 */
		void ZeroClamp(float Epsilon = EPSILON);

		/** @brief Funkcja odwraca wspó³rzêdne wektora, tworz¹c wektor przeciwny.
		 */
		void Negative(void);

		/** @brief Funkcja normalizuj¹ca wektor.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli normalizacja powiod³a siê.
		 */
		int Normalize(void);

		/** @brief Funkcja ustawiaj¹ca wspó³rzêdne wektora.
		 *  @param[in] X Wspó³rzêdna X
		 *  @param[in] Y Wspó³rzêdna Y
		 *  @param[in] Z Wspó³rzêdna Z
		 */
		void Set(float X, float Y, float Z);
		
	public:
		/** @brief Funkcja sprawdzaj¹ca czy wektor jest zerowy.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli wektor ma d³ugoœæ zerow¹.
		 */
		int IsZero(float Epsilon = EPSILON) const;

		/** @brief Funkcja sprawdzaj¹ca czy wektor jest normalny (jednostkowy).
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera, jeœli wektor jest jednostkowy.
		 */
		int IsNormal(void) const;
		
	public:
		/** @brief Funkcja zwraca d³ugoœæ wektora.
		 */
		float Length(void) const;

		/** @brief Funkcja zwraca wartoœæ iloczynu wektorowego.
		 *  @param[in] Vector Wektor, który jest drugim czynnikiem iloczynu.
		 */
		float Dot(const CVector &Vector) const;

		/** @brief Funkcja zwraca odleg³oœæ miêdzy wektorami.
		 *  @param[in] Vector Drugi wektor.
		 */
		float Distance(const CVector &Vector) const;
	
	public:
		/** @brief Operator przypisania.
		 *  @param[in] Vector Wektor Ÿród³owy.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator=(const CVector &Vector);
		
	public:
		/** @brief Operator sumowania wektorów.
		 *  @param[in] Vector Drugi sk³adnik sumy.
		 *  @retval Funkcja zwraca wektor bêd¹cy sum¹ wektorów.
		 */
		CVector operator+(const CVector &Vector) const;

		/** @brief Operator odejmowania wektorów.
		 *  @param[in] Vector Drugi sk³adnik ró¿nicy.
		 *  @retval Funkcja zwraca wektor bêd¹cy ró¿nic¹ wektorów.
		 */
		CVector operator-(const CVector &Vector) const;

		/** @brief Operator iloczynu wektorowego wektorów.
		 *  @param[in] Vector Drugi czynnik iloczynu.
		 *  @retval Funkcja zwraca wektor bêd¹cy iloczynem wektorowym wektorów.
		 */
		CVector operator*(const CVector &Vector) const;

	public:
		/** @brief Operator sumowania wektorów z przypisaniem.
		 *  @param[in] Vector Drugi sk³adnik sumy.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator+=(const CVector &Vector);

		/** @brief Operator odejmowania wektorów z przypisaniem.
		 *  @param[in] Vector Drugi sk³adnik ró¿nicy.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator-=(const CVector &Vector);

		/** @brief Operator iloczynu wektorowego wektorów z przypisaniem.
		 *  @param[in] Vector Drugi czynnik iloczynu.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator*=(const CVector &Vector);

	public:
		/** @brief Operator iloczynu wektora przez liczbê.
		 *  @param[in] Value Liczba rzeczywista przez któr¹ wspó³rzêdne wektora zostan¹ przemno¿one.
		 *  @retval Funkcja zwraca wektor bêd¹cy wynikiem tej operacji.
		 */
		CVector operator*(float Value) const;

		/** @brief Operator dzielenia wektora przez liczbê.
		 *  @param[in] Value Liczba rzeczywista przez któr¹ wspó³rzêdne wektora zostan¹ podzielone.
		 *  @retval Funkcja zwraca wektor bêd¹cy wynikiem tej operacji.
		 */
		CVector operator/(float Value) const;
		
	public:
		/** @brief Operator iloczynu wektora przez liczbê z przypisaniem.
		 *  @param[in] Value Liczba rzeczywista przez któr¹ wspó³rzêdne wektora zostan¹ przemno¿one.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator*=(float Value);

		/** @brief Operator dzielenia wektora przez liczbê z przypisaniem.
		 *  @param[in] Value Liczba rzeczywista przez któr¹ wspó³rzêdne wektora zostan¹ podzielone.
		 *  @retval Funkcja zwraca referencjê do tego wektora.
		 */
		CVector& operator/=(float Value);

	public:
		/** @brief Operator odwraca wspó³rzêdne wektora, tworz¹c wektor przeciwny.
		 *  @retval Funkcja zwraca wektor przeciwny do tego wektora.
		 */
		CVector operator-(void) const;

	public:
		/** @brief Operator porównania dwóch wektorów.
		 *  @retval Funkcja zwraca liczbê ró¿n¹ od zera, jeœli wspó³rzêdne wektora
		 *          s¹ równe sobie z dok³adnoœci¹ EPSILON.
		 */
		int operator==(const CVector &Vector) const;

};
