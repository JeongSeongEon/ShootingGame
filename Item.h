#pragma once

#include "global.h"

class CItem
{
public:
	CItem(void);
	~CItem(void);

	void create_item(int xx,int yy,int ttt);
	void init_item();
	void move();

	bool live;
	float x,y;
	int timer;
};
