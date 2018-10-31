
/** @file BallsDlg.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy obs³uguj¹cej okno edytora bile (CBallsDlg).
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "BallsDlg.h"

#define DELTA 0.1f

// CBallsDlg dialog

IMPLEMENT_DYNAMIC(CBallsDlg, CDialog)

CBallsDlg::CBallsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBallsDlg::IDD, pParent)
	, m_BallScore(0)
	, m_BallRay(1.0f)
	, m_BallMass(1.0f)
	, m_BallColor0(1.0f)
	, m_BallColor1(1.0f)
	, m_BallColor2(1.0f)
	, m_BallColor3(1.0f)
	, m_BallPositionX(0.0f)
	, m_BallPositionY(0.0f)
	, m_BallPositionZ(0.0f)
	, m_BallWhite(0)
	, m_BallRed(1)
	, m_BallColor(0)
	, m_Ball(NULL)
{
	m_Balls = &SnookerApp.m_Billard.m_Balls;
}

CBallsDlg::~CBallsDlg()
{
}

void CBallsDlg::UpdateBallsBox(void)
{
	int Selected = (int)m_BallsBox.GetCurSel();
	int Count = (int)m_Balls->GetCount();
	
	m_BallsBox.ResetContent();
	m_BallsBox.EnableWindow(Count > 0);

	Selected = FLOAT_MID(Selected, 0, Count-1);

	for (int i = 0; i < Count; i++)
	{
		CBall &Ball = m_Balls->GetAt(i);
		CString Name;

		Name.Format("Bila %d", i);

		int Index = m_BallsBox.AddString(Name);
		m_BallsBox.SetItemDataPtr(Index, (void*)&Ball);

		if (Index == Selected)
			m_BallsBox.SetCurSel(Index);
	}

	OnSelectBall();
}

void CBallsDlg::UpdateControls(void)
{
	m_BallDeleteBtn.EnableWindow(m_Ball != NULL);
	m_BallScoreEdit.EnableWindow(m_Ball != NULL);
	m_BallRayEdit.EnableWindow(m_Ball != NULL);
	m_BallMassEdit.EnableWindow(m_Ball != NULL);
	m_BallWhiteBox.EnableWindow(m_Ball != NULL);
	m_BallRedBox.EnableWindow(m_Ball != NULL);
	m_BallColorBox.EnableWindow(m_Ball != NULL);
	m_BallColor0Edit.EnableWindow(m_Ball != NULL);
	m_BallColor1Edit.EnableWindow(m_Ball != NULL);
	m_BallColor2Edit.EnableWindow(m_Ball != NULL);
	m_BallColor3Edit.EnableWindow(m_Ball != NULL);
	m_BallPositionXEdit.EnableWindow(m_Ball != NULL);
	m_BallPositionYEdit.EnableWindow(m_Ball != NULL);
	m_BallPositionZEdit.EnableWindow(m_Ball != NULL);
	m_BallWhiteBox.EnableWindow(m_Ball != NULL);

	if (m_Ball != NULL)
	{
		m_BallScore = m_Ball->m_Score;
		m_BallRay = m_Ball->m_Ray;
		m_BallMass = m_Ball->m_Mass;
		m_BallWhite = m_Ball->m_Type == btWhite;
		m_BallRed = m_Ball->m_Type == btRed;
		m_BallColor = m_Ball->m_Type == btColor;
		m_BallColor0 = m_Ball->m_Color[0];
		m_BallColor1 = m_Ball->m_Color[1];
		m_BallColor2 = m_Ball->m_Color[2];
		m_BallColor3 = m_Ball->m_Color[3];
		m_BallPositionX = m_Ball->m_PositionOriginal.m_X;
		m_BallPositionY = m_Ball->m_PositionOriginal.m_Y;
		m_BallPositionZ = m_Ball->m_PositionOriginal.m_Z;
	}
	else
	{
		m_BallScore = 0;
		m_BallRay = 0.262f;
		m_BallMass = 1.0f;
		m_BallWhite = 0;
		m_BallRed = 1;
		m_BallColor = 0;
		m_BallColor0 = 1.0f;
		m_BallColor1 = 1.0f;
		m_BallColor2 = 1.0f;
		m_BallColor3 = 1.0f;
		m_BallPositionX = 0.0f;
		m_BallPositionY = 0.0f;
		m_BallPositionZ = 0.0f;
	}

	UpdateData(FALSE);
}

BOOL CBallsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateBallsBox();
	OnSelectBall();
	return TRUE;
}

void CBallsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BALL_PREVIOUS, m_BallPreviousBtn);
	DDX_Control(pDX, IDC_BALLS, m_BallsBox);
	DDX_Control(pDX, IDC_BALL_NEXT, m_BallNextBtn);
	DDX_Control(pDX, IDC_BALL_ADD, m_BallAddBtn);
	DDX_Control(pDX, IDC_BALL_DELETE, m_BallDeleteBtn);
	DDX_Text(pDX, IDC_BALL_SCORE, m_BallScore);
	DDX_Control(pDX, IDC_BALL_SCORE, m_BallScoreEdit);
	DDX_Text(pDX, IDC_BALL_RAY, m_BallRay);
	DDX_Control(pDX, IDC_BALL_RAY, m_BallRayEdit);
	DDX_Text(pDX, IDC_BALL_MASS, m_BallMass);
	DDX_Control(pDX, IDC_BALL_MASS, m_BallMassEdit);
	DDX_Check(pDX, IDC_BALL_WHITE, m_BallWhite);
	DDX_Control(pDX, IDC_BALL_WHITE, m_BallWhiteBox);
	DDX_Check(pDX, IDC_BALL_RED, m_BallRed);
	DDX_Control(pDX, IDC_BALL_RED, m_BallRedBox);
	DDX_Check(pDX, IDC_BALL_COLOR, m_BallColor);
	DDX_Control(pDX, IDC_BALL_COLOR, m_BallColorBox);
	DDX_Text(pDX, IDC_BALL_COLOR0, m_BallColor0);
	DDX_Control(pDX, IDC_BALL_COLOR0, m_BallColor0Edit);
	DDX_Text(pDX, IDC_BALL_COLOR1, m_BallColor1);
	DDX_Control(pDX, IDC_BALL_COLOR1, m_BallColor1Edit);
	DDX_Text(pDX, IDC_BALL_COLOR2, m_BallColor2);
	DDX_Control(pDX, IDC_BALL_COLOR2, m_BallColor2Edit);
	DDX_Text(pDX, IDC_BALL_COLOR3, m_BallColor3);
	DDX_Control(pDX, IDC_BALL_COLOR3, m_BallColor3Edit);
	DDX_Text(pDX, IDC_BALL_POSITIONX, m_BallPositionX);
	DDX_Control(pDX, IDC_BALL_POSITIONX, m_BallPositionXEdit);
	DDX_Text(pDX, IDC_BALL_POSITIONY, m_BallPositionY);
	DDX_Control(pDX, IDC_BALL_POSITIONY, m_BallPositionYEdit);
	DDX_Text(pDX, IDC_BALL_POSITIONZ, m_BallPositionZ);
	DDX_Control(pDX, IDC_BALL_POSITIONZ, m_BallPositionZEdit);
}

BEGIN_MESSAGE_MAP(CBallsDlg, CDialog)
	ON_BN_CLICKED(IDC_BALL_PREVIOUS, OnClickedBallPrevious)
	ON_CBN_SELCHANGE(IDC_BALLS, OnSelectBall)
	ON_BN_CLICKED(IDC_BALL_NEXT, OnClickedBallNext)
	ON_BN_CLICKED(IDC_BALL_ADD, OnClickedBallAdd)
	ON_BN_CLICKED(IDC_BALL_DELETE, OnClickedBallDelete)
	ON_EN_CHANGE(IDC_BALL_SCORE, OnChangeBallScore)
	ON_EN_CHANGE(IDC_BALL_RAY, OnChangeBallRay)
	ON_EN_CHANGE(IDC_BALL_MASS, OnChangeBallMass)
	ON_BN_CLICKED(IDC_BALL_WHITE, OnClickedBallWhite)
	ON_BN_CLICKED(IDC_BALL_RED, OnClickedBallRed)
	ON_BN_CLICKED(IDC_BALL_COLOR, OnClickedBallColor)
	ON_EN_CHANGE(IDC_BALL_COLOR0, OnChangeBallColor0)
	ON_EN_CHANGE(IDC_BALL_COLOR1, OnChangeBallColor1)
	ON_EN_CHANGE(IDC_BALL_COLOR2, OnChangeBallColor2)
	ON_EN_CHANGE(IDC_BALL_COLOR3, OnChangeBallColor3)
	ON_EN_CHANGE(IDC_BALL_POSITIONX, OnChangeBallPositionX)
	ON_EN_CHANGE(IDC_BALL_POSITIONY, OnChangeBallPositionY)
	ON_EN_CHANGE(IDC_BALL_POSITIONZ, OnChangeBallPositionZ)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_SCORE_SPIN, OnBallScoreSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_RAY_SPIN, OnBallRaySpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_MASS_SPIN, OnBallMassSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_COLOR0_SPIN, OnBallColor0Spin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_COLOR1_SPIN, OnBallColor1Spin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_COLOR2_SPIN, OnBallColor2Spin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_COLOR3_SPIN, OnBallColor3Spin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_POSITIONX_SPIN, OnBallPositionXSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_POSITIONY_SPIN, OnBallPositionYSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_BALL_POSITIONZ_SPIN, OnBallPositionZSpin)
END_MESSAGE_MAP()

// CBallsDlg message handlers

void CBallsDlg::OnSelectBall()
{
	int Index =(int) m_BallsBox.GetCurSel();
	int Count = (int)m_BallsBox.GetCount();

	m_Ball = NULL;

	if (Index != -1)
		m_Ball = (CBall*)m_BallsBox.GetItemDataPtr(Index);

	m_BallPreviousBtn.EnableWindow(Index > 0);
	m_BallNextBtn.EnableWindow(Index < Count-1);

	UpdateControls();
}

void CBallsDlg::OnClickedBallAdd()
{
	CBall Ball;
	Ball.m_Render = TRUE;
	Ball.m_Simulate = FALSE;
	m_Balls->Add(Ball);
	UpdateBallsBox();
}

void CBallsDlg::OnClickedBallDelete()
{
	int Index = m_BallsBox.GetCurSel();

	if (Index != -1)
	{
		m_Balls->RemoveAt(Index);
		UpdateBallsBox();
	}
}

void CBallsDlg::OnClickedBallPrevious()
{
	int Index = m_BallsBox.GetCurSel();

	if (Index > 0)
	{
		m_BallsBox.SetCurSel(--Index);
		OnSelectBall();
	}
}

void CBallsDlg::OnClickedBallNext()
{
	int Index = m_BallsBox.GetCurSel();
	int Count = m_BallsBox.GetCount();

	if (Index < Count-1)
	{
		m_BallsBox.SetCurSel(++Index);
		OnSelectBall();
	}
}

void CBallsDlg::OnChangeBallScore()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Score = m_BallScore;
}

void CBallsDlg::OnChangeBallRay()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Ray = m_BallRay;
}

void CBallsDlg::OnChangeBallMass()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Mass = m_BallMass;
}

void CBallsDlg::OnClickedBallWhite()
{
	UpdateData();

	if (m_Ball != NULL)
	{
		BOOL Found = FALSE;

		if (m_BallWhite)
		{
			for (int i = 0; i < m_Balls->GetCount(); i++)
			{
				if (m_Balls->GetAt(i).m_Type == btWhite)
				{
					Found = TRUE;
					break;
				}
			}
		}

		if (!Found)
		{
			m_Ball->m_Type = m_BallWhite ? btWhite : m_Ball->m_Type;
		}
		else
		{
			m_BallWhite = FALSE;
			m_BallRed = FALSE;
			m_BallColor = FALSE;
			UpdateData(FALSE);
		}
	}
}

void CBallsDlg::OnClickedBallRed()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Type = m_BallRed ? btRed : m_Ball->m_Type;
}

void CBallsDlg::OnClickedBallColor()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Type = m_BallColor ? btColor : m_Ball->m_Type;
}

void CBallsDlg::OnChangeBallColor0()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Color[0] = m_BallColor0;
}

void CBallsDlg::OnChangeBallColor1()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Color[1] = m_BallColor1;
}

void CBallsDlg::OnChangeBallColor2()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Color[2] = m_BallColor2;
}

void CBallsDlg::OnChangeBallColor3()
{
	UpdateData();

	if (m_Ball != NULL)
		m_Ball->m_Color[3] = m_BallColor3;
}

void CBallsDlg::OnChangeBallPositionX()
{
	UpdateData();

	if (m_Ball != NULL)
	{
		m_Ball->m_Position.m_X = m_BallPositionX;
		m_Ball->m_PositionPrevious.m_X = m_BallPositionX;
		m_Ball->m_PositionOriginal.m_X = m_BallPositionX;
	}
}

void CBallsDlg::OnChangeBallPositionY()
{
	UpdateData();

	if (m_Ball != NULL)
	{
		m_Ball->m_Position.m_Y = m_BallPositionY;
		m_Ball->m_PositionPrevious.m_Y = m_BallPositionY;
		m_Ball->m_PositionOriginal.m_Y = m_BallPositionY;
	}
}

void CBallsDlg::OnChangeBallPositionZ()
{
	UpdateData();

	if (m_Ball != NULL)
	{
		m_Ball->m_Position.m_Z = m_BallPositionZ;
		m_Ball->m_PositionPrevious.m_Z = m_BallPositionZ;
		m_Ball->m_PositionOriginal.m_Z = m_BallPositionZ;
	}
}

void CBallsDlg::OnBallScoreSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallScore -= pNMUpDown->iDelta;
		m_BallScore = FLOAT_MIN(m_BallScore, 0);
		m_Ball->m_Score = m_BallScore;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallRaySpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallRay -= DELTA * pNMUpDown->iDelta;
		m_BallRay = FLOAT_MIN(m_BallRay, 0.0f);
		m_Ball->m_Ray = m_BallRay;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallMassSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallMass -= DELTA * pNMUpDown->iDelta;
		m_BallMass = FLOAT_MIN(m_BallMass, 0.0f);
		m_Ball->m_Mass = m_BallMass;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallColor0Spin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallColor0 -= DELTA * pNMUpDown->iDelta;
		m_BallColor0 = FLOAT_MID(m_BallColor0, 0.0f, 1.0f);
		m_Ball->m_Color[0] = m_BallColor0;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallColor1Spin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallColor1 -= DELTA * pNMUpDown->iDelta;
		m_BallColor1 = FLOAT_MID(m_BallColor1, 0.0f, 1.0f);
		m_Ball->m_Color[1] = m_BallColor1;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallColor2Spin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallColor2 -= DELTA * pNMUpDown->iDelta;
		m_BallColor2 = FLOAT_MID(m_BallColor2, 0.0f, 1.0f);
		m_Ball->m_Color[2] = m_BallColor2;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallColor3Spin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallColor3 -= DELTA * pNMUpDown->iDelta;
		m_BallColor3 = FLOAT_MID(m_BallColor3, 0.0f, 1.0f);
		m_Ball->m_Color[3] = m_BallColor3;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallPositionXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallPositionX -= DELTA * pNMUpDown->iDelta;
		m_Ball->m_Position.m_X = m_BallPositionX;
		m_Ball->m_PositionOriginal.m_X = m_BallPositionX;
		m_Ball->m_PositionPrevious.m_X = m_BallPositionX;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallPositionYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallPositionY -= DELTA * pNMUpDown->iDelta;
		m_Ball->m_Position.m_Y = m_BallPositionY;
		m_Ball->m_PositionOriginal.m_Y = m_BallPositionY;
		m_Ball->m_PositionPrevious.m_Y = m_BallPositionY;
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CBallsDlg::OnBallPositionZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Ball != NULL)
	{
		m_BallPositionZ -= DELTA * pNMUpDown->iDelta;
		m_Ball->m_Position.m_Z = m_BallPositionZ;
		m_Ball->m_PositionOriginal.m_Z = m_BallPositionZ;
		m_Ball->m_PositionPrevious.m_Z = m_BallPositionZ;
		UpdateData(FALSE);
	}

	*pResult = 0;
}
