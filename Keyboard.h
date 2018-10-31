
/** @file Keyboard.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CKeyboard.
 *
 */ 

#pragma once

/**
 *  Klasa zwiera zestaw flag jednoznacznie identyfikuj¹cych ¿¹danie
 *  które przysz³o od klawiatury. Umo¿liwia to prost¹ implementacjê
 *  obs³ugi poruszania kamer¹ w samej grze.
 *
 *  @brief Klasa obs³uguj¹ca klawiaturê.
 */
class CKeyboard {

	public:
		/** @brief Tablica ze stanem klawiszy. */
		int m_State[256];

	public:
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery w g³¹b widoku.
		 */
		int CameraMoveIn;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery z g³êbi widoku.
		 */
		int CameraMoveOut;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery do przodu.
		 */
		int CameraMoveForward;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery do ty³u.
		 */
		int CameraMoveBackward;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery do góry.
		 */
		int CameraMoveUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery do do³u.
		 */
		int CameraMoveDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery w lewo.
		 */
		int CameraMoveLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie kamery w prawo.
		 */
		int CameraMoveRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o powiêkszenie obrazu.
		 */
		int CameraZoomIn;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o pomniejszenie obrazu.
		 */
		int CameraZoomOut;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery do góry.
		 */
		int CameraRollUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery do do³u.
		 */
		int CameraRollDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery w lewo.
		 */
		int CameraRollLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery w prawo.
		 */
		int CameraRollRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery do góry wzglêdem bia³ej bili.
		 */
		int CameraAroundUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery do do³u wzglêdem bia³ej bili.
		 */
		int CameraAroundDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery w lewo wzglêdem bia³ej bili.
		 */
		int CameraAroundLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o obrót kamery w prawo wzglêdem bia³ej bili.
		 */
		int CameraAroundRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie bia³ej bili do przodu.
		 */
		int BallMoveForward;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie bia³ej bili do ty³u.
		 */
		int BallMoveBackward;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie bia³ej bili w lewo.
		 */
		int BallMoveLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przesuniêcie bia³ej bili w prawo.
		 */
		int BallMoveRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przejœcie do nastêpnego stanu.
		 */
		int NextState;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o przejœcie do poprzedniego stanu.
		 */
		int PrevState;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie z klawiatury
		 *         o oddanie strza³u.
		 */
		int Shot;

	public:
		/** @brief Konstruktor domyœlny inicjuj¹cy tablicê stanów klawiszy.
		 */
		CKeyboard(void);

	public:
		/**
		 *  Funkcja powinna zostaæ pod³¹czona do meldunku WM_KEYDOWN g³ównego okna gry.
		 *
		 *  @brief Funkcja wywo³ywana przy naciœniêciu klawisza.
		 */
		void KeyDown(UINT nChar, UINT nFlags);

		/**
		 *  Funkcja powinna zostaæ pod³¹czona do meldunku WM_KEYUP g³ównego okna gry.
		 *
		 *  @brief Funkcja wywo³ywana przy zwolnieniu klawisza.
		 */
		void KeyUp(UINT nChar, UINT nFlags);

	public:
		/**
		 *  Funkcja na podstawie podanego stanu gry odpowiednio uaktualnia
		 *  flagi zgodnie ze stanem klawiszy.
		 *
		 *  @brief Funkcja uaktualnia stan flag.
		 */
		void Update(CBillardState State);

};
