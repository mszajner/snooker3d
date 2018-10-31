
/** @file Player.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CPlayer.
 *
 *  Plik zawiera implementacjê klasy CPlayer.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Player.h"

// CPlayer

CPlayer::CPlayer()
	: m_Name("")
	, m_Score(0)
	, m_Break(0)
	, m_State(psNone)
{
}

CPlayer::CPlayer(const CPlayer &Player)
	: m_Name(Player.m_Name)
	, m_Score(Player.m_Score)
	, m_Break(Player.m_Break)
	, m_State(Player.m_State)
{
}

CPlayer::CPlayer(const CString Name)
	: m_Name(Name)
	, m_Score(0)
	, m_Break(0)
	, m_State(psNone)
{
}

int CPlayer::Read(FILE *File)
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
				// czy jest to slowo NAME
				if (stricmp(Buffer, "NAME") == 0)
				{
					int c, start = 0, end = 0;

					// wyczysc nazwe
					m_Name = "";

					// petla odczytujaca nazwe
					while (!end && ((c = fgetc(File)) != EOF))
					{
						// czy nie natrafino juz na '"'
						if (!start)
						{
							// czy ten znak to '"'
							if (c == '\"')
								// ustaw flage rozpoczecia slowa
								start = 1;
						}
						else
						{
							// czy nie natrafino juz na drugi znak '"'
							if (!end)
							{
								// czy ten znak to '"'
								if (c == '\"')
									// ustaw flage natrafienia na drugi znak '"'
									end = 1;
								else
									// dodaj ten znak do nazwy
									m_Name += (char)c;
							}
						}
					}
				}

				// czy jest to slowo SCORE
				else if (stricmp(Buffer, "SCORE") == 0)
					// odczytaj liczbe punktow zdobytych przez gracza
					ErrorFlag = fscanf(File, "%d", &m_Score) != 1;

				// czy jest to slowo STATE
				else if (stricmp(Buffer, "STATE") == 0)
					// odczytaj stan gracza
					ErrorFlag = fscanf(File, "%d", &m_State) != 1;

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

int CPlayer::Write(FILE *File, const CString &TabFill)
{
	// zapisz slowo BEGIN
	fprintf(File, "%sBEGIN\n", TabFill);

	// zapisz nazwe gracza
	fprintf(File, "%s\tNAME \"%s\"\n", TabFill, m_Name.GetBuffer());
	m_Name.ReleaseBuffer();
	// zapisz liczbe punktow zdobytych przez gracza
	fprintf(File, "%s\tSCORE %d\n", TabFill, m_Score);
	// zapisz stan gracza
	fprintf(File, "%s\tSTATE %d\n", TabFill, m_State);

	// zapisz slowo END
	fprintf(File, "%sEND\n", TabFill);
	return 1;
}

CPlayer& CPlayer::operator=(const CPlayer &Player)
{
	// skopiuj pola
	m_Name = Player.m_Name;
	m_Score = Player.m_Score;
	m_State = Player.m_State;

	// zwroc referencje do tego gracza
	return *this;
}
