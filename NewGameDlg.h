
/** @file NewGameDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CNewGameDlg - okno dialogowe nowej gry.
 *
 */ 

#pragma once

/** @brief Klasa okna dialogowego nowej gry.
 */
class CNewGameDlg : public CDialog {

	private:
		CString m_Player1;
		CString m_Player2;

	private:
		DECLARE_DYNAMIC(CNewGameDlg)

	protected:
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CNewGameDlg(CWnd* pParent = NULL);

		/** @brief Destruktor. 
		 */
		virtual ~CNewGameDlg();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_NEW_GAME_DIALOG };

	public:
		/** @brief Funkcja wywo�ywana przy nci�ni�ciu klawisza OK.
		 */
		afx_msg void OnClickedOk();

		/** @brief Funkcja wywo�ywana przy nci�ni�ciu klawisza Anuluj.
		 */
		afx_msg void OnClickedCancel();
};
