#pragma once
#include "LeapApp.h"
#include "LeapWnd.h"


LeapApp::LeapApp()
{
}

LeapApp::~LeapApp()
{
}

BOOL LeapApp::InitInstance()
{
	LeapWnd * pf = new LeapWnd;
	pf->ShowWindow(m_nCmdShow);
	pf->UpdateWindow();
	this->m_pMainWnd = pf;
	return TRUE;
}

LeapApp app;