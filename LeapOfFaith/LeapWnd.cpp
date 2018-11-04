#pragma once
#include <afxwin.h>
#include "Constant.h"
#include "LeapWnd.h"
#include "Wall.h"


LeapWnd::LeapWnd()
{
	Create(NULL, "Leap Of Faith");
	MoveWindow(100, 100, BG_WIDTH + 2 * WALL_WIDTH+20, BG_HEIGHT);
	pdc = new CDC;
	CClientDC dc(this);
	pdc->CreateCompatibleDC(&dc);
	//初始化素材
	bg = new CBitmap;
	bg->m_hObject = LoadImage(NULL, "bg.bmp",IMAGE_BITMAP, BG_WIDTH, BG_HEIGHT,LR_LOADFROMFILE);
	wallbmp = new CBitmap;
	wallbmp->m_hObject = LoadImage(NULL, "wall.bmp", IMAGE_BITMAP, WALL_WIDTH, WALL_HEIGHT, LR_LOADFROMFILE);

	//初始化左面墙元素
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		lwalls[i] = new Wall(wallbmp, 0, i*WALL_HEIGHT);
	}
	//初始化右面墙元素
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		rwalls[i] = new Wall(wallbmp, WALL_WIDTH+BG_WIDTH, i*WALL_HEIGHT);
	}
	//初始化障碍物
	blockbmp = new CBitmap;
	blockbmp->m_hObject = LoadImage(NULL, "block.bmp", IMAGE_BITMAP, BLOCK_WIDTH, BLOCK_HEIGHT, LR_LOADFROMFILE);
	//初始化指针
	pointbmp = new CBitmap;
	pointbmp->m_hObject = LoadImage(NULL, "arrowa.bmp", IMAGE_BITMAP, POINTER_WIDTH, POINTER_HEIGHT, LR_LOADFROMFILE);
	//初始化小人
	char name[10];
	for (size_t i = 0; i < MAN_NUM; i++)
	{
		sprintf_s(name, "man%da.bmp", i + 1);
		man[i][0] = new CBitmap;
		man[i][0]->m_hObject = LoadImage(NULL, name, IMAGE_BITMAP, MAN_WIDTH, MAN_HEIGHT, LR_LOADFROMFILE);
		sprintf_s(name, "man%db.bmp", i + 1);
		man[i][1] = new CBitmap;
		man[i][1]->m_hObject = LoadImage(NULL, name, IMAGE_BITMAP, MAN_WIDTH, MAN_HEIGHT, LR_LOADFROMFILE);
	}
	//开启计时器
	SetTimer(NULL, 100, NULL);
	
}

LeapWnd::~LeapWnd()
{
}BEGIN_MESSAGE_MAP(LeapWnd, CFrameWnd)
ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_KEYUP()
END_MESSAGE_MAP()


void LeapWnd::ShowStage()
{
		CClientDC dc(this); 
		//画背景
		pdc->SelectObject(bg);
		dc.BitBlt(WALL_WIDTH, bg_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
		dc.BitBlt(WALL_WIDTH, bgback_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
		//画墙
		pdc->SelectObject(wallbmp);
		for (size_t i = 0; i < WALL_NUM; i++)
		{
			dc.BitBlt(lwalls[i]->x, lwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
			dc.BitBlt(rwalls[i]->x, rwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
		}
		//画指针
		if (is_pointer_show)
		{
			pdc->SelectObject(pointbmp);
			dc.BitBlt(POINTER_XOFFSET, POINTER_YOFFSET, POINTER_WIDTH, POINTER_HEIGHT, pdc, 0, 0, SRCAND);
		}
		//画小人
		pdc->SelectObject(man[man_frame][1]);
		dc.BitBlt(MAN_XOFFSET, man_y, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCAND);
		pdc->SelectObject(man[man_frame][0]);
		dc.BitBlt(MAN_XOFFSET, man_y, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCPAINT);
}

/*
* 清除障碍物辅助缓存
*/
void LeapWnd::Release_block_bk_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks_back[i]!=NULL)
		{
			delete stage_blocks_back[i];
			stage_blocks_back[i] = NULL;
		}
	}
}
/*
* 清除障碍物主缓存
*/
void LeapWnd::Release_block_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks[i] != NULL)
		{
			delete stage_blocks[i];
			stage_blocks[i] = NULL;
		}
	}
}

void LeapWnd::Reload_block_bk_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks_back[i] == NULL)
		{
			 
		}
	}
}

void LeapWnd::Reload_block_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks[i] == NULL)
		{
			
		}
	}
}

void LeapWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//画背景
	pdc->SelectObject(bg);
	dc.BitBlt(WALL_WIDTH, bg_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
	dc.BitBlt(WALL_WIDTH, bgback_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
	//画墙
	pdc->SelectObject(wallbmp);
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		dc.BitBlt(lwalls[i]->x, lwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
		dc.BitBlt(rwalls[i]->x, rwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
	}
	//画指针
	if (is_pointer_show)
	{
		pdc->SelectObject(pointbmp);
		dc.BitBlt(POINTER_XOFFSET, POINTER_YOFFSET, POINTER_WIDTH, POINTER_HEIGHT, pdc, 0, 0, SRCAND);
	}
	//画人
	pdc->SelectObject(man[0][1]);
	dc.BitBlt(MAN_XOFFSET, MAN_YOFFSET, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCAND);
	pdc->SelectObject(man[0][0]);
	dc.BitBlt(MAN_XOFFSET, MAN_YOFFSET, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCPAINT);
}



void LeapWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (is_bg_move)
	{
		bg_y = (bg_y + 10);
		bgback_y = (bgback_y + 10);
		if (bg_y >= BG_HEIGHT)
		{
			bg_y = -BG_HEIGHT;
		}
		if (bgback_y >= BG_HEIGHT)
		{
			bgback_y = -BG_HEIGHT;
		}
		for (size_t i = 0; i < WALL_NUM; i++)
		{
			lwalls[i]->y = (lwalls[i]->y + 5);
			rwalls[i]->y = (rwalls[i]->y + 5);
			if ((lwalls[i]->y) >= BG_HEIGHT)
			{
				lwalls[i]->y = -WALL_HEIGHT;
			}
			if ((rwalls[i]->y) >= BG_HEIGHT)
			{
				rwalls[i]->y = -WALL_HEIGHT;
			}
		}
	}
	if (is_man_move)
	{
		if (man_y>MAN_CENTER)
		{
			man_y -= 5;
		}
		else {
			is_bg_move = true;
		}
		man_frame = (man_frame + 1) % MAN_NUM;
	}
	ShowStage();
	CFrameWnd::OnTimer(nIDEvent);
}


void LeapWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	is_man_move = true;
	is_pointer_show = false;
	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}
