
/** @file Mouse.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CMouse.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Mouse.h"

// CMouse

CMouse::CMouse(void)
	: m_Left(0)
	, m_LeftX(0), m_LeftY(0)
	, m_LeftDX(0), m_LeftDY(0)
	, m_Right(0)
	, m_RightX(0), m_RightY(0)
	, m_RightDX(0), m_RightDY(0)
	, Speed(0.008f)
{
}

void CMouse::MouseMove(int X, int Y)
{
	m_X = X;
	m_Y = Y;

	if (m_Left)
	{
		m_LeftDX = X - m_LeftX;
		m_LeftDY = Y - m_LeftY;
	}

	if (m_Right)
	{
		m_RightDX = X - m_RightX;
		m_RightDY = Y - m_RightY;
	}
}

void CMouse::Update(CBillardState State)
{
	switch (State)
	{
	case bsStart:
		break;

	case bsView:
		CameraMoveIn = 0;
		CameraMoveOut = m_Right ? m_RightDY : 0;

		CameraMoveForward = 0;
		CameraMoveBackward = 0;

		CameraMoveUp = 0;
		CameraMoveDown = 0;
		CameraMoveLeft = 0;
		CameraMoveRight = m_Right ? m_RightDX : 0;

		CameraZoomIn = 0;
		CameraZoomOut = 0;

		CameraRollUp = 0;
		CameraRollDown = m_Left ? m_LeftDY : 0;
		CameraRollLeft = 0;
		CameraRollRight = m_Left ? m_LeftDX : 0;

		CameraAroundUp = 0;
		CameraAroundDown = 0;
		CameraAroundLeft = 0;
		CameraAroundRight = 0;
		break;

	case bsBallInHand:
		CameraMoveIn = 0;
		CameraMoveOut = m_Right ? m_RightDY : 0;

		CameraMoveForward = 0;
		CameraMoveBackward = 0;

		CameraMoveUp = 0;
		CameraMoveDown = 0;
		CameraMoveLeft = 0;
		CameraMoveRight = 0;

		CameraZoomIn = 0;
		CameraZoomOut = 0;

		CameraRollUp = 0;
		CameraRollDown = 0;
		CameraRollLeft = 0;
		CameraRollRight = 0;

		CameraAroundUp = 0;
		CameraAroundDown = m_Left ? m_LeftDY : 0;
		CameraAroundLeft = 0;
		CameraAroundRight = m_Left ? m_LeftDX : (m_Right ? m_RightDX : 0);
		break;

	case bsAim:
		CameraMoveIn = 0;
		CameraMoveOut = m_Right ? m_RightDY : 0;

		CameraMoveForward = 0;
		CameraMoveBackward = 0;

		CameraMoveUp = 0;
		CameraMoveDown = 0;
		CameraMoveLeft = 0;
		CameraMoveRight = 0;

		CameraZoomIn = 0;
		CameraZoomOut = 0;

		CameraRollUp = 0;
		CameraRollDown = 0;
		CameraRollLeft = 0;
		CameraRollRight = 0;

		CameraAroundUp = 0;
		CameraAroundDown = m_Left ? m_LeftDY : 0;
		CameraAroundLeft = 0;
		CameraAroundRight = m_Left ? m_LeftDX : (m_Right ? m_RightDX : 0);
		break;

	case bsShot:
		CameraMoveIn = 0;
		CameraMoveOut = m_Right ? m_RightDY : 0;

		CameraMoveForward = 0;
		CameraMoveBackward = 0;

		CameraMoveUp = 0;
		CameraMoveDown = 0;
		CameraMoveLeft = 0;
		CameraMoveRight = m_Right ? m_RightDX : 0;

		CameraZoomIn = 0;
		CameraZoomOut = 0;

		CameraRollUp = 0;
		CameraRollDown = m_Left ? m_LeftDY : 0;
		CameraRollLeft = 0;
		CameraRollRight = m_Left ? m_LeftDX : 0;

		CameraAroundUp = 0;
		CameraAroundDown = 0;
		CameraAroundLeft = 0;
		CameraAroundRight = 0;
		break;

	case bsOver:
		CameraMoveIn = 0;
		CameraMoveOut = m_Right ? m_RightDY : 0;

		CameraMoveForward = 0;
		CameraMoveBackward = 0;

		CameraMoveUp = 0;
		CameraMoveDown = 0;
		CameraMoveLeft = 0;
		CameraMoveRight = m_Right ? m_RightDX : 0;

		CameraZoomIn = 0;
		CameraZoomOut = 0;

		CameraRollUp = 0;
		CameraRollDown = m_Left ? m_LeftDY : 0;
		CameraRollLeft = 0;
		CameraRollRight = m_Left ? m_LeftDX : 0;

		CameraAroundUp = 0;
		CameraAroundDown = 0;
		CameraAroundLeft = 0;
		CameraAroundRight = 0;
		break;
	}

	if (m_Left)
	{
		m_LeftX = m_X;
		m_LeftY = m_Y;
		m_LeftDX = 0;
		m_LeftDY = 0;
	}

	if (m_Right)
	{
		m_RightX = m_X;
		m_RightY = m_Y;
		m_RightDX = 0;
		m_RightDY = 0;
	}
}
