#include "StdAfx.h"
#include "Effect.h"

CEffect::CEffect(void)
{
	live=false;
	type=0;
	x=0;
	y=0;
	speed_x=0;
	speed_y=0;
	angle=0;
	distance=0;
	gravity=0;
}

CEffect::~CEffect(void)
{
}
void CEffect::move()
{
	switch(type)
	{
	case 1:
	case 100:
		speed_x=cos(angle*3.14/180)*distance;
		speed_y=sin(angle*3.14/180)*distance;
		x+=speed_x;
		y+=speed_y;
		break;
	}	
	time--;
	if(time < 1)
	{
		init_effect();
	}
}


void CEffect::create_effect(int t,int xx,int yy,float a,float d,int timer)
{
	init_effect();
	live=true;
	type=t;
	x=xx;
	y=yy;
	angle=a;
	distance=d;
	time=timer;
}
void CEffect::init_effect()
{
	live=false;
	type=0;
	x=0;
	y=0;
	speed_x=0;
	speed_y=0;
	angle=0;
	distance=0;
	gravity=0;
}
