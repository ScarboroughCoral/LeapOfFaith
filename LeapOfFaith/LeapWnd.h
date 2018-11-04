#pragma once
#include <afxwin.h>
#include "Cube.h"
#include "Block.h"
#include "Constant.h"

#define BLOCK_CACHE_SIZE 20

class LeapWnd :public CFrameWnd
{
public:
	LeapWnd();
	~LeapWnd();

private:
	CDC * pdc;
	//背景相关
	CBitmap * bg;
	int bg_y = 0;
	int bgback_y = -BG_HEIGHT;
	bool is_bg_move = false;
	CBitmap * blockbmp;
	//指针
	CBitmap * pointbmp;
	bool is_pointer_show = true;
	//角色相关
	CBitmap * man[MAN_NUM][2];
	int man_frame = 0;
	int man_y = MAN_YOFFSET;
	bool is_man_move = false;
	//墙
	CBitmap * wallbmp;
	Cube * lwalls[WALL_NUM];
	Cube * rwalls[WALL_NUM];
	//障碍物
	bool is_need_create_block = true;
	Block *stage_blocks[BLOCK_CACHE_SIZE];
	Block *stage_blocks_back[BLOCK_CACHE_SIZE];
	void ShowStage();
	void Release_block_bk_cache();
	void Release_block_cache();
	void Reload_block_bk_cache();
	void Reload_block_cache();
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};