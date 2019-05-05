
// MFC_BelegDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MFC_Beleg.h"
#include "MFC_BelegDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBelegDlg-Dialogfeld



CMFCBelegDlg::CMFCBelegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_BELEG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBelegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBelegDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBelegDlg-Meldungshandler

BOOL CMFCBelegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	

	//Spielhintergrund BMP laden
	if (!m_bkg.Load("Hintergrund.bmp")) {
		AfxMessageBox(L"Konnte Hintergrund.bmp nicht laden!");
		OnCancel();
	}
	m_bkg.SetZ(0);
	
	//Feld Sprite BMP laden
	if (!m_field[0][0].Load("94x84_Sprite_4.bmp", CSize(94, 84))) {
		AfxMessageBox(L"Konnte 94x84_Sprite_4.bmp nicht laden!");
		OnCancel();
	}

	//Initialisieren aller Feldinhalte der Matrix
	int z = 1;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j] = m_field[0][0];
			m_field[i][j].SetZ(z);
			m_field[i][j].SetPosition(908 + (79 * i), 67 + (79 * j));
			m_field[i][j].SetAlpha(0.0f);
			z++;

		}
	}

	//Startbildschirm BMP laden + Buffer Initialisieren
	if (!m_start.Load("Startbildschirm.bmp")) {
		AfxMessageBox(L"Konnte Startbildschirm.bmp nicht laden!");
		OnCancel();
	}
	m_start.SetZ(200);
	m_start.SetPosition(0, 0);
	m_buff.Load("Startbildschirm.bmp");

	
	//Start Button BMP laden
	if (!m_button.Load("400x250_Start_button_2.bmp", CSize(400, 250))) {
		AfxMessageBox(L"Konnte 400x250_Start_button_2.bmp nicht laden!");
		OnCancel();
	}
	m_button.SetZ(201);
	m_button.SetPosition(760, 700);




	//alle Elemente des Startbildschirms zur Liste hinzufügen
	m_list.SetWorkspace(&m_buff);
	m_list.Insert(&m_start);
	m_list.Insert(&m_button);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}



// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMFCBelegDlg::OnPaint()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen

	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_list.RedrawAll(&dc, 0, 0);
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMFCBelegDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBelegDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Beim Mausklick ausgelöste Ereignisse
	CClientDC dc(this);
	CSprite *hit = m_list.HitTest(point);

	/*Mausklick im Startbildschirm über dem Start Button: 
		-Startbildschirm und Button verschwinden
		-Puffer wird mit neuem Hintergrund initialisiert 
		-alle Feldsprites werden in die Liste geladen
	*/
	if (hit == &m_button) {
		m_button.SetPosition(1921, 0);
		m_start.SetPosition(1920, 0);
		m_buff.Load("Hintergrund.bmp");
		m_list.Insert(&m_bkg);
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 12; j++){
				m_list.Insert(&m_field[i][j]);
			}
		}
	}
	//falls Mausklick innerhalb des Spiels: wenn ein Feld angeklickt wird, wird die Transparents des Sprits auf diesem Feld auf 100% gesetzt
	else {
		if (hit != NULL) {
			hit->SetAlpha(1.0f);
		}
	}
	m_list.Update(&dc, 0, 0);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBelegDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//wenn im Startbildschirm die Maus über dem Start button hovert, wird das Start Sprite gehighlightet
	CClientDC dc(this);
	CSprite *hit = m_list.HitTest(point);

	if (hit == &m_button)
		m_button.SetSpriteNumber(0, 1);
	else
		m_button.SetSpriteNumber(0, 0);


	m_list.Update(&dc, 0, 0);

	CDialogEx::OnMouseMove(nFlags, point);
}
