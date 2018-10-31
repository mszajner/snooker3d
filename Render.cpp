// Render.cpp : implementation file
//

#include "stdafx.h"
#include "Snooker.h"
#include "Render.h"
#include "Ray.h"
#include <math.h>

#define SCREEN_WIDTH    1024.0f
#define SCREEN_HEIGHT   768.0f

#define PREVIEW_WIDTH   200.0f
#define PREVIEW_HEIGHT  100.0f
#define PREVIEW_X       (SCREEN_WIDTH - PREVIEW_WIDTH - 20.0f)
#define PREVIEW_Y       20.0f

#define BAR_WIDTH       128.0f
#define BAR_HEIGHT      512.0f
#define BAR_X           704.0f
#define BAR_Y           128.0f

#define TEXT_X          20.0f
#define TEXT_Y          20.0f
#define TEXT_W          30.0f
#define TEXT_H          40.0f

#define DFORCE          700.0f

// CRender

CRender::CRender(void)
	: m_RenderBalls(1)
	, m_RenderCamera(1)
	, m_RenderTriangles(0)
	, m_RenderTriangle(-1)
	, m_RenderTable(1)
	, m_RenderLight(1)
	, m_RenderBar(0)
	, m_RenderState(1)
	, m_RenderPreview(1)
	, m_dForce(DFORCE)
{
}

void CRender::Initialize(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	m_Quadric = gluNewQuadric();
	gluQuadricDrawStyle(m_Quadric, GLU_FILL);
	gluQuadricOrientation(m_Quadric, GLU_OUTSIDE);

	m_StickQ = gluNewQuadric();
	gluQuadricDrawStyle(m_StickQ, GLU_FILL);
	gluQuadricOrientation(m_StickQ, GLU_OUTSIDE);
	gluQuadricTexture(m_StickQ, GL_TRUE);

	setDefaultLight(&m_Light);

	m_Light.ambient[0] = 0.9f;
	m_Light.ambient[1] = 0.9f;
	m_Light.ambient[2] = 0.9f;
	m_Light.ambient[3] = 1.0f;

	m_Light.position[1] = 18.0f;

	m_Light.cutOff = 60.0f;

	srand((unsigned)time(NULL));

	initializeTable();

	m_Font.Load("Data\\Textures\\Font.bmp");
	m_StickTex.Load("Data\\Textures\\Stick.bmp");
}

void CRender::Finalize(void)
{
	m_Font.Finalize();
	m_StickTex.Finalize();
	finalizeTable();
	gluDeleteQuadric(m_Quadric);
	gluDeleteQuadric(m_StickQ);
}

void CRender::RenderStick(float Time)
{
	// pobierz bilarda
	const CBillard &Billard = SnookerApp.m_Billard;
	// pobierz kamere
	const CCamera &Camera = SnookerApp.m_Camera;

	// pobierz tablice bil
	const CBalls &Balls = Billard.m_Balls;
	// pobierz biala bile
	const CBall &WhiteBall = Balls[Billard.m_WhiteIndex];

	// wyzeruj kat nachylenia kija
	float StickAlpha = 5.0f;

	// pobierz pozycje kamery
	CVector StickPos(Camera.GetPosition().GetVector());
	StickPos.m_Z = tan(DEGTORAD(StickAlpha))*sqrt(SQR(WhiteBall.m_Position.m_X - StickPos.m_X) + SQR(WhiteBall.m_Position.m_Y - StickPos.m_Y));

	// utworz polprosta kija
	CRay StickRay(StickPos, WhiteBall.GetPosition());

	// przejdz przez wszystkie bile
	for (int i = 0; i < (int)Balls.GetCount(); i++)
	{
		// nie porownuj bialej bili ze soba
		if (i != Billard.m_WhiteIndex)
		{
			// pobierz i-ta bile
			const CBall &Ball = Balls[i];

			CVector BallDir(Ball.GetPosition() - WhiteBall.GetPosition());

			float StickWidth = (BallDir.Length() * 0.3f / 15.0f);
			float StickDistance = 0.05f + Ball.m_Ray + StickWidth;

			// wyznacz odleglosc miedzy bila a polprosta
			float Distance = StickRay.Distance(Ball.GetPosition());

			if (Distance < StickDistance)
			{
				if (StickRay.m_Direction.Dot(BallDir) > 0.0f)
				{
					float Alpha = (float)RADTODEG(atan((StickDistance + 0.05f) / BallDir.Length()));
					if (Alpha > StickAlpha)
					{
						StickAlpha = Alpha;
						StickPos.m_Z = tan(DEGTORAD(StickAlpha))*sqrt(SQR(StickPos.m_X) + SQR(StickPos.m_Y));
						StickRay.SetDirection(WhiteBall.GetPosition() - StickPos);
					}
				}
			}
		}
	}
/*
	Alpha = Camera.GetPosition().GetAlpha() + Alpha;

	//Alpha = RADTODEG(atan(Ray.m_Direction.m_Z / sqrt(SQR(Ray.m_Direction.m_Y) + SQR(Ray.m_Direction.m_X))));
	Alpha = FLOAT_MID(Alpha, -30.0f, 85.0f);
*/
	StickAlpha = 90.0f - StickAlpha;

	if (Billard.m_Force > 0)
	{
		m_Force += m_dForce * Time;

		if (m_dForce > 0)
		{
			if (m_Force > (Billard.m_Force * 0.9f))
				m_dForce = -DFORCE;
		}
		else
		{
			if (m_Force < (Billard.m_Force * 0.1f))
				m_dForce = DFORCE;
		}
	}
	else
	{
		m_Force = 0.0f;
		m_dForce = DFORCE;
	}

	const float sp2[3] = { 0.9f, 0.4f, 0.4f };

	glMaterialfv(GL_FRONT, GL_SPECULAR, sp2);

	glEnable(GL_TEXTURE_2D);
	m_StickTex.Bind();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

	glPushMatrix();
		glTranslatef(WhiteBall.m_Position.m_X, WhiteBall.m_Position.m_Y, WhiteBall.m_Position.m_Z);
		glRotatef(Camera.GetPosition().GetBeta(), 0.0f, 0.0f, -1.0f);
		/*// RenderAxes();
		glBegin(GL_QUADS);
			glColor4f(1.0f, 1.0f, 1.0f, 0.9f);
			glVertex3f(-0.05f,  0.0f, -0.25f);
			glVertex3f( 0.05f,  0.0f, -0.25f);
			glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
			glVertex3f( 0.1f, 17.0f, -0.25f);
			glVertex3f(-0.1f, 17.0f, -0.25f);
		glEnd();*/
		glRotatef(StickAlpha, 1.0f, 0.0f, 0.0f);
		glTranslatef(0.0f, 0.0f, 3*WhiteBall.m_Ray + 5.0f * (m_Force / MAX_FORCE));
		glColor3f(0.8f, 0.4f, 0.0f);
		gluDisk(m_StickQ, 0.0f, 0.06f, 10, 10);
		gluCylinder(m_StickQ, 0.06f, 0.3f, 15.0f, 20, 20);
		glTranslatef(0.0f, 0.0f, 15.0f);
		glColor3f(0.1f, 0.1f, 0.1f);
		gluDisk(m_StickQ, 0.0f, 0.305f, 20, 5);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void CRender::RenderBall(const CBall &Ball)
{
	if (Ball.GetRender())
	{
		const CVector &Position = Ball.GetPosition();
		const CVector &Rotate = Ball.GetRotate();
		float fPosition[3] = { Position.m_X, Position.m_Z, -Position.m_Y };
		float lpos[3] = { 0, 100, 0 };

		glPushMatrix();
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glTranslatef(0.0f, -Ball.m_Ray + 0.015f, 0.0f);
			castBallShadow(fPosition, lpos, 0.3f);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(Position.m_X, Position.m_Y, Position.m_Z);
			glRotatef(-(Ball.GetTrack() * 360.0f)/(2.0f * PI * Ball.GetRay()), 
				Rotate.m_X, Rotate.m_Y, Rotate.m_Z);
			glColor4fv(Ball.GetColor());
			gluSphere(m_Quadric, Ball.GetRay(), 20, 20);
		glPopMatrix();
	}
}

void CRender::RenderBalls(void)
{
	if (m_RenderBalls)
	{
		const CBalls &Balls = SnookerApp.m_Billard.m_Balls;
		const float sp2[3] = { 0.9f, 0.9f, 0.9f };

		glMaterialfv(GL_FRONT, GL_SPECULAR, sp2);
		for (int i = 0; i < Balls.GetCount(); i++)
			RenderBall(Balls[i]);
	}
}

void CRender::RenderTriangle(const CTriangle &Triangle, float Alpha)
{
	const float Color[4][4] = {
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		{ 0.4f, 0.4f, 0.2f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
	};

	int Index = (Triangle.GetHole() << 1) | (Triangle.GetReflect());

	glColor4f(Color[Index][0], Color[Index][1], Color[Index][2], Color[Index][3] * Alpha);
	glBegin(GL_TRIANGLES);
		glNormal3fv((const GLfloat*)&Triangle.m_N.m_X);
		glVertex3fv((const GLfloat*)&Triangle.m_A.m_X);
		glVertex3fv((const GLfloat*)&Triangle.m_B.m_X);
		glVertex3fv((const GLfloat*)&Triangle.m_C.m_X);
	glEnd();
}

void CRender::RenderTriangles(void)
{
	const CTriangles &Triangles = SnookerApp.m_Billard.m_Triangles;

	int Count = (int)Triangles.GetCount();
	float Alpha = (m_RenderTriangle > -1) ? 0.6f : 1.0f;

	//glDisable(GL_CULL_FACE);

	if (m_RenderTriangles)
	{
		for (int i = 0; i < Count; i++)
		{
			const CTriangle &Triangle = Triangles[i];

			if (m_RenderTriangle == i)
				RenderTriangle(Triangle, 0.9f);
			else
				RenderTriangle(Triangle, Alpha);
		}
	}
	else if (m_RenderTriangle > -1)
	{
		RenderTriangle(Triangles[m_RenderTriangle], 1.0f);
	}

	//glEnable(GL_CULL_FACE);
}

void CRender::RenderBar(void)
{
	const CBillard &Billard = SnookerApp.m_Billard;

	if (Billard.m_Force > 0.0f)
	{
		float Radius = Billard.m_Force / MAX_FORCE;

		glColor4f(0.8f, 0.8f, 0.8f, 0.3f);
		glBegin(GL_QUADS);
			glVertex2f(     0.0f, 0.0f);
			glVertex2f(BAR_WIDTH, 0.0f);
			glVertex2f(BAR_WIDTH, BAR_HEIGHT);
			glVertex2f(     0.0f, BAR_HEIGHT);
		glEnd();

		glBegin(GL_QUADS);
			glColor4f(0.9f, 0.9f, 0.9f, 0.3f);
			glVertex2f(     0.0f, 0.0f);
			glVertex2f(BAR_WIDTH, 0.0f);
			glColor4f(0.9f, 0.9f, 0.9f, 0.8f);
			glVertex2f(BAR_WIDTH, BAR_HEIGHT * Radius);
			glVertex2f(     0.0f, BAR_HEIGHT * Radius);
		glEnd();
	}
}

void CRender::RenderAxes(void)
{
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 5.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 5.0f);
	glEnd();
}

void CRender::RenderState(void)
{
	const CString States[6] = {
		"Snooker version 1.0", "Widok", "Ustaw bia³¹ bilê", "Celowanie", "Strza³", "Koniec gry"
	};

	const CBillard &Billard = SnookerApp.m_Billard;
	int w = States[Billard.m_State % 5].GetLength(), h = 1;

	switch (Billard.m_State)
	{
	case bsStart:
		h += 2;
		m_Font.Print("Miros³aw Szajner", TEXT_X, TEXT_Y + 2.0f * TEXT_H, 1.0f, 1.0f, 1.0f, 1.0f, TEXT_W, TEXT_H);
		m_Font.Print("Piotr Repetowski", TEXT_X, TEXT_Y + 1.0f * TEXT_H, 1.0f, 1.0f, 1.0f, 1.0f, TEXT_W, TEXT_H);
		break;

	case bsOver:
		if (Billard.m_StrikerIndex > -1)
		{
			int Count = (int)Billard.m_Players.GetCount();
			h += Count + 1;

			m_Font.Print("Koniec gry!", TEXT_X, TEXT_Y + 3.0f * TEXT_H, 1.0f, 0.0f, 0.0f, 1.0f, TEXT_W, TEXT_H);

			// gra dwoch graczy
			for (int i = 0; i < Count; i++)
			{
				CString Text;
				const CPlayer &Player = Billard.m_Players[i];
				Text.Format("%s: %d pkt%s", Player.GetName(), Player.GetScore(), 
					((Player.GetState() == psFoul) || (Player.GetState() == psWhiteKnockIn)) ? " (Faul)" : "");

				if (Text.GetLength() > w)
					w = Text.GetLength();

				glColor3f(1.0f, 1.0f, 1.0f);
				m_Font.Print(Text, TEXT_X, TEXT_Y + ((Count - i) * TEXT_H), 1.0f, 1.0f, 1.0f, 1.0f, TEXT_W, TEXT_H);
			}
		}
		break;

	default:
		if (Billard.m_StrikerIndex > -1)
		{
			int Count = (int)Billard.m_Players.GetCount();
			h += Count;

			// gra dwoch graczy
			for (int i = 0; i < Count; i++)
			{
				CString Text;
				const CPlayer &Player = Billard.m_Players[i];
				Text.Format("%s: %d pkt", Player.GetName(), Player.GetScore());

				if (!Billard.m_Running && ((Player.GetState() == psFoul) || (Player.GetState() == psWhiteKnockIn)))
					Text = Text + " (faul)";

				if (Text.GetLength() > w)
					w = Text.GetLength();

				if (Billard.m_StrikerIndex == i)
					m_Font.Print(Text, TEXT_X, TEXT_Y + ((Count - i) * TEXT_H), 1.0f, 1.0f, 0.0f, 1.0f, TEXT_W, TEXT_H);
				else
					m_Font.Print(Text, TEXT_X, TEXT_Y + ((Count - i) * TEXT_H), 1.0f, 1.0f, 1.0f, 1.0f, TEXT_W, TEXT_H);

			}
		}
		break;
	}

	glBegin(GL_QUADS);
		glColor4f(0.7f, 0.7f, 0.7f, 0.7f);
		glVertex2f(TEXT_X, TEXT_Y);
		glColor4f(0.7f, 0.7f, 0.7f, 0.3f);
		glVertex2f(TEXT_X + TEXT_W*w, TEXT_Y);
		glVertex2f(TEXT_X + TEXT_W*w, TEXT_Y + TEXT_H*h);
		glVertex2f(TEXT_X, TEXT_Y + TEXT_H*h);
	glEnd();

	m_Font.Print(States[(Billard.m_State) % 5], TEXT_X, TEXT_Y, 1.0f, 1.0f, 1.0f, 1.0f, TEXT_W, TEXT_H);
}

void CRender::RenderPreview(void)
{
	glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2f(        0.00f,  0.00f);
		glVertex2f(PREVIEW_WIDTH,  0.00f);
		glVertex2f(PREVIEW_WIDTH,  PREVIEW_HEIGHT);
		glVertex2f(        0.00f,  PREVIEW_HEIGHT);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
	glBegin(GL_LINE_LOOP);
		glVertex2f(        0.00f,  0.00f);
		glVertex2f(PREVIEW_WIDTH,  0.00f);
		glVertex2f(PREVIEW_WIDTH,  PREVIEW_HEIGHT);
		glVertex2f(        0.00f,  PREVIEW_HEIGHT);
	glEnd();

	glPointSize(2.0f);

	glTranslatef(PREVIEW_WIDTH/2, PREVIEW_HEIGHT/2, 0.0f);

	const CBalls &Balls = SnookerApp.m_Billard.m_Balls;

	for (int i = 0; i < Balls.GetCount(); i++)
	{
		const CBall &Ball = Balls[i];

		if (Ball.GetRender())
		{
			const CVector &Position = Ball.GetPosition();

			float x = (Position.m_X / 35.69f) * PREVIEW_WIDTH;
			float y = (Position.m_Y / 17.78f) * PREVIEW_HEIGHT;

			glColor4fv(Ball.GetColor());
			glBegin(GL_POINTS);
				glVertex2f(x, y);
			glEnd();
		}
	}
}

void CRender::Run(float Time)
{
	// wyczyszczenie bufora obrazu
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// wybierz macierz projekcji
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const CCamera &Camera = SnookerApp.m_Camera;
	const CCameraPosition &Position = Camera.GetPosition();

	// ustaw perspektywe
	gluPerspective(Position.GetFOV(), m_Ratio, Camera.GetNear(), Camera.GetFar());

	// wybierz macierz widoku
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ustaw kamere
	if (m_RenderCamera)
	{
		glRotatef(Position.GetAlpha(), -1.0f, 0.0f, 0.0f);
		glRotatef(Position.GetBeta(),   0.0f, 0.0f, 1.0f);
		glTranslatef(-Position.GetX(), -Position.GetY(), -Position.GetZ()); 
	}

	const CBillard &Billard = SnookerApp.m_Billard;

	// renderuj oswietlenie
	if (m_RenderLight)
	{
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, 12.0f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			glEnable(GL_LIGHTING);
			drawLamp(18.0f, 1.0f, 4.0f, 5.0f);
			setLight(m_Light);
		glPopMatrix();
	}

	// renderuj stol
	if (m_RenderTable)
	{
		glPushMatrix();
			glTranslatef(0.0f, 0.0f, -7.062f);
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			setGround(0.2f, 0.2f, 0.5f);
			drawTable();
		glPopMatrix();
	}

	// rysuj trojkaty i bile
	glPushMatrix();
		// glTranslatef(-17.845f, -8.89f, 0.0f);

		// renderuj trojkaty
		if (m_RenderTriangles || (m_RenderTriangle > -1))
		{
			RenderTriangles();
		}

		// renderuj bile
		if (m_RenderBalls)
		{
			// renderuj bile
			RenderBalls();
		}
	glPopMatrix();

	if (SnookerApp.m_Billard.m_State == bsAim)
		RenderStick(Time);

	// wybierz macierz projekcji
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// ustaw plaski obraz 2D
	glOrtho(0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, 0.0f, Camera.GetFar());

	// wybierz macierz widoku
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);

	// narysuj pasek wzrostu sily
	if (m_RenderBar)
	{
		glPushMatrix();
			glTranslatef(BAR_X, BAR_Y, 0.0f);
			RenderBar();
		glPopMatrix();
	}

	// narysuj tekst aktualnego stanu
	if (m_RenderState)
	{
		glPushMatrix();
			RenderState();
		glPopMatrix();
	}

	// narysuj podglad stolu
	if (m_RenderPreview)
	{
		glPushMatrix();
			glTranslatef(PREVIEW_X, PREVIEW_Y, 0.0f);
			RenderPreview();
		glPopMatrix();
	}

	// wyrzuc na ekran
	glFlush();
}

void CRender::SetRatio(int Width, int Height)
{
	glViewport(0, 0, Width, Height);
	m_Ratio = (float)Width / (float)Height;
}