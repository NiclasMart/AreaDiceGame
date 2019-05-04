
// MFC_Beleg.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CMFCBelegApp:
// Siehe MFC_Beleg.cpp für die Implementierung dieser Klasse
//

class CMFCBelegApp : public CWinApp
{
public:
	CMFCBelegApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMFCBelegApp theApp;
