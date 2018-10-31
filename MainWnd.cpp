
/** @file MainWnd.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CMainWnd - g³ówne okno gry.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "MainWnd.h"

// CMainWnd

IMPLEMENT_DYNAMIC(CMainWnd, CWnd)

CMainWnd::CMainWnd()
	: m_pDC(NULL)
	, m_hRC(NULL)
	, m_IsVisible(FALSE)
	, m_IsFullScreen(FALSE)
{
}

CMainWnd::~CMainWnd()
{
}

void CMainWnd::ShowError(int StringID)
{
	CString Text, Title;
	Text.LoadString(StringID);
	Title.LoadString(AFX_IDS_APP_TITLE);
	::MessageBox(HWND_DESKTOP, Text, Title, MB_OK | MB_ICONEXCLAMATION);
}

BOOL CMainWnd::RegisterClass(void)
{
	CString ClassName;
	WNDCLASSEX wndClass;

	// wczytaj nazwe klasy okna
	ClassName.LoadString(IDS_CLASS_NAME);

	// wyzeruj strukture
	ZeroMemory(&wndClass, sizeof (WNDCLASSEX));

	// wypelnij strukture
	wndClass.cbSize = sizeof (WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = ::DefWindowProc;
	wndClass.hInstance = SnookerApp.m_hInstance;
	wndClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpszClassName = ClassName;

	// zarejestruj klase 
	if (RegisterClassEx(&wndClass) == 0)
	{
		// pokaz blad
		ShowError(IDS_ERROR_REGISTER_CLASS);
		// zakoncz z bledem
		return FALSE;
	}

	// zakoncz z powodzeniem
	return TRUE;
}

BOOL CMainWnd::ChangeDisplayMode(const CDisplayMode &DisplayMode)
{
	DEVMODE DeviceMode;

	// wyzeruj strukture
	ZeroMemory(&DeviceMode, sizeof (DEVMODE));

	// wyeplnij strukture
	DeviceMode.dmSize = sizeof (DEVMODE);
	DeviceMode.dmPelsWidth = DisplayMode.m_Width;
	DeviceMode.dmPelsHeight	= DisplayMode.m_Height;
	DeviceMode.dmBitsPerPel = DisplayMode.m_BPP;
	DeviceMode.dmFields	= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// zmien ustawienia ekranu
	if (ChangeDisplaySettings(&DeviceMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		// pokaz blad
		ShowError(IDS_ERROR_SET_DISPLAY_MODE);
		// zakoncz niepowodzeniem
		return FALSE;
	}

	// zakoncz z powodzeniem
	return TRUE;
}

BOOL CMainWnd::Create(const CDisplayMode &DisplayMode, BOOL FullScreen)
{
	GLuint PixelFormat;
	CString ClassName, WindowTitle;

	DWORD dwWindowStyle = WS_OVERLAPPEDWINDOW;
	DWORD dwWindowExtendedStyle = WS_EX_APPWINDOW;
	RECT WindowRect = { 0, 0, DisplayMode.m_Width, DisplayMode.m_Height };

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof (PIXELFORMATDESCRIPTOR), 1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, DisplayMode.m_BPP, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 16, 0, 0, PFD_MAIN_PLANE, 0,0, 0, 0
	};

	if (!RegisterClass())
		return FALSE;

	// czy ustawic pelny ekran
	if ((m_IsFullScreen = FullScreen) != FALSE)
	{
		if (!ChangeDisplayMode(DisplayMode))
			return Destroy();

		dwWindowStyle = WS_POPUP;
		dwWindowExtendedStyle |= WS_EX_TOPMOST;
	}
	else
	{
		// Adjust Window, Account For Window Borders
		AdjustWindowRectEx(&WindowRect, dwWindowStyle, 0, dwWindowExtendedStyle);
	}

	// wczytaj nazwe klasy okna
	ClassName.LoadString(IDS_CLASS_NAME);

	// wczytaj tytul okna
	WindowTitle.LoadString(AFX_IDS_APP_TITLE);

	// utworz okno
	if (!CreateEx(dwWindowExtendedStyle, ClassName, WindowTitle, dwWindowStyle, 
		0, 0, DisplayMode.m_Width, DisplayMode.m_Height, NULL, NULL, NULL))
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// ustaw ikone glownego okna
	SetIcon(LoadIcon(SnookerApp.m_hInstance, 
		MAKEINTRESOURCE(IDR_MAINFRAME)), FALSE);

	// pobierz kontekst urzadzenia
	m_pDC = GetDC();

	// jesli nie pobrano poprawnego kontekstu
	if (m_pDC == NULL)
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// wybierz format pikseli
	PixelFormat = ChoosePixelFormat(m_pDC->m_hDC, &pfd);

	// jesli nie wybrano poprawnego formatu
	if (PixelFormat == 0)
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// ustaw format pikseli
	if (!SetPixelFormat(m_pDC->m_hDC, PixelFormat, &pfd))
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// utworz kontekst renderowania urzadzenia
	m_hRC = wglCreateContext(m_pDC->m_hDC);

	// jesli nie utworzno kontekstu
	if (m_hRC == NULL)
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// powiaz kontekst renderowania z kontekstem urzadzenia
	if (!wglMakeCurrent(m_pDC->m_hDC, m_hRC))
		// zwroc FALSE -- nie udalo sie utworzyc okna
		return Destroy();

	// czy wybrano pelny ekran
	if (!FullScreen)
		// jesli nie, to wysrodkuj okno
		CenterWindow();
	else
		// jesli tak, przesun na poczatek ekranu
		MoveWindow(0, 0, DisplayMode.m_Width, DisplayMode.m_Height);

	// zwroc TRUE -- udalo utworzyc sie okno
	return TRUE;
}

BOOL CMainWnd::Destroy(void)
{
	CString ClassName;

	if (m_hWnd != NULL)
	{
		// czy istnieje kontekst urzadzenia
		if (m_pDC != NULL)
		{
			// wybierz pusty kontekst dla urzadzenia OpenGL
			wglMakeCurrent(m_pDC->m_hDC, NULL);

			// czy istnieje kontekst renderowania
			if (m_hRC != NULL)
			{
				// opusc kontekst renderowania OpenGL
				wglDeleteContext(m_hRC);

				// wyzeruj wskaznik
				m_hRC = NULL;
			}

			// opusc kontekst urzadzenia
			ReleaseDC(m_pDC);

			// wyzeruj wskaznik
			m_pDC = NULL;
		}

		// zniszcz okno
		DestroyWindow();
	}

	// czy byl wybrano pelny ekran
	if (m_IsFullScreen)
	{
		// ustaw rozdzielczosc pulpitu
		ChangeDisplaySettings(NULL, 0);
	}

	// wczytaj nazwe klasy okna
	ClassName.LoadString(IDS_CLASS_NAME);
	// wyrejestruj klase okna
	UnregisterClass(ClassName, SnookerApp.m_hInstance);
	return FALSE;
}

BEGIN_MESSAGE_MAP(CMainWnd, CWnd)
	//{{AFX_MSG_MAP(CMainWnd)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LOAD_CAMERA1, OnLoadCamera1)
	ON_COMMAND(ID_LOAD_CAMERA2, OnLoadCamera2)
	ON_COMMAND(ID_LOAD_CAMERA3, OnLoadCamera3)
	ON_COMMAND(ID_LOAD_CAMERA4, OnLoadCamera4)
	ON_COMMAND(ID_LOAD_CAMERA5, OnLoadCamera5)
	ON_COMMAND(ID_LOAD_CAMERA6, OnLoadCamera6)
	ON_COMMAND(ID_LOAD_CAMERA7, OnLoadCamera7)
	ON_COMMAND(ID_LOAD_CAMERA8, OnLoadCamera8)
	ON_COMMAND(ID_STORE_CAMERA1, OnStoreCamera1)
	ON_COMMAND(ID_STORE_CAMERA2, OnStoreCamera2)
	ON_COMMAND(ID_STORE_CAMERA3, OnStoreCamera3)
	ON_COMMAND(ID_STORE_CAMERA4, OnStoreCamera4)
	ON_COMMAND(ID_STORE_CAMERA5, OnStoreCamera5)
	ON_COMMAND(ID_STORE_CAMERA6, OnStoreCamera6)
	ON_COMMAND(ID_STORE_CAMERA7, OnStoreCamera7)
	ON_COMMAND(ID_STORE_CAMERA8, OnStoreCamera8)
	ON_COMMAND(ID_MENU_DIALOG, OnMenuDialog)
	ON_COMMAND(ID_NEW_GAME_DIALOG, OnNewGameDialog)
	ON_COMMAND(ID_ABOUT_DIALOG, OnAboutDialog)
	ON_COMMAND(ID_BALLS_DIALOG, OnBallsDialog)
	ON_COMMAND(ID_TRIANGLES_DIALOG, OnTrianglesDialog)
	ON_COMMAND(ID_SAVE_DEFAULT, OnSaveDefault)
END_MESSAGE_MAP()

// CMainWnd message handlers

void CMainWnd::OnSysCommand(UINT nID, LPARAM lParam) 
{
	switch (lParam)
	{
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return;
	}

	CWnd::OnSysCommand(nID, lParam);
}

void CMainWnd::OnClose() 
{
	CWnd::CloseWindow();
	PostMessage(WM_QUIT);
}

void CMainWnd::OnSize(UINT nType, int cx, int cy) 
{	
	switch (nType)
	{
	case SIZE_MINIMIZED:
		m_IsVisible = FALSE;
		break;

	case SIZE_MAXIMIZED:
		m_IsVisible = TRUE;
		SnookerApp.m_Render.SetRatio(cx, cy);
		break;

	case SIZE_RESTORED:
		m_IsVisible = TRUE;
		SnookerApp.m_Render.SetRatio(cx, cy);
		break;
	}
}

void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	SnookerApp.m_Keyboard.KeyDown(nChar, nFlags);
}

void CMainWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	SnookerApp.m_Keyboard.KeyUp(nChar, nFlags);
}

BOOL CMainWnd::OnEraseBkgnd(CDC *pDC) 
{
	// nie pozwol na czyszczenie tla
	return FALSE;
}

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	SnookerApp.m_Mouse.MouseMove(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SnookerApp.m_Mouse.LButtonDown(point.x, point.y);
	CWnd::OnLButtonDown(nFlags, point);
}

void CMainWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	SnookerApp.m_Mouse.LButtonUp(point.x, point.y);
	CWnd::OnLButtonUp(nFlags, point);
}

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	SnookerApp.m_Mouse.RButtonDown(point.x, point.y);
	CWnd::OnRButtonDown(nFlags, point);
}

void CMainWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	SnookerApp.m_Mouse.RButtonUp(point.x, point.y);
	CWnd::OnRButtonUp(nFlags, point);
}

void CMainWnd::OnLoadCamera1()
{
	SnookerApp.m_Camera.LoadPosition(0);
}

void CMainWnd::OnLoadCamera2()
{
	SnookerApp.m_Camera.LoadPosition(1);
}

void CMainWnd::OnLoadCamera3()
{
	SnookerApp.m_Camera.LoadPosition(2);
}

void CMainWnd::OnLoadCamera4()
{
	SnookerApp.m_Camera.LoadPosition(3);
}

void CMainWnd::OnLoadCamera5()
{
	SnookerApp.m_Camera.LoadPosition(4);
}

void CMainWnd::OnLoadCamera6()
{
	SnookerApp.m_Camera.LoadPosition(5);
}

void CMainWnd::OnLoadCamera7()
{
	SnookerApp.m_Camera.LoadPosition(6);
}

void CMainWnd::OnLoadCamera8()
{
	SnookerApp.m_Camera.LoadPosition(7);
}

void CMainWnd::OnStoreCamera1()
{
	SnookerApp.m_Camera.StorePosition(0);
}

void CMainWnd::OnStoreCamera2()
{
	SnookerApp.m_Camera.StorePosition(1);
}

void CMainWnd::OnStoreCamera3()
{
	SnookerApp.m_Camera.StorePosition(2);
}

void CMainWnd::OnStoreCamera4()
{
	SnookerApp.m_Camera.StorePosition(3);
}

void CMainWnd::OnStoreCamera5()
{
	SnookerApp.m_Camera.StorePosition(4);
}

void CMainWnd::OnStoreCamera6()
{
	SnookerApp.m_Camera.StorePosition(5);
}

void CMainWnd::OnStoreCamera7()
{
	SnookerApp.m_Camera.StorePosition(6);
}

void CMainWnd::OnStoreCamera8()
{
	SnookerApp.m_Camera.StorePosition(7);
}

void CMainWnd::OnMenuDialog()
{
	if (m_MenuDlg.m_hWnd == NULL)
		m_MenuDlg.Create(CMenuDlg::IDD, this);

	if (m_MenuDlg.IsWindowVisible())
	{
		m_MenuDlg.ShowWindow(SW_HIDE);
		m_MenuDlg.DestroyWindow();
		SnookerApp.m_Billard.m_Pause--;
	}
	else
	{
		SnookerApp.m_Billard.m_Pause++;
		m_MenuDlg.ShowWindow(SW_SHOW);
	}
}

void CMainWnd::OnHelpDialog(void)
{
	if (m_HelpDlg.m_hWnd == NULL)
		m_HelpDlg.Create(CHelpDlg::IDD, this);

	if (m_HelpDlg.IsWindowVisible())
	{
		m_HelpDlg.ShowWindow(SW_HIDE);
		m_HelpDlg.DestroyWindow();
		SnookerApp.m_Billard.m_Pause--;
	}
	else
	{
		m_HelpDlg.ShowWindow(SW_SHOW);
		SnookerApp.m_Billard.m_Pause++;
	}
}

void CMainWnd::OnNewGameDialog()
{
	if (m_NewGameDlg.m_hWnd == NULL)
		m_NewGameDlg.Create(CNewGameDlg::IDD, this);

	if (m_NewGameDlg.IsWindowVisible())
	{
		m_NewGameDlg.ShowWindow(SW_HIDE);
		m_NewGameDlg.DestroyWindow();
		SnookerApp.m_Billard.m_Pause--;
	}
	else
	{
		m_NewGameDlg.ShowWindow(SW_SHOW);
		SnookerApp.m_Billard.m_Pause++;
	}
}

void CMainWnd::OnAboutDialog()
{
	if (m_AboutDlg.m_hWnd == NULL)
		m_AboutDlg.Create(CAboutDlg::IDD, this);

	if (m_AboutDlg.IsWindowVisible())
	{
		m_AboutDlg.ShowWindow(SW_HIDE);
		m_AboutDlg.DestroyWindow();
		SnookerApp.m_Billard.m_Pause--;
	}
	else
	{
		m_AboutDlg.ShowWindow(SW_SHOW);
		SnookerApp.m_Billard.m_Pause++;
	}
}

void CMainWnd::OnBallsDialog()
{
	if (m_BallsDlg.m_hWnd == NULL)
		m_BallsDlg.Create(CBallsDlg::IDD, this);

	if (m_BallsDlg.IsWindowVisible())
	{
		m_BallsDlg.ShowWindow(SW_HIDE);
		m_BallsDlg.DestroyWindow();
	}
	else
	{
		m_BallsDlg.ShowWindow(SW_SHOW);
	}
}

void CMainWnd::OnTrianglesDialog()
{
	if (m_TrianglesDlg.m_hWnd == NULL)
		m_TrianglesDlg.Create(CTrianglesDlg::IDD, this);

	if (m_TrianglesDlg.IsWindowVisible())
	{
		m_TrianglesDlg.ShowWindow(SW_HIDE);
		m_TrianglesDlg.DestroyWindow();
	}
	else
	{
		m_TrianglesDlg.ShowWindow(SW_SHOW);
	}
}

void CMainWnd::OnSaveDefault()
{
	if (SnookerApp.m_Billard.m_Running)
		return;

	SnookerApp.m_Billard.SaveGame("Data\\Snooker.def");
}
