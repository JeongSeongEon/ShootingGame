#pragma once

#include "global.h"
#include "math.h"

class CBoss
{
public:
	CBoss(void);
	~CBoss(void);

	void init(int ll);
	void die();
	void move();

	bool live;
	float hp,hp_max,angle,distance;

	float x,y,xx,yy,speed_x,speed_y,speed;
	int type,hit_time;

	int del1;
	int del2;
	int shot_num;

	int shot_count;
	int lv;
	bool shot,angry;
};
