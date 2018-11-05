#pragma once
#include <afxwin.h>
class Cube
{
public:
	Cube(CBitmap *);
	Cube();
	~Cube();
public:
	float x;
	float y;
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

