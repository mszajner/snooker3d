
/** @file DisplayDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CDisplayMode i CDisplayDlg.
 *
 *  Plik zawiera definicje klas CDisplayMode i CDisplayDlg. 
 *
 */ 

#pragma once

#include "afxwin.h"
#include "afxtempl.h"

/** @brief Klasa przechowuj�ca informacje o rozdzielczo�ci.
 */
class CDisplayMode : public CObject {

	public:
		/** @brief Szeroko�� ekranu w pikselach. */
		int m_Width;
		/** @brief Wysoko�� ekranu w pikselach. */
		int m_Height;
		/** @brief G��bia kolor�w w bitach. */
		int m_BPP;

	public:
		/** @brief Domy�lny konstruktor. */
		CDisplayMode(void);

		/** @brief Konstruktor kopiuj�cy.
		 *  @param[in] DisplayMode Tryb �r�d�owy.
		 */
		CDisplayMode(const CDisplayMode &DisplayMode);

		/** @brief Konstruktor inicjalizuj�cy. 
		 *  @param[in] Width Szeroko�� ekranu w pikselach.
		 *  @param[in] Height Wysoko�� ekranu w pikselach.
		 *  @param[in] BPP G��bia kolor�w w bitach.
		 */
		CDisplayMode(int Width, int Height, int BPP);

	public:
		/** @brief Funkcja konwertuj�ca rozdzielczo�� na tekst.
		 *  @retval Funkcja zwraca tekst w formacie "m_Width x m_Height x m_BPP".
		 */
		CString ToString(void) const;

		/** @brief Funkcja zamieniaj�ca tekst na rozdzielczo��. */
		void FromString(const CString String);

	public:
		/** @brief Operator por�wnania.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�eli dwa tryby maj�
		 *          takie same parametry.
		 */
		BOOL operator==(const CDisplayMode &DisplayMode) const;

		/** @brief Operator przypisania.
		 *  @param[in] DisplayMode Tryb �r�d�owy.
		 *  @retval Funkcja zwraca referencj� do tego trybu.
		 */
		CDisplayMode& operator=(const CDisplayMode &DisplayMode);

};

// CDisplayDlg dialog

class CDisplayDlg : public CDialog {

	private:
		/** @brief Zmienna powi�zana z kontrolk� listy tryb�w - IDC_RESOLUTIONS. */
		CComboBox m_Resolutions;
		/** @brief Tablica z dost�pnymi trybami graficznymi. */
		CArray<CDisplayMode, CDisplayMode&> m_DisplayModes;

	private:
		DECLARE_DYNAMIC(CDisplayDlg)

	private:
		/** @brief Funkcja sprawdzaj�ca czy podany tryb znajduje si� w tablicy z 
		 *         dost�pnymi trybami.
		 *  @param[in] DisplayMode Poszukiwany tryb.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�eli podany tryb
		 *          znajduje si� w tablicy.
		 */
		BOOL DisplayModeExists(const CDisplayMode &DisplayMode);

		/** @brief Funkcja pobiera dost�pne tryby ze sterownika karty graficznej
		 *         i umiesza je w tablicy m_DisplayModes.
		 */
		void EnumDisplayModes(void);

		/** @brief Funkcja wype�nia kontrolk� listy tryb�w dost�pnymi trybami.
		 */
		void UpdateComboBox(void);

		/** @brief Funkcja wczytuje ustawienia wy�wietlania gry z rejestru.
		 */
		void LoadSettings(void);

		/** @brief Funkcja zapisuje ustawienia wy�wietlania gry do rejestru.
		 */
		void SaveSettings(void);

		/** @brief Funkcja zaznacza w kontrolce listy tryb�w tryb o podanych
		 *         parametrach.
		 *  @param[in] DisplayMode Wzorcowy tryb, kt�ry chcemy zaznaczy�.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li znaleziono
		 *          tryb na li�cie i uda�o si� go zaznaczy�.
		 */
		BOOL SelectDisplayMode(const CDisplayMode &DisplayMode);

	protected:
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);    

		/** @brief Funkcja wywo�ywana po wci�ni�ciu przycisku OK.
		 */
		virtual void OnOK();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CDisplayDlg(CWnd* pParent = NULL);

		/** @brief Destruktor domy�lny.
		 */
		virtual ~CDisplayDlg();

		/** @brief Funkcja wywo�ywana przy inicjalizacji dialogu.
		 */
		virtual BOOL OnInitDialog();

		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_DISPLAY_DIALOG };

	public:
		/** @brief Zmienna powi�zana z kontrolk� "Pe�ny ekran" - IDC_FULLSCREEN. */
		BOOL m_FullScreen;

		/** @brief Zmienna powi�zana z kontrolk� "Nie pytaj ponownie" - IDC_DONT_ASK_AGAIN. */
		BOOL m_DontAskAgain;

		/** @brief Zmienna przechowuj�ca wybrany tryb graficzny. */
		CDisplayMode m_DisplayMode;

};
