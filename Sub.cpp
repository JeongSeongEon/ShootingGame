#include "StdAfx.h"
#include "Sub.h"

CSub::CSub(void)
{
	live=false;
	x=0;
	y=0;
	type=0;
	num=0;
	shot_del=0;
}

CSub::~CSub(void)
{
}

void CSub::init(int numm,int id)
{
	live=true;
	type=id;
	num=numm;
	shot_del=sub_missile_del_max[id];

}
void CSub::die()
{
	live=false;
	x=0;
	y=0;
	type=0;
	num=0;
	shot_del=0;
}
void CSub::move(float xxx,float yyy,int count,float a_angle)
{
	float angle=360/count;

	x=xxx+cos(((angle*num)+a_angle)*3.14/180)*30;
	y=yyy+sin(((angle*num)+a_angle)*3.14/180)*30;
}


