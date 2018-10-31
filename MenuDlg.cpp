
/** @file MenuDlg.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CMenuDlg - okno dialogowe menu.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "MenuDlg.h"

// CMenuDlg dialog

IMPLEMENT_DYNAMIC(CMenuDlg, CDialog)
CMenuDlg::CMenuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMenuDlg::IDD, pParent)
{
}

CMenuDlg::~CMenuDlg()
{
}

void CMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMenuDlg, CDialog)
	ON_BN_CLICKED(IDC_NEW_GAME, OnClickedNewGame)
	ON_BN_CLICKED(IDC_TRENNING, OnClickedTrenning)
	ON_BN_CLICKED(IDC_LOAD_GAME, OnClickedLoadGame)
	ON_BN_CLICKED(IDC_SAVE_GAME, OnClickedSaveGame)
	ON_BN_CLICKED(IDC_ABOUT, OnClickedAbout)
	ON_BN_CLICKED(IDC_EXIT, OnClickedExit)
	ON_BN_CLICKED(IDC_HELPBTN, OnBnClickedHelp)
	ON_BN_CLICKED(IDC_RETURN, OnClickedReturn)
END_MESSAGE_MAP()

// CMenuDlg message handlers

void CMenuDlg::OnClickedNewGame()
{
	SnookerApp.m_MainWnd.OnNewGameDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}

void CMenuDlg::OnClickedTrenning()
{
	SnookerApp.m_Billard.NewGame(CPlayers());
	SnookerApp.m_MainWnd.OnMenuDialog();
}

void CMenuDlg::OnClickedLoadGame()
{
	CString Filter, DefaultExt;

	Filter.LoadString(IDS_FILTER);
	DefaultExt.LoadString(IDS_DEFAULTEXT);

	CFileDialog FileDialog(TRUE, DefaultExt, NULL, OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT | OFN_EXPLORER, Filter, this);

	if (FileDialog.DoModal() == IDOK)
		SnookerApp.m_Billard.LoadGame(FileDialog.GetPathName());
}

void CMenuDlg::OnClickedSaveGame()
{
	CString Filter, DefaultExt;

	Filter.LoadString(IDS_FILTER);
	DefaultExt.LoadString(IDS_DEFAULTEXT);

	CFileDialog FileDialog(FALSE, DefaultExt, NULL, OFN_HIDEREADONLY 
		| OFN_OVERWRITEPROMPT | OFN_EXPLORER, Filter, this);

	if (FileDialog.DoModal() == IDOK)
		SnookerApp.m_Billard.SaveGame(FileDialog.GetPathName());
}

void CMenuDlg::OnClickedAbout()
{
	SnookerApp.m_MainWnd.OnAboutDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}

void CMenuDlg::OnClickedExit()
{
	SnookerApp.m_MainWnd.SendMessage(WM_CLOSE);
}

void CMenuDlg::OnBnClickedHelp()
{
	SnookerApp.m_MainWnd.OnHelpDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}

void CMenuDlg::OnClickedReturn()
{
	SnookerApp.m_MainWnd.OnMenuDialog();
}
