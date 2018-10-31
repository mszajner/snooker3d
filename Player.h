
/** @file Player.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CPlayer.
 *
 *  Plik zawiera interfejs klasy CPlayer oraz dodatkowe typy potrzebne
 *  do definicji tej klasy.
 *
 */ 

#pragma once

#include "Ball.h"

/** @brief Stan gracza.
 */
typedef enum {
	/** @brief Stan pocz�tkowy gracz, bez faulu, przed wbiciem czerwonej bili.
	 */
	psNone,

	/** @brief Gracz pope�ni� b��d, niew�a�ciwa kolejno�� wbicia bil, pierwsza 
	 *          dotkni�ta bila kolorwa, etc.
	 */
	psFoul,

	/** @brief Gracz wbi� bia�a bil�!
	 */
	psWhiteKnockIn,

	/** @brief Gracz ma bia�� bil� w r�ce. Mo�e j� ustawi� na stole.
	 */
	psBallInHand,

	/** @brief Gracz wbi� czerwon� bil�, bez faulu.
	 */
	psRedKnockIn
} CPlayerState;

/**
 *  Klasa zawiera pola potrzebne do opisu i zarz�dzania graczem.
 *
 *  @brief Klasa reprezentuj�ca gracza.
 */
class CPlayer {

	private:
		/** @brief Imi� gracza. */
		CString m_Name;
		/** @brief Liczba punkt�w zdobytych przez gracza w ostatnim uderzeniu. */
		int m_Break;
		/** @brief Liczba punkt�w zdobytych przez gracza. */
		int m_Score;
		/** @brief Stan gracza. */
		CPlayerState m_State;

	public:
		/** @brief Konstruktor domy�lny. */
		CPlayer(void);

		/** @brief Konstruktor kopiuj�cy. 
		 *  @param[in] Player Gracz �r�d�owy.
		 */
		CPlayer(const CPlayer &Player);

		/** @brief Konstruktor z ustawianiem imienia gracza.
		 *  @param[in] Name Imi� gracza
		 */
		CPlayer(const CString Name);

	public:
		/** @brief Funkcja odczytuj�ca gracza z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj�ca gracza do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype�nienie tabulacja przed ka�d� lini�.
		 *  @retval Zwraca warto�� r�n� od zera je�li operacja powiod�a si�.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja podaje nazw� gracza.
		 *  @retval Funkcja zwraca nazw� gracza.
		 */
		const CString& GetName(void) const { return m_Name; };

		/** @brief Funkcja podaje liczb� punkt�w zdobytych przez gracza w ostatnim uderzeniu.
		 *  @retval Funkcja zwraca liczb� punkt�w zdobytych przez gracza w ostatnim uderzeniu.
		 */
		int GetBreak(void) const { return m_Break; };

		/** @brief Funkcja podaje liczb� punkt�w zdobytych przez gracza.
		 *  @retval Funkcja zwraca liczb� punkt�w zdobytych przez gracza.
		 */
		int GetScore(void) const { return m_Score; };

		/** @brief Funkcja podaje stan gracza.
		 *  @retval Funkcja zwraca stan gracza.
		 */
		CPlayerState GetState(void) const { return m_State; };

	public:
		/** @brief Funkcja ustawia nazw� gracza.
		 *  @param[in] Name Nowa nazwa gracza.
		 */
		void SetName(const CString &Name) { m_Name = Name; };

		/** @brief Funkcja ustawia liczb� punkt�w zdobytych przez gracza w ostatnim uderzeniu.
		 *  @param[in] Break Nowa liczba punkt�w.
		 */
		void SetBreak(int Break) { m_Break = Break; };

		/** @brief Funkcja ustawia liczb� punkt�w gracza.
		 *  @param[in] Score Nowa liczba punkt�w.
		 */
		void SetScore(int Score) { m_Score = Score; };

		/** @brief Funkcja ustawia stan gracza.
		 *  @param[in] State Nowa stan gracza.
		 */
		void SetState(CPlayerState State) { m_State = State; };

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Player Gracz �r�d�owy.
		 */
		CPlayer& operator=(const CPlayer &Player);

};
