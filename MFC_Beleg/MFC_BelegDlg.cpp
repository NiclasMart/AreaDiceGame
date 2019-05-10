
// MFC_BelegDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MFC_Beleg.h"
#include "MFC_BelegDlg.h"
#include "afxdialogex.h"
#include <time.h>

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
	ON_WM_TIMER()
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
	srand((unsigned)time(NULL));

	m_state = 0;
	

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

	//Würfel Sprite BMP laden
	if (!m_dice[0].Load("241x233_Wuerfel_3x2.bmp", CSize(241, 233))) {
		AfxMessageBox(L"Konnte 241x233_Wuerfel_3x2.bmp nicht laden!");
		OnCancel();
	}

	m_dice[1] = m_dice[0];
	for (int i = 0; i < 2; i++){
		m_dice[i].SetZ(10);
		m_dice[i].SetSpriteNumber(rand() % 3, rand() % 2);
		m_dice[i].SetPosition(260 + i*200, 850);
	}
	

	//Initialisieren aller Feldinhalte der Matrix
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_field[i][j] = m_field[0][0];
			m_field[i][j].SetMatrixPos(i, j);
			m_field[i][j].SetZ(1);
			m_field[i][j].SetPosition(908 + (79 * i), 67 + (79 * j));
			m_field[i][j].SetAlpha(0.0f);
		}
	}

	//Startbildschirm BMP laden + Buffer Initialisieren
	if (!m_startbkg.Load("Startbildschirm.bmp")) {
		AfxMessageBox(L"Konnte Startbildschirm.bmp nicht laden!");
		OnCancel();
	}
	m_startbkg.SetZ(50);
	m_startbkg.SetPosition(0, 0);
	m_buff.Load("Startbildschirm.bmp");

	
	//Start Button BMP laden
	if (!m_startbutton.Load("400x250_Start_button_2.bmp", CSize(400, 250))) {
		AfxMessageBox(L"Konnte 400x250_Start_button_2.bmp nicht laden!");
		OnCancel();
	}
	m_startbutton.SetZ(51);
	m_startbutton.SetPosition(760, 700);

	//restliche Button laden
	if (!m_menubutton[0].Load("175x60_buttons_0x12.bmp", CSize(175, 60))) {
		AfxMessageBox(L"Konnte 175x60_buttons_0x12.bmp nicht laden!");
		OnCancel();
	}
	m_menubutton[0].SetZ(30);
	m_menubutton[0].SetPosition(100, 50);
	for (int i = 1; i < 4; i++) {
		m_menubutton[i] = m_menubutton[0];
		m_menubutton[i].SetSpriteNumber(0, i * 2);
		m_menubutton[i].SetPosition(275 + (i - 1)*175, 50);
		m_menubutton[i].SetZ(30);
	}

	//Würfelbutton initialisieren
	m_dicebutton = m_menubutton[0];
	m_dicebutton.SetZ(30);
	m_dicebutton.SetPosition(368, 750);
	m_dicebutton.SetSpriteNumber(0, 8);

	//initialisiere Next Button
	m_nextbutton = m_menubutton[0];
	m_nextbutton.SetZ(30);
	m_nextbutton.SetPosition(1300, 1);
	m_nextbutton.SetSpriteNumber(0, 10);


	//alle Elemente des Startbildschirms zur Liste hinzufügen
	m_list.SetWorkspace(&m_buff);
	m_list.Insert(&m_startbkg);
	m_list.Insert(&m_startbutton);
	

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
		-alle Feldsprites werden in die Liste geladen*/
	if (hit == &m_startbutton) {
		statemachine(0, NULL);
	}

	//Für Würfelbutton
	if (hit == &m_dicebutton) {
		statemachine(4, NULL);
	}

	//Ende Button
	if (hit == &m_menubutton[3]) {
		statemachine(1, NULL);
	}

	if (hit == &m_nextbutton) {
		statemachine(6, NULL);
	}
	if (hit == &m_menubutton[0]) {
		statemachine(3, NULL);
	}
	else {
		if (hit != NULL) {
			statemachine(7, point);
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

	//Butoon im Startmenü
	if (hit == &m_startbutton)
		m_startbutton.SetSpriteNumber(0, 1);
	else
		m_startbutton.SetSpriteNumber(0, 0);

	//Würfelbutton
	if (hit == &m_dicebutton)
		m_dicebutton.SetSpriteNumber(0, 9);
	else
		m_dicebutton.SetSpriteNumber(0, 8);

	//Nextbutton
	if (hit == &m_nextbutton)
		m_nextbutton.SetSpriteNumber(0, 11);
	else
		m_nextbutton.SetSpriteNumber(0, 10);

	//Menue Buttons
	for (int i = 0; i < 4; i++) {
		if (hit == &m_menubutton[i])
			m_menubutton[i].SetSpriteNumber(0, 1 + i * 2);
		else
			m_menubutton[i].SetSpriteNumber(0, i * 2);
	}


	m_list.Update(&dc, 0, 0);

	CDialogEx::OnMouseMove(nFlags, point);
}


//Wird beim Klick auf den Start button im Startmenu aufgerufen; initialisiert das Spielfeld
void CMFCBelegDlg::InitGame(){
	m_startbutton.SetPosition(1921, 0);
	m_startbkg.SetPosition(1920, 0);

	m_buff.Load("Hintergrund.bmp");
	m_list.Insert(&m_bkg);

	m_list.Insert(&m_dicebutton);
	m_list.Insert(&m_dice[0]);
	m_list.Insert(&m_dice[1]);
	m_list.Insert(&m_nextbutton);
	for (int i = 0; i < 4; i++) {
		m_list.Insert(&m_menubutton[i]);
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_list.Insert(&m_field[i][j]);
		}
	}
}


//wird beim Klick auf einen Würfel aufgerufen, Switcht zwischen Status würfeln und nicht würfeln
void CMFCBelegDlg::InitDice(){

	SetTimer(1, 75, NULL);
	SetTimer(2, 2000, NULL);
	

}


//ändert zufällig aussehen des Würfels beim Mürfeln
void CMFCBelegDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein, und/oder benutzen Sie den Standard.
	CClientDC dc(this);

	if (nIDEvent == 2) {
		KillTimer(1);
		KillTimer(2);
		statemachine(5, NULL);
	}
	else {
		if (nIDEvent == 1) {
			m_dice[0].SetSpriteNumber(rand() % 3, rand() % 2);
			m_dice[1].SetSpriteNumber(rand() % 3, rand() % 2);
			m_list.Update(&dc, 0, 0);
		}
	}
	

	CDialogEx::OnTimer(nIDEvent);
}

void CMFCBelegDlg::game(bool player) {

	return;
}

void CMFCBelegDlg::set_field(CPoint point) {

	CSprite *hit = m_list.HitTest(point);

	hit->SetAlpha(1.0f);

}


void CMFCBelegDlg::statemachine(int event, CPoint point) {

	switch (m_table[event][m_state].action) {
	case -1: return;
		break;
	case 0: 
		break;
	case 1: InitGame();
		break;
	case 2: OnCancel();
		break;
	case 3: //game(TRUE)
		break;
	case 4: InitDice();
		break;
	case 5: KillTimer(1);
		break;
	case 6: //reset_game()
		break;
	case 7: //game(FALSE)
		break;
	case 8: set_field(point);
		break;
	}
	m_state = m_table[event][m_state].next_state;
}
