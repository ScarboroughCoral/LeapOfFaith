#pragma once
#include <afxwin.h>
#include "Cube.h"
#include "Block.h"
#include "Constant.h"

#define BLOCK_CACHE_SIZE 5

class LeapWnd :public CFrameWnd
{
public:
	LeapWnd();
	~LeapWnd();

private:
	CDC * pdc;
	//背景相关
	CBitmap * bg;
	float bg_y = 0;
	float bgback_y = -BG_HEIGHT;
	bool is_bg_move = false;
	CBitmap * blockbmp;
	//指针
	CBitmap * pointbmp;
	CBitmap * pointtmpbmp;
	bool is_pointer_show = true;
	float angle = 0;
	float deltaY = 1;
	float deltaX = 0;
	bool is_signed = false;
	//角色相关
	CBitmap * man[MAN_NUM][2];
	int man_frame = 0;
	float man_y = MAN_YOFFSET;
	float man_x = MAN_XOFFSET;
	bool is_man_move = false;
	//墙
	CBitmap * wallbmp;
	Cube * lwalls[WALL_NUM];
	Cube * rwalls[WALL_NUM];
	//障碍物
	bool is_need_create_block = true;
	Block *stage_blocks[BLOCK_CACHE_SIZE][2];
	Block *stage_blocks_back[BLOCK_CACHE_SIZE][2];
	//控制相关
	bool is_gameover = false;
	UINT timer = 1;
	int score = 0;
	int elapsed_time = 0;


	void ShowStage();
	void Release_block_bk_cache();
	void Release_block_cache();
	void Reload_block_bk_cache(bool is_first);
	void Reload_block_cache();
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
};