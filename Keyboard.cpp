
/** @file Keyboard.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CKeyboard.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Keyboard.h"

// CKeyboard

CKeyboard::CKeyboard()
{
	ZeroMemory(&m_State, sizeof(m_State));
}

void CKeyboard::KeyDown(UINT nChar, UINT nFlags)
{
	if (nChar >= 0 && nChar <= 255)
		m_State[nChar] = TRUE;
}

void CKeyboard::KeyUp(UINT nChar, UINT nFlags)
{
	if (nChar >= 0 && nChar <= 255)
		m_State[nChar] = FALSE;
}

void CKeyboard::Update(CBillardState State)
{
	switch (State)
	{
	case bsStart:
		CameraMoveIn         = 0;
		CameraMoveOut        = 0;

		CameraMoveForward    = 0;
		CameraMoveBackward   = 0;

		CameraMoveUp         = 0;
		CameraMoveDown       = 0;
		CameraMoveLeft       = 0;
		CameraMoveRight      = 0;

		CameraZoomIn         = 0;
		CameraZoomOut        = 0;

		CameraRollUp         = 0;
		CameraRollDown       = 0;
		CameraRollLeft       = 0;
		CameraRollRight      = 0;

		CameraAroundUp       = 0;
		CameraAroundDown     = 0;
		CameraAroundLeft     = 0;
		CameraAroundRight    = 0;

		BallMoveForward      = 0;
		BallMoveBackward     = 0;
		BallMoveLeft         = 0;
		BallMoveRight        = 0;

		NextState            = 0;
		PrevState            = 0;
		Shot                 = 0;
		break;

	case bsView:
		CameraMoveIn         = m_State[VK_PRIOR];
		CameraMoveOut        = m_State[VK_NEXT];

		CameraMoveForward    = m_State[VK_UP];
		CameraMoveBackward   = m_State[VK_DOWN];

		CameraMoveUp         = m_State[VK_HOME];
		CameraMoveDown       = m_State[VK_END];
		CameraMoveLeft       = m_State[VK_LEFT];
		CameraMoveRight      = m_State[VK_RIGHT];

		CameraZoomIn         = m_State[VK_ADD];
		CameraZoomOut        = m_State[VK_SUBTRACT];

		CameraRollUp         = m_State['W'];
		CameraRollDown       = m_State['S'];
		CameraRollLeft       = m_State['A'];
		CameraRollRight      = m_State['D'];

		CameraAroundUp       = 0;
		CameraAroundDown     = 0;
		CameraAroundLeft     = 0;
		CameraAroundRight    = 0;

		BallMoveForward      = 0;
		BallMoveBackward     = 0;
		BallMoveLeft         = 0;
		BallMoveRight        = 0;

		NextState            = m_State[VK_SPACE];
		PrevState            = m_State[VK_BACK];
		Shot                 = 0;

		m_State[VK_BACK]     = 0;
		m_State[VK_SPACE]    = 0;
		break;

	case bsBallInHand:
		CameraMoveIn         = m_State[VK_PRIOR];
		CameraMoveOut        = m_State[VK_NEXT];

		CameraMoveForward    = 0;
		CameraMoveBackward   = 0;

		CameraMoveUp         = 0;
		CameraMoveDown       = 0;
		CameraMoveLeft       = 0;
		CameraMoveRight      = 0;

		CameraZoomIn         = m_State[VK_ADD];
		CameraZoomOut        = m_State[VK_SUBTRACT];

		CameraRollUp         = 0;
		CameraRollDown       = 0;
		CameraRollLeft       = 0;
		CameraRollRight      = 0;

		CameraAroundUp       = m_State['W'];
		CameraAroundDown     = m_State['S'];
		CameraAroundLeft     = m_State['A'];
		CameraAroundRight    = m_State['D'];

		BallMoveForward      = m_State[VK_UP];
		BallMoveBackward     = m_State[VK_DOWN];
		BallMoveLeft         = m_State[VK_LEFT];
		BallMoveRight        = m_State[VK_RIGHT];

		NextState            = m_State[VK_SPACE];
		PrevState            = m_State[VK_BACK];
		Shot                 = 0;

		m_State[VK_BACK]     = 0;
		m_State[VK_SPACE]    = 0;
		break;

	case bsAim:
		CameraMoveIn         = m_State[VK_PRIOR];
		CameraMoveOut        = m_State[VK_NEXT];

		CameraMoveForward    = 0;
		CameraMoveBackward   = 0;

		CameraMoveUp         = 0;
		CameraMoveDown       = 0;
		CameraMoveLeft       = 0;
		CameraMoveRight      = 0;

		CameraZoomIn         = m_State[VK_ADD];
		CameraZoomOut        = m_State[VK_SUBTRACT];

		CameraRollUp         = 0;
		CameraRollDown       = 0;
		CameraRollLeft       = 0;
		CameraRollRight      = 0;

		CameraAroundUp       = m_State['W'] || m_State[VK_UP];
		CameraAroundDown     = m_State['S'] || m_State[VK_DOWN];
		CameraAroundLeft     = m_State['A'] || m_State[VK_LEFT];
		CameraAroundRight    = m_State['D'] || m_State[VK_RIGHT];

		BallMoveForward      = 0;
		BallMoveBackward     = 0;
		BallMoveLeft         = 0;
		BallMoveRight        = 0;

		NextState            = 0;
		PrevState            = m_State[VK_BACK];
		Shot                 = m_State[VK_SPACE];

		m_State[VK_BACK]     = 0;
		break;

	case bsShot:
		CameraMoveIn         = m_State[VK_PRIOR];
		CameraMoveOut        = m_State[VK_NEXT];

		CameraMoveForward    = m_State[VK_UP];
		CameraMoveBackward   = m_State[VK_DOWN];

		CameraMoveUp         = m_State[VK_HOME];
		CameraMoveDown       = m_State[VK_END];
		CameraMoveLeft       = m_State[VK_LEFT];
		CameraMoveRight      = m_State[VK_RIGHT];

		CameraZoomIn         = m_State[VK_ADD];
		CameraZoomOut        = m_State[VK_SUBTRACT];

		CameraRollUp         = m_State['W'];
		CameraRollDown       = m_State['S'];
		CameraRollLeft       = m_State['A'];
		CameraRollRight      = m_State['D'];

		CameraAroundUp       = 0;
		CameraAroundDown     = 0;
		CameraAroundLeft     = 0;
		CameraAroundRight    = 0;

		BallMoveForward      = 0;
		BallMoveBackward     = 0;
		BallMoveLeft         = 0;
		BallMoveRight        = 0;

		NextState            = 0;
		PrevState            = 0;
		Shot                 = 0;
		break;

	case bsOver:
		CameraMoveIn         = m_State[VK_PRIOR];
		CameraMoveOut        = m_State[VK_NEXT];

		CameraMoveForward    = m_State[VK_UP];
		CameraMoveBackward   = m_State[VK_DOWN];

		CameraMoveUp         = m_State[VK_HOME];
		CameraMoveDown       = m_State[VK_END];
		CameraMoveLeft       = m_State[VK_LEFT];
		CameraMoveRight      = m_State[VK_RIGHT];

		CameraZoomIn         = m_State[VK_ADD];
		CameraZoomOut        = m_State[VK_SUBTRACT];

		CameraRollUp         = m_State['W'];
		CameraRollDown       = m_State['S'];
		CameraRollLeft       = m_State['A'];
		CameraRollRight      = m_State['D'];

		CameraAroundUp       = 0;
		CameraAroundDown     = 0;
		CameraAroundLeft     = 0;
		CameraAroundRight    = 0;

		BallMoveForward      = 0;
		BallMoveBackward     = 0;
		BallMoveLeft         = 0;
		BallMoveRight        = 0;

		NextState            = 0;
		PrevState            = 0;
		Shot                 = 0;
		break;
	}
}
