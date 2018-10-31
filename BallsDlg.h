
/** @file BallsDlg.h
 *  @author Miros³aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag³ówkowy klasy obs³uguj¹cej okno edytora bil CBallsDlg.
 *
 *  Plik zawiera definicjê klasy CBallsDlg obs³uguj¹cej okno
 *  dialogowe edytor bil.
 *
 */ 

#pragma once

#include "afxwin.h"
#include "Billard.h"

/** @brief Klasa obs³uguj¹ca okno dialogowe edytor bil.
 */
class CBallsDlg : public CDialog {

	public:
		/** @brief WskaŸnik na aktualnie edytowan¹ bilê.
		 */
		CBall *m_Ball;
		/** @brief WskaŸnik na tablicê bilê.
		 */
		CBalls *m_Balls;
		/** @brief Przycisk wyboru poprzedniej bili (<-, IDC_BALL_PREVIOUS).
		 */
		CButton m_BallPreviousBtn;
		/** @brief Lista wyboru bili - kontrolka IDC_BALLS.
		 */
		CComboBox m_BallsBox;
		/** @brief Przycisk wyboru nastêpnej bili (->, IDC_BALL_NEXT).
		 */
		CButton m_BallNextBtn;
		/** @brief Przycisk dodawania bili (+, IDC_BALL_ADD).
		 */
		CButton m_BallAddBtn;
		/** @brief Przycisk usuwania bili (-, IDC_BALL_DELETE).
		 */
		CButton m_BallDeleteBtn;
		/** @brief Liczba punktów bili - zmienna powi¹zana z oknem edycyjnym - IDC_BALL_SCORE.
		 */
		int m_BallScore;
		/** @brief Edytor liczby punktów bili - IDC_BALL_SCORE.
		 */
		CEdit m_BallScoreEdit;
		/** @brief Promieñ bili - zmienna powi¹zana z oknem edycyjnym - IDC_BALL_RAY.
		 */
		float m_BallRay;
		/** @brief Edytor promienia bili - IDC_BALL_RAY.
		 */
		CEdit m_BallRayEdit;
		/** @brief Masa bili - zmienna powi¹zana z oknem edycyjnym - IDC_BALL_MASS.
		 */
		float m_BallMass;
		/** @brief Edytor masy bili - IDC_BALL_MASS.
		 */
		CEdit m_BallMassEdit;
		/** @brief Flaga oznaczaj¹ca bilê bia³¹ - zmienna powi¹zana z przyciskiem IDC_BALL_WHITE.
		 */
		BOOL m_BallWhite;
		/** @brief Przycisk flagi oznaczaj¹cej bilê bia³¹ - IDC_BALL_WHITE.
		 */
		CButton m_BallWhiteBox;
		/** @brief Flaga oznaczaj¹ca bilê czerwon¹ - zmienna powi¹zana z przyciskiem IDC_BALL_RED.
		 */
		BOOL m_BallRed;
		/** @brief Przycisk flagi oznaczaj¹cej bilê czerwon¹ - IDC_BALL_RED.
		 */
		CButton m_BallRedBox;
		/** @brief Flaga oznaczaj¹ca bilê kolorow¹ - zmienna powi¹zana z przyciskiem IDC_BALL_COLOR.
		 */
		BOOL m_BallColor;
		/** @brief Przycisk flagi oznaczaj¹cy bilê kolorow¹ - IDC_BALL_COLOR.
		 */
		CButton m_BallColorBox;
		/** @brief Czerwony kolor bili - zmienna powi¹zana z oknem edycyjnym IDC_BALL_COLOR0.
		 */
		float m_BallColor0;
		/** @brief Edytor czerwonego koloru bili - IDC_BALL_COLOR0.
		 */
		CEdit m_BallColor0Edit;
		/** @brief Zielony kolor bili - zmienna powi¹zana z oknem edycyjnym IDC_BALL_COLOR1.
		 */
		float m_BallColor1;
		/** @brief Edytor zielonego koloru bili - IDC_BALL_COLOR1.
		 */
		CEdit m_BallColor1Edit;
		/** @brief Niebieski kolor bili - zmienna powi¹zana z oknem edycyjnym IDC_BALL_COLOR2.
		 */
		float m_BallColor2;
		/** @brief Edytor niebieskiego koloru bili - IDC_BALL_COLOR2.
		 */
		CEdit m_BallColor2Edit;
		/** @brief PrzeŸroczystoœæ bili - zmienna powi¹zana z oknem edycyjnym IDC_BALL_COLOR3.
		 */
		float m_BallColor3;
		/** @brief Edytor przeŸroczystoœci bili - IDC_BALL_COLOR3.
		 */
		CEdit m_BallColor3Edit;
		/** @brief Pozycja bili na osi X - zmienna powi¹zana z oknem edycyjnym IDC_BALL_POSITIONX.
		 */
		float m_BallPositionX;
		/** @brief Edytor pozycji bili na osi X - IDC_BALL_POSITIONX.
		 */
		CEdit m_BallPositionXEdit;
		/** @brief Pozycja bili na osi Y - zmienna powi¹zana z oknem edycyjnym IDC_BALL_POSITIONY.
		 */
		float m_BallPositionY;
		/** @brief Edytor pozycji bili na osi Y - IDC_BALL_POSITIONY.
		 */
		CEdit m_BallPositionYEdit;
		/** @brief Pozycja bili na osi Z - zmienna powi¹zana z oknem edycyjnym IDC_BALL_POSITIONZ.
		 */
		float m_BallPositionZ;
		/** @brief Edytor pozycji bili na osi Z - IDC_BALL_POSITIONZ.
		 */
		CEdit m_BallPositionZEdit;

	private:
		/** @brief Funkcja wype³niaj¹ca listê bil.
		 */
		void UpdateBallsBox(void);
		/** @brief Funkcje wype³niaj¹ca kontrolki zgodnie z zaznaczon¹ bil¹.
		 */
		void UpdateControls(void);

	private:
		DECLARE_DYNAMIC(CBallsDlg)

	protected:
		/** @brief Funkcja obs³uguj¹ca kontrolki znajduj¹ce siê w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domyœlny.
		 */
		CBallsDlg(CWnd* pParent = NULL);

		/** @brief Destruktor.
		 */
		virtual ~CBallsDlg();

		/** @brief Funkcja wywo³ywana przy inicjalizacji dialogu.
		 */
		virtual BOOL OnInitDialog();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_BALLS_DIALOG };

	public:
		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku poprzednia bila.
		 */
		afx_msg void OnClickedBallPrevious();

		/** @brief Funkcja wywo³ywana przy wybraniu bili.
		 */
		afx_msg void OnSelectBall();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku nastêpna bila.
		 */
		afx_msg void OnClickedBallNext();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku dodaj bilê.
		 */
		afx_msg void OnClickedBallAdd();

		/** @brief Funkcja wywo³ywana przy wciœniêciu przycisku usuñ bilê.
		 */
		afx_msg void OnClickedBallDelete();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze liczby punktów bili.
		 */
		afx_msg void OnChangeBallScore();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze promienia bili.
		 */
		afx_msg void OnChangeBallRay();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze masy bili.
		 */
		afx_msg void OnChangeBallMass();

		/** @brief Funkcja wywo³ywana przy klikniêciu na znacznik Bia³a bila.
		 */
		afx_msg void OnClickedBallWhite();

		/** @brief Funkcja wywo³ywana przy klikniêciu na znacznik Czerwona bila.
		 */
		afx_msg void OnClickedBallRed();

		/** @brief Funkcja wywo³ywana przy klikniêciu na znacznik Kolorowa bila.
		 */
		afx_msg void OnClickedBallColor();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze koloru czerwonego bili.
		 */
		afx_msg void OnChangeBallColor0();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze koloru zielonego bili.
		 */
		afx_msg void OnChangeBallColor1();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze koloru niebieskiego bili.
		 */
		afx_msg void OnChangeBallColor2();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze przeŸroczystoœci bili.
		 */
		afx_msg void OnChangeBallColor3();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze pozycji bili na osi X.
		 */
		afx_msg void OnChangeBallPositionX();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze pozycji bili na osi Y.
		 */
		afx_msg void OnChangeBallPositionY();

		/** @brief Funkcja wywo³ywana przy zmianie w edytorze pozycji bili na osi Z.
		 */
		afx_msg void OnChangeBallPositionZ();

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z liczb¹ punktów bili.
		 */
		afx_msg void OnBallScoreSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z promieniem bili.
		 */
		afx_msg void OnBallRaySpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z mas¹ bili.
		 */
		afx_msg void OnBallMassSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z kolorem czerwonym bili.
		 */
		afx_msg void OnBallColor0Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z kolorem zielonym bili.
		 */
		afx_msg void OnBallColor1Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z kolorem niebieskim bili.
		 */
		afx_msg void OnBallColor2Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z przeŸroczystoœci¹ bili.
		 */
		afx_msg void OnBallColor3Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z pozycj¹ bili na osi X.
		 */
		afx_msg void OnBallPositionXSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z pozycj¹ bili na osi Y.
		 */
		afx_msg void OnBallPositionYSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo³ywana przy klikniêciu na pasek zwi¹zany z pozycj¹ bili na osi Z.
		 */
		afx_msg void OnBallPositionZSpin(NMHDR *pNMHDR, LRESULT *pResult);

};
