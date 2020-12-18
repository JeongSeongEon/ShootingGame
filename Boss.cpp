#include "StdAfx.h"
#include "Boss.h"

CBoss::CBoss(void)
{
	init(0);
}

CBoss::~CBoss(void)
{
}

void CBoss::move()
{
	angle=get_angle(x,y,xx,yy);
	
	if(get_distance(x,y,xx,yy)>distance)
	{
		speed_x=cos(angle*3.14/180)*distance;
		speed_y=sin(angle*3.14/180)*distance;
		x+=speed_x;
		y+=speed_y;
	}
	else
	{
		x=xx;
		y=yy;
		xx=(c_wid*(1.0/3.0))/2+rand_num(c_wid*(2.0/3.0));
		yy=50+rand_num(300);
	}	
}
void CBoss::init(int ll)
{
	lv=ll;
	live=true;

	hp=boss_hp[boss_path[lv]];
	hp_max=boss_hp[boss_path[lv]];

	//hp=10;
	//hp_max=10;

	del1=boss_del1[boss_path[lv]];
	switch(boss_path[lv])
	{
	case 9:
	case 10:
		del2=30;
		break;
	default:
		del2=100;
		break;
	}
	shot_num=0;

	speed_x=0;
	speed_y=0;
	speed=0;

	x=c_wid/2;
	y=-50;

	xx=(c_wid*(2.0/3.0))/2+rand_num(c_wid*(2.0/3.0));
	yy=50+rand_num(300);

	type=rand_num(2)+1;
	
	hit_time=0;
	angle=rand_num(360);
	distance=3;
	shot_count=0;
	shot=false;
	angry=false;
}
void CBoss::die()
{
	
	lv=1;
	live=false;

	hp=boss_hp[boss_path[lv]];
	hp_max=boss_hp[boss_path[lv]];

	del1=boss_del1[boss_path[lv]];
	del2=100;
	shot_num=0;

	speed_x=0;
	speed_y=0;
	speed=0;

	x=c_wid/2;
	y=-50;

	xx=(c_wid*(2.0/3.0))/2+rand_num(c_wid*(2.0/3.0));
	yy=50+rand_num(300);

	type=rand_num(2)+1;
	
	hit_time=0;
	angle=rand_num(360);
	distance=3;
	shot_count=0;
	shot=false;
	angry=false;
}