
/** @file Ball.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy reprezentuj¹cej bilê CBall.
 *
 *  Plik zawiera implementacjê klasy CBall reprezentuj¹c¹ pojedyncz¹ bilê.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Ball.h"
#include "Ray.h"
#include <math.h>

// CBall

CBall::CBall(void)
	: m_Score(0)
	, m_Type(btWhite)
	, m_Simulate(0)
	, m_Render(0)
	, m_KnockedIn(0)
	, m_OutOfBoard(0)
	, m_Ray(0.262f)
	, m_Mass(1.0f)
	, m_Track(0.0f)
	, m_TrackPrevious(0.0f)
	, m_Position(0.262f, 0.262f, 0.262f)
	, m_PositionPrevious(0.262f, 0.262f, 0.262f)
	, m_PositionOriginal(0.262f, 0.262f, 0.262f)
	, m_Velocity(0.0f, 0.0f, 0.0f)
	, m_VelocityNormal(0.0f, 0.0f, 0.0f)
	, m_Rotate(1.0f, 0.0f, 0.0f)
	, m_Force(0.0f, 0.0f, 0.0f)
	, m_Triangle(NULL)
{
	// ustaw bialy kolor
	m_Color[0] = m_Color[1] = m_Color[2] = m_Color[3] = 1.0f;
}

CBall::CBall(const CBall &Ball)
{
	// kopiuj pola bili
	memcpy(this, &Ball, sizeof(CBall));
}

int CBall::Read(FILE *File)
{
	char Buffer[32];
	int ErrorFlag = 0, BeginFlag = 0, EndFlag = 0;

	// glowna petla odczytujaca
	while (!EndFlag && !ErrorFlag && (fscanf(File, "%s", Buffer) == 1))
	{
		// czy nie odczytano juz slowa kluczowe BEGIN
		if (!BeginFlag)
		{
			// jezeli nie, to czy odczytano w koncu slowo BEGIN
			if (stricmp(Buffer, "BEGIN") == 0)
				// jesli tak, to ustaw flage odczytania slowa BEGIN
				BeginFlag = 1;
		}
		else
		{
			// czy jeszcze nie odczytano slowa END
			if (!EndFlag)
			{
				// czy odczytano slowo SCORE
				if (stricmp(Buffer, "SCORE") == 0)
					// odczytaj liczbe punktow bili
					ErrorFlag = fscanf(File, "%d", &m_Score) != 1;

				// czy odczytano slowo TYPE
				else if (stricmp(Buffer, "TYPE") == 0)
					// odczytaj typ bili
					ErrorFlag = fscanf(File, "%d", &m_Type) != 1;

				// czy odczytano slowo SIMULATE
				else if (stricmp(Buffer, "SIMULATE") == 0)
					// odczytaj flage aktywnosci symulacji bili
					ErrorFlag = fscanf(File, "%d", &m_Simulate) != 1;

				// czy odczytano slowo RENDER
				else if (stricmp(Buffer, "RENDER") == 0)
					// odczytaj flage aktywnosci renderowania bili
					ErrorFlag = fscanf(File, "%d", &m_Render) != 1;

				// czy odczytano slowo KNOCKED_IN
				else if (stricmp(Buffer, "KNOCKED_IN") == 0)
					// odczytaj flage wbicia bili
					ErrorFlag = fscanf(File, "%d", &m_KnockedIn) != 1;

				// czy odczytano slowo OUT_OF_BOARD
				else if (stricmp(Buffer, "OUT_OF_BOARD") == 0)
					// odczytaj flage wbicia bili
					ErrorFlag = fscanf(File, "%d", &m_OutOfBoard) != 1;

				// czy odczytano slowo RAY
				else if (stricmp(Buffer, "RAY") == 0)
					// odczytaj promien bili
					ErrorFlag = fscanf(File, "%f", &m_Ray) != 1;

				// czy odczytano slowo MASS
				else if (stricmp(Buffer, "MASS") == 0)
					// odczytaj mase bili
					ErrorFlag = fscanf(File, "%f", &m_Mass) != 1;

				// czy odczytano slowo TRACK
				else if (stricmp(Buffer, "TRACK") == 0)
					// odczytaj droge przebyta przez bile
					ErrorFlag = fscanf(File, "%f", &m_Track) != 1;

				// czy odczytano slowo TRACK_PREVIOUS
				else if (stricmp(Buffer, "TRACK_PREVIOUS") == 0)
					// odczytaj poprzednia przebyta droge przez bile
					ErrorFlag = fscanf(File, "%f", &m_TrackPrevious) != 1;

				// czy odczytano slowo COLOR
				else if (stricmp(Buffer, "COLOR") == 0)
				{
					// odczytaj kolor
					ErrorFlag = fscanf(File, "%f %f %f %f", &m_Color[0], &m_Color[1], &m_Color[2], &m_Color[3]) != 4;

					// przeskaluj kolor
					m_Color[0] /= 255.0f;
					m_Color[1] /= 255.0f;
					m_Color[2] /= 255.0f;
					m_Color[3] /= 255.0f;
				}

				// czy odczytano slowo POSITION
				else if (stricmp(Buffer, "POSITION") == 0)
					// odczytaj aktualna pozycje bili
					ErrorFlag = !m_Position.Read(File);

				// czy odczytano slowo POSITION_PREVIOUS
				else if (stricmp(Buffer, "POSITION_PREVIOUS") == 0)
					// odczytaj poprzednia pozycje bili
					ErrorFlag = !m_PositionPrevious.Read(File);

				// czy odczytano slowo POSITION_ORIGINAL
				else if (stricmp(Buffer, "POSITION_ORIGINAL") == 0)
					// odczytaj oryginalna pozycje bili
					ErrorFlag = !m_PositionOriginal.Read(File);

				// czy odczytano slowo VELOCITY
				else if (stricmp(Buffer, "VELOCITY") == 0)
					// odczytaj predkosc bili
					ErrorFlag = !m_Velocity.Read(File);

				// czy odczytano slowo VELOCITY_NORMAL
				else if (stricmp(Buffer, "VELOCITY_NORMAL") == 0)
					// odczytaj wektor normalny predkosci
					ErrorFlag = !m_VelocityNormal.Read(File);

				// czy odczytano slowo ROTATE
				else if (stricmp(Buffer, "ROTATE") == 0)
					// odczytaj wektor obrotu bili
					ErrorFlag = !m_Rotate.Read(File);

				// czy odczytano slowo FORCE
				else if (stricmp(Buffer, "FORCE") == 0)
					// odczytaj sile przylozona do bili
					ErrorFlag = !m_Force.Read(File);

				// czy odczytano slowo END
				else if (stricmp(Buffer, "END") == 0)
					// ustaw flage odczytania slowa END
					EndFlag = 1;
			}
		}
	}

	// zwroc flage odczytania slowa END
	return EndFlag;
}

int CBall::Write(FILE *File, const CString &TabFill)
{
	// zapisz slowo BEGIN
	fprintf(File, "%sBEGIN\n", TabFill);

	// zapisz liczbe punktow bili
	fprintf(File, "%s\tSCORE %d\n", TabFill, m_Score);
	// zapisz liczbe punktow bili
	fprintf(File, "%s\tTYPE %d\n", TabFill, m_Type);
	// zapisz flage symulacji
	fprintf(File, "%s\tSIMULATE %d\n", TabFill, m_Simulate);
	// zapisz flage renderowania
	fprintf(File, "%s\tRENDER %d\n", TabFill, m_Render);
	// zapisz flage wbicia
	fprintf(File, "%s\tKNOCKED_IN %d\n", TabFill, m_KnockedIn);
	// zapisz flage wybicia poza stol
	fprintf(File, "%s\tOUT_OF_BOARD %d\n", TabFill, m_OutOfBoard);
	// zapisz promien bili
	fprintf(File, "%s\tRAY %f\n", TabFill, m_Ray);
	// zapisz mase bili
	fprintf(File, "%s\tMASS %f\n", TabFill, m_Mass);
	// zapisz droge przebyta przez bile
	fprintf(File, "%s\tTRACK %f\n",TabFill,  m_Track);
	// zapisz poprzednia droge przebyta przez bile
	fprintf(File, "%s\tTRACK_PREVIOUS %f\n", TabFill, m_TrackPrevious);
	// zapisz kolor
	fprintf(File, "%s\tCOLOR %f %f %f %f\n", TabFill, m_Color[0]*255.0f, m_Color[1]*255.0f, m_Color[2]*255.0f, m_Color[3]*255.0f);

	// zapisz aktualna pozycje
	fprintf(File, "%s\tPOSITION\n", TabFill);
	if (!m_Position.Write(File, TabFill + "\t"))
		return 0;

	// zapisz poprzednia pozycje
	fprintf(File, "%s\tPOSITION_PREVIOUS\n", TabFill);
	if (!m_PositionPrevious.Write(File, TabFill + "\t"))
		return 0;

	// zapisz oryginalna pozycje
	fprintf(File, "%s\tPOSITION_ORIGINAL\n", TabFill);
	if (!m_PositionOriginal.Write(File, TabFill + "\t"))
		return 0;

	// zapisz predkosc bili
	fprintf(File, "%s\tVELOCITY\n", TabFill);
	if (!m_Velocity.Write(File, TabFill + "\t"))
		return 0;

	// zapisz wektor normalny predkosci
	fprintf(File, "%s\tVELOCITY_NORMAL\n", TabFill);
	if (!m_VelocityNormal.Write(File, TabFill + "\t"))
		return 0;

	// zapisz wektor obrotu bili
	fprintf(File, "%s\tROTATE\n", TabFill);
	if (!m_Rotate.Write(File, TabFill + "\t"))
		return 0;

	// zapisz sile przylozona do bili
	fprintf(File, "%s\tFORCE\n", TabFill);
	if (!m_Force.Write(File, TabFill + "\t"))
		return 0;

	// zapisz slowo END
	fprintf(File, "%sEND\n", TabFill);
	return 1;
}

void CBall::AddForce(const CVector &Force)
{
	// dodaj sile
	m_Force += Force;
}

void CBall::AddFrictionForce(void)
{
	//CVector Force = -m_Velocity;
	//Force.Normalize();
	//Force *= 98.1f * 0.1f;
	//AddForce(Force);
	// dodaj sile tarcia
	AddForce((-m_Velocity) * 0.8f / m_Mass);
}

void CBall::AddGravityForce(void)
{
	// dodaj sile grawitacji
	AddForce(CVector(0.0f, 0.0f, -98.1f) * m_Mass);
}

void CBall::ApplyForce(float Time)
{
	// czy symulacja bili wlaczona
	if (!GetSimulate())
	{
		m_Force.Zero();
		return;
	}

	// wyznacz nowa predkosc
	m_Velocity += (m_Force / m_Mass) * Time;

	// wyzeruj sile
	m_Force.Zero();

	// wyznacz wektor obrotu
	Rotate();
}

void CBall::Simulate(float Time)
{
	// czy symulacja bili wlaczona
	if (!GetSimulate())
		return;

	// zachowaj aktualna pozycje
	m_PositionPrevious = m_Position;
	// zachowaj aktualnie przebyta droge
	m_TrackPrevious = m_Track;

	// wyznacz przesuniecie w podanym czasie
	CVector Movement = m_Velocity * Time;

	// dodaj przesuniecie do aktualnej pozycji
	m_Position += Movement;

	// wyznacz dlugosc wektora przesuniecia i dodaj do aktualnie przebytej drogi
	m_Track += Movement.Length();

	// jesli wartosc drogi jest wieksza od 100.0
	if (m_Track > 100.0f)
	{
		// odejmij wartosc 100.0 od drogi
		m_Track -= 100.0f;
		// odejmij wartosc 100.0 od poprzedniej drogi
		m_TrackPrevious -= 100.0f;
	}
}

void CBall::Restore(void)
{
	// czy symulacja bili wlaczona
	if (!GetSimulate())
		return;

	// przywroc pozycje bili
	m_Position = m_PositionPrevious;
	// przywroc przebyta droge
	m_Track = m_TrackPrevious;
}

void CBall::Reset(void)
{
	// wlacz renderowanie
	m_Render = 1;
	// wlacz symulacje
	m_Simulate = 1;
	// wyzeruj flage wbicia bili
	m_KnockedIn = 0;
	// wyzeruj flage wybicia bili poza stol
	m_OutOfBoard = 0;

	// przywroc oryginalna pozycje
	m_Position = m_PositionOriginal;
	m_PositionPrevious = m_PositionOriginal;

	// wyzeruj licznik drogi
	m_Track = 0.0f;
	m_TrackPrevious = 0.0f;

	// wyzeruj sile
	m_Force.Zero();
	// wyzeruj predkosc
	m_Velocity.Zero();

	// wyznacz wektor obrotu
	Rotate();
}

void CBall::Rotate(void)
{
	// czy symulacja bili wylaczona?
	if (!GetSimulate())
		return;

	// pobierz wektor predkosci
	m_VelocityNormal = m_Velocity;

	// normalizuj wektor predkosci
	if (m_VelocityNormal.Normalize())
	{
		// wyznacz wektor obrotu
		m_Rotate = m_VelocityNormal * CVector(0.0f, 0.0f, 1.0f);

		// normalizuj wektor obrotu
		m_Rotate.Normalize();
	}
}

void CBall::Stop(void)
{
	// wyzeruj predkosc
	m_Velocity.Zero();

	// wyzeruj sile
	m_Force.Zero();
}

int CBall::IsInTriangle(const CTriangle *Triangle)
{
	// sprawdz czy podano nowy trójk¹t
	Triangle = Triangle ? Triangle : m_Triangle;

	// czy wskaŸnik na trójk¹t nie jest pusty i trójk¹t zawiera punkt
	if (Triangle && Triangle->Contains(m_Position))
	{
		// zapamietaj wskaŸnik na nowy trójk¹t
		m_Triangle = Triangle;
		m_Position.m_Z = m_Triangle->m_A.m_Z;
		return 1;
	}

	return 0;
}

int CBall::FindCollision(float FullTime, float &Time, const CBall &Ball) const
{
	// wyznacz wzgledna predkosc miedzy bilami
	CVector Relative = m_Velocity - Ball.m_Velocity;

	// czy wzgledna predkosc jest zerowa?
	if (Relative.IsZero(0.005f))
		// jesli tak, to zwroc false -- nie ma kolizji
		return 0;

	CRay Ray;

	// utworz polprosta o poczatku w bili i kierunku rownoleglym do wzglednej predkosci
	Ray.Set(m_PositionPrevious, Relative);

	// wyznacz odleglosc miedzy dwoma srodkami bil
	float Diameter = m_Ray + Ball.m_Ray;

	// czy odleglosc polprostej od bili jest wieksza od odleglosci miedzy dwoma srodkami
	if (Ray.Distance(Ball.m_PositionPrevious) > Diameter)
		// jesli tak, to zwroc false -- nie ma kolizji
		return 0;

	// podziel czas na 150 czesci
	float MyTime, Add = FullTime / 150.0f;

	// przesun przez kazda czesc
	for (MyTime = 0.0f; MyTime < Time; )
	{
		// przesun o jedna czesc
		MyTime += Add;

		// wyznacz nowa pozycje
		CVector Position = m_PositionPrevious + (Relative * MyTime);

		// czy odleglosc pozycji o pozycji bili jest mniejsza od odleglosci miedzy srodkami bil
		if (Position.Distance(Ball.m_PositionPrevious) <= Diameter)
		{
			// czy czas jest mniejszy od ogolnego czasu
			if (Time > (MyTime - Add))
			{
				// zapamietaj nowy czas
				Time = MyTime - Add;
				// zwroc true -- znaleziono kolizje
				return 1;
			}
		}
	}

	// zwroc 0 -- nie znaleziono kolizji
	return 0;
}

int CBall::FindCollision(float FullTime, float &Time, const CTriangle &Triangle) const
{
	// czy bila sie nie toczy?
	if (!IsMoving())
		return 0;

	// wyznacz iloczy skalarny wektora predkosci i normalnej trojkata
	float Dot = m_VelocityNormal.Dot(Triangle.m_N);

	// jesli wynik jest 0.0 -- wektory prostopadle
	if (FLOAT_EQ(Dot, 0.0f))
		return 0;

	// wyznacz stronê po której bila znajduje siê wzgledem trojkata
	float CollisionPoint = Triangle.m_N.Dot(Triangle.m_A - m_PositionPrevious) / Dot;

	// czy bila jest po stronie normalnej trojkata?
	if (CollisionPoint < -EPSILON)
		return 0;

	// wyznacz przebyta droge od poprzedniego punktu
	float Distance = (float)fabs(m_Track - m_TrackPrevious);

	// wyznacz czas kolizji
	float CollisionTime = CollisionPoint * FullTime / Distance;

	// jesli czas kolizji jest wiekszy od calego czasu
	if ((CollisionTime > Time) || (CollisionTime > FullTime))
		return 0;

	if ((CollisionPoint <= EPSILON) && (Dot > EPSILON))
		return 0;

	// wyznacz punkt kolizji
	CVector Point = m_PositionPrevious + (m_VelocityNormal * (CollisionPoint));

	// czy trojkat zawiera ten punkt
	if (Triangle.Contains(Point))
	{
		// jesli tak, to zapamietaj czas kolizji
		Time = CollisionTime;
		// zwroc TRUE -- nastapila kolizja
		return 1;
	}

	// zwroc FALSE -- nie ma kolizji
	return 0;
}

void CBall::Reflect(CBall &Ball)
{
	float M, M1, M2;
	CVector XAxis, A;
	CVector U1x, U1y, V1x, V1y;
	CVector U2x, U2y, V2x, V2y;

	// wyznacz wektor prostopadly do plaszczyzny styku
	XAxis = Ball.m_Position - m_Position;

	// znormalizuj wektor
	XAxis.Normalize();

	// wyznacz czastkowe nowe predkosci dla pierwszej bili
	U1x = XAxis * XAxis.Dot(m_Velocity);
	U1y = m_Velocity - U1x;

	// odwroc wektor prostopadly
	XAxis.Negative();

	// wyznacz czastkowe nowe predkosci dla drugiej bili
	U2x = XAxis * XAxis.Dot(Ball.m_Velocity);
	U2y = Ball.m_Velocity - U2x;

	// pobierz mase pierwszej bili
	M1 = m_Mass;
	// pobierz mase drugiej bili
	M2 = Ball.m_Mass;
	// wyznacz calkowita mase
	M = M1 + M2;

	// wyznacz czastkowy wektor
	A = (U1x * M1) + (U2x * M2);

	// wyznacz czastkowe predkosci
	V1x = (A - (U1x - U2x) * M2) / M;
	V2x = (A - (U2x - U1x) * M1) / M;

	// wyznacz nowa predkosc pierwszej bili
	if (GetSimulate())
		m_Velocity = V1x + U1y;
	// wyznacz nowa predkosc drugiej bili
	if (Ball.GetSimulate())
		Ball.m_Velocity = V2x + U2y;

	// wyznacz wektor obrotu pierwszej bili
	Rotate();
	// wyznacz wektor obrotu drugiej bili
	Ball.Rotate();
}

void CBall::Reflect(const CTriangle &Triangle)
{
	// czy trójk¹t jest do³kiem
	if (Triangle.GetHole())
	{
		// jesli jest, to zatrzymaj bile
		Stop();
		// ustaw flage wbicia bili
		m_KnockedIn = 1;
		// wylacz symulacje bili
		m_Simulate = 0;
		// wylacz renderowanie bili
		m_Render = 0;
	}

	// czy symulacja bili wlaczona i trojkat jest odbijajacym
	if (!GetSimulate() || !Triangle.GetReflect())
		return;

	// oblicz dlugosc wektora predkosci
	float VelocityLength = m_Velocity.Length();

	// wyznacz wektor przeciwny do wektora predkosci
	m_Velocity = m_VelocityNormal;
	m_Velocity.Negative();

	// wyznacz iloczyn skalarny wektora normalnego plaszczyzny i wektora przeciwnego predkosci
	float Temp = 2.0f * Triangle.m_N.Dot(m_Velocity);

	// pomnoz wynik iloczynu przez wektor normalny plaszczyzny
	m_Velocity = m_VelocityNormal + (Triangle.m_N * Temp);

	// wyznacz wektor jednostkowy mnozenia
	m_Velocity.Normalize();

	// przywroc dlugosc wektora predkosci
	m_Velocity *= VelocityLength * 0.95f;

	// oblicz wektor obrotu bili
	Rotate();
}

CBall& CBall::operator=(const CBall &Ball)
{
	// kopiuj pola bili
	memcpy(this, &Ball, sizeof(CBall));

	// zwroc referencje do tej bili
	return *this;
}
