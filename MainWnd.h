
/** @file MainWnd.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CMainWnd - g��wne okno gry.
 *
 */ 

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "MenuDlg.h"
#include "NewGameDlg.h"
#include "BallsDlg.h"
#include "TrianglesDlg.h"
#include "AboutDlg.h"
#include "DisplayDlg.h"
#include "HelpDlg.h"

/** @brief Klasa okna g��wnego gry.
 */
class CMainWnd : public CWnd {

	public:
		/** @brief Kontekst urz�dzenia. */
		CDC *m_pDC;
		/** @brief Kontkst renderowania. */
        HGLRC m_hRC;
		/** @brief Flaga identyfikuj�ca czy okno jest widoczne. */
		BOOL m_IsVisible;
		/** @brief Flaga identyfikuj�ca czy jest w��czony tryb pe�noekranowy. */
		BOOL m_IsFullScreen;
		/** @brief Okno dialogowe menu. */
		CMenuDlg m_MenuDlg;
		/** @brief Okno dialogowe nowej gry. */
		CNewGameDlg m_NewGameDlg;
		/** @brief Okno dialogowe edytora bil. */
		CBallsDlg m_BallsDlg;
		/** @brief Okno dialogowe edytora tr�jk�t�w. */
		CTrianglesDlg m_TrianglesDlg;
		/** @brief Okno dialogowe o programie. */
		CAboutDlg m_AboutDlg;
		/** @brief Okno dialogowe pomocy. */
		CHelpDlg m_HelpDlg;

	private:
		/** @brief Funkcja wy�wietlaj�ca okno z komunikatem b��du.
		 *  @param[in] StringID Identyfikator tekstu z komunikatem w zasobach.
		 */
		void ShowError(int StringID);

		/** @brief Funkcja rejestruje klas� okna.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� zarejestrowa� klas�.
		 */
		BOOL RegisterClass(void);

		/** @brief Funkcja ustawiaj�ca podany tryb graficzny.
		 *  @param[in] DisplayMode ��dany tryb graficzny.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� ustawi� tryb graficzny.
		 */
		BOOL ChangeDisplayMode(const CDisplayMode &DisplayMode);

	private:
		DECLARE_DYNAMIC(CMainWnd)

	protected:
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CMainWnd();

		/** @brief Destruktor.
		 */
		virtual ~CMainWnd();

	public:
		/** @brief Funkcja tworzy okno o podanych parametrach.
		 *  @param[in] DisplayMode Tryb graficzny - rozmiar okna.
		 *  @param[in] FullScreen Tryb pe�noekranowy (1 - tak, 0 - nie).
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� utworzy� okno.
		 */
		BOOL Create(const CDisplayMode &DisplayMode, BOOL FullScreen);

		/** @brief Funkcja niszczy okno.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� zniszczy� okno.
		 */
		BOOL Destroy(void);

	public:
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnClose(void);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);	
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnLoadCamera1(void);
		afx_msg void OnLoadCamera2(void);
		afx_msg void OnLoadCamera3(void);
		afx_msg void OnLoadCamera4(void);
		afx_msg void OnLoadCamera5(void);
		afx_msg void OnLoadCamera6(void);
		afx_msg void OnLoadCamera7(void);
		afx_msg void OnLoadCamera8(void);
		afx_msg void OnStoreCamera1(void);
		afx_msg void OnStoreCamera2(void);
		afx_msg void OnStoreCamera3(void);
		afx_msg void OnStoreCamera4(void);
		afx_msg void OnStoreCamera5(void);
		afx_msg void OnStoreCamera6(void);
		afx_msg void OnStoreCamera7(void);
		afx_msg void OnStoreCamera8(void);
		afx_msg void OnHelpDialog(void);
		afx_msg void OnNewGameDialog(void);
		afx_msg void OnMenuDialog(void);
		afx_msg void OnAboutDialog(void);
		afx_msg void OnBallsDialog(void);
		afx_msg void OnTrianglesDialog(void);
		afx_msg void OnSaveDefault(void);

};
