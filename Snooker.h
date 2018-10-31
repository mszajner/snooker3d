// Snooker.h : main header file for the Snooker application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include "resource.h"
#include "MainWnd.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Billard.h"
#include "Render.h"
#include "Timer.h"
#include "Draw.h"

// CSnookerApp:
// See Snooker.cpp for the implementation of this class
//

class CSnookerApp : public CWinApp {

	public:
		HACCEL     m_hAccel;
		CMainWnd   m_MainWnd;
		CRender    m_Render;
		CBillard   m_Billard;
		CTimer     m_Timer;
		CKeyboard  m_Keyboard;
		CMouse     m_Mouse;
		CCamera    m_Camera;

	public:
		CSnookerApp();
		virtual ~CSnookerApp(void);

	public:
		DECLARE_MESSAGE_MAP()

	public:
		virtual BOOL InitInstance();

};

extern CSnookerApp SnookerApp;
