
/** @file Camera.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CCamera i CCameraPosition.
 *
 *  Plik zawiera implementacjê klasy CCamera i CCameraPosition.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Camera.h"
#include <math.h>

// CCameraPosition

CCameraPosition::CCameraPosition(void)
	: m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
	, m_Alpha(0.0f)
	, m_Beta(0.0f)
	, m_FOV(0.0f)
{
}

CCameraPosition::CCameraPosition(const CCameraPosition &Position)
	: m_X(Position.m_X)
	, m_Y(Position.m_Y)
	, m_Z(Position.m_Z)
	, m_Alpha(Position.m_Alpha)
	, m_Beta(Position.m_Beta)
	, m_FOV(Position.m_FOV)
{
}

CCameraPosition::CCameraPosition(float X, float Y, float Z, float Alpha, float Beta, float FOV)
	: m_X(X)
	, m_Y(Y)
	, m_Z(Z)
	, m_Alpha(Alpha)
	, m_Beta(Beta)
	, m_FOV(FOV)
{
}

int CCameraPosition::Read(FILE *File)
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
				// czy jest to slowo X
				if (stricmp(Buffer, "X") == 0)
					// jesli tak, to odczytaj wspó³rzêdn¹ X
					ErrorFlag = fscanf(File, "%f", &m_X) != 1;

				// czy jest to slowo Y
				else if (stricmp(Buffer, "Y") == 0)
					// jesli tak, to odczytaj wspó³rzêdn¹ Y
					ErrorFlag = fscanf(File, "%f", &m_Y) != 1;

				// czy jest to slowo Z
				else if (stricmp(Buffer, "Z") == 0)
					// jesli tak, to odczytaj wspó³rzêdn¹ Z
					ErrorFlag = fscanf(File, "%f", &m_Z) != 1;

				// czy jest to slowo ALPHA
				else if (stricmp(Buffer, "ALPHA") == 0)
					// jesli tak, to odczytaj k¹t Alpha
					ErrorFlag = fscanf(File, "%f", &m_Alpha) != 1;

				// czy jest to slowo BETA
				else if (stricmp(Buffer, "BETA") == 0)
					// jesli tak, to odczytaj k¹t Beta
					ErrorFlag = fscanf(File, "%f", &m_Beta) != 1;

				// czy jest to slowo FOV
				else if (stricmp(Buffer, "FOV") == 0)
					// jesli tak, to odczytaj k¹t perspektywy
					ErrorFlag = fscanf(File, "%f", &m_FOV) != 1;

				// czy jest to slowo END
				else if (stricmp(Buffer, "END") == 0)
					// ustaw flage odczytania slowa END
					EndFlag = 1;
			}
		}
	}

	// zwroc flage odczytania slowa END
	return EndFlag;
}

int CCameraPosition::Write(FILE *File, const CString &TabFill)
{
	return fprintf(File, "%sBEGIN\n%s\tX %f\n%s\tY %f\n%s\tZ %f\n%s\tALPHA %f\n%s\tBETA %f\n%s\tFOV %f\n%sEND\n",
		TabFill, TabFill, m_X, TabFill, m_Y, TabFill, m_Z, TabFill, m_Alpha, TabFill, m_Beta, TabFill, m_FOV, TabFill);
}

void CCameraPosition::MoveTo(float Time, const CCameraPosition &Position)
{
	for (int i = 0; i < (Time * 100.0f); i++)
	{
		if ((Position.m_Beta - m_Beta) < -180.0f)
			m_Beta -= 360.0f;

		if ((Position.m_Beta - m_Beta) > 180.0f)
			m_Beta += 360.0f;

		m_dX = ((0.9f * m_dX) + 0.003f * (Position.m_X - m_X)); // * Time;
		m_dY = ((0.9f * m_dY) + 0.003f * (Position.m_Y - m_Y)); // * Time;
		m_dZ = ((0.9f * m_dZ) + 0.003f * (Position.m_Z - m_Z)); // * Time;

		m_dAlpha = (0.9f * m_dAlpha) + 0.003f * (Position.m_Alpha - m_Alpha);
		m_dBeta = (0.9f * m_dBeta) + 0.003f * (Position.m_Beta - m_Beta);
		m_dFOV = (0.9f * m_dFOV) + 0.003f * (Position.m_FOV - m_FOV);

		m_X += m_dX;
		m_Y += m_dY;
		m_Z += m_dZ;

		m_Alpha += m_dAlpha;
		m_Beta += m_dBeta;
		m_FOV += m_dFOV;
	}
}

CCameraPosition& CCameraPosition::operator=(const CCameraPosition &Position)
{
	// skopiuj parametry pozycji
	m_X = Position.m_X;
	m_Y = Position.m_Y;
	m_Z = Position.m_Z;
	m_Alpha = Position.m_Alpha;
	m_Beta = Position.m_Beta;
	m_FOV = Position.m_FOV;

	return *this;
}

// CCamera

CCamera::CCamera()
	: m_Position(-14.0f, -7.0f, 7.0f, 60.0f, 60.0f, 38.6f)
	, m_Target(-14.0f, -7.0f, 7.0f, 60.0f, 60.0f, 38.6f)
	, m_Min(-100.0f, -100.0f, 1.048f, 0.0f, -360.0f, 1.0f)
	, m_Max(100.0f, 100.0f, 100.0f, 90.0f, 360.0f, 90.0f)
	, m_BallIndex(-1)
	, m_MoveFactor(10.0f)
	, m_RollFactor(30.0f)
	, m_FlyFactor(20.0f)
{
	// m_Positions.Add(CCameraPosition(-100.0f, -50.0f, 50.0f, 60.0f, 60.0f, 38.6f));
	m_Positions.Add(CCameraPosition(-14.0f, -7.0f, 7.0f, 60.0f, 60.0f, 38.6f));
	// m_Positions.Add(CCameraPosition(0.0f, 0.0f, 400.0f, 0.0f, 0.0f, 30.7f));
	m_Positions.Add(CCameraPosition(0.0f, 0.0f, 51.0f, 0.0f, 0.0f, 30.7f));
	// m_Positions.Add(CCameraPosition(-170.0f, 0.0f, 30.0f, 80.0f, 90.0f, 38.6f));
	m_Positions.Add(CCameraPosition(-24.0f, 0.0f, 4.0f, 80.0f, 90.0f, 38.6f));
	// m_Positions.Add(CCameraPosition(170.0f, 0.0f, 30.0f, 80.0f, -90.0f, 38.6f));
	m_Positions.Add(CCameraPosition(24.0f, 0.0f, 4.0f, 80.0f, -90.0f, 38.6f));
	// m_Positions.Add(CCameraPosition(-220.0f, 0.0f, 120.0f, 53.0f, 90.0f, 38.6f));
	m_Positions.Add(CCameraPosition(-31.0f, 0.0f, 17.0f, 53.0f, 90.0f, 38.6f));
	// m_Positions.Add(CCameraPosition(220.0f, 0.0f, 120.0f, 53.0f, -90.0f, 38.6f));
	m_Positions.Add(CCameraPosition(31.0f, 0.0f, 17.0f, 53.0f, -90.0f, 38.6f));
	// m_Positions.Add(CCameraPosition(-229.0f, -121.0f, 176.0f, 48.0f, 56.5f, 38.6f));
	m_Positions.Add(CCameraPosition(-32.0f, -17.0f, 25.0f, 48.0f, 56.5f, 38.6f));
	// m_Positions.Add(CCameraPosition(-229.0f, 121.0f, 176.0f, 48.0f, 123.5f, 38.6f));
	m_Positions.Add(CCameraPosition(-32.0f, 17.0f, 25.0f, 48.0f, 123.5f, 38.6f));
}

void CCamera::UpdatePerspective(void)
{
	float ax = (float)fabs(m_Position.m_X);
	float ay = (float)fabs(m_Position.m_Y);
	float az = m_Position.m_Z;

	if (ax < 150.0f)
	{
		if (ay < 80.0f)
			m_Near = az - 5.0f; 
		else
			m_Near = (float)sqrt(SQR(ay-80) + SQR(az-5));
	}
	else
	{
		if (ay < 80.0f)
			m_Near = (float)sqrt(SQR(ax-150.0f)+SQR(az-5.0f));
		else
			m_Near = (float)sqrt(SQR(ax-150.0f)+SQR(ay-80.0f)+SQR(az-5.0f));
	}

	m_Near *= 0.8f;

	if (m_Near < 1.0f)
		m_Near = 1.0f;

	m_Far = (float)sqrt(SQR(ax+150)+SQR(ay+80)+SQR(az));
}

int CCamera::Read(FILE *File)
{
	char Buffer[32];
	int ErrorFlag = 0, BeginFlag = 0, EndFlag = 0;

	while (!EndFlag && !ErrorFlag && (fscanf(File, "%s", Buffer) == 1))
	{
		if (!BeginFlag)
		{
			if (stricmp(Buffer, "BEGIN") == 0)
				BeginFlag = 1;
		}
		else
		{
			if (!EndFlag)
			{
				if (stricmp(Buffer, "MOVE_FACTOR") == 0)
					ErrorFlag = fscanf(File, "%f", &m_MoveFactor) != 1;

				else if (stricmp(Buffer, "ROLL_FACTOR") == 0)
					ErrorFlag = fscanf(File, "%f", &m_RollFactor) != 1;

				else if (stricmp(Buffer, "FLY_FACTOR") == 0)
					ErrorFlag = fscanf(File, "%f", &m_FlyFactor) != 1;

				else if (stricmp(Buffer, "BALL_INDEX") == 0)
					ErrorFlag = fscanf(File, "%f", &m_BallIndex) != 1;

				else if (stricmp(Buffer, "MIN") == 0)
					ErrorFlag = !m_Min.Read(File);

				else if (stricmp(Buffer, "MAX") == 0)
					ErrorFlag = !m_Max.Read(File);

				else if (stricmp(Buffer, "TARGET") == 0)
					ErrorFlag = !m_Target.Read(File);

				else if (stricmp(Buffer, "POSITION") == 0)
					ErrorFlag = !m_Position.Read(File);

				else if (stricmp(Buffer, "POSITIONS") == 0)
				{
					CCameraPosition Position;

					if (!(ErrorFlag = !Position.Read(File)))
						m_Positions.Add(Position);
				}

				else if (stricmp(Buffer, "END") == 0)
					EndFlag = 1;
			}
		}
	}

	return EndFlag;
}

int CCamera::Write(FILE *File, const CString &TabFill)
{
	fprintf(File, "%sBEGIN\n", TabFill);

	fprintf(File, "%s\tMOVE_FACTOR %f\n", TabFill, m_MoveFactor);
	fprintf(File, "%s\tROLL_FACTOR %f\n", TabFill, m_RollFactor);
	fprintf(File, "%s\tFLY_FACTOR %f\n", TabFill, m_FlyFactor);
	fprintf(File, "%s\tBALL_INDEX %d\n", TabFill, m_BallIndex);

	fprintf(File, "%s\tMIN\n", TabFill);
	if (!m_Min.Write(File, TabFill + "\t"))
		return 0;

	fprintf(File, "%s\tMAX\n", TabFill);
	if (!m_Max.Write(File, TabFill + "\t"))
		return 0;

	fprintf(File, "%s\tTARGET\n", TabFill);
	if (!m_Target.Write(File, TabFill + "\t"))
		return 0;

	fprintf(File, "%s\tPOSITION\n", TabFill);
	if (!m_Position.Write(File, TabFill + "\t"))
		return 0;

	for (int i = 0; i < (int)m_Positions.GetCount(); i++)
	{
		fprintf(File, "%s\tPOSITIONS\n", TabFill);
		if (!m_Positions[i].Write(File, TabFill + "\t"))
			return 0;
	}

	fprintf(File, "%sEND\n", TabFill);
	return 1;
}

void CCamera::Run(float Time)
{
	if (m_BallIndex > -1)
	{
		CBalls &Balls = SnookerApp.m_Billard.m_Balls;
		CBall &Ball = Balls[m_BallIndex];

		if (!Ball.GetRender())
			SetBall(-1);
		else
		{
			int BallIndex = m_BallIndex;
			LookAt(Ball.GetPosition());
			m_BallIndex = BallIndex;
		}
	}

	m_Position.MoveTo(Time, m_Target);
	UpdatePerspective();
}

void CCamera::LoadPosition(int Index)
{
	m_Target = m_Positions[Index];
}

void CCamera::StorePosition(int Index)
{
	m_Positions[Index] = m_Target;
}

int CCamera::Load(const CString FileName)
{
	FILE *File;

	if ((File = fopen(FileName, "rt")) != NULL)
	{
		m_Positions.RemoveAll();
		int r = Read(File);
		fclose(File);
		return r;
	}

	return 0;
}

int CCamera::Save(const CString FileName)
{
	FILE *File;

	if ((File = fopen(FileName, "wt")) != NULL)
	{
		int r = Write(File);
		fclose(File);
		return r;
	}

	return 0;
}

void CCamera::MoveForward(float Factor)
{
	m_Target.m_X += 2.0f * m_MoveFactor * Factor * 
		(float)sin(m_Target.m_Beta / 57.29578);
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);

	m_Target.m_Y += 2.0f * m_MoveFactor * Factor * 
		(float)cos(m_Target.m_Beta / 57.29578);
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::MoveBackward(float Factor)
{
	MoveForward(-Factor);
}

void CCamera::MoveIn(float Factor)
{
	float TempAlpha = (float)sin(m_Target.m_Alpha / 57.29578);
	float TempBeta = (float)cos(m_Target.m_Beta / 57.29578);

	m_Target.m_X += 2.0f * m_MoveFactor * Factor * 
		(float)sin(m_Target.m_Alpha / 57.29578) * (float)sin(m_Target.m_Beta / 57.29578);
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);

	m_Target.m_Y += 2.0f * m_MoveFactor * Factor * 
		(float)sin(m_Target.m_Alpha / 57.29578) * (float)cos(m_Target.m_Beta / 57.29578);;
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);

	m_Target.m_Z -= 2.0f * m_MoveFactor * Factor * 
		(float)(cos(m_Target.m_Alpha / 57.29578));
	m_Target.m_Z = FLOAT_MID(m_Target.m_Z, m_Min.m_Z, m_Max.m_Z);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::MoveOut(float Factor)
{
	MoveIn(-Factor);
}

void CCamera::MoveUp(float Factor)
{
	m_Target.m_Z += m_MoveFactor * Factor;
	m_Target.m_Z = FLOAT_MID(m_Target.m_Z, m_Min.m_Z, m_Max.m_Z);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::MoveDown(float Factor)
{
	MoveUp(-Factor);
}

void CCamera::MoveLeft(float Factor)
{
	m_Target.m_X -= m_MoveFactor * Factor *
		(float)cos(m_Target.m_Beta / 57.29578);
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);

	m_Target.m_Y += m_MoveFactor * Factor * 
		(float)sin(m_Target.m_Beta/57.29578);
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::MoveRight(float Factor)
{
	MoveLeft(-Factor);
}

void CCamera::ZoomIn(float Factor)
{
	m_Target.m_FOV -= m_MoveFactor * Factor;
	m_Target.m_FOV = FLOAT_MID(m_Target.m_FOV, m_Min.m_FOV, m_Max.m_FOV);
	SetBall(-1);
}

void CCamera::ZoomOut(float Factor)
{
	ZoomIn(-Factor);
}

void CCamera::RollUp(float Factor)
{
	m_Target.m_Alpha += m_RollFactor * Factor;
	m_Target.m_Alpha = FLOAT_MID(m_Target.m_Alpha, m_Min.m_Alpha, m_Max.m_Alpha);
	SetBall(-1);
}

void CCamera::RollDown(float Factor)
{
	RollUp(-Factor);
}

void CCamera::RollLeft(float Factor)
{
	m_Target.m_Beta -= m_RollFactor * Factor;
	SetBall(-1);
}

void CCamera::RollRight(float Factor)
{
	RollLeft(-Factor);
}

void CCamera::AroundUp(float Factor, const CVector &Point)
{
	float Distance = (CVector(m_Position.m_X, 
		m_Position.m_Y, m_Position.m_Z) - Point).Length();

	if (FLOAT_EQ(Distance, 0.0f))
		m_Target.m_Alpha = 0.0f;
	else
		m_Target.m_Alpha -= m_RollFactor * Factor * 7.338f / (float)sqrt(Distance);

	Distance = FLOAT_MIN(Distance, 1.0f);

	m_Target.m_Alpha = FLOAT_MID(m_Target.m_Alpha, m_Min.m_Alpha, m_Max.m_Alpha);

	m_Target.m_X = Point.m_X - Distance * (float)
		(sin(m_Target.m_Beta / 57.29578) * sin(m_Target.m_Alpha / 57.29578));
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);

	m_Target.m_Y = Point.m_Y - Distance * (float)
		(cos(m_Target.m_Beta / 57.29578) * sin(m_Target.m_Alpha / 57.29578));
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);

	m_Target.m_Z = Point.m_Z + Distance * (float)cos(m_Target.m_Alpha / 57.29578);
	m_Target.m_Z = FLOAT_MID(m_Target.m_Z, m_Min.m_Z, m_Max.m_Z);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::AroundDown(float Factor, const CVector &Point)
{
	AroundUp(-Factor, Point);
}

void CCamera::AroundLeft(float Factor, const CVector &Point)
{
	float Distance = (Point - CVector(m_Target.m_X, 
		m_Target.m_Y, 0.0f)).Length();

	Distance = FLOAT_MIN(Distance, 1.0f);

	m_Target.m_Beta += m_RollFactor * Factor * 7.338f / (float)sqrt(Distance);

	m_Target.m_X = Point.m_X - Distance * (float)sin(m_Target.m_Beta / 57.29578);
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);

	m_Target.m_Y = Point.m_Y - Distance * (float)cos(m_Target.m_Beta / 57.29578);
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);

	SetBall(-1);
	UpdatePerspective();
}

void CCamera::AroundRight(float Factor, const CVector &Point)
{
	AroundLeft(-Factor, Point);
}

void CCamera::LookAt(const CVector &Point)
{
	CCameraPosition Target;

	float Temp = (float)sqrt(SQR(m_Position.m_X-Point.m_X)
		+ SQR(m_Position.m_Y-Point.m_Y));

	Target.m_X = 8.0f * (m_Position.m_X - Point.m_X) / Temp + Point.m_X;
	Target.m_Y = 8.0f * (m_Position.m_Y - Point.m_Y) / Temp + Point.m_Y;
	Target.m_Z = Point.m_Z + 3.0f;

	Target.m_Alpha = 70.0f;
	Target.m_Beta = (float)(atan((Point.m_X - Target.m_X)/(Point.m_Y - Target.m_Y))*180.0f/PI);

	if (Target.m_Y > Point.m_Y)
		Target.m_Beta -= 180.0f;

	Target.m_FOV = 38.6f;

	SetPosition(Target);
	SetBall(-1);
}

void CCamera::SetBall(int BallIndex)
{
	m_BallIndex = BallIndex;
}

void CCamera::SetPosition(const CCameraPosition &Position)
{
	m_Target = Position;
	m_Target.m_X = FLOAT_MID(m_Target.m_X, m_Min.m_X, m_Max.m_X);
	m_Target.m_Y = FLOAT_MID(m_Target.m_Y, m_Min.m_Y, m_Max.m_Y);
	m_Target.m_Z = FLOAT_MID(m_Target.m_Z, m_Min.m_Z, m_Max.m_Z);
	m_Target.m_Alpha = FLOAT_MID(m_Target.m_Alpha, m_Min.m_Alpha, m_Max.m_Alpha);

	m_Position.m_Beta = (float)fmod(m_Position.m_Beta, 360.0f);
	m_Target.m_Beta = (float)fmod(m_Target.m_Beta, 360.0f);
	
	if (m_Target.m_Beta > (m_Position.m_Beta + 180.0f))
		m_Target.m_Beta-= 360.0f;

	if (m_Target.m_Beta < (m_Position.m_Beta - 180.0f))
		m_Target.m_Beta += 360.0f;

	SetBall(-1);
}

void CCamera::FlyAround(float Time)
{
	m_Target.m_Beta += m_FlyFactor * Time;

	m_Target.m_X = -40.0f * (float)sin(m_Target.m_Beta*PI/180.0);
	m_Target.m_Y = -40.0f * (float)cos(m_Target.m_Beta*PI/180.0);

	m_Target.m_Z = 10.0f;
	m_Target.m_FOV = 36.8f;

	m_Target.m_Alpha = (float)(atan(sqrt(SQR(m_Target.m_X) + 
		SQR(m_Target.m_Y))/m_Target.m_Z)) * 180.0f / PI;
}
