#pragma once
#include <afxwin.h>
#include "Constant.h"
#include "LeapWnd.h"
#include "Wall.h"
#include "BitmapRotate.h"

#define LEVEL 2


LeapWnd::LeapWnd()
{
	Create(NULL, "Leap Of Faith");
	MoveWindow(100, 100, BG_WIDTH + 2 * WALL_WIDTH+20, BG_HEIGHT);
	pdc = new CDC;
	CClientDC dc(this);
	pdc->CreateCompatibleDC(&dc);
	//��ʼ���ز�
	bg = new CBitmap;
	bg->m_hObject = LoadImage(NULL, "bg.bmp",IMAGE_BITMAP, BG_WIDTH, BG_HEIGHT,LR_LOADFROMFILE);
	wallbmp = new CBitmap;
	wallbmp->m_hObject = LoadImage(NULL, "wall.bmp", IMAGE_BITMAP, WALL_WIDTH, WALL_HEIGHT, LR_LOADFROMFILE);

	//��ʼ������ǽԪ��
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		lwalls[i] = new Wall(wallbmp, 0, i*WALL_HEIGHT);
	}
	//��ʼ������ǽԪ��
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		rwalls[i] = new Wall(wallbmp, WALL_WIDTH+BG_WIDTH, i*WALL_HEIGHT);
	}
	//��ʼ���ϰ���
	blockbmp = new CBitmap;
	blockbmp->m_hObject = LoadImage(NULL, "block.bmp", IMAGE_BITMAP, BLOCK_WIDTH, BLOCK_HEIGHT, LR_LOADFROMFILE);
	Reload_block_cache();
	Reload_block_bk_cache(true);
	//��ʼ��ָ��
	pointbmp = new CBitmap;
	pointtmpbmp = new CBitmap;
	pointbmp->m_hObject = LoadImage(NULL, "arrowa.bmp", IMAGE_BITMAP, POINTER_WIDTH, POINTER_HEIGHT, LR_LOADFROMFILE);
	pointtmpbmp->m_hObject = LoadImage(NULL, "arrowa.bmp", IMAGE_BITMAP, POINTER_WIDTH, POINTER_HEIGHT, LR_LOADFROMFILE);
	//��ʼ��С��
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
	//������ʱ��
	timer = SetTimer(1, 100, NULL);
	
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
		//������
		pdc->SelectObject(bg);
		dc.BitBlt(WALL_WIDTH, bg_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
		dc.BitBlt(WALL_WIDTH, bgback_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
		//��ǽ
		pdc->SelectObject(wallbmp);
		for (size_t i = 0; i < WALL_NUM; i++)
		{
			dc.BitBlt(lwalls[i]->x, lwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
			dc.BitBlt(rwalls[i]->x, rwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
		}
		//���ϰ���
		pdc->SelectObject(blockbmp);
		for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
		{
			Block * tmp = stage_blocks[i][0];
			for (size_t i = 0; i < tmp->num; i++)
			{
				dc.BitBlt(tmp->x + i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
			}

			tmp = stage_blocks[i][1];

			for (size_t i = 0; i < tmp->num; i++)
			{
				dc.BitBlt(tmp->x - i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
			}
		}
		for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
		{
			Block * tmp = stage_blocks_back[i][0];
			for (size_t i = 0; i < tmp->num; i++)
			{
				dc.BitBlt(tmp->x + i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
			}

			tmp = stage_blocks_back[i][1];

			for (size_t i = 0; i < tmp->num; i++)
			{
				dc.BitBlt(tmp->x - i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
			}
		}
		//��ָ��
		if (is_pointer_show)
		{
			pdc->SelectObject(pointtmpbmp);
			dc.BitBlt(POINTER_XOFFSET, POINTER_YOFFSET, POINTER_WIDTH, POINTER_HEIGHT, pdc, 0, 0, SRCAND);
		}
		//��С��
		pdc->SelectObject(man[man_frame][1]);
		dc.BitBlt(man_x, man_y, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCAND);
		pdc->SelectObject(man[man_frame][0]);
		dc.BitBlt(man_x, man_y, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCPAINT);
}

/*
* ����ϰ��︨������
*/
void LeapWnd::Release_block_bk_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks_back[i][0]!=NULL)
		{
			delete stage_blocks_back[i][0];
			stage_blocks_back[i][0] = NULL;
		}
		if (stage_blocks_back[i][1] != NULL)
		{
			delete stage_blocks_back[i][1];
			stage_blocks_back[i][1] = NULL;
		}
	}
}
/*
* ����ϰ���������
*/
void LeapWnd::Release_block_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks[i][0] != NULL)
		{
			delete stage_blocks[i][0];
			stage_blocks[i][0] = NULL;
		}
		if (stage_blocks[i][1] != NULL)
		{
			delete stage_blocks[i][1];
			stage_blocks[i][1] = NULL;
		}
	}
}
/*
* �����ϰ��︨������
*/
void LeapWnd::Reload_block_bk_cache(bool is_first)
{
	int t = is_first ? 2 : 1;
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks_back[i][0] == NULL)
		{
			int y = rand() % BG_HEIGHT - BG_HEIGHT*t;
			int width = rand() % LEVEL +1;
			stage_blocks_back[i][0] = new Block(blockbmp, WALL_WIDTH, y, width);
		}
		if (stage_blocks_back[i][1] == NULL)
		{
			int y = rand() % BG_HEIGHT - BG_HEIGHT * t;
			int width = rand() % LEVEL +1;
			stage_blocks_back[i][1] = new Block(blockbmp, WALL_WIDTH + BG_WIDTH - BLOCK_WIDTH, y, width);
		}
	}
}
/*
* �����ϰ���������
*/
void LeapWnd::Reload_block_cache()
{
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		if (stage_blocks[i][0] == NULL)
		{
			int y = rand() % BG_HEIGHT - BG_HEIGHT;
			int width = rand() % LEVEL +1;
			stage_blocks[i][0] = new Block(blockbmp, WALL_WIDTH, y, width);

		}
		if (stage_blocks[i][1] == NULL)
		{
			int y = rand() % BG_HEIGHT - BG_HEIGHT;
			int width = rand() % LEVEL +1;
			stage_blocks[i][1] = new Block(blockbmp, WALL_WIDTH+BG_WIDTH- BLOCK_WIDTH, y, width);

		}
	}
}

void LeapWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//������
	pdc->SelectObject(bg);
	dc.BitBlt(WALL_WIDTH, bg_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
	dc.BitBlt(WALL_WIDTH, bgback_y, BG_WIDTH, BG_HEIGHT, pdc, 0, 0, SRCCOPY);
	//��ǽ
	pdc->SelectObject(wallbmp);
	for (size_t i = 0; i < WALL_NUM; i++)
	{
		dc.BitBlt(lwalls[i]->x, lwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
		dc.BitBlt(rwalls[i]->x, rwalls[i]->y, WALL_WIDTH, WALL_HEIGHT, pdc, 0, 0, SRCCOPY);
	}
	//���ϰ���
	pdc->SelectObject(blockbmp);
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		Block * tmp = stage_blocks[i][0];
		for (size_t i = 0; i < tmp->num; i++)
		{
			dc.BitBlt(tmp->x+i*tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
		}
		
		tmp = stage_blocks[i][1];

		for (size_t i = 0; i < tmp->num; i++)
		{
			dc.BitBlt(tmp->x - i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
		}
	}
	for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
	{
		Block * tmp = stage_blocks_back[i][0];
		for (size_t i = 0; i < tmp->num; i++)
		{
			dc.BitBlt(tmp->x + i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
		}

		tmp = stage_blocks_back[i][1];

		for (size_t i = 0; i < tmp->num; i++)
		{
			dc.BitBlt(tmp->x - i * tmp->width, tmp->y, tmp->width, tmp->height, pdc, 0, 0, SRCCOPY);
		}
	}
	//��ָ��
	if (is_pointer_show)
	{
		pdc->SelectObject(pointbmp);
		dc.BitBlt(POINTER_XOFFSET, POINTER_YOFFSET, POINTER_WIDTH, POINTER_HEIGHT, pdc, 0, 0, SRCAND);
	}
	//����
	pdc->SelectObject(man[0][1]);
	dc.BitBlt(MAN_XOFFSET, MAN_YOFFSET, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCAND);
	pdc->SelectObject(man[0][0]);
	dc.BitBlt(MAN_XOFFSET, MAN_YOFFSET, MAN_WIDTH, MAN_HEIGHT, pdc, 0, 0, SRCPAINT);
}



void LeapWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (is_bg_move)
	{
		bg_y = (bg_y + deltaY);
		bgback_y = (bgback_y + deltaY);
		for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
		{
			stage_blocks[i][0]->y += deltaY;
			stage_blocks_back[i][0]->y += deltaY;
			stage_blocks[i][1]->y += deltaY;
			stage_blocks_back[i][1]->y += deltaY;
		}
		if (bg_y >= BG_HEIGHT)
		{
			bg_y = -BG_HEIGHT;
			Release_block_bk_cache();
			Reload_block_bk_cache(false);
		}
		if (bgback_y >= BG_HEIGHT)
		{
			bgback_y = -BG_HEIGHT;
			Release_block_cache();
			Reload_block_cache();
		}
		for (size_t i = 0; i < WALL_NUM; i++)
		{
			lwalls[i]->y = (lwalls[i]->y + deltaY);
			rwalls[i]->y = (rwalls[i]->y + deltaY);
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
			man_y -= deltaY;
		}
		else {
			is_bg_move = true;
		}
		man_x += deltaX;
		if (man_x<= WALL_WIDTH)
		{
			man_x = WALL_WIDTH;
		}
		if ((man_x + MAN_WIDTH) >= (WALL_WIDTH + BG_WIDTH))
		{
			man_x = WALL_WIDTH + BG_WIDTH - MAN_WIDTH;
		}


		
		score += deltaY;
		man_frame = (man_frame + 1) % MAN_NUM;

		//��ײ���
		for (size_t i = 0; i < BLOCK_CACHE_SIZE; i++)
		{
			Block * current = stage_blocks[i][0];
			for (size_t i = 0; i < current->num; i++)
			{
				if (man_x >= current->x&&man_x <= (current->x + current->num*current->width) && man_y >= current->y&&man_y <= (current->y + current->height))
				{
					deltaX = -deltaX;
				}
			}
			current = stage_blocks[i][1];
			current = stage_blocks_back[i][0];
			current = stage_blocks_back[i][1];
		}
		//��ǽ
		if (man_x <= WALL_WIDTH || (man_x + MAN_WIDTH) >= (WALL_WIDTH + BG_WIDTH))
		{
			deltaX = -deltaX;
		}
	}
	else {
		CBitmap * tmp= pointtmpbmp;
		if (!is_signed)
		{
			angle += 10;
			pointtmpbmp = BmpRotate(pointbmp, angle);
		}
		else
		{
			angle -= 10;
			pointtmpbmp = BmpRotate(pointbmp, angle);
		}
		if (angle==90)
		{
			is_signed = true;
		}
		if (angle==-90)
		{
			is_signed = false;
		}
		if (tmp!=NULL)
		{
			delete tmp;
		}
		

	}
	ShowStage();
	//ʱ�����
	elapsed_time++;
	if (elapsed_time>=300||deltaY<0)
	{
		is_gameover = true;
	}
	if (is_gameover)
	{
		KillTimer(timer);
		char result[256];
		if (score>=2000)
		{
			sprintf_s(result, "You Win!Your height is %d!", score);
		}
		else
		{
			sprintf_s(result, "You Lose!Your height is %d!", score);
		}
		MessageBox(result);
	}
	CFrameWnd::OnTimer(nIDEvent);
}


void LeapWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	is_man_move = true;
	is_pointer_show = false;
	if (angle == 90|| angle == -90)
	{
		deltaY = 0;
		deltaX = 10;
	}
	else if (angle==0)
	{
		deltaX = 0;
	}
	else {
		deltaX = -tan(angle*PI / 180)*deltaY;
	}
	CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}
