
/** @file AboutDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy obs�ugi okna dialogowego o programie CAboutDlg.
 *
 *  Plik zawiera definicj� klasy CAboutDlg obs�uguj�cej okno dialogowe
 *  o programie.
 */ 

#pragma once

/** @brief Klasa obs�uguj�ca okno dialogowe o programie.
 */
class CAboutDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CAboutDlg)

	public:
		/** @brief Konstruktor domy�lny.
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
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/**
		 *  Funkcja wywo�uje dwie metody z klasy CMainWnd (klasa 
		 *  globalna SnookerApp.m_MainWnd). Najpierw metod� OnAboutDialog, 
		 *  kt�ra zamyka ten dialog, a nast�pnie metod� OnMenuDialog, 
		 *  kt�ra pokazuje menu.
		 *
		 *  @brief Funkcja obs�uguj�ca wci�ni�cie przycisku OK.
		 */
		afx_msg void OnClickedOk();

};
