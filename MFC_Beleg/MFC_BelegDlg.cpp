
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
	: CDialogEx(IDD_MFC_BELEG_DIALOG, pParent), m_wintest(&Matrix.m_field[0][0])
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
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BOOL CMFCBelegDlg::PreTranslateMessage(MSG* pMsg) {
	// return CDialog::PreTranslateMessage(pMsg); 
	return CWnd::PreTranslateMessage(pMsg); 
}
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

	//Anfangszustand setzen (Zustand: Spielstart) und  Zustandsmatrix initialisieren
	m_state = 0;
	struct tab  table[13][6] = {
		{ { 1, 1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { 1, 2 }, { 2, 2 }, { 2, 2 }, { 4, 2 }, { 5, 2 } },
		{ { -1, -1 }, { -1, -1 }, { 1, 6 }, { 1, 6 }, { 1, 6 }, { 1, 6 } },
		{ { -1, -1 }, { 2, 3 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { -1, -1 }, { 4, 4 }, { -1, -1 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { 3, 5 }, { -1, -1 } },
		{ { -1, -1 }, { -1, -1 }, { -1, -1 }, { 3, 8 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { 1, 9 }, { 2, 9 }, { 3, 9 }, { 4, 9 }, { 5, 9 } },
		{ { -1, -1 }, { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 5, 10 } },
		{ { -1, -1 }, { -1, -1 }, { -1, -1 }, { 3, 11 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { -1, -1 }, { -1, -1 }, { 3, 7 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { -1, -1 }, { -1, -1 }, { 2, 12 }, { -1, -1 }, { -1, -1 } },
		{ { -1, -1 }, { 1, 13 }, { -1, -1 }, { -1, -1 }, { -1, -1 }, { -1, -1 } }
	};
	memcpy(m_table, table, sizeof(table));
	
	//Spielhintergrund BMP laden
	if (!m_bkg.Load("Hintergrund.bmp")) {
		AfxMessageBox(L"Konnte Hintergrund.bmp nicht laden!");
		OnCancel();
	}
	m_bkg.SetZ(0);
	
	//Schrift laden
	if (!m_font.Load("325x60_Schrift_4.bmp", CSize(325, 60))) {
		AfxMessageBox(L"Konnte 325x60_Schrift_4.bmp nicht laden!");
		OnCancel();
	}
	m_font.SetZ(40);
	m_font.SetPosition(1921, 0);
	m_list.Insert(&m_font);
	
	//Win Sprite laden
	if (!m_win.Load("140x400_win_3.bmp", CSize(400, 140))) {
		AfxMessageBox(L"Konnte 140x400_win_3.bmp nicht laden!");
		OnCancel();
	}
	m_win.SetZ(60);
	m_win.SetPosition(1921, 0);
	m_list.Insert(&m_win);
	
	//Feld Sprite BMP laden
	if (!Matrix.m_field[0][0].Load("94x84_Sprite_4.bmp", CSize(94, 85))) {
		AfxMessageBox(L"Konnte 94x84_Sprite_4.bmp nicht laden!");
		OnCancel();
	}

	//Initialisieren aller Feldinhalte der Matrix
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			Matrix.m_field[i][j] = Matrix.m_field[0][0];

			Matrix.m_field[i][j].SetZ(2);
			Matrix.m_field[i][j].SetPosition(908 + (79 * i), 67 + (79 * j));
			Matrix.m_field[i][j].SetAlpha(0.0f);
			
		}
	}


	//Würfel Sprite BMP laden
	if (!m_dice[0].Load("200x170_Wuerfel_6.bmp", CSize(200, 170))) {
		AfxMessageBox(L"Konnte 200x170_Wuerfel_6.bmp nicht laden!");
		OnCancel();
	}

	m_dice[1] = m_dice[0];
	for (int i = 0; i < 2; i++){
		m_dice[i].SetZ(10);
		m_dice[i].SetSpriteNumber(0, rand() % 6);
		m_dice[i].SetPosition(260 + i*200, 850);
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

	//Checkbox initialisieren
	if (!m_checkbox[0].Load("49x344_Checkbox_3.bmp", CSize(344, 49))) {
		AfxMessageBox(L"Konnte 49x344_Checkbox_3.bmp nicht laden!");
		OnCancel();
	}
	m_checkbox[0].SetZ(30);
	m_checkbox[1] = m_checkbox[0];
	m_checkbox[1].SetSpriteNumber(0, 1);
	m_checkbox[0].SetPosition(100, 125);
	m_checkbox[1].SetPosition(385, 125);


	//Info + info-zurück Button initialisieren
	if (!m_info.Load("Info.bmp")) {
		AfxMessageBox(L"Konnte Info.bmp nicht laden!");
		OnCancel();
	}
	m_info.SetZ(100);
	m_info.SetPosition(1921, 0);

	m_infobutton = m_menubutton[3];
	m_infobutton.SetZ(101);
	m_infobutton.SetPosition(1921, 0);

	//alle Elemente des Startbildschirms zur Liste hinzufügen
	m_list.SetWorkspace(&m_buff);
	m_list.Insert(&m_startbkg);
	m_list.Insert(&m_startbutton);

	player_num = 0;
	round = 1;
	computer_enemy = FALSE;

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
		Statemachine(0);
	}

	//Würfelbutton
	if (hit == &m_dicebutton) {
		Statemachine(4);
	}

	//Start Button
	if (hit == &m_menubutton[0]) {
		Statemachine(3);
	}
	//Reset Button
	if (hit == &m_menubutton[1]) {
		Statemachine(2);
	}
	//Ende Button
	if (hit == &m_menubutton[3]) {
		Statemachine(1);
	}
	//Next Button
	if (hit == &m_nextbutton) {
		Statemachine(11);
	}
	//Computergegner Button
	if (hit == &m_checkbox[1]) {
		Statemachine(12);
	}

	//Info Button
	if (hit == &m_menubutton[2]) {
		

		m_info.SetPosition(0, 0);
		m_infobutton.SetPosition(1700, 950);
	}

	//Info-zurück Button
	if (hit == &m_infobutton) {
		m_info.SetPosition(1921, 0);
		m_infobutton.SetPosition(1921, 0);
	}

	CFieldSprite *hit2 = dynamic_cast<CFieldSprite*>(hit);						//dynamic Cast -> wenn Cast erfolgreich muss es sich um ein Matrix Feld handeln
	if ((hit2 != NULL)) {
		if (Statemachine(6)) m_state = 2;										//falls das Setzen des Feldes erfolgreich war, wird der Spieler gewechselt
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

	//info-zurück Button
	if (hit == &m_infobutton)
		m_infobutton.SetSpriteNumber(0, 7);
	else
		m_infobutton.SetSpriteNumber(0, 6);


	//Spielfelder
	if (hit == &m_bkg) Matrix.ResetBuff();										//falls Spielfeld verlassen, setzte alles zurück
	CFieldSprite *hit2 = dynamic_cast<CFieldSprite*>(hit);						//dynamic Cast -> wenn Cast erfolgreich muss es sich um ein Matrix Feld handeln
	if ((Statemachine(9)) && (hit2 != NULL)) {									//Prüft ob Zustand eine Feldeingabe erlaubt und ob Cast erfolgreich (damit Matrix Feld
		if (Matrix.pt_field != hit2) {											//wenn sich Maus auf ein neues Feld verschiebt, wird Neuzeichnen eingeleitet, ansonsten nicht
			Matrix.ResetBuff();													//Setzt alle Inhalte der Puffer (Vorschaupuffer und Zeichenpuffer zurück				
			Matrix.pt_field = hit2;												//speicher die Adresse des Feldes auf welches gezeigt wird
			Matrix.SetBuff(hit2, dice_value[0], dice_value[1], player_num, round);		//Puffer werden neu geladen
			Matrix.DrawPrevBuff();												//zeichne die Vorschau Puffermatrix
		}
															
	}

	CString test;
	test.Format(L"Feld 0: %d    Feld 1: %d  Status: %d", m_wintest.player_points[0], m_wintest.player_points[1], Matrix.valid_field_pos == TRUE ? 1 : 0);
	SetWindowText(test);
	
	m_list.Update(&dc, 0, 0);

	CDialogEx::OnMouseMove(nFlags, point);
}



//erkennt Tastendruck auf R und schickt dann das entsprechende Ereignis zur Drehung des Vorschaufeldes
void CMFCBelegDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	if (nChar == 0x52) Statemachine(10);
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
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
	m_list.Insert(&m_checkbox[0]);
	m_list.Insert(&m_checkbox[1]);
	m_list.Insert(&m_info);
	m_list.Insert(&m_infobutton);
	for (int i = 0; i < 4; i++) {
		m_list.Insert(&m_menubutton[i]);
	}
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			m_list.Insert(&Matrix.m_field[i][j]);
		}
	}
	return;
}


//wird beim Klick auf einen Würfel aufgerufen, Switcht zwischen Status würfeln und nicht würfeln
void CMFCBelegDlg::InitDice(){

	SetTimer(1, 75, NULL);
	SetTimer(2, 2000, NULL);
	
	return;
}


//ändert zufällig aussehen des Würfels beim Mürfeln
void CMFCBelegDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Fügen Sie hier Ihren Meldungsbehandlungscode ein, und/oder benutzen Sie den Standard.
	CClientDC dc(this);


	switch (nIDEvent) {
		case 2: 
			KillTimer(1);
			KillTimer(2);
			Statemachine(5);
		break;
		case 1: 
			dice_value[0] = rand() % 6;
			dice_value[1] = rand() % 6;
			m_dice[0].SetSpriteNumber(0, dice_value[0]);
			m_dice[1].SetSpriteNumber(0, dice_value[1]);
			dice_value[0]++;
			dice_value[1]++;
			m_list.Update(&dc, 0, 0);
		break;
		case 3: 
			EnemyTurn();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


//ändert die Spielernummer falls erster Aufruf playerchange = FALSE, sonst TRUE
void CMFCBelegDlg::Game(bool playerchange) {
	
	if (playerchange) {
		if (player_num == 0) player_num = 1;
		else player_num = 0;
		round++;

		if ((player_num == 1) && (computer_enemy)) {
			InitEnemyTurn();
			
		}
	}
	m_font.SetPosition(100, 200);
	m_font.SetSpriteNumber(0, player_num);
	
	
	return;
}


//angecklicktes Feld wird sichtbar gemacht
bool CMFCBelegDlg::SetField() {
	
	int winner;
	

	if ((!computer_enemy) || (player_num == 0)) {									//wenn entweder der Computergegner nicht angeschaltet ist, oder der andere Spieler am Zug ist
		if (!Matrix.DrawFieldBuff(player_num)) {
			Matrix.ResetBuff();
			return FALSE;
		}
	}

	if ((m_wintest.WinControll(&Matrix.m_field[0][0], winner) == TRUE)) {			//Siegkontrolle
		Matrix.ResetControlState();													//wenn ein Spieler gewonnen hat wird FALSE zurück gegeben und die Funktion Win() gerufen
		m_state = 5;
		Win(winner);
		return FALSE;
	}
	else {																			//wenn der Spieler nicht gewonnen hat, wird der Spieler gewechselt und beide Puffer resetet
		Matrix.ResetControlState();
		Game(TRUE);
		Matrix.ResetBuff();
		return TRUE;
	}
	
}


//Setzt Spielfeld zurück
void CMFCBelegDlg::ResetGame() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			Matrix.m_field[i][j].SetAlpha(0.0f);
			Matrix.m_field[i][j].SetPlayernum(-1);
		}
	}
	m_font.SetPosition(1921, 0);
	player_num = 0;
	Matrix.ResetState();
	m_win.SetPosition(1921, 0);
	Matrix.ResetControlState();
	round = 1;
}


//drehen des zu setzenden Feldes
void CMFCBelegDlg::RotateField() {
	CClientDC dc(this);

	int temp = dice_value[0];														//Würfelzahlen vertauschen
	dice_value[0] = dice_value[1];
	dice_value[1] = temp;

	if (Matrix.pt_field != NULL) {													//Checkt ob Maus auf bkg, wenn ja wird das Feld nicht neu gezeichnet 
		CFieldSprite* pt = Matrix.pt_field;											//aktuelles Feld wird zwischengespeicher (notwendig wegen ResetBuff())

		Matrix.ResetBuff();
		Matrix.pt_field = pt;														//zurückschreiben des Feldes auf den Feld Pointer
		Matrix.SetBuff(Matrix.pt_field, dice_value[0], dice_value[1], player_num, round);	//Puffer werden neu initialisiert mit vertauschten Würfelzahlen (Rotation) 
		Matrix.DrawPrevBuff();								
	}
	m_list.Update(&dc, 0, 0);
}


void CMFCBelegDlg::Win(int &winner) {

	CClientDC dc(this);

	m_font.SetPosition(1921, 0);
	m_win.SetSpriteNumber(0, winner);
	m_win.SetPosition(275, 400);

	m_list.Update(&dc, 0, 0);
	return;
}

void CMFCBelegDlg::InitEnemy() {

	if (computer_enemy) {
		m_checkbox[1].SetSpriteNumber(0, 1);
		computer_enemy = FALSE;
	}
	else {
		m_checkbox[1].SetSpriteNumber(0, 2);
		computer_enemy = TRUE;
	}
}

void CMFCBelegDlg::InitEnemyTurn() {

	CClientDC dc(this);

	InitDice();
	SetTimer(3, 3000, NULL);
	m_list.Update(&dc, 0, 0);
}

void CMFCBelegDlg::EnemyTurn() {

	CClientDC dc(this);
	int winner;

	KillTimer(3);
	m_enemy.EnemyTurn(&Matrix.m_field[0][0], Matrix, round, player_num, dice_value[0], dice_value[1], &dc, m_list);

	if (m_wintest.WinControll(&Matrix.m_field[0][0], winner)) {						//Siegkontrolle
		Matrix.ResetControlState();													//wenn ein Spieler gewonnen hat wird FALSE zurück gegeben und die Funktion Win() gerufen
		m_state = 5;
		Win(winner);
		return;
	}

	Game(TRUE);
	m_list.Update(&dc, 0, 0);
}



//bestimmt anhand des Momentanen Zustands und des eingetroffenen Ereignisses die folgende Aktion
bool CMFCBelegDlg::Statemachine(int event) {

	switch (m_table[event][m_state].action) {
	case -1: return FALSE;
		break;
	case 0: 
		break;
	case 1: InitGame();
		break;
	case 2: OnCancel();
		break;
	case 3: Game(FALSE);
		break;
	case 4: InitDice();
		break;
	case 5: KillTimer(1);
		break;
	case 6: ResetGame();
		break;
	case 7: RotateField();
		break;
	case 8: return SetField();
		break;
	case 9: //show_info()
		break;
	case 10: //close_info()
		break;
	case 11: return TRUE;
		break;
	case 12:
		if ((!computer_enemy) || (player_num == 0)) {
			Matrix.ResetBuff();
			Game(TRUE);
	}
		break;
	case 13: InitEnemy();
	}
	m_state = m_table[event][m_state].next_state;
}


