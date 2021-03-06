
/** @file AboutDlg.cpp
 *  @author Mirosław Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy obsługi okna dialogowego o programie CAboutDlg.
 *
 *  Plik zawiera implementację klasy obsługującej okno dialogowe
 *  o programie.
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "AboutDlg.h"

// CAboutDlg dialog

IMPLEMENT_DYNAMIC(CAboutDlg, CDialog)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
END_MESSAGE_MAP()

// CAboutDlg message handlers

void CAboutDlg::OnClickedOk(void)
{
	SnookerApp.m_MainWnd.OnAboutDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}
