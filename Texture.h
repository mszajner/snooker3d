
/** @file Texture.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CTexture.
 *
 *  Plik zawiera interfejs klasy CTexture.
 *
 */ 

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

/** @brief Klasa ³aduj¹ca i binduj¹ca tekstury.
 */
class CTexture {

	private:
		/** @brief Identyfikator tekstury. */
		GLuint m_TextureId;
		/** @brief WskaŸnik do struktury wczytanej tesktury. */
		AUX_RGBImageRec *m_Texture;

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CTexture();

		/** @brief Destruktor. 
		 */
		~CTexture();

	public:
		/** @brief Funkcja ³aduje teksturê z pliku.
		 *  @param[in] FileName Nazwa pliku bitmapy.
		 *  @param[in] LA Flaga czy tekstura ma byæ wczytana jako LUMINANCE_ALPHA czy RGBA.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli uda³o siê wczytaæ teksturê.
		 */
		int Load(const CString &FileName, int LA = 0);

		/** @brief Funkcja zwalnia przydzielone zasoby teksturze.
		 */
		void Finalize(void);

	public:
		/** @brief Funkcja wybiera teksturê do teksturowania kolejnych elementów 3D.
		 */
		void Bind(void);

};
