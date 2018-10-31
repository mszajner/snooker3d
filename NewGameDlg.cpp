
/** @file NewGameDlg.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CNewGameDlg - okno dialogowe nowej gry.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "NewGameDlg.h"

// CNewGameDlg dialog

IMPLEMENT_DYNAMIC(CNewGameDlg, CDialog)
CNewGameDlg::CNewGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewGameDlg::IDD, pParent)
	, m_Player1(_T(""))
	, m_Player2(_T(""))
{
}

CNewGameDlg::~CNewGameDlg()
{
}

void CNewGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PLAYER1, m_Player1);
	DDX_Text(pDX, IDC_PLAYER2, m_Player2);
}

BEGIN_MESSAGE_MAP(CNewGameDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnClickedCancel)
END_MESSAGE_MAP()

// CNewGameDlg message handlers

void CNewGameDlg::OnClickedOk()
{
	CPlayers Players;
	UpdateData();
	if (m_Player1.IsEmpty())
		m_Player1 = "Gracz 1";
	if (m_Player2.IsEmpty())
		m_Player2 = "Gracz 2";
	SnookerApp.m_MainWnd.OnNewGameDialog();
	Players.Add(CPlayer(m_Player1));
	Players.Add(CPlayer(m_Player2));
	SnookerApp.m_Billard.NewGame(Players);
}

void CNewGameDlg::OnClickedCancel()
{
	SnookerApp.m_MainWnd.OnNewGameDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}
