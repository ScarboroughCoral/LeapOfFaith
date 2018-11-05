#pragma once
#include "Cube.h"
#include "Constant.h"
#include <afxwin.h>

class Block:public Cube
{
public:
	float width;
	float  height;
	int num;
public:
	Block(CBitmap *, float x, float y, int num, float w, float h);
	~Block();

private:
	
};


inline Block::Block(CBitmap *bmp, float x, float y, int num, float w = BLOCK_WIDTH, float h=BLOCK_HEIGHT):Cube(bmp)
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

