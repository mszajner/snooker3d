
/** @file Render.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy CRender.
 *
 *  Plik zawiera interfejs klasy CRender.
 *
 */ 

#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "Camera.h"
#include "Billard.h"
#include "Draw.h"
#include "MyFont.h"

/**
 *  Klasa zawiera szereg funkcji odpowiedzialnych za renderowanie element�w gry.
 *  Renderuje st�, bile, o�wietlenie, kij, itd.
 *
 *  @brief Klasa reprezentuje obiekt renderowania.
 */
class CRender {

	private:
		/** @brief Stosunek szeroko�ci do wysoko�ci okna renderowania. */
		float m_Ratio;
		/** @brief Kwadryka bil. */
		GLUquadricObj *m_Quadric;
		/** @brief Kwadryka kija. */
		GLUquadricObj *m_StickQ;
		/** @brief Parametry �wiat�a. */
		LIGHT m_Light;
		/** @brief Czcionka. */
		CMyFont m_Font;
		/** @brief Tekstura kija. */
		CTexture m_StickTex;
		/** @brief Si�a uderzenia. */
		float m_Force, m_dForce;

	public:
		/** @brief Flaga renderowania bil. */
		int m_RenderBalls;
		/** @brief Flaga renderowania kamery. */
		int m_RenderCamera;
		/** @brief Flaga renderowania tr�jk�ta. */
		int m_RenderTriangle;
		/** @brief Flaga renderowania tr�jk�t�w. */
		int m_RenderTriangles;
		/** @brief Flaga renderowania sto�u. */
		int m_RenderTable;
		/** @brief Flaga renderowania o�wietlenia. */
		int m_RenderLight;
		/** @brief Flaga renderowania paska wzrostu sto�u. */
		int m_RenderBar;
		/** @brief Flaga renderowania opis�w. */
		int m_RenderState;
		/** @brief Flaga renderowania podgl�du sto�u. */
		int m_RenderPreview;

	private:
		/** @brief Funkcja renderuj�ca st�. 
		 *  @param[in] Time Czas, kt�ry up�yn�� od poprzedniej klatki.
		 */
		void RenderStick(float Time);

		/** @brief Funkcja redneruj�ca bil�.
		 */
		void RenderBall(const CBall &Ball);

		/** @brief Funkcja renderuj�ca wszystkie bile.
		 */
		void RenderBalls(void);

		/** @brief Funkcja renderuj�ca pojedynczy tr�jk�t.
		 */
		void RenderTriangle(const CTriangle &Triangle, float Alpha = 1.0f);

		/** @brief Funkcja renderuj�ca wszystkie tr�jk�tu.
		 */
		void RenderTriangles(void);

		/** @brief Funkcja renderuj�ca pasek wzrostu si�y.
		 */
		void RenderBar(void);

		/** @brief Funkcja renderuj�ca aktualny uk�ad wsp�rz�dnych.
		 */
		void RenderAxes(void);

		/** @brief Funkcja renderuj�ca opisy.
		 */
		void RenderState(void);

		/** @brief Funkcja renderuj�ca podgl�d sto�u.
		 */
		void RenderPreview(void);

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CRender(void);

	public:
		/** @brief Funkcja inicjalizuj�ca klas� renderowania.
		 */
		void Initialize(void);

		/** @brief Funkcja zwalniaj�ca zasoby renderowania.
		 */
		void Finalize(void);

	public:
		/** @brief G��wna funkcja renderuj�ca.
		 *  @param[in] Time Czas, kt�ry up�yn�� od poprzedniej klatki.
		 */
		void Run(float Time);

		void SetQuadricStyle(GLenum style) {
			gluQuadricDrawStyle(m_Quadric, style);
			gluQuadricDrawStyle(m_StickQ, style);
		}

	public:
		/** @brief Ustaw wsp�czynnik perspektywy.
		 */
		void SetRatio(int Width, int Height);

};
