
/** @file Billard.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy billarda CBillard.
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Billard.h"
#include <stdlib.h>
#include <math.h>
#include "Sound.h"

// CBillard

CBillard::CBillard()
	: m_State(bsStart)
	, m_Running(0)
	, m_Pause(0)
	, m_ColorCount(0)
	, m_ColorLeftCount(0)
	, m_RedCount(0)
	, m_RedLeftCount(0)
	, m_StrikerIndex(-1)
	, m_WhiteIndex(-1)
	, m_Force(0.0f)
{
	// inicjuj generator licz pseudolosowych
	srand((unsigned)time(NULL));
}

int CBillard::Read(FILE *File)
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
				// jesli tak ,to ustaw flage odczytania slowa BEGIN
				BeginFlag = 1;
		}
		else
		{
			// czy nie odczytano juz slowa END
			if (!EndFlag)
			{
				// czy jest to slowo STATE
				if (stricmp(Buffer, "STATE") == 0)
					// odczytaj stan gry
					ErrorFlag = fscanf(File, "%d", &m_State) != 1;

				// czy jest to slowo STRIKER_INDEX
				else if (stricmp(Buffer, "STRIKER_INDEX") == 0)
					// odczytaj indeks rozgrywajacego
					ErrorFlag = fscanf(File, "%d", &m_StrikerIndex) != 1;

				// czy jest to slowo PLAYER
				else if (stricmp(Buffer, "PLAYER") == 0)
				{
					CPlayer Player;

					// odczytaj kolejnego gracza
					if (!(ErrorFlag = !Player.Read(File)))
					{
						// dodaj gracza do tablicy
						m_Players.Add(Player);
					}
				}

				// czy jest to slowo BALL
				else if (stricmp(Buffer, "BALL") == 0)
				{
					CBall Ball;

					// odczytaj kolejna bile
					if (!(ErrorFlag = !Ball.Read(File)))
					{
						// dodaj bile do tablicy
						int Index = (int)m_Balls.Add(Ball);

						// jaka bile wczytano
						switch (Ball.m_Type)
						{
						case btWhite: // biala
							// zapamietaj indeks bialej bili
							m_WhiteIndex = Index;
							break;

						case btRed: // czerwona
							// zwieksz licznik czerwonych bil
							m_RedCount++;
							// czy bila nie zostala wbita
							if (!Ball.GetKnockedIn())
								// zwieksz licznik pozostalych czerwonych bil
								m_RedLeftCount++;
							break;

						case btColor: // kolorowa
							// zwieksz licznik kolorowych bil
							m_ColorCount++;
							// czy bila nie zostala wbita
							if (!Ball.GetKnockedIn())
								// zwieksz licznik pozostalych kolorowych bil
								m_ColorLeftCount++;
							break;
						}
					}
				}

				// czy jest to slowo TRIANGLE
				else if (stricmp(Buffer, "TRIANGLE") == 0)
				{
					CTriangle Triangle;

					// odczytaj kolejny trojkat
					if (!(ErrorFlag = !Triangle.Read(File)))
						m_Triangles.Add(Triangle);
				}

				// czy jest to slowo CAMERA
				else if (stricmp(Buffer, "CAMERA") == 0)
				{
					// odczytaj kamera
					ErrorFlag = !SnookerApp.m_Camera.Read(File);
				}

				// czy jest to slowo END
				else if (stricmp(Buffer, "END") == 0)
					// ustaw flage odczytania slowa END
					EndFlag = 1;
			}
		}
	}

	// zwroc flage END
	return EndFlag;
}

int CBillard::Write(FILE *File, const CString &TabFill)
{
	// zapisz slowo BEGIN
	fprintf(File, "%sBEGIN\n", TabFill);
	// zapisz stan gry
	fprintf(File, "%s\tSTATE %d\n", TabFill, m_State);
	// zapisz indeks rozgrywajacego
	fprintf(File, "%s\tSTRIKER_INDEX %d\n", TabFill, m_StrikerIndex);

	// zapisz graczy
	for (int i = 0; i < (int)m_Players.GetCount(); i++)
	{
		fprintf(File, "\n%s\tPLAYER\n", TabFill);
		if (!m_Players[i].Write(File, TabFill + "\t"))
			return 0;
	}

	// zapisz ustawienia kamery
	fprintf(File, "%s\tCAMERA\n", TabFill);
	SnookerApp.m_Camera.Write(File, TabFill + "\t");

	// zapisz bile
	for (int i = 0; i < (int)m_Balls.GetCount(); i++)
	{
		fprintf(File, "\n%s\tBALL\n", TabFill);
		if (!m_Balls[i].Write(File, TabFill + "\t"))
			return 0;
	}

	// zapisz trojkaty
	for (int i = 0; i < (int)m_Triangles.GetCount(); i++)
	{
		fprintf(File, "\n%s\tTRIANGLE\n", TabFill);
		if (!m_Triangles[i].Write(File, TabFill + "\t"))
			return 0;
	}

	// zapisz slowo END
	fprintf(File, "%sEND\n", TabFill);
	return 1;
}

void CBillard::NewGame(const CPlayers &Players)
{
	// ustaw graczy
	m_Players.RemoveAll();
	m_Players.Append(Players);

	// przywroc wszystkie bile na swoje miejsca
	Reset();

	// pozostaly wszystkie kolorowe bile
	m_ColorLeftCount = m_ColorCount;

	// pozostaly wszystkie czerwone bile
	m_RedLeftCount = m_RedCount;

	// domyslnie ustaw trening
	m_StrikerIndex = -1;

	// czy podano graczy?
	if ((int)m_Players.GetCount() > 0)
	{
		m_StrikerIndex = 0;
		m_Players[m_StrikerIndex].SetState(psBallInHand);
	}

	// ustaw stan gry na widok
	SetState(bsView);
	SnookerApp.m_Camera.LoadPosition(3);
}

int CBillard::LoadGame(const CString FileName)
{
	FILE *File;

	// otworz plik do czytania
	if ((File = fopen(FileName, "rt")) != NULL)
	{
		// usun wszystkie bile
		m_Balls.RemoveAll();

		// usun wszystkich graczy
		m_Players.RemoveAll();

		// usun wszystkie trojkaty
		m_Triangles.RemoveAll();

		// odczytaj dane z pliku
		int Result = Read(File);

		// zamknij plik
		fclose(File);

		// zwroc wynik odczytania danych
		return Result;
	}

	// zwroc zero - nie udalo sie wczytac
	return 0;
}

int CBillard::SaveGame(const CString FileName)
{
	FILE *File;

	// otworz plik do zapisu
	if ((File = fopen(FileName, "wt")) != NULL)
	{
		// zapisz dane do pliku
		int Result = Write(File);

		// zamknij plik
		fclose(File);

		// zwroc wynik zapisania
		return Result;
	}

	// zwroc zero - nie udalo sie zapisac
	return 0;
}

void CBillard::Run(float Time)
{
	// jaki stan gry?
	switch (m_State)
	{
	case bsStart: // gra jeszcze nie rozpoczeta
	case bsOver: // gra zakonczona
		// obracaj kamere dookola stolu
		SnookerApp.m_Camera.FlyAround(Time);
		break;

	default: // inny stan
        // przetworz klawiature i myszke
		ProcessControls(Time);
		break;
	}

	if (m_Pause)
		return;

	// przyloz sily do bil (grawitacja, tarcie)
	if (ApplyForces(Time))
	{
		// bile jeszcze sie tocza, czy znacznik trwania symulacji ustawiony?
		if (!m_Running)
		{
			// ustaw znacznik trwania symulacji
			m_Running = TRUE;

			// wywolaj funkcje z klasy CBillard
			OnStart();
		}
	}
	else
	{
		// zadna bila juz sie nie toczy, czy znacznik trwania symulacji wyzerowany?
		if (m_Running)
		{
			// wyzeruj znacznik trwania symulacji
			m_Running = FALSE;

			// wywolaj funkcje z klasy CBillard
			OnStop();
		}
	}

	if (!m_Running)
		return;

	float FullTime = Time, PrevTime = Time;

	// glowna petla symulacji
	while (Time > EPSILON)
	{
		int TriangleCollision, BallsCollision;
		int Ball = -1, Triangle = -1, Ball1 = -1, Ball2 = -1;
		float TriangleTime = Time, BallsTime = Time;

		// przesun bile
		Simulate(Time);

		// sprawdzanie kolizji z bandami
		TriangleCollision = FindTriangleCollision(Time, TriangleTime, Ball, Triangle);

		// sprawdzanie kolizji miedzy bilami
		BallsCollision = FindBallsCollision(Time, BallsTime, Ball1, Ball2);

		// czy wykryto kolizje miedzy bilami?
		if (BallsCollision)
		{
			// czy nie wykryto kolizji z banda lub czas kolizji
			// z banda jest wiekszy od czasu kolizji miedzy bilami?
			if (!TriangleCollision || (TriangleTime > BallsTime))
			{
				ASSERT((Ball1 != -1) && (Ball2 != -1));

				CBall &Ball1a = m_Balls[Ball1];
				CBall &Ball2a = m_Balls[Ball2];

				// ustaw czas na czas po kolizji miedzy bilami
				Time -= BallsTime;

				// przywroc pozycje bil przed symulacja
				Restore();

				// wywolaj funkcje z klasy CBillard
				OnCollision(Ball1a, Ball2a);

				float Volume = Ball1a.m_Velocity.Length() + Ball2a.m_Velocity.Length();
				
				Sound.Play(SAMPLES_BALL2BALL, (long)((DSBVOLUME_MIN / 2) + 
					(DSBVOLUME_MAX - DSBVOLUME_MIN) * Volume / 20.0f));

				// przesun do punktu kolizji
				Simulate(BallsTime);

				// wykonaj odbicie
				Ball1a.Reflect(Ball2a);

				// powtorz obliczenia dla nowego czasu
				continue;
			}
		}

		// czy wykryto kolizje z banda?
		if (TriangleCollision)
		{
			ASSERT((Ball != -1) && (Triangle != -1));

			CBall &Balla = m_Balls[Ball];
			CTriangle Trianglea = m_Triangles[Triangle];

			// ustaw czas na czas po kolizji z banda
			Time -= TriangleTime;

			// przywroc pozycje bil przed symulacja
			Restore();

			// czy trojkatem jest dolkiem?
			if (Trianglea.GetHole())
			{
				// wywolaj funkcje wbicia bili
				OnKnockIn(Balla);

				float Volume = Balla.m_Velocity.Length();
				
				Sound.Play(SAMPLES_BALL2HOLE, (long)((DSBVOLUME_MIN / 2) + 
					(DSBVOLUME_MAX - DSBVOLUME_MIN) * Volume / 10.0f));
			}
			else
			{
				float Volume = Balla.m_Velocity.Length();
				
				Sound.Play(SAMPLES_BALL2BAND, (long)((DSBVOLUME_MIN / 2)+ 
					(DSBVOLUME_MAX - DSBVOLUME_MIN) * Volume / 10.0f));
			}

			// przesun do punktu kolizji
			Simulate(TriangleTime);

			// wykonaj odbicie
			Balla.Reflect(Trianglea);
		}
		else
		{
			// nie wykryto kolizji -- zakoncz petle
			break;
		}

		// ASSERT(!FLOAT_EQ_EPS(Time, PrevTime, 0.0001f));
		PrevTime = Time;
	}
}

void CBillard::ProcessControls(float Time)
{
	CKeyboard &Keyboard = SnookerApp.m_Keyboard;
	CCamera &Camera = SnookerApp.m_Camera;
	CMouse &Mouse = SnookerApp.m_Mouse;

	// uaktualnij klawiature
	Keyboard.Update(m_State);
	// uaktualnij myszke
	Mouse.Update(m_State);

	// gwiazdka
	if (Keyboard.m_State[VK_MULTIPLY])
		SnookerApp.m_Render.SetQuadricStyle(GLU_FILL);
	// dzielenie
	else if (Keyboard.m_State[VK_DIVIDE])
		SnookerApp.m_Render.SetQuadricStyle(GLU_LINE);

	// czy gracz zwieksza sile uderzenia
	if (Keyboard.Shot)
	{
		// wyznacz krok wzrostu sily
		float Step = ((float)rand() / RAND_MAX) * Time;
		// wyznacz aktualna pozycje sily
		float T = m_Force / MAX_FORCE;

		// zwieksz sile w sposob zwalniajacy ze wzrostem i losowy
		m_Force += (20.0f - (10.f*T))*(1-T) + (Step - (Step/2.0f))*T;
		// wlacz renderowanie paska
		SnookerApp.m_Render.m_RenderBar = 1;

		// czy przekroczono wartosc maksymalna
		if (m_Force >= MAX_FORCE)
		{
			// ustaw wartosc maksymalna
			m_Force = MAX_FORCE;
			// zwolnij klawisz uderzenia
			Keyboard.Shot = 0;
		}
	}
	else
	{
		// czy wczesniej sila byla niezerowa
		if (m_Force > 0.0f)
		{
			// czy istnieje w liscie biala bila
			ASSERT(m_WhiteIndex > -1);

			// pobierz pozycje kamery i bili
			const CCameraPosition &Position = Camera.GetPosition();
			CVector Vector = m_Balls[m_WhiteIndex].GetPosition();

			Sound.Play(SAMPLES_STICK2BALL, (long)((DSBVOLUME_MIN / 2) + 
				(DSBVOLUME_MAX - DSBVOLUME_MIN) * m_Force / MAX_FORCE));

			// wyznacz wektor przylozenia sily
			Vector -= CVector(Position.GetX(), Position.GetY(), Vector.m_Z);
			Vector.Normalize();
			Vector *= m_Force;
			m_Force = 0;
			SnookerApp.m_Render.m_RenderBar = 0;

			// dodaj sile do bialej bili
			m_Balls[m_WhiteIndex].AddForce(Vector);
			m_Running = 1;

			// przejdz do nastepnego stanu
			NextState();

			// podnies sie znad stolu
			CCameraPosition Target = Camera.GetPosition();
			if (Target.m_Z < 5.0f)
				Target.m_Z = 5.0f;
			Camera.SetPosition(Target);
		}
		else
		{
			if (Keyboard.CameraMoveIn)
				Camera.MoveIn(Time);
			else if (Keyboard.CameraMoveOut)
				Camera.MoveOut(Time);

			if (Keyboard.CameraMoveForward)
				Camera.MoveForward(Time);
			else if (Keyboard.CameraMoveBackward)
				Camera.MoveBackward(Time);

			if (Keyboard.CameraMoveUp)
				Camera.MoveUp(Time);
			else if (Keyboard.CameraMoveDown)
				Camera.MoveDown(Time);

			if (Keyboard.CameraMoveLeft)
				Camera.MoveLeft(Time);
			else if (Keyboard.CameraMoveRight)
				Camera.MoveRight(Time);

			if (Keyboard.CameraZoomIn)
				Camera.ZoomIn(Time);
			else if (Keyboard.CameraZoomOut)
				Camera.ZoomOut(Time);

			if (Keyboard.CameraRollUp)
				Camera.RollUp(Time);
			else if (Keyboard.CameraRollDown)
				Camera.RollDown(Time);

			if (Keyboard.CameraRollLeft)
				Camera.RollLeft(Time);
			else if (Keyboard.CameraRollRight)
				Camera.RollRight(Time);

			if (Mouse.CameraMoveIn)
				Camera.MoveIn(Mouse.CameraMoveIn * Mouse.Speed);
			else if (Mouse.CameraMoveOut)
				Camera.MoveOut(Mouse.CameraMoveOut * Mouse.Speed);

			if (Mouse.CameraMoveForward)
				Camera.MoveForward(Mouse.CameraMoveForward * Mouse.Speed);
			else if (Mouse.CameraMoveBackward)
				Camera.MoveBackward(Mouse.CameraMoveBackward * Mouse.Speed);

			if (Mouse.CameraMoveUp)
				Camera.MoveUp(Mouse.CameraMoveUp * Mouse.Speed);
			else if (Mouse.CameraMoveDown)
				Camera.MoveDown(Mouse.CameraMoveDown * Mouse.Speed);

			if (Mouse.CameraMoveLeft)
				Camera.MoveLeft(Mouse.CameraMoveLeft * Mouse.Speed);
			else if (Mouse.CameraMoveRight)
				Camera.MoveRight(Mouse.CameraMoveRight * Mouse.Speed);

			if (Mouse.CameraZoomIn)
				Camera.ZoomIn(Mouse.CameraZoomIn * Mouse.Speed);
			else if (Mouse.CameraZoomOut)
				Camera.ZoomOut(Mouse.CameraZoomOut * Mouse.Speed);

			if (Mouse.CameraRollUp)
				Camera.RollUp(Mouse.CameraRollUp * Mouse.Speed);
			else if (Mouse.CameraRollDown)
				Camera.RollDown(Mouse.CameraRollDown * Mouse.Speed);

			if (Mouse.CameraRollLeft)
				Camera.RollLeft(Mouse.CameraRollLeft * Mouse.Speed);
			else if (Mouse.CameraRollRight)
				Camera.RollRight(Mouse.CameraRollRight * Mouse.Speed);

			if (m_WhiteIndex > -1)
			{
				CBall &Ball = m_Balls[m_WhiteIndex];
				const CVector &BallPos = Ball.GetPosition();
				const CCameraPosition &Position = Camera.GetPosition();
				CVector Direction = Ball.GetPosition() - 
					CVector(Position.GetX(), Position.GetY(), Ball.m_Position.m_Z);

				// odleglosc kamery od bili
				float Distance = Direction.Length();

				if (Keyboard.CameraAroundUp)
					Camera.AroundUp(Time * (Distance / 32.0f), BallPos);
				else if (Keyboard.CameraAroundDown)
					Camera.AroundDown(Time * (Distance / 32.0f), BallPos);

				if (Keyboard.CameraAroundLeft)
					Camera.AroundLeft(Time * (Distance / 32.0f), BallPos);
				else if (Keyboard.CameraAroundRight)
					Camera.AroundRight(Time * (Distance / 32.0f), BallPos);

				if (Mouse.CameraAroundUp)
					Camera.AroundUp(Mouse.CameraAroundUp * Mouse.Speed, BallPos);
				else if (Mouse.CameraAroundDown)
					Camera.AroundDown(Mouse.CameraAroundDown * Mouse.Speed, BallPos);

				if (Mouse.CameraAroundLeft)
					Camera.AroundLeft(Mouse.CameraAroundLeft * Mouse.Speed * (Distance / 32.0f), BallPos);
				else if (Mouse.CameraAroundRight)
					Camera.AroundRight(Mouse.CameraAroundRight * Mouse.Speed * (Distance / 32.0f), BallPos);

				if (m_State == bsBallInHand)
				{
					if ((Keyboard.BallMoveForward || Keyboard.BallMoveBackward || 
						Keyboard.BallMoveLeft || Keyboard.BallMoveRight))
					{
						Direction.Normalize();
						CVector Cross = Direction * CVector(0.0f, 0.0f, 1.0f);
						Cross.Normalize();
						Direction *= 5.0f;
						Cross *= 5.0f;

						if (Keyboard.BallMoveForward)
							//Ball.m_Velocity += Direction;
							Ball.AddForce(Direction);
						else if (Keyboard.BallMoveBackward)
							//Ball.m_Velocity += -Direction;
							Ball.AddForce(-Direction);

						if (Keyboard.BallMoveLeft)
							// Ball.m_Velocity += -Cross;
							Ball.AddForce(-Cross);
						else if (Keyboard.BallMoveRight)
							// Ball.m_Velocity += Cross;
							Ball.AddForce(Cross);

						Camera.SetBall(m_WhiteIndex);
					}
					else
					{
						Ball.m_Velocity.Zero();
					}
				}
			}

			if (Keyboard.NextState)
				NextState();
			else if (Keyboard.PrevState)
				PreviousState();
		}
	}
}

void CBillard::NextState(void)
{
	// czy trwa jeszcze symulacja
	if (m_Running)
		// jesli tak, to nie zmieniaj stanu
		return;

	// jaki jest aktualny stan
	switch (m_State)
	{
	case bsView: // widok
		// przejdz do celowania
		SetState(bsAim);

		// czy jest to gra dwuosobowa
		if (m_StrikerIndex > -1)
		{
			// pobierz rozgrywajacego
			CPlayer &Striker = m_Players[m_StrikerIndex];

			// czy rozgrywajacy ma bile w rece?
			if (Striker.GetState() == psBallInHand)
				// jesli tak, to przejdz do ustawiania bialej bili
				SetState(bsBallInHand);
		}
		else
		{
			// jesli trening, przejdz do ustawiania bialej bili
			SetState(bsBallInHand);
		}
		break;

	case bsBallInHand: // bila w rece
		// przejdz do celowania
		SetState(bsAim);
		break;

	case bsAim: // celowanie
		// przejdz do strzalu
		SetState(bsShot);
		break;

	case bsShot: // strzal
		// przejdz do widoku
		SetState(bsView);
		break;
	}
}

void CBillard::PreviousState(void)
{
	// czy trwa jeszcze symulacja
	if (m_Running)
		// jesli tak, to nie zmieniaj stanu
		return;

	// jaki jest aktualny stan?
	switch (m_State)
	{
	case bsView: // widok
		// nic nie zmieniaj
		break;

	case bsBallInHand: // bila w rece
		// przejdz do widoku
		SetState(bsView);
		break;

	case bsAim: // celowanie
		// przejdz do widoku
		SetState(bsView);

		// czy gra jest dwuosobowa
		if (m_StrikerIndex > -1)
		{
			// pobierz rozgrywajacego
			CPlayer &Striker = m_Players[m_StrikerIndex];

			// czy rozgrywajacy ma biala bile w rece
			if (Striker.GetState() == psBallInHand)
				// jesli tak, to przejdz do ustawiania bialej bili
				SetState(bsBallInHand);
		}
		else
		{
			// jesli gra treningowa, to przejdz ustawiania bialej bili
			SetState(bsBallInHand);
		}
		break;

	case bsShot: // strzal
		// nic nie zmieniaj
		break;
	}
}

void CBillard::SetState(CBillardState State)
{
	// czy trwa jeszcze symulacja
	if (m_Running)
		// jesli tak, to nie zmieniaj stanu
		return;

	// czy nastapila zmiana stau?
	if (m_State != State)
	{
		// jaki jest aktualny stan?
		switch (m_State)
		{
		case bsBallInHand: // bila w rece
			// wlacz symulacje pozostalych bil
			for (int i = 0; i < (int)m_Balls.GetCount(); i++)
			{
				// pobierz i-ta bile
				CBall &Ball = m_Balls[i];

				// czy bila jest rozna od bialej
				if (Ball.GetType() != btWhite)
					// wlacz symulacje
					Ball.m_Simulate = 1;
			}
			break;
		}

		// jaki jest nowy stan?
		switch (State)
		{
		case bsBallInHand: // bila w rece
			// wylacz symulacje pozostalych bil
			for (int i = 0; i < (int)m_Balls.GetCount(); i++)
			{
				// pobierz i-ta bile
				CBall &Ball = m_Balls[i];

				// czy bila jest rozna od bialej
				if (Ball.GetType() != btWhite)
					// wylacz symulacje
					Ball.m_Simulate = 0;
			}
			// skieruj kamere na biala bile
			SnookerApp.m_Camera.SetBall(m_WhiteIndex);
			break;

		case bsAim: // celowanie
			// skieruj kamere na biala bile
			SnookerApp.m_Camera.SetBall(m_WhiteIndex);
			break;
		}

		// zapamietaj nowy stan
		m_State = State;
	}
}

void CBillard::OnStart(void)
{
	// czy stan gry - bila w rece
	if (m_State == bsBallInHand)
		// nie wykonuj rozpoczecia strzalu
		return;

	// czy gra jest dwuosobowa
	if (m_StrikerIndex > -1)
	{
		// pobierz rozgrywajacego
		CPlayer &Striker = m_Players[m_StrikerIndex];

		// wyzerowanie licznika punktow zdobytych przy uderzeniu
		Striker.SetBreak(0);

		// jaki jest stan rozgrywajacego
		switch (Striker.GetState())
		{
		case psBallInHand: // bila w rece
			// to zabierz ja
			Striker.SetState(psNone);
			break;
		}
	}

	// wyczysc flage kolizji
	m_Collision = 0;

	// ustaw stan na strzal
	SetState(bsShot);
}

void CBillard::OnStop(void)
{
	// czy stan gry - bila w rece
	if (m_State == bsBallInHand)
		// nie wykonuj zakonczenia strzalu
		return;

	// czy istnieje biala bila
	if (m_WhiteIndex > -1)
	{
		// czy wbito biala bile
		if (m_Balls[m_WhiteIndex].m_KnockedIn)
			// przywroc biala bile na oryginalnego miejsce
			Reset(m_WhiteIndex);
	}

	// czy zostaly jeszcze czerwone bile
	if (m_RedLeftCount)
	{
		// przejdz przez wszystkie bile
		for (int i = 0; i < (int)m_Balls.GetCount(); i++)
		{
			// pobierz i-ta bile
			CBall &Ball = m_Balls[i];

			// czy bila jest wbita i jest to bila kolorowa
			if (Ball.m_KnockedIn && (Ball.m_Type == btColor))
				// przywroc bile na oryginalne miejsce
				Reset(i);
		}
	}

	// czy nie ma juz zadnych bil
	if (!m_RedLeftCount && !m_ColorLeftCount)
	{
		// przejdz do stanu zakonczenia gry
		SetState(bsOver);
	}
	else
	{
		// przejdz przez wszystkie bile
		for (int i = 0; i < (int)m_Balls.GetCount(); i++)
		{
			// pobierz i-ta bile
			CBall &Ball = m_Balls[i];

			// jesli wypadla poza stol
			if (Ball.m_OutOfBoard)
				// przywroc
				Reset(i);
		}

		// przejdz do widoku
		SetState(bsView);

		// czy jest to gra dwuosobowa
		if (m_StrikerIndex > -1)
		{
			// pobierz liczbe graczy
			int Count = (int)m_Players.GetCount();
			// zatrzymaj symulacje dla rozgrywajacego
			CPlayer &Striker = m_Players[m_StrikerIndex];

			// czy nastapila kolizja z jakakolwiek bila?
			if (!m_Collision && (Striker.GetState() != psWhiteKnockIn))
				// faul... zadna bila nie zostala dotknieta
				Striker.SetState(psFoul);

			// jaki jest stan gracza
			switch (Striker.GetState())
			{
			case psNone:
			case psRedKnockIn:
				// ustaw status rozgrywajacego na zerowy
				Striker.SetState(psNone);
				// czy rozgrywajacy wbil jakakolwiek bile
				if (Striker.GetBreak() > 0)
				{
					// dodaj liczbe punktow zdobytych w uderzeniu do wszystkich punktow
					Striker.SetScore(Striker.GetScore() + Striker.GetBreak());
					break;
				}

			case psFoul:
			case psWhiteKnockIn:
				// przejdz przez wszystkich graczy
				for (int i = 1, f = 0; (i <= (Count + 1)) && !f; i++)
				{
					// wyznacz indeks kolejnego gracza
					int Index = (m_StrikerIndex + i) % Count;
					// pobierz gracza
					CPlayer &Player = m_Players[Index];

					// jak jest aktualny stan Index-go gracza
					switch (Player.GetState())
					{
					case psNone:
						f = 1;
						// jesli sie udalo, zapamietaj indeks nowego rozgrywajacego
						m_StrikerIndex = Index;
						// czy rozgrywajacy popelnij faul
						if (Striker.GetState() == psFoul)
							// dodaj punkty z rozbic do punktow przeciwnika
							Player.SetScore(Player.GetScore() + Striker.GetBreak());
						// ustaw stan gracza, w zaleznosci od aktualnego stanu rozgrywajacego
						Player.SetState((Striker.GetState() == psWhiteKnockIn) ? psBallInHand : psNone);
						break;

					case psWhiteKnockIn:
					case psFoul:
						// jesli gracz mial faul lub wbil biala bile, to skasuj go
						Player.SetState(psNone);
						break;
					}
				}
				break;
			}
		}
	}
}

void CBillard::OnKnockIn(CBall &Ball)
{
	// czy stan gry - bila w rece
	if (m_State == bsBallInHand)
		// nie wykonuj zakonczenia strzalu
		return;

	if (m_StrikerIndex > -1)
	{
		// pobierz rozgrywajacego
		CPlayer &Striker = m_Players[m_StrikerIndex];

		// dodaj liczbe punktow bili do punktow zdobytych w tym uderzeniu
		Striker.SetBreak(Striker.GetBreak() + Ball.m_Score);

		// jaka bile wbito?
		switch (Ball.m_Type)
		{
		case btWhite: // biala
			// ustaw stan wbicia bialej bili
			Striker.SetState(psWhiteKnockIn);
			break;

		case btRed: // czerwona
			switch (Striker.GetState())
			{
			case psNone: // wczesniej nic nie wbil
				// ustaw stan wbicia czerwonej bili
				Striker.SetState(psRedKnockIn);
				break;

			case psRedKnockIn: // wczesniej juz wbil czerwona
				// ustaw faul - tylko jedna czerwona bile mozna wbic
				Striker.SetState(psFoul);
				break;
			}
			break;

		case btColor: // kolorowa
			switch (Striker.GetState())
			{
			case psNone: // wczesniej nic nie wbil
				// czy pozostaly jeszcze czerwone bile
				if (m_RedLeftCount)
				{
					// ustaw faul - najpierw trzeba wbic czerwona
					Striker.SetState(psFoul);
				}
				else
				{
					// przejdz przez wszystkie bile
					for (int i = 0; i < m_Balls.GetCount(); i++)
					{
						// pobierz i-ta bile
						const CBall &Balli = m_Balls[i];
						
						// czy bila jest kolorowa
						if (Balli.m_Type == btColor)
						{
							// czy bila nie jest wbita i ma mniej punktow niz ta wbita
							if (!Balli.m_KnockedIn && (Balli.m_Score < Ball.m_Score))
							{
								// jesli tak, to ustaw foul gracza
								Striker.SetState(psFoul);
							}
						}
					}
				}
				break;

			case psRedKnockIn: // wczesniej wbil czerwona bile
				// skasuj stan wbicia czerwonej bili
				Striker.SetState(psNone);
				break;
			}
		}
	}

	// sprawdz typ bili
	switch (Ball.m_Type)
	{
	case btRed: // czerwona
		// zmniejsz licznik czerwonych bil pozostajacych na stole
		m_RedLeftCount--;
		break;

	case btColor: // kolorowa
		// zmniejsz licznik kolorowych bil pozostajacych na stole
		m_ColorLeftCount--;
		break;
	}
}

void CBillard::OnCollision(CBall &Ball1, CBall &Ball2)
{
	// czy stan gry - bila w rece
	if (m_State == bsBallInHand)
		// nie wykonuj zakonczenia strzalu
		return;

	// czy gra jest dwuosobowa i jest to pierwsza kolizja bialej bili
	if ((m_StrikerIndex > -1) && !m_Collision)
	{
		CBall *Ball = NULL;

		// czy jedna z bil jest biala a druga nie
		if ((Ball1.m_Type == btWhite) && (Ball2.m_Type != btWhite))
			Ball = &Ball2;

		// czy jedna z bil nie jest biala a druga jest
		if ((Ball1.m_Type != btWhite) && (Ball2.m_Type == btWhite))
			Ball = &Ball1;

		// czy kolizja byl jednej bialej i innej bili
		if (Ball != NULL)
		{
			// jaka bile uderzyla biala bila
			switch (Ball->m_Type)
			{
			case btColor: // kolorowa
				// czy na stole sa jeszcze czerwone?
				if (m_RedLeftCount)
				{
					// pobierz rozgrywajacego
					CPlayer &Striker = m_Players[m_StrikerIndex];
					// jesli sa, to ustaw faul gracza
					Striker.SetState(psFoul);
				}
				break;
			}

			// ustaw flage kolizji
			m_Collision = 1;
		}
	}
}

int CBillard::ApplyForces(float Time)
{
	// wyzeruj znacznik aktywnosci symulacji
	int Running = 0;

	for (int i = 0; i < (int)m_Balls.GetCount(); i++)
	{
		// pobierz i-ta bile
		CBall &Ball = m_Balls[i];

		// czy symulacja bili wlaczona
		if (!Ball.GetSimulate())
			continue;

		if (Ball.m_Position.m_Z < -6.0f)
		{
			Ball.m_OutOfBoard = 1;
			Ball.m_Simulate = 0;
			Ball.m_Render = 0;
			continue;
		}

		if (!Ball.IsInTriangle() && !FindTriangle(Ball))
		{
			if ((m_State == bsBallInHand) && (m_WhiteIndex == i))
			{
				Ball.m_Position = Ball.m_PositionPrevious;
				Stop(m_WhiteIndex);
			}
			else
			{
				// przyloz sile grawitacji
				Ball.AddGravityForce();
			}
		}
		else
		{
			if ((m_State == bsBallInHand) && (m_WhiteIndex == i))
			{
				if (m_StrikerIndex > -1)
				{
					float x = Ball.m_Position.m_X;
					float y = Ball.m_Position.m_Y;

					// sprawdz czy biala bila wyszla poza strefe "D"
					if ((SQR(y) > (SQR(2.92f) - SQR(x - 10.475f))) || (x < 10.475f))
					{
						Ball.m_Position = Ball.m_PositionPrevious;
						Stop(m_WhiteIndex);
					}
				}
			}
		}

		// czy bila aktualnie porusza sie?
		if (Ball.IsMoving())
		{
			// ustaw znacznik aktywnosci symulacji
			Running = 1;

			// przyloz sile tarcia
			Ball.AddFrictionForce();
		}
		else
		{
			// zatrzymaj bile
			Ball.m_Velocity.Zero();
		}

		// aplikuj sile do bili
		Ball.ApplyForce(Time);
	}

	// zwroc znacznik aktywnosci symulacji
	return Running;
}

void CBillard::Simulate(float Time)
{
	// przejdz przez wszystkie bile
	for (int i = 0; i < m_Balls.GetCount(); i++)
		// symuluj i-ta bile
		m_Balls[i].Simulate(Time);
}

void CBillard::Restore(int Index)
{
	// czy podano jedna bile do przywrocenia
	if (Index >= 0)
	{
		// jesli tak to przywroc bile
		m_Balls[Index].Restore();
	}
	else
	{
		// przejdz przez wszystkie bile
		for (int i = 0; i < m_Balls.GetCount(); i++)
			// przywroc i-ta bile
			m_Balls[i].Restore();
	}
}

void CBillard::Reset(int Index)
{
	// czy podano jedna bile do zresetowania
	if (Index >= 0)
	{
		// resetuj bile
		m_Balls[Index].Reset();

		// przywroc bile na oryginalne miejsce z korekcja
		CBall &Ball1 = m_Balls[Index];

		// przejdz przez wszystkie inne bile
		for (int i = 0; i < m_Balls.GetCount(); i++)
		{
			// pobierz i-ta bile
			CBall &Ball2 = m_Balls[i];

			// nie sprawdzaj sama siebie
			if (i != Index)
			{
				// oblicz odleglosc srodkow bil, gdy mniejszy od srednicy
				if (Ball1.m_Position.Distance(Ball2.m_Position) < (Ball1.m_Ray + Ball2.m_Ray))
				{
					// wyznacz wektor przesuniecia
					CVector Vector(Ball1.m_Position - Ball2.m_Position);
					// koryguj pozycje bili
					Ball1.m_Position += Vector;
					// przegladaj bile od poczatku
					continue;
				}
			}
		}

		// zapisz aktualna pozycje do poprzedniej
		Ball1.m_PositionPrevious = Ball1.m_Position;
	}
	else
	{
		// przejdz przez wszystkie bile
		for (int i = 0; i < m_Balls.GetCount(); i++)
			// resetuj i-ta bile
			m_Balls[i].Reset();
	}
}

void CBillard::Stop(int Index)
{
	// czy podano jedna bile do zatrzymania
	if (Index >= 0)
	{
		// zatrzymaj bile
		m_Balls[Index].Stop();
	}
	else
	{
		// przejdz przez wszystkie bile
		for (int i = 0; i < m_Balls.GetCount(); i++)
			// zatrzymaj i-ta bile
			m_Balls[i].Stop();
	}
}

int CBillard::FindTriangle(CBall &Ball)
{
	// przejdz przez wszystkie trojkaty
	for (int i = 0; i < (int)m_Triangles.GetCount(); i++)
	{
		// pobierz i-ty trojkat
		const CTriangle &Triangle = m_Triangles[i];

		// czy nie jest to trojkat odbijajacy ani dolek
		if (!Triangle.GetReflect() && !Triangle.GetHole())
			// sprawdz czy bila jest w tym trojkacie
			if (Ball.IsInTriangle(&Triangle))
				// jesli jest, zwroc 1
				return 1;
	}

	// zwroc 0 -- bila nie jest nad zadnym trojkatem
	return 0;
}

int CBillard::FindBallsCollision(float FullTime, float &Time, int &Ball1, int &Ball2)
{
	// wyzeruj znacznik wykrycia kolizji
	int Result = 0;

	// przejdz przez bile
	for (int i = 0; i < (int)(m_Balls.GetCount()-1); i++)
	{
		// pobierz i-ta bile
		CBall &Ball1a = m_Balls[i];

		// czy symulacja bili wlaczona?
		if (!Ball1a.GetSimulate())
			continue;

		// przejdz przez reszte bil
		for (int j = i+1; j < m_Balls.GetCount(); j++)
		{
			// pobierz j-ta bile
			CBall &Ball2a = m_Balls[j];

			// czy bile koliduja ze soba?
			if (Ball1a.FindCollision(FullTime, Time, Ball2a))
			{
				// zapisz indeksy kolidujacych bil
				Ball1 = i;
				Ball2 = j;

				// ustaw znacznik wykrycia kolizji
				Result = 1;
			}
		}
	}

	// zwroc znacznik wykrycia kolizji
	return Result;
}

int CBillard::FindTriangleCollision(float FullTime, float &Time, int &Ball, int &Triangle)
{
	// wyzeruj znacznik wykrycia kolizji
	int Result = 0;

	// przejdz przez wszystkie bile
	for (int i = 0; i < (int)m_Balls.GetCount(); i++)
	{
		// pobierz i-ta bile
		CBall &Balla = m_Balls[i];

		// czy symulacja bili jest wlaczona i bila porusza sie
		if (!Balla.GetSimulate() || !Balla.IsMoving())
			continue;

		// przejdz przez wszystkie trojkaty
		for (int j = 0; j < m_Triangles.GetCount(); j++)
		{
			CTriangle &Trianglea = m_Triangles[j];

			// czy bila koliduje z i-tym trojkatem
			if (Balla.FindCollision(FullTime, Time, Trianglea))
			{
				// zapisz indeksy kolidujacej bili i trojkata
				Ball = i;
				Triangle = j;

				// to ustaw znacznik wykrycia kolizji
				Result = 1;
			}
		}
	}

	// zwroc znacznik wykrycia kolizji
	return Result;
}
