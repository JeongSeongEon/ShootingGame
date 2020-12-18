#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void)
{
	x=c_wid/2;
	y=660;
	speed_x=0;
	speed_y=0;
	speed=5;
	live=true;

	up=false;		
	down=false;		
	right=false;		
	left=false;		
	sh=false;


	shot=false;	
	slow=false;
	shot_angle_p=true;

	del=0;
	del_max=0;
	hp=10;
	hit_time=0;

	sub_count=0;
	sub_angle=0;

	bool up,down,right,left,sh;
	bool num[5];
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::die()
{
	live=false;
}
void CPlayer::init()
{
	x=c_wid/2;
	y=660;
	speed_x=0;
	speed_y=0;
	speed=5;

	type=2;
	type_temp=type;
	live=true;

	up=false;		
	down=false;		
	right=false;		
	left=false;		
	shot=false;	
	slow=false;

	sh=false;
	num[0]=0;
	num[1]=0;
	num[2]=0;
	num[3]=0;
	num[4]=0;
	super=false;

	del=player_missile_del_max[type-1]*3;
	del_max=player_missile_del_max[type-1]*3;
	hp=10;
	hit_time=0;
	//type_change(PLAYER_TYPE_MAX);
}
void CPlayer::type_change(int idd)
{
	type=idd;
	//type=PLAYER_TYPE_MAX;
	del=player_missile_del_max[type-1]*3;
	del_max=player_missile_del_max[type-1]*3;
	switch(type)
	{
	case 13:
		shot_angle_max=60;
		shot_angle=0;
		shot_angle_p=true;
		break;
	case 14:
		shot_angle_max=80;
		shot_angle=0;
		shot_angle_p=true;
		break;
	case 15:
	case 16:
		shot_angle=rand_num(360);
		break;
	}
}
void CPlayer::move()
{
	if(up)
	{
		speed_y=-speed;
	}
	if(down)
	{
		speed_y=speed;
	}
	if(right)
	{
		speed_x=speed;
	}
	if(left)
	{
		speed_x=-speed;
	}

	if(slow)
	{
		speed_x=speed_x*0.55;
		speed_y=speed_y*0.55;
	}

	if(abs(speed_x)>0.1)
	{
		x+=speed_x;
		if(x<+5)
		{
			x=+5;
		}
		else if(x>c_wid-5)
		{
			x=c_wid-5;
		} 
		speed_x=speed_x*0.7;
	}
	if(abs(speed_y)>0.1)
	{
		y+=speed_y;
		if(y<5)
		{
			y=5;
		}
		else if(y>c_hei-5)
		{
			y=c_hei-5;
		}
		speed_y=speed_y*0.7;
	}
}
