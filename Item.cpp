#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
	init_item();
}

CItem::~CItem(void)
{
}

void CItem::move()
{
	timer--;
	if(timer<1)
	{
		init_item();
	}
}
void CItem::init_item()
{
	live=false;
	x=0;
	y=0;
	timer=0;
}
void CItem::create_item(int xxx,int yyy,int time)
{	
	live=true;
	x=xxx;
	y=yyy;
	timer=time;
}
