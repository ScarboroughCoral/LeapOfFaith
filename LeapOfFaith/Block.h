#pragma once
#include "Cube.h"
#include "Constant.h"
#include <afxwin.h>

class Block:public Cube
{
public:
	int width;
	int  height;
	int num;
public:
	Block(CBitmap *,int x,int y,int num,int w,int h);
	~Block();

private:
	
};


inline Block::Block(CBitmap *bmp, int x, int y, int num,int w = BLOCK_WIDTH, int h=BLOCK_HEIGHT):Cube(bmp)
{
	this->x = x;
	this->y = y;
	this->num = num;
	this->width = w;
	this->height = h;
}

inline Block::~Block()
{
}

