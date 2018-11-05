#pragma once
#include "Cube.h"
#include <afxwin.h>

class Wall:public Cube
{
public:
	Wall(CBitmap *, float x, float y);
	~Wall();

private:

};

Wall::Wall(CBitmap *bmp, float x, float y):Cube(bmp)
{
	this->x = x;
	this->y = y;
}

Wall::~Wall()
{
}
