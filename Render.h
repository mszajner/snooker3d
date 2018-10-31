
/** @file Render.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy CRender.
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
 *  Klasa zawiera szereg funkcji odpowiedzialnych za renderowanie elementów gry.
 *  Renderuje stó³, bile, oœwietlenie, kij, itd.
 *
 *  @brief Klasa reprezentuje obiekt renderowania.
 */
class CRender {

	private:
		/** @brief Stosunek szerokoœci do wysokoœci okna renderowania. */
		float m_Ratio;
		/** @brief Kwadryka bil. */
		GLUquadricObj *m_Quadric;
		/** @brief Kwadryka kija. */
		GLUquadricObj *m_StickQ;
		/** @brief Parametry œwiat³a. */
		LIGHT m_Light;
		/** @brief Czcionka. */
		CMyFont m_Font;
		/** @brief Tekstura kija. */
		CTexture m_StickTex;
		/** @brief Si³a uderzenia. */
		float m_Force, m_dForce;

	public:
		/** @brief Flaga renderowania bil. */
		int m_RenderBalls;
		/** @brief Flaga renderowania kamery. */
		int m_RenderCamera;
		/** @brief Flaga renderowania trójk¹ta. */
		int m_RenderTriangle;
		/** @brief Flaga renderowania trójk¹tów. */
		int m_RenderTriangles;
		/** @brief Flaga renderowania sto³u. */
		int m_RenderTable;
		/** @brief Flaga renderowania oœwietlenia. */
		int m_RenderLight;
		/** @brief Flaga renderowania paska wzrostu sto³u. */
		int m_RenderBar;
		/** @brief Flaga renderowania opisów. */
		int m_RenderState;
		/** @brief Flaga renderowania podgl¹du sto³u. */
		int m_RenderPreview;

	private:
		/** @brief Funkcja renderuj¹ca stó³. 
		 *  @param[in] Time Czas, który up³yn¹³ od poprzedniej klatki.
		 */
		void RenderStick(float Time);

		/** @brief Funkcja redneruj¹ca bilê.
		 */
		void RenderBall(const CBall &Ball);

		/** @brief Funkcja renderuj¹ca wszystkie bile.
		 */
		void RenderBalls(void);

		/** @brief Funkcja renderuj¹ca pojedynczy trójk¹t.
		 */
		void RenderTriangle(const CTriangle &Triangle, float Alpha = 1.0f);

		/** @brief Funkcja renderuj¹ca wszystkie trójk¹tu.
		 */
		void RenderTriangles(void);

		/** @brief Funkcja renderuj¹ca pasek wzrostu si³y.
		 */
		void RenderBar(void);

		/** @brief Funkcja renderuj¹ca aktualny uk³ad wspó³rzêdnych.
		 */
		void RenderAxes(void);

		/** @brief Funkcja renderuj¹ca opisy.
		 */
		void RenderState(void);

		/** @brief Funkcja renderuj¹ca podgl¹d sto³u.
		 */
		void RenderPreview(void);

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CRender(void);

	public:
		/** @brief Funkcja inicjalizuj¹ca klasê renderowania.
		 */
		void Initialize(void);

		/** @brief Funkcja zwalniaj¹ca zasoby renderowania.
		 */
		void Finalize(void);

	public:
		/** @brief G³ówna funkcja renderuj¹ca.
		 *  @param[in] Time Czas, który up³yn¹³ od poprzedniej klatki.
		 */
		void Run(float Time);

		void SetQuadricStyle(GLenum style) {
			gluQuadricDrawStyle(m_Quadric, style);
			gluQuadricDrawStyle(m_StickQ, style);
		}

	public:
		/** @brief Ustaw wspó³czynnik perspektywy.
		 */
		void SetRatio(int Width, int Height);

};
