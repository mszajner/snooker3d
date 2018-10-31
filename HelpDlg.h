
/** @file HelpDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy obs³ugi okna pomocy CHelpDlg.
 *
 *  Plik zawiera definicjê klasy CHelpDlg obs³uguj¹cej okno dialogowe pomocy.
 */ 

#pragma once

/** @brief Klasa obs³uguj¹ca okno dialogowe pomocy.
 */
class CHelpDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CHelpDlg)

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CHelpDlg(CWnd* pParent = NULL);

		/** @brief Destruktor. 
		 */
		virtual ~CHelpDlg();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_HELP_DIALOG };

	protected:
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);

		DECLARE_MESSAGE_MAP()

	public:
		/**
		 *  Funkcja wywo³uje dwie metody z klasy CMainWnd (klasa 
		 *  globalna SnookerApp.m_MainWnd). Najpierw metodê OnHelpDialog, 
		 *  która zamyka ten dialog, a nastêpnie metodê OnMenuDialog, 
		 *  która pokazuje menu.
		 *
		 *  @brief Funkcja wywo³ywana przy wciœniêciu przycisku OK.
		 */
		afx_msg void OnClickedOk();

};
