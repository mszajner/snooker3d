
/** @file DisplayDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CDisplayMode i CDisplayDlg.
 *
 *  Plik zawiera definicje klas CDisplayMode i CDisplayDlg. 
 *
 */ 

#pragma once

#include "afxwin.h"
#include "afxtempl.h"

/** @brief Klasa przechowuj¹ca informacje o rozdzielczoœci.
 */
class CDisplayMode : public CObject {

	public:
		/** @brief Szerokoœæ ekranu w pikselach. */
		int m_Width;
		/** @brief Wysokoœæ ekranu w pikselach. */
		int m_Height;
		/** @brief G³êbia kolorów w bitach. */
		int m_BPP;

	public:
		/** @brief Domyœlny konstruktor. */
		CDisplayMode(void);

		/** @brief Konstruktor kopiuj¹cy.
		 *  @param[in] DisplayMode Tryb Ÿród³owy.
		 */
		CDisplayMode(const CDisplayMode &DisplayMode);

		/** @brief Konstruktor inicjalizuj¹cy. 
		 *  @param[in] Width Szerokoœæ ekranu w pikselach.
		 *  @param[in] Height Wysokoœæ ekranu w pikselach.
		 *  @param[in] BPP G³êbia kolorów w bitach.
		 */
		CDisplayMode(int Width, int Height, int BPP);

	public:
		/** @brief Funkcja konwertuj¹ca rozdzielczoœæ na tekst.
		 *  @retval Funkcja zwraca tekst w formacie "m_Width x m_Height x m_BPP".
		 */
		CString ToString(void) const;

		/** @brief Funkcja zamieniaj¹ca tekst na rozdzielczoœæ. */
		void FromString(const CString String);

	public:
		/** @brief Operator porównania.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera je¿eli dwa tryby maj¹
		 *          takie same parametry.
		 */
		BOOL operator==(const CDisplayMode &DisplayMode) const;

		/** @brief Operator przypisania.
		 *  @param[in] DisplayMode Tryb Ÿród³owy.
		 *  @retval Funkcja zwraca referencjê do tego trybu.
		 */
		CDisplayMode& operator=(const CDisplayMode &DisplayMode);

};

// CDisplayDlg dialog

class CDisplayDlg : public CDialog {

	private:
		/** @brief Zmienna powi¹zana z kontrolk¹ listy trybów - IDC_RESOLUTIONS. */
		CComboBox m_Resolutions;
		/** @brief Tablica z dostêpnymi trybami graficznymi. */
		CArray<CDisplayMode, CDisplayMode&> m_DisplayModes;

	private:
		DECLARE_DYNAMIC(CDisplayDlg)

	private:
		/** @brief Funkcja sprawdzaj¹ca czy podany tryb znajduje siê w tablicy z 
		 *         dostêpnymi trybami.
		 *  @param[in] DisplayMode Poszukiwany tryb.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera je¿eli podany tryb
		 *          znajduje siê w tablicy.
		 */
		BOOL DisplayModeExists(const CDisplayMode &DisplayMode);

		/** @brief Funkcja pobiera dostêpne tryby ze sterownika karty graficznej
		 *         i umiesza je w tablicy m_DisplayModes.
		 */
		void EnumDisplayModes(void);

		/** @brief Funkcja wype³nia kontrolkê listy trybów dostêpnymi trybami.
		 */
		void UpdateComboBox(void);

		/** @brief Funkcja wczytuje ustawienia wyœwietlania gry z rejestru.
		 */
		void LoadSettings(void);

		/** @brief Funkcja zapisuje ustawienia wyœwietlania gry do rejestru.
		 */
		void SaveSettings(void);

		/** @brief Funkcja zaznacza w kontrolce listy trybów tryb o podanych
		 *         parametrach.
		 *  @param[in] DisplayMode Wzorcowy tryb, który chcemy zaznaczyæ.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli znaleziono
		 *          tryb na liœcie i uda³o siê go zaznaczyæ.
		 */
		BOOL SelectDisplayMode(const CDisplayMode &DisplayMode);

	protected:
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);    

		/** @brief Funkcja wywo³ywana po wciœniêciu przycisku OK.
		 */
		virtual void OnOK();

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CDisplayDlg(CWnd* pParent = NULL);

		/** @brief Destruktor domyœlny.
		 */
		virtual ~CDisplayDlg();

		/** @brief Funkcja wywo³ywana przy inicjalizacji dialogu.
		 */
		virtual BOOL OnInitDialog();

		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_DISPLAY_DIALOG };

	public:
		/** @brief Zmienna powi¹zana z kontrolk¹ "Pe³ny ekran" - IDC_FULLSCREEN. */
		BOOL m_FullScreen;

		/** @brief Zmienna powi¹zana z kontrolk¹ "Nie pytaj ponownie" - IDC_DONT_ASK_AGAIN. */
		BOOL m_DontAskAgain;

		/** @brief Zmienna przechowuj¹ca wybrany tryb graficzny. */
		CDisplayMode m_DisplayMode;

};
