
/** @file Texture.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CTexture.
 *
 *  Plik zawiera interfejs klasy CTexture.
 *
 */ 

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

/** @brief Klasa �aduj�ca i binduj�ca tekstury.
 */
class CTexture {

	private:
		/** @brief Identyfikator tekstury. */
		GLuint m_TextureId;
		/** @brief Wska�nik do struktury wczytanej tesktury. */
		AUX_RGBImageRec *m_Texture;

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CTexture();

		/** @brief Destruktor. 
		 */
		~CTexture();

	public:
		/** @brief Funkcja �aduje tekstur� z pliku.
		 *  @param[in] FileName Nazwa pliku bitmapy.
		 *  @param[in] LA Flaga czy tekstura ma by� wczytana jako LUMINANCE_ALPHA czy RGBA.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� wczyta� tekstur�.
		 */
		int Load(const CString &FileName, int LA = 0);

		/** @brief Funkcja zwalnia przydzielone zasoby teksturze.
		 */
		void Finalize(void);

	public:
		/** @brief Funkcja wybiera tekstur� do teksturowania kolejnych element�w 3D.
		 */
		void Bind(void);

};
