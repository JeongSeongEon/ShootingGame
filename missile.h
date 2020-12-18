#pragma once

#include "global.h"

class CMissile
{
public:
	CMissile(void);
	~CMissile(void);

	void move(float xxx,float yyy);
	void create_missile(int t,int xx,int yy,float a,float d,long ty);
	void create_missile(int t,int xx,int yy,float a,float d,long ty,int a_x,int a_y);
	void init_missile();

	bool live,disappear;
	int type,bounce,live_time;
	float x,y,speed_x,speed_y,a_x,a_y,sin_speed;
	float angle,distance,gravity;
	float temp1,temp2,temp3;
	unsigned long type2;
};
