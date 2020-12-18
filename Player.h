#pragma once
#include <math.h>
#include "global.h"

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	void init();
	void die();
	void move();
	void type_change(int idd);

	bool live;
	int hp,hit_time,shot_angle_max;
	float speed_x,speed_y,speed,shot_angle;
	long x,y;

	int type,type_temp;
	int del,del_max;
	
	bool shot,slow,shot_angle_p;
	bool up,down,right,left,sh;
	bool num[5];
	bool super;

	int sub_count;
	float sub_angle;
};
