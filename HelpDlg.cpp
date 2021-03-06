
/** @file HelpDlg.cpp
 *  @author Mirosław Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy obsługi okna dialogowego pomocy CHelpDlg.
 *
 *  Plik zawiera implementację klasy obsługującej okno dialogowe pomocy.
 */

#include "stdafx.h"
#include "Snooker.h"
#include "HelpDlg.h"

// CHelpDlg dialog

IMPLEMENT_DYNAMIC(CHelpDlg, CDialog)
CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnClickedOk)
END_MESSAGE_MAP()

// CHelpDlg message handlers

void CHelpDlg::OnClickedOk()
{
	SnookerApp.m_MainWnd.OnHelpDialog();
	SnookerApp.m_MainWnd.OnMenuDialog();
}
