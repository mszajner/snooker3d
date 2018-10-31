
/** @file Mouse.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CMouse.
 *
 */ 

#pragma once

/**
 *  Klasa zwiera zestaw flag jednoznacznie identyfikuj¹cych ¿¹danie
 *  które przysz³o od myszki. Umo¿liwia to prost¹ implementacjê
 *  obs³ugi poruszania kamer¹ w samej grze.
 *
 *  @brief Klasa odpowiedzialna za obs³ugê myszki.
 */
class CMouse {

	private:
		/** @brief Flaga identyfikuj¹ca przyciœniecie lewego klawisza myszki. */
		int m_Left;
		/** @brief Flaga identyfikuj¹ca przyciœniecie prawego klawisza myszki. */
		int m_Right;
		/** @brief Aktualna pozycja myszki na osi OX. */
		int m_X;
		/** @brief Aktualna pozycja myszki na osi OY. */
		int m_Y;
		/** @brief Pozycja myszki na osi OX gdy wciœniêto lewy klawisz myszki. */
		int m_LeftX;
		/** @brief Przyrost przesuniêcia myszki na osi OX w czasie trzymania 
		 *         lewego klawisza od ostatniego wywo³ania metody Update.
		 */
		int m_LeftDX;
		/** @brief Pozycja myszki na osi OY gdy wciœniêto lewy klawisz myszki. */
		int m_LeftY;
		/** @brief Przyrost przesuniêcia myszki na osi OY w czasie trzymania 
		 *         lewego klawisza od ostatniego wywo³ania metody Update.
		 */
		int m_LeftDY;
		/** @brief Pozycja myszki na osi OX gdy wciœniêto prawy klawisz myszki. */
		int m_RightX;
		/** @brief Przyrost przesuniêcia myszki na osi OX w czasie trzymania 
		 *         prawego klawisza od ostatniego wywo³ania metody Update.
		 */
		int m_RightDX;
		/** @brief Pozycja myszki na osi OY gdy wciœniêto prawy klawisz myszki. */
		int m_RightY;
		/** @brief Przyrost przesuniêcia myszki na osi OY w czasie trzymania 
		 *         prawego klawisza od ostatniego wywo³ania metody Update.
		 */
		int m_RightDY;

	public:
		/** @brief Szybkoœæ ruchu myszki. */
		float Speed;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery w g³¹b widoku. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveIn;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery z g³êbi widoku. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveOut;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery do przodu. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveForward;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery do ty³u. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveBackward;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery do góry. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery do do³u. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery w lewo. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o przesuniêcie kamery w prawo. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraMoveRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o powiêkszenie obrazu. Wartoœæ jest równa przyrostowi 
		 *         przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraZoomIn;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o pomniejszenie obrazu. Wartoœæ jest równa przyrostowi 
		 *         przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraZoomOut;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery do góry. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraRollUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery do do³u. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraRollDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery w lewo. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraRollLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery w prawo. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraRollRight;

		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery do góry wokó³ bia³ej bili. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraAroundUp;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery do do³u wokó³ bia³ej bili. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraAroundDown;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery w lewo wokó³ bia³ej bili. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraAroundLeft;
		/** @brief Flaga identyfikuj¹ca czy przysz³o ¿¹danie od myszki
		 *         o obrót kamery w prawo wokó³ bia³ej bili. Wartoœæ jest równa
		 *         przyrostowi przesuniêcia od ostatniego wywo³ania metody Update.
		 */
		int CameraAroundRight;

	public:
		/** @brief Domyœlny konstruktor.
		 */
		CMouse(void);

	public:
		/**
		 *  Funkcja powinna byæ wywo³ywana w meldunku WM_LBUTTONDOWN g³ównego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametrów.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void LButtonDown(int X, int Y) { m_Left = 1; m_LeftX = X; m_LeftDX = 0; m_LeftY = Y; m_LeftDY = 0; };

		/**
		 *  Funkcja powinna byæ wywo³ywana w meldunku WM_LBUTTONUP g³ównego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametrów.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void LButtonUp(int X, int Y) { m_Left = 0; m_LeftX = X; m_LeftDX = 0; m_LeftY = Y; m_LeftDY = 0; };

	public:
		/**
		 *  Funkcja powinna byæ wywo³ywana w meldunku WM_RBUTTONDOWN g³ównego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametrów.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void RButtonDown(int X, int Y) { m_Right = 1; m_RightX = X; m_RightDX = 0; m_RightY = Y; m_RightDY = 0; };

		/**
		 *  Funkcja powinna byæ wywo³ywana w meldunku WM_RBUTTONUP g³ównego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametrów.
		 *  @param[in] X Pozycja myszki na osi OX.
		 *  @param[in] Y Pozycja myszki na osi OY.
		 */
		void RButtonUp(int X, int Y) { m_Right = 0; m_RightX = X; m_RightDX = 0; m_RightY = Y; m_RightDY = 0; };

	public:
		/**
		 *  Funkcja powinna byæ wywo³ywana w meldunku WM_MOUSEMOVE g³ównego okna.
		 *
		 *  @brief Funkcja uaktualnia zmienne odpowiednio do parametrów.
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
