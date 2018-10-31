// TrianglesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Snooker.h"
#include "TrianglesDlg.h"
#include ".\trianglesdlg.h"

#define DELTA 0.1f

// CTrianglesDlg dialog

IMPLEMENT_DYNAMIC(CTrianglesDlg, CDialog)

CTrianglesDlg::CTrianglesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrianglesDlg::IDD, pParent)
	, m_TriangleAX(0.0f)
	, m_TriangleAY(0.0f)
	, m_TriangleAZ(0.0f)
	, m_TriangleBX(0.0f)
	, m_TriangleBY(1.0f)
	, m_TriangleBZ(0.0f)
	, m_TriangleCX(1.0f)
	, m_TriangleCY(1.0f)
	, m_TriangleCZ(0.0f)
	, m_TriangleHole(FALSE)
	, m_TriangleReflect(FALSE)
	, m_RenderTable(TRUE)
	, m_RenderTriangles(FALSE)
	, m_RenderTriangle(TRUE)
{
	m_Triangle = NULL;
	m_Triangles = &SnookerApp.m_Billard.m_Triangles;
}

CTrianglesDlg::~CTrianglesDlg()
{
}

void CTrianglesDlg::UpdateTrianglesBox(void)
{
	int Selected = (int)m_TrianglesBox.GetCurSel();
	int Count = (int)m_Triangles->GetCount();
	
	m_TrianglesBox.ResetContent();
	m_TrianglesBox.EnableWindow(Count > 0);

	Selected = FLOAT_MID(Selected, 0, Count-1);

	for (int i = 0; i < Count; i++)
	{
		CTriangle &Triangle = m_Triangles->GetAt(i);
		CString Name;
		
		Name.Format("Trojkat %d", i);

		int Index = m_TrianglesBox.AddString(Name);
		m_TrianglesBox.SetItemDataPtr(Index, (void*)&Triangle);

		if (Index == Selected)
			m_TrianglesBox.SetCurSel(Index);
	}

	OnSelectTriangle();
}

void CTrianglesDlg::UpdateControls(void)
{
	m_TriangleDeleteBtn.EnableWindow(m_Triangle != NULL);
	m_TriangleAXEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleAYEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleAZEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleBXEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleBYEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleBZEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleCXEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleCYEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleCZEdit.EnableWindow(m_Triangle != NULL);
	m_TriangleHoleBox.EnableWindow(m_Triangle != NULL);
	m_TriangleReflectBox.EnableWindow(m_Triangle != NULL);
	m_RenderTriangleBox.EnableWindow(m_Triangle != NULL);
	m_TriangleAXSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleAYSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleAZSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleBXSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleBYSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleBZSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleCXSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleCYSpin.EnableWindow(m_Triangle != NULL);
	m_TriangleCZSpin.EnableWindow(m_Triangle != NULL);

	if (m_Triangle != NULL)
	{
		m_TriangleAX = m_Triangle->m_A.m_X;
		m_TriangleAY = m_Triangle->m_A.m_Y;
		m_TriangleAZ = m_Triangle->m_A.m_Z;
		m_TriangleBX = m_Triangle->m_B.m_X;
		m_TriangleBY = m_Triangle->m_B.m_Y;
		m_TriangleBZ = m_Triangle->m_B.m_Z;
		m_TriangleCX = m_Triangle->m_C.m_X;
		m_TriangleCY = m_Triangle->m_C.m_Y;
		m_TriangleCZ = m_Triangle->m_C.m_Z;
		m_TriangleHole = m_Triangle->m_Hole;
		m_TriangleReflect = m_Triangle->m_Reflect;
		m_TriangleNX = m_Triangle->m_N.m_X;
		m_TriangleNY = m_Triangle->m_N.m_Y;
		m_TriangleNZ = m_Triangle->m_N.m_Z;
	}
	else
	{
		m_TriangleAX = 0.0f;
		m_TriangleAY = 0.0f;
		m_TriangleAZ = 0.0f;
		m_TriangleBX = 0.0f;
		m_TriangleBY = 1.0f;
		m_TriangleBZ = 0.0f;
		m_TriangleCX = 1.0f;
		m_TriangleCY = 1.0f;
		m_TriangleCZ = 0.0f;
		m_TriangleHole = FALSE;
		m_TriangleReflect = FALSE;
		m_TriangleNX = 0.0f;
		m_TriangleNY = 0.0f;
		m_TriangleNZ = 1.0f;
	}

	UpdateData(FALSE);
}

void CTrianglesDlg::UpdateN(void)
{
	if (m_Triangle != NULL)
	{
		m_TriangleNX = m_Triangle->m_N.m_X;
		m_TriangleNY = m_Triangle->m_N.m_Y;
		m_TriangleNZ = m_Triangle->m_N.m_Z;
		UpdateData(FALSE);
	}
}

BOOL CTrianglesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateTrianglesBox();
	OnSelectTriangle();
	OnClickedRenderTable();
	OnClickedRenderTriangle();
	OnClickedRenderTriangles();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	return TRUE;
}

void CTrianglesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRIANGLE_PREVIOUS, m_TrianglePreviousBtn);
	DDX_Control(pDX, IDC_TRIANGLES, m_TrianglesBox);
	DDX_Control(pDX, IDC_TRIANGLE_NEXT, m_TriangleNextBtn);
	DDX_Control(pDX, IDC_TRIANGLE_ADD, m_TriangleAddBtn);
	DDX_Control(pDX, IDC_TRIANGLE_DELETE, m_TriangleDeleteBtn);
	DDX_Text(pDX, IDC_TRIANGLE_AX, m_TriangleAX);
	DDX_Control(pDX, IDC_TRIANGLE_AX, m_TriangleAXEdit);
	DDX_Text(pDX, IDC_TRIANGLE_AY, m_TriangleAY);
	DDX_Control(pDX, IDC_TRIANGLE_AY, m_TriangleAYEdit);
	DDX_Text(pDX, IDC_TRIANGLE_AZ, m_TriangleAZ);
	DDX_Control(pDX, IDC_TRIANGLE_AZ, m_TriangleAZEdit);
	DDX_Text(pDX, IDC_TRIANGLE_BX, m_TriangleBX);
	DDX_Control(pDX, IDC_TRIANGLE_BX, m_TriangleBXEdit);
	DDX_Text(pDX, IDC_TRIANGLE_BY, m_TriangleBY);
	DDX_Control(pDX, IDC_TRIANGLE_BY, m_TriangleBYEdit);
	DDX_Text(pDX, IDC_TRIANGLE_BZ, m_TriangleBZ);
	DDX_Control(pDX, IDC_TRIANGLE_BZ, m_TriangleBZEdit);
	DDX_Text(pDX, IDC_TRIANGLE_CX, m_TriangleCX);
	DDX_Control(pDX, IDC_TRIANGLE_CX, m_TriangleCXEdit);
	DDX_Text(pDX, IDC_TRIANGLE_CY, m_TriangleCY);
	DDX_Control(pDX, IDC_TRIANGLE_CY, m_TriangleCYEdit);
	DDX_Text(pDX, IDC_TRIANGLE_CZ, m_TriangleCZ);
	DDX_Control(pDX, IDC_TRIANGLE_CZ, m_TriangleCZEdit);
	DDX_Check(pDX, IDC_TRIANGLE_HOLE, m_TriangleHole);
	DDX_Control(pDX, IDC_TRIANGLE_HOLE, m_TriangleHoleBox);
	DDX_Check(pDX, IDC_TRIANGLE_REFLECT, m_TriangleReflect);
	DDX_Control(pDX, IDC_TRIANGLE_REFLECT, m_TriangleReflectBox);
	DDX_Check(pDX, IDC_RENDER_TABLE, m_RenderTable);
	DDX_Control(pDX, IDC_RENDER_TABLE, m_RenderTableBox);
	DDX_Check(pDX, IDC_RENDER_TRIANGLES, m_RenderTriangles);
	DDX_Control(pDX, IDC_RENDER_TRIANGLES, m_RenderTrianglesBox);
	DDX_Check(pDX, IDC_RENDER_TRIANGLE, m_RenderTriangle);
	DDX_Control(pDX, IDC_RENDER_TRIANGLE, m_RenderTriangleBox);
	DDX_Control(pDX, IDC_TRIANGLE_AX_SPIN, m_TriangleAXSpin);
	DDX_Control(pDX, IDC_TRIANGLE_AY_SPIN, m_TriangleAYSpin);
	DDX_Control(pDX, IDC_TRIANGLE_AZ_SPIN, m_TriangleAZSpin);
	DDX_Control(pDX, IDC_TRIANGLE_BX_SPIN, m_TriangleBXSpin);
	DDX_Control(pDX, IDC_TRIANGLE_BY_SPIN, m_TriangleBYSpin);
	DDX_Control(pDX, IDC_TRIANGLE_BZ_SPIN, m_TriangleBZSpin);
	DDX_Control(pDX, IDC_TRIANGLE_CX_SPIN, m_TriangleCXSpin);
	DDX_Control(pDX, IDC_TRIANGLE_CY_SPIN, m_TriangleCYSpin);
	DDX_Control(pDX, IDC_TRIANGLE_CZ_SPIN, m_TriangleCZSpin);
	DDX_Control(pDX, IDC_TRIANGLE_N_SPIN, m_TriangleNSpin);
	DDX_Text(pDX, IDC_TRIANGLE_NX, m_TriangleNX);
	DDX_Text(pDX, IDC_TRIANGLE_NY, m_TriangleNY);
	DDX_Text(pDX, IDC_TRIANGLE_NZ, m_TriangleNZ);
}

BEGIN_MESSAGE_MAP(CTrianglesDlg, CDialog)
	ON_BN_CLICKED(IDC_TRIANGLE_PREVIOUS, OnClickedTrianglePrevious)
	ON_CBN_SELCHANGE(IDC_TRIANGLES, OnSelectTriangle)
	ON_BN_CLICKED(IDC_TRIANGLE_NEXT, OnClickedTriangleNext)
	ON_BN_CLICKED(IDC_TRIANGLE_ADD, OnClickedTriangleAdd)
	ON_BN_CLICKED(IDC_TRIANGLE_DELETE, OnClickedTriangleDelete)
	ON_EN_CHANGE(IDC_TRIANGLE_AX, OnChangeTriangleAX)
	ON_EN_CHANGE(IDC_TRIANGLE_AY, OnChangeTriangleAY)
	ON_EN_CHANGE(IDC_TRIANGLE_AZ, OnChangeTriangleAZ)
	ON_EN_CHANGE(IDC_TRIANGLE_BX, OnChangeTriangleBX)
	ON_EN_CHANGE(IDC_TRIANGLE_BY, OnChangeTriangleBY)
	ON_EN_CHANGE(IDC_TRIANGLE_BZ, OnChangeTriangleBZ)
	ON_EN_CHANGE(IDC_TRIANGLE_CX, OnChangeTriangleCX)
	ON_EN_CHANGE(IDC_TRIANGLE_CY, OnChangeTriangleCY)
	ON_EN_CHANGE(IDC_TRIANGLE_CZ, OnChangeTriangleCZ)
	ON_BN_CLICKED(IDC_TRIANGLE_HOLE, OnClickedTriangleHole)
	ON_BN_CLICKED(IDC_TRIANGLE_REFLECT, OnClickedTriangleReflect)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_AX_SPIN, OnTriangleAXSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_AY_SPIN, OnTriangleAYSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_AZ_SPIN, OnTriangleAZSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_BX_SPIN, OnTriangleBXSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_BY_SPIN, OnTriangleBYSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_BZ_SPIN, OnTriangleBZSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_CX_SPIN, OnTriangleCXSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_CY_SPIN, OnTriangleCYSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_CZ_SPIN, OnTriangleCZSpin)
	ON_BN_CLICKED(IDC_RENDER_TABLE, OnClickedRenderTable)
	ON_BN_CLICKED(IDC_RENDER_TRIANGLE, OnClickedRenderTriangle)
	ON_BN_CLICKED(IDC_RENDER_TRIANGLES, OnClickedRenderTriangles)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRIANGLE_N_SPIN, OnTriangleNSpin)
END_MESSAGE_MAP()

// CTrianglesDlg message handlers

void CTrianglesDlg::OnClickedTrianglePrevious()
{
	int Index = m_TrianglesBox.GetCurSel();

	if (Index > 0)
	{
		m_TrianglesBox.SetCurSel(--Index);
		OnSelectTriangle();
	}
}

void CTrianglesDlg::OnSelectTriangle()
{
	int Index = (int)m_TrianglesBox.GetCurSel();
	int Count = (int)m_TrianglesBox.GetCount();

	m_Triangle = NULL;

	if (Index != -1)
		m_Triangle = (CTriangle*)m_TrianglesBox.GetItemDataPtr(Index);

	m_TriangleIndex = Index;
	OnClickedRenderTriangle();
	m_TrianglePreviousBtn.EnableWindow(Index > 0);
	m_TriangleNextBtn.EnableWindow(Index < Count-1);

	UpdateControls();
}

void CTrianglesDlg::OnClickedTriangleNext()
{
	int Index = m_TrianglesBox.GetCurSel();
	int Count = m_TrianglesBox.GetCount();

	if (Index < Count-1)
	{
		m_TrianglesBox.SetCurSel(++Index);
		OnSelectTriangle();
	}
}

void CTrianglesDlg::OnClickedTriangleAdd()
{
	CTriangle Triangle;

	UpdateData();

	Triangle.m_A.m_X = m_TriangleAX;
	Triangle.m_A.m_Y = m_TriangleAY;
	Triangle.m_A.m_Z = m_TriangleAZ;
	Triangle.m_B.m_X = m_TriangleBX;
	Triangle.m_B.m_Y = m_TriangleBY;
	Triangle.m_B.m_Z = m_TriangleBZ;
	Triangle.m_C.m_X = m_TriangleCX;
	Triangle.m_C.m_Y = m_TriangleCY;
	Triangle.m_C.m_Z = m_TriangleCZ;
	Triangle.m_Hole = m_TriangleHole;
	Triangle.m_Reflect = m_TriangleReflect;

	m_Triangles->Add(Triangle);
	UpdateTrianglesBox();
}

void CTrianglesDlg::OnClickedTriangleDelete()
{
	int Index = m_TrianglesBox.GetCurSel();

	if (Index != -1)
	{
		m_Triangles->RemoveAt(Index);
		UpdateTrianglesBox();
	}
}

void CTrianglesDlg::OnChangeTriangleAX()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_A.m_X = m_TriangleAX;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleAY()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_A.m_Y = m_TriangleAY;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleAZ()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_A.m_Z = m_TriangleAZ;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleBX()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_B.m_X = m_TriangleBX;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleBY()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_B.m_Y = m_TriangleBY;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleBZ()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_B.m_Z = m_TriangleBZ;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleCX()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_C.m_X = m_TriangleCX;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleCY()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_C.m_Y = m_TriangleCY;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnChangeTriangleCZ()
{
	UpdateData();

	if (m_Triangle != NULL)
	{
		m_Triangle->m_C.m_Z = m_TriangleCZ;
		m_Triangle->SetN();
		UpdateN();
	}
}

void CTrianglesDlg::OnClickedTriangleHole()
{
	UpdateData();

	if (m_Triangle != NULL)
		m_Triangle->m_Hole = m_TriangleHole;
}

void CTrianglesDlg::OnClickedTriangleReflect()
{
	UpdateData();

	if (m_Triangle != NULL)
		m_Triangle->m_Reflect = m_TriangleReflect;
}

void CTrianglesDlg::OnTriangleAXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleAX -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_A.m_X = m_TriangleAX;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleAYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleAY -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_A.m_Y = m_TriangleAY;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleAZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleAZ -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_A.m_Z = m_TriangleAZ;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleBXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleBX -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_B.m_X = m_TriangleBX;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleBYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleBY -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_B.m_Y = m_TriangleBY;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleBZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleBZ -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_B.m_Z = m_TriangleBZ;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleCXSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleCX -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_C.m_X = m_TriangleCX;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleCYSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleCY -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_C.m_Y = m_TriangleCY;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnTriangleCZSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		m_TriangleCZ -= DELTA * pNMUpDown->iDelta;
		m_Triangle->m_C.m_Z = m_TriangleCZ;
		m_Triangle->SetN();
		UpdateN();
		UpdateData(FALSE);
	}

	*pResult = 0;
}

void CTrianglesDlg::OnClickedRenderTable()
{
	CRender &Render = SnookerApp.m_Render;

	UpdateData();
	Render.m_RenderTable = m_RenderTable;
}

void CTrianglesDlg::OnClickedRenderTriangle()
{
	CRender &Render = SnookerApp.m_Render;

	UpdateData();

	if (m_RenderTriangle)
		Render.m_RenderTriangle = m_TriangleIndex;
	else
		Render.m_RenderTriangle = -1;
}

void CTrianglesDlg::OnClickedRenderTriangles()
{
	CRender &Render = SnookerApp.m_Render;

	UpdateData();
	Render.m_RenderTriangles = m_RenderTriangles;
}

void CTrianglesDlg::OnTriangleNSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	if (m_Triangle != NULL)
	{
		float Delta = -(SQR(DELTA) * pNMUpDown->iDelta);
		CVector Vector = m_Triangle->m_N * Delta;
		m_Triangle->m_A += Vector;
		m_Triangle->m_B += Vector;
		m_Triangle->m_C += Vector;
		m_Triangle->SetN();
		UpdateN();
		UpdateControls();
		// UpdateData(FALSE);
	}

	*pResult = 0;
}

BOOL CTrianglesDlg::DestroyWindow()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return CDialog::DestroyWindow();
}
