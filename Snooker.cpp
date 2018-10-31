// Snooker.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Snooker.h"
#include "DisplayDlg.h"
#include "Sound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "SnookerDLL.lib")

// The one and only CSnookerApp object

CSnookerApp SnookerApp;

// CSnookerApp

BEGIN_MESSAGE_MAP(CSnookerApp, CWinApp)
END_MESSAGE_MAP()

// CSnookerApp construction

CSnookerApp::CSnookerApp()
	: m_hAccel(NULL)
{
}

CSnookerApp::~CSnookerApp(void)
{
}

// CSnookerApp initialization

BOOL CSnookerApp::InitInstance()
{
	// inicjuj kontrolki systemowe
	InitCommonControls();

	// inicjuj aplikacje
	if (!CWinApp::InitInstance())
		return FALSE;

	// ustaw klucz rejestru aplikacji
	SetRegistryKey(_T("Snooker"));

	// ustaw wskaznik na glowne okno aplikacji
	m_pMainWnd = &m_MainWnd;

	// utworz dialog wyboru trybu wyswietlania
	CDisplayDlg DisplayDlg;

	// wyswietl okno wyboru trybu wyswietlania
	if (DisplayDlg.DoModal() != IDOK)
		// jesli wybrano CANCEL, zakoncz aplikacje
		return FALSE;

	// utworz okno aplikacji
	if (m_MainWnd.Create(DisplayDlg.m_DisplayMode, DisplayDlg.m_FullScreen))
	{
		// inicjalizuj renderowanie
		m_Render.Initialize();

		// wczytaj domyslne ustawienia gry
		m_Billard.LoadGame("Data\\Snooker.def");
		// zresetuj gre
		m_Billard.Reset();

		// pokaz okno
		m_MainWnd.ShowWindow(SW_NORMAL);

		// zaladuj skroty klawiszowe
		m_hAccel = LoadAccelerators(m_hInstance, 
			MAKEINTRESOURCE(IDR_MAINFRAME));

		// pokaz menu
		m_MainWnd.OnMenuDialog();

		Sound.Initialize(m_MainWnd.m_hWnd);

		// glowna petla meldunkow
		while (TRUE)
		{
			MSG Message;

			// czy sa meldunki w kolejce do obslugi
			if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
			{
				//if ((Message.hwnd == m_MainWnd.m_hWnd) || 
				//	(Message.hwnd == m_MainWnd.m_MenuDlg.m_hWnd))
				if (TranslateAccelerator(m_MainWnd.m_hWnd, m_hAccel, &Message))
					continue;
				{
					// jesli meldunek jest inny od WM_QUIT
					if (Message.message != WM_QUIT)
					{
						// tlumacz meldunek
						TranslateMessage(&Message);
						// przetworz meldunek
						DispatchMessage(&Message);
					}
					else
					{
						// jesli jest rowny WM_QUIT, zakoncz petle
						break;
					}
				}
			}

			// nie ma meldunkow w kolejce
			else
			{
				// czy okno jest widoczne
				if (m_MainWnd.m_IsVisible)
				{
					// pobierz czas
					float Time = m_Timer.Get();

					// uruchom gre
					m_Billard.Run(Time);
					// przesun kamere
					m_Camera.Run(Time);
					// renderuj obraz
					m_Render.Run(Time);

					// simulate and render
					SwapBuffers (m_MainWnd.m_pDC->m_hDC);
				}
				else
				{
					// poczekaj na meldunek
					WaitMessage();
				}
			}
		}

		Sound.Finalize();

		// usun tabele ze skrotami klawiszowymi
		DestroyAcceleratorTable(m_hAccel);

		// finalizuj renderowanie
		m_Render.Finalize();

		// zniszcz okno aplikacji
		m_MainWnd.Destroy();
	}
	else
	{
		CString Text, Title;

		// zaladuj tekst bledu
		Text.LoadString(IDS_ERROR_CREATE_WINDOW);
		// zaladuj tytul aplikacji
		Title.LoadString(AFX_IDS_APP_TITLE);

		// wyswietl okno informacyjne
		MessageBox(HWND_DESKTOP, Text, Title, MB_OK | MB_ICONEXCLAMATION);
	}

	// zakoncz aplikacje
	return FALSE;
}
