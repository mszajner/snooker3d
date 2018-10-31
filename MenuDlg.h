
/** @file MenuDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CMenuDlg - okno dialogowe menu.
 *
 */ 

#pragma once

/** @brief Klasa obs�uguj�ca okno dialogowe menu.
 */
class CMenuDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CMenuDlg)

	protected:
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CMenuDlg(CWnd* pParent = NULL);

		/** @brief Destruktor. 
		 */
		virtual ~CMenuDlg();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_MENU_DIALOG };

	public:
		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Nowa gra".
		 */
		afx_msg void OnClickedNewGame();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Trening".
		 */
		afx_msg void OnClickedTrenning();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Wczytaj gr�...".
		 */
		afx_msg void OnClickedLoadGame();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Zapisz gr�...".
		 */
		afx_msg void OnClickedSaveGame();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "O programie...".
		 */
		afx_msg void OnClickedAbout();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Zako�cz".
		 */
		afx_msg void OnClickedExit();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Pomoc".
		 */
		afx_msg void OnBnClickedHelp();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku "Powr�t do gry".
		 */
		afx_msg void OnClickedReturn();

};
