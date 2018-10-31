
/** @file DisplayDlg.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CDisplayMode i CDisplayDlg.
 *
 *  Plik zawiera implementacje klas CDisplayMode i CDisplayDlg. 
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "DisplayDlg.h"

// CDisplayMode

CDisplayMode::CDisplayMode(void)
	: m_Width(0)
	, m_Height(0)
	, m_BPP(0)
{
}

CDisplayMode::CDisplayMode(const CDisplayMode &DisplayMode)
	: m_Width(DisplayMode.m_Width)
	, m_Height(DisplayMode.m_Height)
	, m_BPP(DisplayMode.m_BPP)
{
}

CDisplayMode::CDisplayMode(int Width, int Height, int BPP)
	: m_Width(Width)
	, m_Height(Height)
	, m_BPP(BPP)
{
}

CString CDisplayMode::ToString(void) const
{
	CString String;

	// zamien na string
	String.Format("%d x %d x %d", m_Width, m_Height, m_BPP);

	// zwroc string
	return String;
}

void CDisplayMode::FromString(const CString String)
{
	int Start = 0, Previous = 0, Counter = 0;

	// szukaj dzielnika 'x'
	while ((Start = String.Find("x", 0)) >= 0)
	{
		int Value;

		// pobierz czesc tekstu (miedzy dzielnikami 'x')
		CString Text = String.Mid(Previous, Start - 1);

		// zamien na liczbe
		sscanf(Text, "%d", &Value);

		// ktory parametr?
		switch (Counter++)
		{
		case 0:
			// zapamietaj jako szerokosc
			m_Width = Value;
			break;

		case 1:
			// zapamietaj jako wysokosc
			m_Height = Value;
			break;

		case 2:
			// zapamietaj jako glebie koloru
			m_BPP = Value;
			break;
		}

		// zapamietaj pozycje dzielnika 'x'
		Previous = Start + 1;
	}
}

BOOL CDisplayMode::operator==(const CDisplayMode &DisplayMode) const
{
	// porownaj parametry trybu
	return (DisplayMode.m_Width == m_Width) && (DisplayMode.m_Height == m_Height)
		&& (DisplayMode.m_BPP == m_BPP);
}

CDisplayMode& CDisplayMode::operator=(const CDisplayMode &DisplayMode)
{
	// skopiuj parametry trybu
	m_Width = DisplayMode.m_Width;
	m_Height = DisplayMode.m_Height;
	m_BPP = DisplayMode.m_BPP;

	// zwroc referencje do tego trybu
	return *this;
}

// CDisplayDlg dialog

IMPLEMENT_DYNAMIC(CDisplayDlg, CDialog)
CDisplayDlg::CDisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayDlg::IDD, pParent)
	, m_FullScreen(FALSE)
	, m_DontAskAgain(FALSE)
	, m_DisplayMode(640, 480, 16)
{
}

CDisplayDlg::~CDisplayDlg()
{
}

void CDisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RESOLUTIONS, m_Resolutions);
	DDX_Check(pDX, IDC_FULLSCREEN, m_FullScreen);
	DDX_Check(pDX, IDC_DONT_ASK_AGAIN, m_DontAskAgain);
}

BEGIN_MESSAGE_MAP(CDisplayDlg, CDialog)
END_MESSAGE_MAP()

// CDisplayDlg message handlers

BOOL CDisplayDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// pobierz dostepne tryby graficzne
	EnumDisplayModes();

	// uaktualnij liste trybow
	UpdateComboBox();

	// wczytaj ustawienia
	LoadSettings();

	// uaktualnij kontrolki
	UpdateData(FALSE);

	// czy program ma nie pytac ponownie?
	if (m_DontAskAgain)
	{
		// wcisnij OK od razu
		OnOK();
	}

	return TRUE;
}

// CDisplayDlg methods

BOOL CDisplayDlg::DisplayModeExists(const CDisplayMode &DisplayMode)
{
	// przejdz po wszystkich trybach
	for(int i = 0; i < m_DisplayModes.GetSize(); i++)
	{
		// porownaj i-tryb
		if (m_DisplayModes[i] == DisplayMode)
			// zwroc true -- znaleziono tryb
			return TRUE;
	}

	// zwroc false -- nie znaleziono trybu
	return FALSE;
}

void CDisplayDlg::EnumDisplayModes(void)
{
	DWORD dwModeNumber = 0;
	DEVMODE	DeviceMode;

	// wyczysc poprzednia liste
	m_DisplayModes.RemoveAll();

	// przegladaj dostepne tryby
	while (EnumDisplaySettings(NULL, dwModeNumber, &DeviceMode))
	{
		// przejdz do nastepnego trybu
		dwModeNumber++;

		// czy tryb jest 16 lub 32-bitowy
		if ((DeviceMode.dmBitsPerPel != 16) && (DeviceMode.dmBitsPerPel != 32))
			continue;

		// czy rozdzielczosc jest wieksza niz 640x480
		if ((DeviceMode.dmPelsWidth < 640) || (DeviceMode.dmPelsHeight < 480))
			continue;

		// utworz tryb
		CDisplayMode DisplayMode(DeviceMode.dmPelsWidth, 
			DeviceMode.dmPelsHeight, DeviceMode.dmBitsPerPel);

		// czy tryb istnieje na liscie
		if (!DisplayModeExists(DisplayMode))
			// jesli nie, dodaj tryb do listy
			m_DisplayModes.Add(DisplayMode);
	}
}

void CDisplayDlg::UpdateComboBox(void)
{
	// wyczysc poprzednia liste
	m_Resolutions.ResetContent();

	// przejdz przez wszystkie tryby
	for (int i = 0; i < m_DisplayModes.GetSize(); i++)
	{
		int Index;

		// zamien tryb na tekst
		CString Text = m_DisplayModes[i].ToString();

		// dodaj tekst do listy
		Index = m_Resolutions.AddString(Text);

		// zapamietaj wskaznik do trybu
		m_Resolutions.SetItemData(Index, (DWORD_PTR)&m_DisplayModes[i]);
	}

	// czy znaleziono jakies tryby
	if (m_Resolutions.GetCount() <= 0)
	{
		CString Text;

		// wczytaj tekst do wyswietlenia z zasobow
		Text.LoadString(IDS_NOT_SUPPORTED);

		// jesli nie, to dodaj odpowiedni tekst
		m_Resolutions.AddString(Text);

		// deaktywuj liste wyboru
		m_Resolutions.EnableWindow(FALSE);
	}

	// zaznacz pierwsza pozycje
	m_Resolutions.SetCurSel(0);
}

void CDisplayDlg::LoadSettings(void)
{
	// wczytaj tryb
	m_DisplayMode.m_Width = SnookerApp.GetProfileInt("Display Settings", "Width", m_DisplayMode.m_Width);
	m_DisplayMode.m_Height = SnookerApp.GetProfileInt("Display Settings", "Height", m_DisplayMode.m_Height);
	m_DisplayMode.m_BPP = SnookerApp.GetProfileInt("Display Settings", "BPP", m_DisplayMode.m_BPP);

	// wczytaj dodatkowe opcje
	m_FullScreen = SnookerApp.GetProfileInt("Display Settings", "Fullscreen", m_FullScreen);
	m_DontAskAgain = SnookerApp.GetProfileInt("Display Settings" , "DontAskAgain", m_DontAskAgain);

	// zaznacz wczytany tryb
	if (!SelectDisplayMode(m_DisplayMode))
	{
		// przypadkiem nie zamykaj okna
		m_DontAskAgain = FALSE;
	}
}

void CDisplayDlg::SaveSettings(void)
{
	// pobierz indeks zaznaczonego trybu
	int Selected  = m_Resolutions.GetCurSel();

	// czy zaznaczono cokolwiek
	if (Selected >= 0)
	{
		SnookerApp.WriteProfileInt("Display Settings", "Width", m_DisplayMode.m_Width);
		SnookerApp.WriteProfileInt("Display Settings", "Height", m_DisplayMode.m_Height);
		SnookerApp.WriteProfileInt("Display Settings", "BPP", m_DisplayMode.m_BPP);

		SnookerApp.WriteProfileInt("Display Settings", "FullScreen", m_FullScreen);
		SnookerApp.WriteProfileInt("Display Settings", "DontAskAgain", m_DontAskAgain);
	}
}

BOOL CDisplayDlg::SelectDisplayMode(const CDisplayMode &DisplayMode)
{
	// przejdz przez wszystkie tryby
	for (int i = 0; i < m_Resolutions.GetCount(); i++)
	{
		// pobierz wskaznik na tryb z listy
		const CDisplayMode &Mode = *(CDisplayMode*)m_Resolutions.GetItemDataPtr(i);

		// czy tryby sa rowne
		if (Mode == DisplayMode)
		{
			// zaznacz pozycje
			m_Resolutions.SetCurSel(i);

			// zwroc true -- znaleziono tryb
			return TRUE;
		}
	}

	// zwroc false -- nie znaleziono trybu
	return FALSE;
}

void CDisplayDlg::OnOK()
{
	// pobierz wartosci z kontrolek
	UpdateData();

	// pobierz indeks zaznaczonego trybu
	int Selected = m_Resolutions.GetCurSel();

	// pobierz tryb
	m_DisplayMode = ((CDisplayMode*)m_Resolutions.GetItemDataPtr(Selected))[0];

	// zapisz ustawienia
	SaveSettings();

	// wcisnij OK
	CDialog::OnOK();
}
