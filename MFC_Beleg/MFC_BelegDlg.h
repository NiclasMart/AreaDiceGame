
// MFC_BelegDlg.h: Headerdatei
//

#pragma once
#include "spritelib.h";
#include "CSpriteField.h"


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
	CSprite m_startbkg, m_bkg, m_startbutton, m_menubutton[4], m_dicebutton, m_nextbutton, m_dice[2], m_font;
	CSprite m_field[12][12];
	CSpriteList m_list;
	int playernum;
	void InitDice();
	void InitGame();
	void game(bool playerchange);
	void set_field(CPoint point);
	void reset_game();
	void statemachine(int event, CPoint point);

	int m_state;
	struct {
		int next_state;
		int action;
	}m_table[10][5] = {
	   {{1, 1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
	   {{-1, -1}, {1, 2}, {2, 2}, {2, 2}, {4, 2}},
	   {{-1, -1}, {-1, -1}, {1, 6}, {1, 6}, {1, 6}},
	   {{-1, -1}, {2, 3}, {-1, -1}, {-1, -1}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {4, 4}, {-1, -1}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {3, 5}},
	   {{-1, -1}, {-1, -1}, {-1, -1}, {2, 7}, {-1, -1}},
	   {{-1, -1}, {-1, -1}, {-1, -1}, {3, 8}, {-1, -1}},
	   {{-1, -1}, {1, 9}, {2, 9}, {3, 9}, {4, 9}},
	   {{-1, -1}, {1, 10}, {2, 10}, {3, 10}, {4, 10}}
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
