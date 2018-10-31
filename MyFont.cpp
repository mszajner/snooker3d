
/** @file MyFont.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CMyFont.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "MyFont.h"

// CMyFont

CMyFont::CMyFont()
	: m_FontList(0)
{
}

CMyFont::~CMyFont()
{
	Finalize();
}

int CMyFont::Load(const CString &FileName)
{
	if (!m_Texture.Load(FileName, 1))
		return 0;

	// zarezerwuj miejsce na 256 list
	m_FontList = glGenLists(256);

	int x, y, i;
	float fx, fy;
	const float dx = 1.0f / 16.0f, dy = 1.0f / 16.0f;

	for (y = 0, i = 0, fy = 0.0f; y < 16; y++, fy += dy)
	{
		for (x = 0, fx = 0.0f; x < 16; x++, i++, fx += dx)
		{
			glNewList(m_FontList + i, GL_COMPILE);
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
				glBegin(GL_QUADS);
					glTexCoord2f(fx,      1.0f-(fy + dy)); glVertex2f(0.0f, 0.0f);
					glTexCoord2f(fx + dx, 1.0f-(fy + dy)); glVertex2f(1.0f, 0.0f);
					glTexCoord2f(fx + dx, 1.0f-(fy));      glVertex2f(1.0f, 1.0f);
					glTexCoord2f(fx,      1.0f-(fy));      glVertex2f(0.0f, 1.0f);
				glEnd();
				glTranslatef(1.0f, 0.0f, 0.0f);
			glEndList();
		}
	}

	return 0;
}

void CMyFont::Finalize(void)
{
	// usun listy
	if (m_FontList > 0)
	{
		glDeleteLists(m_FontList, 256);
		m_FontList = 0;
		m_Texture.Finalize();
	}
}

void CMyFont::Print(const CString &Text, float X, float Y, float R, float G, float B, float A, float W, float H)
{
	glPushAttrib(GL_ENABLE_BIT);

	// wlacz teksturowanie
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// wybierz teksture
	m_Texture.Bind();

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(X, Y, 0.0f);
		glScalef(W, H, 1.0f);
		glListBase(m_FontList);
		glColor4f(R, G, B, A);
		glCallLists((GLsizei)Text.GetLength(), GL_UNSIGNED_BYTE, Text);
	glPopMatrix();

	glPopAttrib();
}
