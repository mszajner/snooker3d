
/** @file MyFont.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CMyFont.
 *
 */ 

#pragma once

#include "Texture.h"

/** @brief Klasa czcionki.
 */
class CMyFont {

	private:
		/** @brief Tekstura zawieraj�ca znaki. */
		CTexture m_Texture;
		/** @brief Identyfikator listy znak�w. */
		GLuint m_FontList;

	public:
		/** @brief Domy�lny konstruktor.
		 */
		CMyFont();

		/** @brief Destruktor.
		 */
		~CMyFont();

	public:
		/** @brief Funkcja �aduje i tworzy czcionk� z pliku graficznego BMP.
		 *  @param[in] FileName Nazwa pliku.
		 *  @retval Funkcja zwraca warto�� r�n� od zera je�li uda�o si� za�adowa�
		 *          i utworzy� czcionk�.
		 */
		int Load(const CString &FileName);

		/** @brief Funkcja usuwa teksture i listy.
		 */
		void Finalize(void);

	public:
		/** @brief Funkcja wy�wietla tekst na podanych wsp�rz�dnych.
		 *  @param[in] Text Tekst do wy�wietlenia.
		 *  @param[in] Position Pozycja tekstu.
		 *  @param[in] X Pozycja tekstu na osi OX.
		 *  @param[in] Y Pozycja tekstu na osi OY.
		 *  @param[in] R Sk�adnik czerwony koloru tekstu.
		 *  @param[in] G Sk�adnik zielony koloru tekstu.
		 *  @param[in] B Sk�adnik niebieski koloru tekstu.
		 *  @param[in] A Prze�roczysto�� tekstu.
		 *  @param[in] W Szeroko�� pojedynczej litery.
		 *  @param[in] H Wysoko�� pojedynczej litery.
		 */
		void Print(const CString &Text, float X, float Y, 
			float R = 1.0f, float G = 1.0f, float B = 1.0f, float A = 1.0f, 
			float W = 16.0f, float H = 16.0f);

};
