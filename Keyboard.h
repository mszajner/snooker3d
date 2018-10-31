
/** @file Keyboard.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CKeyboard.
 *
 */ 

#pragma once

/**
 *  Klasa zwiera zestaw flag jednoznacznie identyfikuj�cych ��danie
 *  kt�re przysz�o od klawiatury. Umo�liwia to prost� implementacj�
 *  obs�ugi poruszania kamer� w samej grze.
 *
 *  @brief Klasa obs�uguj�ca klawiatur�.
 */
class CKeyboard {

	public:
		/** @brief Tablica ze stanem klawiszy. */
		int m_State[256];

	public:
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery w g��b widoku.
		 */
		int CameraMoveIn;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery z g��bi widoku.
		 */
		int CameraMoveOut;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery do przodu.
		 */
		int CameraMoveForward;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery do ty�u.
		 */
		int CameraMoveBackward;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery do g�ry.
		 */
		int CameraMoveUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery do do�u.
		 */
		int CameraMoveDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery w lewo.
		 */
		int CameraMoveLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie kamery w prawo.
		 */
		int CameraMoveRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o powi�kszenie obrazu.
		 */
		int CameraZoomIn;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o pomniejszenie obrazu.
		 */
		int CameraZoomOut;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery do g�ry.
		 */
		int CameraRollUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery do do�u.
		 */
		int CameraRollDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery w lewo.
		 */
		int CameraRollLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery w prawo.
		 */
		int CameraRollRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery do g�ry wzgl�dem bia�ej bili.
		 */
		int CameraAroundUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery do do�u wzgl�dem bia�ej bili.
		 */
		int CameraAroundDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery w lewo wzgl�dem bia�ej bili.
		 */
		int CameraAroundLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o obr�t kamery w prawo wzgl�dem bia�ej bili.
		 */
		int CameraAroundRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie bia�ej bili do przodu.
		 */
		int BallMoveForward;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie bia�ej bili do ty�u.
		 */
		int BallMoveBackward;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie bia�ej bili w lewo.
		 */
		int BallMoveLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przesuni�cie bia�ej bili w prawo.
		 */
		int BallMoveRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przej�cie do nast�pnego stanu.
		 */
		int NextState;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o przej�cie do poprzedniego stanu.
		 */
		int PrevState;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie z klawiatury
		 *         o oddanie strza�u.
		 */
		int Shot;

	public:
		/** @brief Konstruktor domy�lny inicjuj�cy tablic� stan�w klawiszy.
		 */
		CKeyboard(void);

	public:
		/**
		 *  Funkcja powinna zosta� pod��czona do meldunku WM_KEYDOWN g��wnego okna gry.
		 *
		 *  @brief Funkcja wywo�ywana przy naci�ni�ciu klawisza.
		 */
		void KeyDown(UINT nChar, UINT nFlags);

		/**
		 *  Funkcja powinna zosta� pod��czona do meldunku WM_KEYUP g��wnego okna gry.
		 *
		 *  @brief Funkcja wywo�ywana przy zwolnieniu klawisza.
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
