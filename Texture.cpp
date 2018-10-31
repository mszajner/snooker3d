
/** @file Texture.cpp
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik implementacji klasy CTexture.
 *
 *  Plik zawiera implementacjê klasy CTexture.
 *
 */ 

#include "stdafx.h"
#include "Snooker.h"
#include "Texture.h"

// CTexture

CTexture::CTexture()
	: m_TextureId(0)
	, m_Texture(NULL)
{
}

CTexture::~CTexture()
{
	Finalize();
}

int CTexture::Load(const CString &FileName, int LA)
{
	int Status = 0;

	if (m_Texture = auxDIBImageLoad(FileName))
	{
		Status = 1;

		if (LA)
		{
			unsigned char *Data = new unsigned char [m_Texture->sizeX * m_Texture->sizeY * 2];

			for (int x = 0, i = 0, j = 0; i < (m_Texture->sizeY*m_Texture->sizeX); i++, j+=3, x+=2)
			{
				Data[x] = 0;
				Data[x+1] = (m_Texture->data[j] + m_Texture->data[j+1] + m_Texture->data[j+2]) / 3;
			}

			// wygeneruj miejsce na teksture
			glGenTextures(1, &m_TextureId);

			// wybierz teksture
			Bind();

			// zaladuj teksture z wczytanego pliku
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, m_Texture->sizeX,
				m_Texture->sizeY, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, Data);

			delete Data;
		}
		else
		{
			// wygeneruj miejsce na teksture
			glGenTextures(1, &m_TextureId);

			// wybierz teksture
			Bind();

			// zaladuj teksture z wczytanego pliku
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Texture->sizeX,
				m_Texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Texture->data);
		}

		// ustaw parametry tekstury
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// zwolnij pamiec
		free(m_Texture->data);
		free(m_Texture);
		m_Texture = NULL;
	}

	// zwroc status
	return Status;
}

void CTexture::Finalize(void)
{
	// zwolnij teksture
	if (m_TextureId > 0)
	{
		glDeleteTextures(1, &m_TextureId);
		m_TextureId = 0;
	}

	if (m_Texture != NULL)
	{
		free(m_Texture->data);
		free(m_Texture);
		m_Texture = NULL;
	}
}

void CTexture::Bind(void)
{
	// wybierz teksture
	if (m_TextureId > 0)
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
}
