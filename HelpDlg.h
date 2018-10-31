
/** @file HelpDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy obs�ugi okna pomocy CHelpDlg.
 *
 *  Plik zawiera definicj� klasy CHelpDlg obs�uguj�cej okno dialogowe pomocy.
 */ 

#pragma once

/** @brief Klasa obs�uguj�ca okno dialogowe pomocy.
 */
class CHelpDlg : public CDialog {

	private:
		DECLARE_DYNAMIC(CHelpDlg)

	public:
		/** @brief Konstruktor domy�lny.
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
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);

		DECLARE_MESSAGE_MAP()

	public:
		/**
		 *  Funkcja wywo�uje dwie metody z klasy CMainWnd (klasa 
		 *  globalna SnookerApp.m_MainWnd). Najpierw metod� OnHelpDialog, 
		 *  kt�ra zamyka ten dialog, a nast�pnie metod� OnMenuDialog, 
		 *  kt�ra pokazuje menu.
		 *
		 *  @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku OK.
		 */
		afx_msg void OnClickedOk();

};
