#pragma once
#include "global.h"

class CEffect
{
public:
	CEffect(void);
	~CEffect(void);

	void move();
	void create_effect(int t,int xx,int yy,float a,float d,int timer);
	void init_effect();

	bool live;
	int type,time;
	float x,y,speed_x,speed_y;
	float angle,distance,gravity;
};
