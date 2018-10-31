
/** @file BallsDlg.h
 *  @author Miros�aw Szajner (noozy@tlen.pl)
 *  @version 1.0
 *  @date 2006
 *  @brief Plik nag��wkowy klasy obs�uguj�cej okno edytora bil CBallsDlg.
 *
 *  Plik zawiera definicj� klasy CBallsDlg obs�uguj�cej okno
 *  dialogowe edytor bil.
 *
 */ 

#pragma once

#include "afxwin.h"
#include "Billard.h"

/** @brief Klasa obs�uguj�ca okno dialogowe edytor bil.
 */
class CBallsDlg : public CDialog {

	public:
		/** @brief Wska�nik na aktualnie edytowan� bil�.
		 */
		CBall *m_Ball;
		/** @brief Wska�nik na tablic� bil�.
		 */
		CBalls *m_Balls;
		/** @brief Przycisk wyboru poprzedniej bili (<-, IDC_BALL_PREVIOUS).
		 */
		CButton m_BallPreviousBtn;
		/** @brief Lista wyboru bili - kontrolka IDC_BALLS.
		 */
		CComboBox m_BallsBox;
		/** @brief Przycisk wyboru nast�pnej bili (->, IDC_BALL_NEXT).
		 */
		CButton m_BallNextBtn;
		/** @brief Przycisk dodawania bili (+, IDC_BALL_ADD).
		 */
		CButton m_BallAddBtn;
		/** @brief Przycisk usuwania bili (-, IDC_BALL_DELETE).
		 */
		CButton m_BallDeleteBtn;
		/** @brief Liczba punkt�w bili - zmienna powi�zana z oknem edycyjnym - IDC_BALL_SCORE.
		 */
		int m_BallScore;
		/** @brief Edytor liczby punkt�w bili - IDC_BALL_SCORE.
		 */
		CEdit m_BallScoreEdit;
		/** @brief Promie� bili - zmienna powi�zana z oknem edycyjnym - IDC_BALL_RAY.
		 */
		float m_BallRay;
		/** @brief Edytor promienia bili - IDC_BALL_RAY.
		 */
		CEdit m_BallRayEdit;
		/** @brief Masa bili - zmienna powi�zana z oknem edycyjnym - IDC_BALL_MASS.
		 */
		float m_BallMass;
		/** @brief Edytor masy bili - IDC_BALL_MASS.
		 */
		CEdit m_BallMassEdit;
		/** @brief Flaga oznaczaj�ca bil� bia�� - zmienna powi�zana z przyciskiem IDC_BALL_WHITE.
		 */
		BOOL m_BallWhite;
		/** @brief Przycisk flagi oznaczaj�cej bil� bia�� - IDC_BALL_WHITE.
		 */
		CButton m_BallWhiteBox;
		/** @brief Flaga oznaczaj�ca bil� czerwon� - zmienna powi�zana z przyciskiem IDC_BALL_RED.
		 */
		BOOL m_BallRed;
		/** @brief Przycisk flagi oznaczaj�cej bil� czerwon� - IDC_BALL_RED.
		 */
		CButton m_BallRedBox;
		/** @brief Flaga oznaczaj�ca bil� kolorow� - zmienna powi�zana z przyciskiem IDC_BALL_COLOR.
		 */
		BOOL m_BallColor;
		/** @brief Przycisk flagi oznaczaj�cy bil� kolorow� - IDC_BALL_COLOR.
		 */
		CButton m_BallColorBox;
		/** @brief Czerwony kolor bili - zmienna powi�zana z oknem edycyjnym IDC_BALL_COLOR0.
		 */
		float m_BallColor0;
		/** @brief Edytor czerwonego koloru bili - IDC_BALL_COLOR0.
		 */
		CEdit m_BallColor0Edit;
		/** @brief Zielony kolor bili - zmienna powi�zana z oknem edycyjnym IDC_BALL_COLOR1.
		 */
		float m_BallColor1;
		/** @brief Edytor zielonego koloru bili - IDC_BALL_COLOR1.
		 */
		CEdit m_BallColor1Edit;
		/** @brief Niebieski kolor bili - zmienna powi�zana z oknem edycyjnym IDC_BALL_COLOR2.
		 */
		float m_BallColor2;
		/** @brief Edytor niebieskiego koloru bili - IDC_BALL_COLOR2.
		 */
		CEdit m_BallColor2Edit;
		/** @brief Prze�roczysto�� bili - zmienna powi�zana z oknem edycyjnym IDC_BALL_COLOR3.
		 */
		float m_BallColor3;
		/** @brief Edytor prze�roczysto�ci bili - IDC_BALL_COLOR3.
		 */
		CEdit m_BallColor3Edit;
		/** @brief Pozycja bili na osi X - zmienna powi�zana z oknem edycyjnym IDC_BALL_POSITIONX.
		 */
		float m_BallPositionX;
		/** @brief Edytor pozycji bili na osi X - IDC_BALL_POSITIONX.
		 */
		CEdit m_BallPositionXEdit;
		/** @brief Pozycja bili na osi Y - zmienna powi�zana z oknem edycyjnym IDC_BALL_POSITIONY.
		 */
		float m_BallPositionY;
		/** @brief Edytor pozycji bili na osi Y - IDC_BALL_POSITIONY.
		 */
		CEdit m_BallPositionYEdit;
		/** @brief Pozycja bili na osi Z - zmienna powi�zana z oknem edycyjnym IDC_BALL_POSITIONZ.
		 */
		float m_BallPositionZ;
		/** @brief Edytor pozycji bili na osi Z - IDC_BALL_POSITIONZ.
		 */
		CEdit m_BallPositionZEdit;

	private:
		/** @brief Funkcja wype�niaj�ca list� bil.
		 */
		void UpdateBallsBox(void);
		/** @brief Funkcje wype�niaj�ca kontrolki zgodnie z zaznaczon� bil�.
		 */
		void UpdateControls(void);

	private:
		DECLARE_DYNAMIC(CBallsDlg)

	protected:
		/** @brief Funkcja obs�uguj�ca kontrolki znajduj�ce si� w oknie.
		 */
		virtual void DoDataExchange(CDataExchange* pDX);
		DECLARE_MESSAGE_MAP()

	public:
		/** @brief Konstruktor domy�lny.
		 */
		CBallsDlg(CWnd* pParent = NULL);

		/** @brief Destruktor.
		 */
		virtual ~CBallsDlg();

		/** @brief Funkcja wywo�ywana przy inicjalizacji dialogu.
		 */
		virtual BOOL OnInitDialog();

	public:
		/** @brief Identyfikator dialogu w zasobach.
		 */
		enum { IDD = IDD_BALLS_DIALOG };

	public:
		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku poprzednia bila.
		 */
		afx_msg void OnClickedBallPrevious();

		/** @brief Funkcja wywo�ywana przy wybraniu bili.
		 */
		afx_msg void OnSelectBall();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku nast�pna bila.
		 */
		afx_msg void OnClickedBallNext();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku dodaj bil�.
		 */
		afx_msg void OnClickedBallAdd();

		/** @brief Funkcja wywo�ywana przy wci�ni�ciu przycisku usu� bil�.
		 */
		afx_msg void OnClickedBallDelete();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze liczby punkt�w bili.
		 */
		afx_msg void OnChangeBallScore();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze promienia bili.
		 */
		afx_msg void OnChangeBallRay();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze masy bili.
		 */
		afx_msg void OnChangeBallMass();

		/** @brief Funkcja wywo�ywana przy klikni�ciu na znacznik Bia�a bila.
		 */
		afx_msg void OnClickedBallWhite();

		/** @brief Funkcja wywo�ywana przy klikni�ciu na znacznik Czerwona bila.
		 */
		afx_msg void OnClickedBallRed();

		/** @brief Funkcja wywo�ywana przy klikni�ciu na znacznik Kolorowa bila.
		 */
		afx_msg void OnClickedBallColor();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze koloru czerwonego bili.
		 */
		afx_msg void OnChangeBallColor0();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze koloru zielonego bili.
		 */
		afx_msg void OnChangeBallColor1();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze koloru niebieskiego bili.
		 */
		afx_msg void OnChangeBallColor2();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze prze�roczysto�ci bili.
		 */
		afx_msg void OnChangeBallColor3();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze pozycji bili na osi X.
		 */
		afx_msg void OnChangeBallPositionX();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze pozycji bili na osi Y.
		 */
		afx_msg void OnChangeBallPositionY();

		/** @brief Funkcja wywo�ywana przy zmianie w edytorze pozycji bili na osi Z.
		 */
		afx_msg void OnChangeBallPositionZ();

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z liczb� punkt�w bili.
		 */
		afx_msg void OnBallScoreSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z promieniem bili.
		 */
		afx_msg void OnBallRaySpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z mas� bili.
		 */
		afx_msg void OnBallMassSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z kolorem czerwonym bili.
		 */
		afx_msg void OnBallColor0Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z kolorem zielonym bili.
		 */
		afx_msg void OnBallColor1Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z kolorem niebieskim bili.
		 */
		afx_msg void OnBallColor2Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z prze�roczysto�ci� bili.
		 */
		afx_msg void OnBallColor3Spin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z pozycj� bili na osi X.
		 */
		afx_msg void OnBallPositionXSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z pozycj� bili na osi Y.
		 */
		afx_msg void OnBallPositionYSpin(NMHDR *pNMHDR, LRESULT *pResult);

		/** @brief Funkcja wywo�ywana przy klikni�ciu na pasek zwi�zany z pozycj� bili na osi Z.
		 */
		afx_msg void OnBallPositionZSpin(NMHDR *pNMHDR, LRESULT *pResult);

};
