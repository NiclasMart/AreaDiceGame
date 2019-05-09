
// MFC_BelegDlg.h: Headerdatei
//

#pragma once
#include "spritelib.h";
#include "CSpriteMatrix.h"


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
	CSprite m_startbkg, m_bkg, m_startbutton, m_menubutton[4], m_dicebutton, m_dice[2];
	CSpriteMatrix m_field[12][12];
	CSpriteList m_list;
	bool Dicestate;			//gibt an, ob gerade gewürfelt wird oder nicht
	void InitDice();
	void InitGame();
	void statemachine(int event);

	int m_state;
	struct {
		int next_state;
		int action;
	}m_table[8][4] = {
	   {{1, 1}, {-1, -1}, {-1, -1}, {-1, -1}},
	   {{-1, -1}, {1, 2}, {2, 2}, {4, 2}},
	   {{-1, -1}, {-1, -1}, {1, 6}, {1, 6}},
	   {{-1, -1}, {2, 3}, {-1, -1}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {4, 4}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {-1, -1}, {2, 5}},
	   {{-1, -1}, {-1, -1}, {2, 7}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {2, 8}, {-1, -1}}
	};


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
