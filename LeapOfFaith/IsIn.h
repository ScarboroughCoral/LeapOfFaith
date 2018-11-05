#pragma once
bool IsIn(int x, int y, int sx, int sy, int w, int h) {
	return x >= sx && x <= (sx + w) && y >= sy && y <= (sy + h);
}

bool IsBetween(int p1,int p2, int sp1,int sp2) {
	return (sp1 >= p1 && sp1 <= p2) || (p1 >= sp1 && p2 <= sp2) || (sp2 >= p1 && sp2 <= p2);
}