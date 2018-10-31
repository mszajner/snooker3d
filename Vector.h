
/** @file Vector.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CVector.
 *
 *  Plik zawiera interfejs klasy CVector oraz dodatkowe makrodefinicje
 *  u�atwiaj�ce obliczenia matematyczne.
 *
 */ 

#pragma once

/** @brief Liczba PI u�ywana w obliczeniach.
 */
#define PI 3.14159265358979323846f

/** @brief Dok�adno�� oblicze�.
 */
#define EPSILON 0.005f

/** @brief Makro zwraca kwadrat podanej liczby.
 */
#define	SQR(x) ((x) * (x))

/** @brief Makro konwertuje k�t podany w stopniach na k�t w radianach.
 */
#define	DEGTORAD(x)	(((x) * PI) / 180.0f)

/** @brief Makro konwertuje k�t podany w radianach na k�t w stopniach.
 */
#define	RADTODEG(x)	(((x) * 180.0f) / PI)

/** @brief Makro zwraca zero, je�eli liczba jest bliska zero lub t� liczb� w przeciwnym wypadku.
 */
#define ZERO_CLAMP(x) ((EPSILON > fabs(x)) ? 0.0f : (x))

/** @brief Makro zwraca zero, je�eli liczba jest bliska zero lub t� liczb� w przeciwnym wypadku.
 */
#define ZERO_CLAMP_EPS(x,eps) ((eps > fabs(x)) ? 0.0f : (x))

/** @brief Makro zwraca czy liczba x jest r�wna liczbie v z dok�adno�ci� EPSILON.
 */
#define FLOAT_EQ(x,v) (((v) - EPSILON) < (x) && (x) < ((v) + EPSILON))

/** @brief Makro zwraca czy liczba x jest r�wna liczbie v z dok�adno�ci� eps.
 */
#define FLOAT_EQ_EPS(x,v,eps) (((v) - eps) < (x) && (x) < ((v) + eps))

/** @brief Makro sprawdza czy x jest z zakresu (min, max) i gdy przekracza to zwraca granice.
 */
#define FLOAT_MID(x,min,max) (((x) >= (min)) ? (((x) <= (max)) ? (x) : (max)) : (min))

/** @brief Makro sprawdza czy x jest wi�ksza od min, je�eli nie, to zwraca min.
 */
#define FLOAT_MIN(x,min)     (((x) >= (min)) ? (x) : (min))

/** @brief Makro sprawdza czy x jest mniejsze od max, je�eli nie, to zwraca max.
 */
#define FLOAT_MAX(x,max)     (((x) <= (max)) ? (x) : (max))

#include <stdio.h>

/** @brief Klasa reprezentuj�ca wektor w przestrzeni.
 */
class CVector {

	public:
		/** @brief Wsp�rz�dna X */
		float m_X;
		/** @brief Wsp�rz�dna Y */
		float m_Y;
		/** @brief Wsp�rz�dna Z */
		float m_Z;

	public:
		/** @brief Konstruktor domy�lny */
		CVector(void);

		/** @brief Kontruktor ustawiaj�cy wsp�rz�dne 
		 *  @param[in] X Wsp�rz�dna X
		 *  @param[in] Y Wsp�rz�dna Y
		 *  @param[in] Z Wsp�rz�dna Z
		 */
		CVector(float X, float Y, float Z);

		/** @brief Konstruktor kopiuj�cy
		 *  @param[in] Vector Wektor �r�d�owy
		 */
		CVector(const CVector &Vector);
		
	public:
		/** @brief Funkcja odczytuj�ca wektor z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj�ca wektor do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja zeruj�ca wsp�rz�dne wektora.
		 */
		void Zero(void);

		/** @brief Funkcja zeruj�ca wsp�rz�dne wektora, je�li s� bliskie 0 (z dok�adno�ci� EPSILON).
		 */
		void ZeroClamp(float Epsilon = EPSILON);

		/** @brief Funkcja odwraca wsp�rz�dne wektora, tworz�c wektor przeciwny.
		 */
		void Negative(void);

		/** @brief Funkcja normalizuj�ca wektor.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li normalizacja powiod�a si�.
		 */
		int Normalize(void);

		/** @brief Funkcja ustawiaj�ca wsp�rz�dne wektora.
		 *  @param[in] X Wsp�rz�dna X
		 *  @param[in] Y Wsp�rz�dna Y
		 *  @param[in] Z Wsp�rz�dna Z
		 */
		void Set(float X, float Y, float Z);
		
	public:
		/** @brief Funkcja sprawdzaj�ca czy wektor jest zerowy.
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li wektor ma d�ugo�� zerow�.
		 */
		int IsZero(float Epsilon = EPSILON) const;

		/** @brief Funkcja sprawdzaj�ca czy wektor jest normalny (jednostkowy).
		 *  @retval Funkcja zwraca warto�� r�n� od zera, je�li wektor jest jednostkowy.
		 */
		int IsNormal(void) const;
		
	public:
		/** @brief Funkcja zwraca d�ugo�� wektora.
		 */
		float Length(void) const;

		/** @brief Funkcja zwraca warto�� iloczynu wektorowego.
		 *  @param[in] Vector Wektor, kt�ry jest drugim czynnikiem iloczynu.
		 */
		float Dot(const CVector &Vector) const;

		/** @brief Funkcja zwraca odleg�o�� mi�dzy wektorami.
		 *  @param[in] Vector Drugi wektor.
		 */
		float Distance(const CVector &Vector) const;
	
	public:
		/** @brief Operator przypisania.
		 *  @param[in] Vector Wektor �r�d�owy.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator=(const CVector &Vector);
		
	public:
		/** @brief Operator sumowania wektor�w.
		 *  @param[in] Vector Drugi sk�adnik sumy.
		 *  @retval Funkcja zwraca wektor b�d�cy sum� wektor�w.
		 */
		CVector operator+(const CVector &Vector) const;

		/** @brief Operator odejmowania wektor�w.
		 *  @param[in] Vector Drugi sk�adnik r�nicy.
		 *  @retval Funkcja zwraca wektor b�d�cy r�nic� wektor�w.
		 */
		CVector operator-(const CVector &Vector) const;

		/** @brief Operator iloczynu wektorowego wektor�w.
		 *  @param[in] Vector Drugi czynnik iloczynu.
		 *  @retval Funkcja zwraca wektor b�d�cy iloczynem wektorowym wektor�w.
		 */
		CVector operator*(const CVector &Vector) const;

	public:
		/** @brief Operator sumowania wektor�w z przypisaniem.
		 *  @param[in] Vector Drugi sk�adnik sumy.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator+=(const CVector &Vector);

		/** @brief Operator odejmowania wektor�w z przypisaniem.
		 *  @param[in] Vector Drugi sk�adnik r�nicy.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator-=(const CVector &Vector);

		/** @brief Operator iloczynu wektorowego wektor�w z przypisaniem.
		 *  @param[in] Vector Drugi czynnik iloczynu.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator*=(const CVector &Vector);

	public:
		/** @brief Operator iloczynu wektora przez liczb�.
		 *  @param[in] Value Liczba rzeczywista przez kt�r� wsp�rz�dne wektora zostan� przemno�one.
		 *  @retval Funkcja zwraca wektor b�d�cy wynikiem tej operacji.
		 */
		CVector operator*(float Value) const;

		/** @brief Operator dzielenia wektora przez liczb�.
		 *  @param[in] Value Liczba rzeczywista przez kt�r� wsp�rz�dne wektora zostan� podzielone.
		 *  @retval Funkcja zwraca wektor b�d�cy wynikiem tej operacji.
		 */
		CVector operator/(float Value) const;
		
	public:
		/** @brief Operator iloczynu wektora przez liczb� z przypisaniem.
		 *  @param[in] Value Liczba rzeczywista przez kt�r� wsp�rz�dne wektora zostan� przemno�one.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator*=(float Value);

		/** @brief Operator dzielenia wektora przez liczb� z przypisaniem.
		 *  @param[in] Value Liczba rzeczywista przez kt�r� wsp�rz�dne wektora zostan� podzielone.
		 *  @retval Funkcja zwraca referencj� do tego wektora.
		 */
		CVector& operator/=(float Value);

	public:
		/** @brief Operator odwraca wsp�rz�dne wektora, tworz�c wektor przeciwny.
		 *  @retval Funkcja zwraca wektor przeciwny do tego wektora.
		 */
		CVector operator-(void) const;

	public:
		/** @brief Operator por�wnania dw�ch wektor�w.
		 *  @retval Funkcja zwraca liczb� r�n� od zera, je�li wsp�rz�dne wektora
		 *          s� r�wne sobie z dok�adno�ci� EPSILON.
		 */
		int operator==(const CVector &Vector) const;

};
