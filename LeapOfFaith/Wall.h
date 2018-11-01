#pragma once
#include "Cube.h"
#include <afxwin.h>

class Wall:public Cube
{
public:
	Wall(CBitmap *, int x, int y);
	~Wall();

private:

};

Wall::Wall(CBitmap *bmp,int x,int y):Cube(bmp)
{
	this->x = x;
	this->y = y;
}

Wall::~Wall()
{
}
