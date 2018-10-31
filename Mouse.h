
/** @file Mouse.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CMouse.
 *
 */ 

#pragma once

/**
 *  Klasa zwiera zestaw flag jednoznacznie identyfikuj�cych ��danie
 *  kt�re przysz�o od myszki. Umo�liwia to prost� implementacj�
 *  obs�ugi poruszania kamer� w samej grze.
 *
 *  @brief Klasa odpowiedzialna za obs�ug� myszki.
 */
class CMouse {

	private:
		/** @brief Flaga identyfikuj�ca przyci�niecie lewego klawisza myszki. */
		int m_Left;
		/** @brief Flaga identyfikuj�ca przyci�niecie prawego klawisza myszki. */
		int m_Right;
		/** @brief Aktualna pozycja myszki na osi OX. */
		int m_X;
		/** @brief Aktualna pozycja myszki na osi OY. */
		int m_Y;
		/** @brief Pozycja myszki na osi OX gdy wci�ni�to lewy klawisz myszki. */
		int m_LeftX;
		/** @brief Przyrost przesuni�cia myszki na osi OX w czasie trzymania 
		 *         lewego klawisza od ostatniego wywo�ania metody Update.
		 */
		int m_LeftDX;
		/** @brief Pozycja myszki na osi OY gdy wci�ni�to lewy klawisz myszki. */
		int m_LeftY;
		/** @brief Przyrost przesuni�cia myszki na osi OY w czasie trzymania 
		 *         lewego klawisza od ostatniego wywo�ania metody Update.
		 */
		int m_LeftDY;
		/** @brief Pozycja myszki na osi OX gdy wci�ni�to prawy klawisz myszki. */
		int m_RightX;
		/** @brief Przyrost przesuni�cia myszki na osi OX w czasie trzymania 
		 *         prawego klawisza od ostatniego wywo�ania metody Update.
		 */
		int m_RightDX;
		/** @brief Pozycja myszki na osi OY gdy wci�ni�to prawy klawisz myszki. */
		int m_RightY;
		/** @brief Przyrost przesuni�cia myszki na osi OY w czasie trzymania 
		 *         prawego klawisza od ostatniego wywo�ania metody Update.
		 */
		int m_RightDY;

	public:
		/** @brief Szybko�� ruchu myszki. */
		float Speed;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery w g��b widoku. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveIn;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery z g��bi widoku. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveOut;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery do przodu. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveForward;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery do ty�u. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveBackward;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery do g�ry. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery do do�u. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery w lewo. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o przesuni�cie kamery w prawo. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraMoveRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o powi�kszenie obrazu. Warto�� jest r�wna przyrostowi 
		 *         przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraZoomIn;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o pomniejszenie obrazu. Warto�� jest r�wna przyrostowi 
		 *         przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraZoomOut;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery do g�ry. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraRollUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery do do�u. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraRollDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery w lewo. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraRollLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery w prawo. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraRollRight;

		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery do g�ry wok� bia�ej bili. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraAroundUp;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery do do�u wok� bia�ej bili. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraAroundDown;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery w lewo wok� bia�ej bili. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraAroundLeft;
		/** @brief Flaga identyfikuj�ca czy przysz�o ��danie od myszki
		 *         o obr�t kamery w prawo wok� bia�ej bili. Warto�� jest r�wna
		 *         przyrostowi przesuni�cia od ostatniego wywo�ania metody Update.
		 */
		int CameraAroundRight;

	public:
		/** @brief Domy�lny konstruktor.
		 */
		CMouse(void);

	public:
		/**
		 *  Funkcja powinna by� wywo�ywana w meldunku WM_LBUTTONDOWN g��wnego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametr�w.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void LButtonDown(int X, int Y) { m_Left = 1; m_LeftX = X; m_LeftDX = 0; m_LeftY = Y; m_LeftDY = 0; };

		/**
		 *  Funkcja powinna by� wywo�ywana w meldunku WM_LBUTTONUP g��wnego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametr�w.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void LButtonUp(int X, int Y) { m_Left = 0; m_LeftX = X; m_LeftDX = 0; m_LeftY = Y; m_LeftDY = 0; };

	public:
		/**
		 *  Funkcja powinna by� wywo�ywana w meldunku WM_RBUTTONDOWN g��wnego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametr�w.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void RButtonDown(int X, int Y) { m_Right = 1; m_RightX = X; m_RightDX = 0; m_RightY = Y; m_RightDY = 0; };

		/**
		 *  Funkcja powinna by� wywo�ywana w meldunku WM_RBUTTONUP g��wnego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametr�w.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void RButtonUp(int X, int Y) { m_Right = 0; m_RightX = X; m_RightDX = 0; m_RightY = Y; m_RightDY = 0; };

	public:
		/**
		 *  Funkcja powinna by� wywo�ywana w meldunku WM_MOUSEMOVE g��wnego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametr�w.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void MouseMove(int X, int Y);

	public:
		/**
		 *  Funkcja na podstawie podanego stanu gry odpowiednio uaktualnia
		 *  flagi zgodnie ze myszki.
		 *
		 *  @brief Funkcja uaktualnia stan flag.
		 */
		void Update(CBillardState State);

};
