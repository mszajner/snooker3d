
/** @file AboutDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy obs³ugi okna dialogowego o programie CAboutDlg.
 *
 *  Plik zawiera definicjê klasy CAboutDlg obs³uguj¹cej okno dialogowe
 *  o programie.
 */ 

#pragma once

/** @brief Klasa obs³uguj¹ca okno dialogowe o programie.
 */
class CAboutDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CAboutDlg)

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CAboutDlg(CWnd* pParent = NULL);

		/** @brief Destruktor.
		 */
		virtual ~CAboutDlg();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_ABOUT_DIALOG };

	protected:
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/**
		 *  Funkcja wywo³uje dwie metody z klasy CMainWnd (klasa 
		 *  globalna SnookerApp.m_MainWnd). Najpierw metodê OnAboutDialog, 
		 *  która zamyka ten dialog, a nastêpnie metodê OnMenuDialog, 
		 *  która pokazuje menu.
		 *
		 *  @brief Funkcja obs³uguj¹ca wciœniêcie przycisku OK.
		 */
		afx_msg void OnClickedOk();

};
