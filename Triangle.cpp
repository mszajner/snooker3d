
/** @file Triangle.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CTriangle.
 *
 *  Plik zawiera implementacjê klasy CTriangle.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Triangle.h"
#include "Ray.h"

// CTriangle

CTriangle::CTriangle()
	: m_Hole(0)
	, m_Reflect(0)
	, m_A(0.0f, 0.0f, 0.0f)
	, m_B(1.0f, 0.0f, 0.0f)
	, m_C(1.0f, 1.0f, 0.0f)
{
	SetN();
}

CTriangle::CTriangle(const CTriangle &Triangle)
	: m_Hole(Triangle.m_Hole)
	, m_Reflect(Triangle.m_Reflect)
	, m_A(Triangle.m_A)
	, m_B(Triangle.m_B)
	, m_C(Triangle.m_C)
	, m_N(Triangle.m_N)
{
}

CTriangle::CTriangle(const CVector &A, const CVector &B, const CVector &C)
{
	// ustaw wspolrzedne wektora
	Set(A, B, C);
}

int CTriangle::Read(FILE *File)
{
	char Buffer[32];
	int ErrorFlag = 0, BeginFlag = 0, EndFlag = 0;

	// glowna petla odczytujaca
	while (!EndFlag && !ErrorFlag && (fscanf(File, "%s", Buffer) == 1))
	{
		// czy nie odczytano juz slowa BEGIN
		if (!BeginFlag)
		{
			// jesli nie, to czy jest to slowo BEGIN
			if (stricmp(Buffer, "BEGIN") == 0)
				// jesli tak, to ustaw flage odczytania slowa BEGIN
				BeginFlag = 1;
		}
		else
		{
			// czy nie odczytano juz slowa END
			if (!EndFlag)
			{
				// czy jest to slowo HOLE
				if (stricmp(Buffer, "HOLE") == 0)
					// jesli tak, to odczytaj flage czy trojkat jest dolkiem
					ErrorFlag = fscanf(File, "%d", &m_Hole) != 1;

				// czy jest to slowo REFLECT
				else if (stricmp(Buffer, "REFLECT") == 0)
					// jesli tak, to odczytaj flage czy trojkat odbija bile
					ErrorFlag = fscanf(File, "%d", &m_Reflect) != 1;

				// czy jest to slowo A
				else if (stricmp(Buffer, "A") == 0)
					// jesli tak, to odczytaj wierzcholek A
					ErrorFlag = !m_A.Read(File);

				// czy jest to slowo B
				else if (stricmp(Buffer, "B") == 0)
					// jesli tak, to odczytaj wierzcholek B
					ErrorFlag = !m_B.Read(File);

				// czy jest to slowo C
				else if (stricmp(Buffer, "C") == 0)
					// jesli tak, to odczytaj wierzcholek C
					ErrorFlag = !m_C.Read(File);

				// czy jest to slowo END
				else if (stricmp(Buffer, "END") == 0)
				{
					// jesli tak, to wyznacz wektor normalny do tego trojkata
					SetN();
					// ustaw flage odczytania slowa END
					EndFlag = 1;
				}
			}
		}
	}

	// zwroc flage odczytania slowa END
	return EndFlag;
}

int CTriangle::Write(FILE *File, const CString &TabFill)
{
	// zapisz slowo BEGIN
	fprintf(File, "%sBEGIN\n", TabFill);

	// zapisz flage czy trojkat jest dolkiem
	fprintf(File, "%s\tHOLE %d\n", TabFill, m_Hole);
	// zapisz flage czy trojkat odbija bile
	fprintf(File, "%s\tREFLECT %d\n", TabFill, m_Reflect);

	// zapisz wierzcholek A
	fprintf(File, "%s\tA\n", TabFill);
	if (!m_A.Write(File, TabFill + "\t"))
		return 0;

	// zapisz wierzcholek B
	fprintf(File, "%s\tB\n", TabFill);
	if (!m_B.Write(File, TabFill + "\t"))
		return 0;

	// zapisz wierzcholek C
	fprintf(File, "%s\tC\n", TabFill);
	if (!m_C.Write(File, TabFill + "\t"))
		return 0;

	// zapisz slowo END
	fprintf(File, "%sEND\n", TabFill);
	return 1;
}

void CTriangle::Set(const CVector &A, const CVector &B, const CVector &C)
{
	// ustaw wierzcholki
	m_A = A;
	m_B = B;
	m_C = C;

	// wyznacz wektor normalny
	SetN();
}

void CTriangle::SetA(const CVector &A)
{
	// ustaw wierzcholek A
	m_A = A;

	// wyznacz wektor normalny
	SetN();
}

void CTriangle::SetB(const CVector &B)
{
	// ustaw wierzcholek B
	m_B = B;

	// wyznacz wektor normalny
	SetN();
}

void CTriangle::SetC(const CVector &C)
{
	// ustaw wierzcholek C
	m_C = C;

	// wyznacz wektor normalny
	SetN();
}

void CTriangle::SetN(void)
{
	CVector VectorBA, VectorCA;

	// wyznacz wektory pokrywajace sie z bokami trojkata
	VectorBA = m_B - m_A;
	VectorCA = m_C - m_A;

	// wyznacz iloczyn wektorowy
	m_N = VectorBA * VectorCA;

	// normalizuj wektor normalny
	m_N.Normalize();
}

int CTriangle::Contains(const CVector &Point) const
{
	// wyznacz trzy polproste zawierajace boki trojkata
	CRay RayBC(m_B, m_C);
	CRay RayAC(m_A, m_C);
	CRay RayAB(m_A, m_B);

	// sprawdz czy punkt znajduje sie wewnatrz trojkata
	return RayBC.AreAtSameSide(Point, m_A) && 
		RayAC.AreAtSameSide(Point, m_B) && RayAB.AreAtSameSide(Point, m_C);
}

CTriangle& CTriangle::operator=(const CTriangle &Triangle)
{
	// skopiuj pola
	m_Hole = Triangle.m_Hole;
	m_Reflect = Triangle.m_Reflect;
	m_A = Triangle.m_A;
	m_B = Triangle.m_B;
	m_C = Triangle.m_C;
	m_N = Triangle.m_N;

	// zwroc referencje do tego trojkata
	return *this;
}
