
/** @file NewGameDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CNewGameDlg - okno dialogowe nowej gry.
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
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domyœlny.
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
		/** @brief Funkcja wywo³ywana przy nciœniêciu klawisza OK.
		 */
		afx_msg void OnClickedOk();

		/** @brief Funkcja wywo³ywana przy nciœniêciu klawisza Anuluj.
		 */
		afx_msg void OnClickedCancel();
};
