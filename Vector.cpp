
/** @file Vector.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CVector.
 *
 *  Plik zawiera implementacjê klasy CVector.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Vector.h"
#include <math.h>

// CVector

CVector::CVector()
	: m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
{
}

CVector::CVector(float X, float Y, float Z)
	: m_X(X)
	, m_Y(Y)
	, m_Z(Z)
{
}

CVector::CVector(const CVector &Vector)
	: m_X(Vector.m_X)
	, m_Y(Vector.m_Y)
	, m_Z(Vector.m_Z)
{
}

int CVector::Read(FILE *File)
{
	char Buffer[32];
	int ErrorFlag = 0, BeginFlag = 0, EndFlag = 0;

	// glowna petla odczytujaca
	while (!EndFlag && !ErrorFlag && (fscanf(File, "%s", Buffer) == 1))
	{
		// czy nie odczytano juz slowa BEGIN
		if (!BeginFlag)
		{
			// jesli nie, to sprawdz czy odczytane slowo jest slowem BEGIN
			if (stricmp(Buffer, "BEGIN") == 0)
				// ustaw flage odczytania slowa BEGIN
				BeginFlag = 1;
		}
		else
		{
			// czy nie odczytano juz slowa END
			if (!EndFlag)
			{
				// czy jest to slowo X?
				if (stricmp(Buffer, "X") == 0)
					// jesli tak, to odczytaj wspolrzedna X
					ErrorFlag = fscanf(File, "%f", &m_X) != 1;

				// czy jest to slowo Y?
				else if (stricmp(Buffer, "Y") == 0)
					// jesli tak, to odczytaj wspolrzedna Y
					ErrorFlag = fscanf(File, "%f", &m_Y) != 1;

				// czy jest to slowo Z?
				else if (stricmp(Buffer, "Z") == 0)
					// jesli tak, to odczytaj wspolrzedna Z
					ErrorFlag = fscanf(File, "%f", &m_Z) != 1;

				// czy jest to slowo END
				else if (stricmp(Buffer, "END") == 0)
					// jesli tak, to ustaw flage odczytania slowa END
					EndFlag = 1;
			}
		}
	}

	// zwroc flage END
	return EndFlag;
}

int CVector::Write(FILE *File, const CString &TabFill)
{
	// zapisz wspolrzedne wektora
	return fprintf(File, "%sBEGIN\n%s\tX %f\n%s\tY %f\n%s\tZ %f\n%sEND\n", TabFill, 
		TabFill, m_X, TabFill, m_Y, TabFill, m_Z, TabFill);
}

void CVector::Zero(void)
{
	// wyzeruj wspolrzedne
	m_X = m_Y = m_Z = 0.0f;
}

void CVector::ZeroClamp(float Epsilon)
{
	// wyzeruj wspolrzedne, jesli sa bliskie zero
	m_X = ZERO_CLAMP_EPS(m_X, Epsilon);
	m_Y = ZERO_CLAMP_EPS(m_Y, Epsilon);
	m_Z = ZERO_CLAMP_EPS(m_Z, Epsilon);
}

void CVector::Negative(void)
{
	// odwroc wspolrzedne wektora
	m_X = -m_X;
	m_Y = -m_Y;
	m_Z = -m_Z;
}

int CVector::Normalize(void)
{
	// oblicz d³ugoœæ wektora
	float Distance = Length();

	// jeœli d³ugoœæ wektora jest zerowa
	if (Distance > 0.0f)
	{
		// dokonaj normalizacji wspó³rzêdnych
		m_X /= Distance;
		m_Y /= Distance;
		m_Z /= Distance;

		// zwroc 1 -- dokonano normalizacji
		return 1;
	}

	// zwroc 0 -- nie udalo sie dokonac normalizacji
	return 0;
}

void CVector::Set(float X, float Y, float Z)
{
	// ustaw wspolrzedne wektora
	m_X = X;
	m_Y = Y;
	m_Z = Z;
}
		
int CVector::IsZero(float Epsilon) const
{
	// czy dlugosc wektora jest zerowa
	return FLOAT_EQ_EPS(Length(), 0.0f, Epsilon);
}

int CVector::IsNormal(void) const
{
	// czy dlugosc wektora jest rowna 1.0
	return FLOAT_EQ(Length(), 1.0f);
}

float CVector::Length(void) const
{
	// wyznacz dlugosc wektora
	return (float)sqrt(SQR(m_X) + SQR(m_Y) + SQR(m_Z));
}

float CVector::Distance(const CVector &Vector) const
{
	return CVector(Vector - *this).Length();
}

float CVector::Dot(const CVector &Vector) const
{
	// wyznacz iloczyn skalarny dwoch wektorow
	return (m_X * Vector.m_X) + (m_Y * Vector.m_Y) + (m_Z * Vector.m_Z);
}

CVector& CVector::operator=(const CVector &Vector)
{
	// skopiuj wspolrzedne wektora
	m_X = Vector.m_X;
	m_Y = Vector.m_Y;
	m_Z = Vector.m_Z;

	// zwroc referencje do tego wektora
	return *this;
}
		
CVector CVector::operator+(const CVector &Vector) const
{
	// dodaj wspolrzedne wektorow
	return CVector(m_X + Vector.m_X, m_Y + Vector.m_Y, m_Z + Vector.m_Z);
}

CVector CVector::operator-(const CVector &Vector) const
{
	// odejmij wspolrzedne wektorow
	return CVector(m_X - Vector.m_X, m_Y - Vector.m_Y, m_Z - Vector.m_Z);
}

CVector CVector::operator*(const CVector &Vector) const
{
	// wyznacz iloczyn wektorowy wektorow
	return CVector(
		(m_Y * Vector.m_Z) - (m_Z * Vector.m_Y),
		(m_Z * Vector.m_X) - (m_X * Vector.m_Z),
		(m_X * Vector.m_Y) - (m_Y * Vector.m_X)
	);
}

CVector& CVector::operator+=(const CVector &Vector)
{
	// dodaj wspolrzedne wektora do wspolrzednych tego wektora
	m_X += Vector.m_X;
	m_Y += Vector.m_Y;
	m_Z += Vector.m_Z;

	// zwroc referencje do tego wektora
	return *this;
}

CVector& CVector::operator-=(const CVector &Vector)
{
	// odejmij wspolrzedne wektora od wspolrzednych tego wektora
	m_X -= Vector.m_X;
	m_Y -= Vector.m_Y;
	m_Z -= Vector.m_Z;

	// zwroc referencje do tego wektora
	return *this;
}

CVector& CVector::operator*=(const CVector &Vector)
{
	// wyznacz wspolrzedne iloczynu wektorowego
	float X = (m_Y * Vector.m_Z) - (m_Z * Vector.m_Y);
	float Y = (m_Z * Vector.m_X) - (m_X * Vector.m_Z);
	float Z = (m_X * Vector.m_Y) - (m_Y * Vector.m_X);

	// zapisz te wspolrzedne do tego wektora
	m_X = X;
	m_Y = Y;
	m_Z = Z;

	// zwroc referencje do tego wektora
	return *this;
}

CVector CVector::operator*(float Value) const
{
	// pomnoz wspolrzedne wektora przez skale
	return CVector(m_X * Value, m_Y * Value, m_Z * Value);
}

CVector CVector::operator/(float Value) const
{
	// podziel wspolrzedne wektora przez skale
	return CVector(m_X / Value, m_Y / Value, m_Z / Value);
}
		
CVector& CVector::operator*=(float Value)
{
	// pomnoz wspolrzedne tego wektora przez skale
	m_X *= Value;
	m_Y *= Value;
	m_Z *= Value;

	// zwroc referencje do tego wekora
	return *this;
}

CVector& CVector::operator/=(float Value)
{
	// podziel wspolrzedne tego wektora przez skale
	m_X /= Value;
	m_Y /= Value;
	m_Z /= Value;

	// zwroc referencje do tego wektora
	return *this;
}

CVector CVector::operator-(void) const
{
	// odwroc wspolrzedne tego wektora
	return CVector(-m_X, -m_Y, -m_Z);
}

int CVector::operator==(const CVector &Vector) const
{
	// porownaj wspolrzedne wektora
	return FLOAT_EQ(m_X, Vector.m_X) && 
		FLOAT_EQ(m_Y, Vector.m_Y) && FLOAT_EQ(m_Z, Vector.m_Z);
}
