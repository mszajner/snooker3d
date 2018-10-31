#pragma once

#include "afxwin.h"
#include "Billard.h"

// CTrianglesDlg dialog

class CTrianglesDlg : public CDialog {

	public:
		int m_TriangleIndex;
		CTriangle *m_Triangle;
		CTriangles *m_Triangles;
		CButton m_TrianglePreviousBtn;
		CComboBox m_TrianglesBox;
		CButton m_TriangleNextBtn;
		CButton m_TriangleAddBtn;
		CButton m_TriangleDeleteBtn;
		float m_TriangleAX;
		CEdit m_TriangleAXEdit;
		float m_TriangleAY;
		CEdit m_TriangleAYEdit;
		float m_TriangleAZ;
		CEdit m_TriangleAZEdit;
		float m_TriangleBX;
		CEdit m_TriangleBXEdit;
		float m_TriangleBY;
		CEdit m_TriangleBYEdit;
		float m_TriangleBZ;
		CEdit m_TriangleBZEdit;
		float m_TriangleCX;
		CEdit m_TriangleCXEdit;
		float m_TriangleCY;
		CEdit m_TriangleCYEdit;
		float m_TriangleCZ;
		CEdit m_TriangleCZEdit;
		BOOL m_TriangleHole;
		CButton m_TriangleHoleBox;
		BOOL m_TriangleReflect;
		CButton m_TriangleReflectBox;
		BOOL m_RenderTable;
		CButton m_RenderTableBox;
		BOOL m_RenderTriangles;
		CButton m_RenderTrianglesBox;
		BOOL m_RenderTriangle;
		CButton m_RenderTriangleBox;
		CSpinButtonCtrl m_TriangleAXSpin;
		CSpinButtonCtrl m_TriangleAYSpin;
		CSpinButtonCtrl m_TriangleAZSpin;
		CSpinButtonCtrl m_TriangleBXSpin;
		CSpinButtonCtrl m_TriangleBYSpin;
		CSpinButtonCtrl m_TriangleBZSpin;
		CSpinButtonCtrl m_TriangleCXSpin;
		CSpinButtonCtrl m_TriangleCYSpin;
		CSpinButtonCtrl m_TriangleCZSpin;
		CSpinButtonCtrl m_TriangleNSpin;
		float m_TriangleNX;
		float m_TriangleNY;
		float m_TriangleNZ;

	private:
		void UpdateTrianglesBox(void);
		void UpdateControls(void);
		void UpdateN(void);

	private:
		DECLARE_DYNAMIC(CTrianglesDlg)

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		virtual BOOL OnInitDialog();
		DECLARE_MESSAGE_MAP()

	public:
		CTrianglesDlg(CWnd* pParent = NULL);
		virtual ~CTrianglesDlg();

	public:
		enum { IDD = IDD_TRIANGLES_DIALOG };

	public:
		afx_msg void OnClickedTrianglePrevious();
		afx_msg void OnSelectTriangle();
		afx_msg void OnClickedTriangleNext();
		afx_msg void OnClickedTriangleAdd();
		afx_msg void OnClickedTriangleDelete();
		afx_msg void OnChangeTriangleAX();
		afx_msg void OnChangeTriangleAY();
		afx_msg void OnChangeTriangleAZ();
		afx_msg void OnChangeTriangleBX();
		afx_msg void OnChangeTriangleBY();
		afx_msg void OnChangeTriangleBZ();
		afx_msg void OnChangeTriangleCX();
		afx_msg void OnChangeTriangleCY();
		afx_msg void OnChangeTriangleCZ();
		afx_msg void OnChangeTriangleName();
		afx_msg void OnClickedTriangleHole();
		afx_msg void OnClickedTriangleReflect();
		afx_msg void OnTriangleAXSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleAYSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleAZSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleBXSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleBYSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleBZSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleCXSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleCYSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnTriangleCZSpin(NMHDR *pNMHDR, LRESULT *pResult);
		afx_msg void OnClickedRenderTable();
		afx_msg void OnClickedRenderTriangle();
		afx_msg void OnClickedRenderTriangles();
		afx_msg void OnTriangleNSpin(NMHDR *pNMHDR, LRESULT *pResult);

		virtual BOOL DestroyWindow();
};
