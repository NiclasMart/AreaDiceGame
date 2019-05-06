
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
	CSprite m_start, m_bkg, m_button, m_dice;
	CSpriteMatrix m_field[12][12];
	CSpriteList m_list;


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
};
