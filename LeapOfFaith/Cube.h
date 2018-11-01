#pragma once
#include <afxwin.h>
class Cube
{
public:
	Cube(CBitmap *);
	Cube();
	~Cube();
public:
	int x;
	int y;
protected:
	CBitmap * bmp;

private:


};


inline Cube::Cube(CBitmap * bmp)
{
	this->bmp = bmp;
}

inline Cube::Cube()
{
}

inline Cube::~Cube()
{
}

