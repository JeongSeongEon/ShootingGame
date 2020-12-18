#pragma once
#include <math.h>
#include "global.h"

class CSub
{
public:
	CSub(void);
	~CSub(void);

	void init(int num,int id);
	void die();
	void move(float xxx,float yyy,int count,float a_angle);

	bool live;
	long x,y;
	int type,num;
	int shot_del;
};
