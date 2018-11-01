#pragma once
#include <afxwin.h>
#include "Cube.h"
#include "Constant.h"

class LeapWnd :public CFrameWnd
{
public:
	LeapWnd();
	~LeapWnd();

private:
	CDC * pdc;
	CBitmap * bg;
	int bg_y = 0;
	int bgback_y = -BG_HEIGHT;
	bool is_bg_move = false;
	CBitmap * wallbmp;
	CBitmap * blockbmp;
	CBitmap * pointbmp;
	CBitmap * man[MAN_NUM][2];
	int man_frame = 0;
	int man_y = MAN_YOFFSET;
	bool is_man_move = false;
	Cube * lwalls[WALL_NUM];
	Cube * rwalls[WALL_NUM];
	void ShowStage();
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};