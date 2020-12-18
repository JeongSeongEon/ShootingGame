#include "StdAfx.h"
#include "global.h"



float rand_num(int num)
{
	return rand()%num; 
}

float get_angle(float x1,float y1,float x2,float y2)
{
	return atan2((y2-y1),(x2-x1))*180/3.14;
}
float get_distance(float x1,float y1,float x2,float y2)
{
	return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}