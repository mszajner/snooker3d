
/** @file Player.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CPlayer.
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
	/** @brief Stan pocz¹tkowy gracz, bez faulu, przed wbiciem czerwonej bili.
	 */
	psNone,

	/** @brief Gracz pope³ni³ b³¹d, niew³aœciwa kolejnoœæ wbicia bil, pierwsza 
	 *          dotkniêta bila kolorwa, etc.
	 */
	psFoul,

	/** @brief Gracz wbi³ bia³a bilê!
	 */
	psWhiteKnockIn,

	/** @brief Gracz ma bia³¹ bilê w rêce. Mo¿e j¹ ustawiæ na stole.
	 */
	psBallInHand,

	/** @brief Gracz wbi³ czerwon¹ bilê, bez faulu.
	 */
	psRedKnockIn
} CPlayerState;

/**
 *  Klasa zawiera pola potrzebne do opisu i zarz¹dzania graczem.
 *
 *  @brief Klasa reprezentuj¹ca gracza.
 */
class CPlayer {

	private:
		/** @brief Imiê gracza. */
		CString m_Name;
		/** @brief Liczba punktów zdobytych przez gracza w ostatnim uderzeniu. */
		int m_Break;
		/** @brief Liczba punktów zdobytych przez gracza. */
		int m_Score;
		/** @brief Stan gracza. */
		CPlayerState m_State;

	public:
		/** @brief Konstruktor domyœlny. */
		CPlayer(void);

		/** @brief Konstruktor kopiuj¹cy. 
		 *  @param[in] Player Gracz Ÿród³owy.
		 */
		CPlayer(const CPlayer &Player);

		/** @brief Konstruktor z ustawianiem imienia gracza.
		 *  @param[in] Name Imiê gracza
		 */
		CPlayer(const CString Name);

	public:
		/** @brief Funkcja odczytuj¹ca gracza z pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Read(FILE *File);

		/** @brief Funkcja zapisuj¹ca gracza do pliku tekstowego.
		 *  @param[in] File Otwarty plik.
		 *  @param[in] TabFill Wype³nienie tabulacja przed ka¿d¹ lini¹.
		 *  @retval Zwraca wartoœæ ró¿n¹ od zera jeœli operacja powiod³a siê.
		 */
		int Write(FILE *File, const CString &TabFill = "");

	public:
		/** @brief Funkcja podaje nazwê gracza.
		 *  @retval Funkcja zwraca nazwê gracza.
		 */
		const CString& GetName(void) const { return m_Name; };

		/** @brief Funkcja podaje liczbê punktów zdobytych przez gracza w ostatnim uderzeniu.
		 *  @retval Funkcja zwraca liczbê punktów zdobytych przez gracza w ostatnim uderzeniu.
		 */
		int GetBreak(void) const { return m_Break; };

		/** @brief Funkcja podaje liczbê punktów zdobytych przez gracza.
		 *  @retval Funkcja zwraca liczbê punktów zdobytych przez gracza.
		 */
		int GetScore(void) const { return m_Score; };

		/** @brief Funkcja podaje stan gracza.
		 *  @retval Funkcja zwraca stan gracza.
		 */
		CPlayerState GetState(void) const { return m_State; };

	public:
		/** @brief Funkcja ustawia nazwê gracza.
		 *  @param[in] Name Nowa nazwa gracza.
		 */
		void SetName(const CString &Name) { m_Name = Name; };

		/** @brief Funkcja ustawia liczbê punktów zdobytych przez gracza w ostatnim uderzeniu.
		 *  @param[in] Break Nowa liczba punktów.
		 */
		void SetBreak(int Break) { m_Break = Break; };

		/** @brief Funkcja ustawia liczbê punktów gracza.
		 *  @param[in] Score Nowa liczba punktów.
		 */
		void SetScore(int Score) { m_Score = Score; };

		/** @brief Funkcja ustawia stan gracza.
		 *  @param[in] State Nowa stan gracza.
		 */
		void SetState(CPlayerState State) { m_State = State; };

	public:
		/** @brief Operator przypisania.
		 *  @param[in] Player Gracz Ÿród³owy.
		 */
		CPlayer& operator=(const CPlayer &Player);

};
