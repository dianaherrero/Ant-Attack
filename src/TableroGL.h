#pragma once
#include <stdlib.h>
#include "Tablero.h"


class TableroGL
{
protected:
	float width;
	int l, m;								 //size 
	//Tablero* m_tablero;

	//visualization	
	double center_x, center_y, center_z;
	double dist;

	//mouse	
	int xcell_sel, ycell_sel;			//cell selected with mouse
	bool leftButton;

public:
	TableroGL(){
		dist = 50;					//distance of viewpoint from center of the board
		center_z = 0;
	}
	~TableroGL(){}
	void init();
	void Draw();
	void MouseButton(int x, int y,bool down);
	void world2cell(double x, double y, int& cell_x, int& cell_y);
	void SetSize(int li, int mi) { l = li; m = mi; }
	int Getx_elegida() { return xcell_sel; }
	int Gety_elegida() { return ycell_sel; }
	void SetWidth(float w) { width = w; }
};

