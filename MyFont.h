
/** @file MyFont.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @author Piotr Repetowski (peter_r@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CMyFont.
 *
 */ 

#pragma once

#include "Texture.h"

/** @brief Klasa czcionki.
 */
class CMyFont {

	private:
		/** @brief Tekstura zawieraj¹ca znaki. */
		CTexture m_Texture;
		/** @brief Identyfikator listy znaków. */
		GLuint m_FontList;

	public:
		/** @brief Domyœlny konstruktor.
		 */
		CMyFont();

		/** @brief Destruktor.
		 */
		~CMyFont();

	public:
		/** @brief Funkcja ³aduje i tworzy czcionkê z pliku graficznego BMP.
		 *  @param[in] FileName Nazwa pliku.
		 *  @retval Funkcja zwraca wartoœæ ró¿n¹ od zera jeœli uda³o siê za³adowaæ
		 *          i utworzyæ czcionkê.
		 */
		int Load(const CString &FileName);

		/** @brief Funkcja usuwa teksture i listy.
		 */
		void Finalize(void);

	public:
		/** @brief Funkcja wyœwietla tekst na podanych wspó³rzêdnych.
		 *  @param[in] Text Tekst do wyœwietlenia.
		 *  @param[in] Position Pozycja tekstu.
		 *  @param[in] X Pozycja tekstu na osi OX.
		 *  @param[in] Y Pozycja tekstu na osi OY.
		 *  @param[in] R Sk³adnik czerwony koloru tekstu.
		 *  @param[in] G Sk³adnik zielony koloru tekstu.
		 *  @param[in] B Sk³adnik niebieski koloru tekstu.
		 *  @param[in] A PrzeŸroczystoœæ tekstu.
		 *  @param[in] W Szerokoœæ pojedynczej litery.
		 *  @param[in] H Wysokoœæ pojedynczej litery.
		 */
		void Print(const CString &Text, float X, float Y, 
			float R = 1.0f, float G = 1.0f, float B = 1.0f, float A = 1.0f, 
			float W = 16.0f, float H = 16.0f);

};
