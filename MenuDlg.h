
/** @file MenuDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CMenuDlg - okno dialogowe menu.
 *
 */ 

#pragma once

/** @brief Klasa obs³uguj¹ca okno dialogowe menu.
 */
class CMenuDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CMenuDlg)

	protected:
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domyœlny.
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
		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Nowa gra".
		 */
		afx_msg void OnClickedNewGame();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Trening".
		 */
		afx_msg void OnClickedTrenning();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Wczytaj grê...".
		 */
		afx_msg void OnClickedLoadGame();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Zapisz grê...".
		 */
		afx_msg void OnClickedSaveGame();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "O programie...".
		 */
		afx_msg void OnClickedAbout();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Zakoñcz".
		 */
		afx_msg void OnClickedExit();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Pomoc".
		 */
		afx_msg void OnBnClickedHelp();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku "Powrót do gry".
		 */
		afx_msg void OnClickedReturn();

};
