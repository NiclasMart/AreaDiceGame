
// MFC_BelegDlg.h: Headerdatei
//

#pragma once
#include "spritelib.h"
#include "CSpriteMatrix.h"
#include "ControllMachine.h"
#include "EnemyPlayer.h"



// CMFCBelegDlg-Dialogfeld
class CMFCBelegDlg : public CDialogEx
{
// Konstruktion
public:
	CMFCBelegDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_BELEG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	CDIB m_buff;
	CSprite m_startbkg, m_bkg, m_info, m_infobutton, m_startbutton, m_menubutton[4], m_dicebutton, m_nextbutton, m_dice[2], m_font, m_win, m_checkbox[2];
	CSpriteMatrix Matrix;
	CSpriteList m_list;
	ControllMachine m_wintest;
	EnemyPlayer m_enemy;


	bool computer_enemy;
	int player_num;
	int dice_value[2];
	int round;

	void InitDice();
	void InitGame();
	void Game(bool playerchange);
	bool SetField();
	void ResetGame();
	void ShowField(CPoint point);
	bool Statemachine(int event);
	void RotateField();
	void Win(int &winner);
	void InitEnemy();
	void InitEnemyTurn();
	void EnemyTurn();

	

	


	int m_state;
	struct tab {
		int next_state;
		int action;
	} m_table[13][6];


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
