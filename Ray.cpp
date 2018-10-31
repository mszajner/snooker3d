
/** @file Ray.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CRay.
 *
 *  Plik zawiera implementacjê klasy CRay.
 *
 */

#include "stdafx.h"
#include "Snooker.h"
#include "Ray.h"

// CRay

CRay::CRay(void)
{
}

CRay::CRay(const CVector &Point1, const CVector &Point2)
	: m_Point(Point2)
	, m_Direction(Point1 - Point2)
{
	// normalizuj wektor kierunkowy
	m_Direction.Normalize();
}

CRay::CRay(const CRay &Ray)
	: m_Point(Ray.m_Point)
	, m_Direction(Ray.m_Direction)
{
}

void CRay::Negative(void)
{
	// odwroc wektor kierunkowy
	m_Direction.Negative();
}

void CRay::Set(const CVector &Point, const CVector &Direction)
{
	// ustaw punkt poczatkowy polprostej
	m_Point = Point;

	// ustaw wektor kierunkowy polprostej
	m_Direction = Direction;

	// normalizuj wektor kierunkowy polprostej
	m_Direction.Normalize();
}

void CRay::SetPoint(const CVector &Point)
{
	// ustaw punkt poczatkowy polprostej
	m_Point = Point;
}

void CRay::SetDirection(const CVector &Direction)
{
	// ustaw wektor kierunkowy polprostej
	m_Direction = Direction;

	// normalizuj wektor kierunkowy polprostej
	m_Direction.Normalize();
}

void CRay::AdjacentPoints(const CRay &Ray, CVector &Point1, CVector &Point2) const
{
	// wyznacz iloczyn skalarny wektorow kierunkowych dwoch prostych
	float temp = m_Direction.Dot(Ray.m_Direction);

	// wyznacz pomocnicza wartosc
	float temp2 = 1.0f - temp*temp;

	if (temp2 < EPSILON)
	{
		float Delta;

		Delta = m_Direction.Dot(m_Point - Ray.m_Point) / temp;

		Point1 = m_Point;
		Point2 = Ray.m_Point + (Ray.m_Direction) * Delta;
	}
	else
	{
		float a, b, mu, lambda;

		a = m_Direction.Dot(Ray.m_Point - m_Point);
		b = Ray.m_Direction.Dot(m_Point - Ray.m_Point);

		mu = (b * temp*a) / temp2;
		lambda = (a + temp*b) / temp2;

		Point1 = m_Point + (m_Direction * lambda);
		Point2 = Ray.m_Point + (Ray.m_Direction * mu);
	} 
}

int CRay::AreAtSameSide(const CVector &Point1, const CVector &Point2) const
{
	CVector Vector1, Vector2;

	Vector1 = m_Direction * (Point1 - m_Point);
	Vector2 = m_Direction * (Point2 - m_Point);

	return (Vector1.Dot(Vector2) >= 0.0f);
}
	
float CRay::Distance(const CRay &Ray) const
{
	CVector Point1, Point2;
	AdjacentPoints(Ray, Point1, Point2);
	return Point1.Distance(Point2);
}

float CRay::Distance(const CVector &Point) const
{
	CVector Vector;
	Vector = m_Point + (m_Direction * m_Direction.Dot(Point - m_Point));
	return Point.Distance(Vector);
}
	
CRay CRay::operator-(void) const
{
	CRay Ray;
	Ray.SetPoint(m_Point);
	Ray.SetDirection(-m_Direction);
	return Ray;
}
