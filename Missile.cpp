#include "StdAfx.h"
#include "Missile.h"

CMissile::CMissile(void)
{
	live=false;
	type=0;
	x=0;
	y=0;
	live_time=0;
	speed_x=0;
	speed_y=0;
	angle=0;
	distance=0;
	gravity=0;
	type2=0x0;///////////  1  좌우  벽튕  중력  유도(스무스) 유도 속도sin    각도+- 직선
			  ///////////  2                                      점점가속도
	init_missile();
	disappear=false;//아이탬 먹고 사라지는지
}

CMissile::~CMissile(void)
{
}

void CMissile::move(float xxx2,float yyy2)
{
	float a_angle=0;
	float p_angle=6;
	int type_id=0;

	float t_x,t_y;
	
	if(type2 & 0x10000)
	{
		switch(type)
		{
		case 1011:
			t_x=((speed_x-x)*0.32);
			t_y=((speed_y-y)*0.32);
			break;
		default:
			t_x=((speed_x-x)*0.08);
			t_y=((speed_y-y)*0.08);
			break;
		}
		
		if(abs(speed_x-x)<1 && abs(speed_y-y)<1)
		{
			angle+=33;
		}
		else
		{
			angle=get_angle(x,y,x+((speed_x-x)*0.08),y+((speed_y-y)*0.08));
		}

		
		x+=t_x;
		y+=t_y;
	}
	else
	{
		//if((type<100 && true) || (type2 & 0x1000))
		if((type2 & 0x1000))
		{
			a_angle=get_angle(x,y,xxx2,yyy2);

			if(abs(angle-a_angle)<p_angle)
			{
				angle=a_angle;
			}
			else
			{			
				
				angle+=360;
				a_angle+=360;

				while(angle>360)
				{
					angle-=360;
				}
				while(a_angle>360)
				{
					a_angle-=360;
				}

				if(abs(angle-a_angle)<180)
				{
					if(angle<a_angle)
					{
						angle+=p_angle;
					}
					else
					{
						angle-=p_angle;
					}
				}
				else
				{
					if(angle<a_angle)
					{
						angle-=p_angle;
					}
					else
					{
						angle+=p_angle;
					}
				}
			}
		}
		if((type2 & 0xF00)>>8 == 1)
		{
			temp1++;
			sin_speed=3*(sin(temp1/10)+1);
			distance=sin_speed;
		}
		
		if((type2 & 0xF00)>>8 == 2)
		{
			if(distance<22)
			{
				distance+=0.3;
			}
		}
		if((type2 & 0xF0)>0)
		{
			type_id = (type2 & 0xF0)>>4;
			switch(type_id)
			{
			case 1:
				if(temp1<temp2)
				{
					temp1+=1;
				}
				angle=temp3+temp1;
				break;
			case 2:				
				if(temp1>temp2*-1)
				{
					temp1-=1;
				}
				angle=temp3+temp1;
				break;
			}
		} 

		speed_x=cos(angle*3.14/180)*distance;
		speed_y=sin(angle*3.14/180)*distance;

		x+=speed_x;
		y+=speed_y;
		
		if(type2 & 0x100000)
		{
			gravity=G+A+gravity;
			y+=gravity;
			temp1=get_angle(x-speed_x,y-speed_y,x,y+gravity);
		}
		if(type2 & 0x10000000)
		{
			temp1++;
			temp2=(100*(sin(temp1/2.5)))-10;
			x-=temp3;
			temp3=temp2;
			x+=temp2;
		}
		if(type2 & 0x1000000)
		{
			if(x<0 || x>c_wid)
			{
				angle=angle*-1+180;
				bounce++;
				if(bounce>5)
				{
					init_missile();
				}
			}
		}
	}
	
	switch(type)
	{
	case 4:
		if(x<0 || x>c_wid)
		{
			angle=angle*-1+180;
			bounce++;
			if(bounce>9)
			{
				init_missile();
			}
		}
		break;
	case 151:
		if(temp1<1)
		{
			if(distance<5)
			{
				distance+=0.2;
			}
		}
		else
		{
			temp1--;
		}
		break;
	}


	/*
	switch(type)
	{
	case 1:
		gravity=G+A+gravity;
		speed_x=cos(angle*3.14/180)*distance;
		speed_y=sin(angle*3.14/180)*distance;
		x+=speed_x;
		y+=speed_y;
		//y+=speed_y+gravity;
		break;
	case 101:
		if(temp1<temp2)
		{
			temp1+=1;
		}
		speed_x=cos((angle+temp1)*3.14/180)*distance;
		speed_y=sin((angle+temp1)*3.14/180)*distance;
		x+=speed_x;
		y+=speed_y;
		break;
	case 102:
		if(temp1<temp2)
		{
			temp1+=1;
		}
		speed_x=cos((angle-temp1)*3.14/180)*distance;
		speed_y=sin((angle-temp1)*3.14/180)*distance;
		
		x+=speed_x;
		y+=speed_y;
		break;
	case 202:
	case 201:
		temp1++;
		temp2=3*(sin(temp1/10)+1);
		speed_x=cos(angle*3.14/180)*(temp2);
		speed_y=sin(angle*3.14/180)*(temp2);
		x+=speed_x;
		y+=speed_y;
		break;
	case 1001:
	case 1002:
		if(temp1>4)
		{
		}
		break;
	}
	*/
	if(x<-300 || x>c_wid+300 || y<-300 || y>c_hei+300)
	{
		init_missile();
	}
}

void CMissile::create_missile(int t,int xx,int yy,float a,float d,long ty)
{
	create_missile(t,xx,yy,a,d,ty,0,0);
}
void CMissile::create_missile(int t,int xx,int yy,float a,float d,long ty,int aa_x,int aa_y)
{
	init_missile();
	live=true;
	type=t;
	x=xx;
	y=yy;
	angle=a;
	distance=d;
	a_x=aa_x;
	a_y=aa_y;
	type2=ty;
	sin_speed=1;
	live_time=0;

	temp3=0;
	temp2=0;
	temp1=0;

	switch(type)
	{
	case 2:	
	case 3:	
		temp2=13;
		temp1=temp2;
		break;
	case 101:
	case 102:		
		temp1=0;
		temp2=100;
		temp3=angle;
		break;
	case 150:
		speed_x=a_x;
		speed_y=a_y;
		if(angle)
		{
			temp1=70+(distance*3);
		}
		else
		{
			temp1=80+(distance*5);
		}
		break;
	case 151:
		temp1=100;
		break;
	case 156:
	case 157:
		temp1=0;
		temp2=100;
		temp3=angle;
		break;
	case 158:
		speed_x=a_x;
		speed_y=a_y;
		temp1=90;//시간 
		temp2=1+(float)rand_num(300)/100.0;//속도
		distance=temp2;
		temp3=0;//
		break;
	case 201:
	case 202:
		temp1=0;
		temp2=100;
		temp3=0;
		break;
	case 1001:
	case 1002:
	case 1003:
		speed_x=a_x;
		speed_y=a_y;
		temp1=70;
		temp2=0;
		temp3=0;
		break;
	case 1004:
		temp1=13;
		break;
	case 1005:
		temp1=6;
		break;
	case 1006:
		speed_x=a_x;
		speed_y=a_y;
		temp1=70;
		temp2=90;
		break;
	case 1007:
		speed_x=a_x;
		speed_y=a_y;
		temp1=70;
		temp2=-90;
		break;
	case 1008:
		speed_x=a_x;
		speed_y=a_y;
		temp1=40+rand_num(80);//시간
		temp2=0;//각도
		temp3=21;//시간2
		break;
	case 1009:
		speed_x=a_x;
		speed_y=a_y;
		temp1=40;//시간
		temp2=0;//각도
		temp3=0;//시간2
		break;
	case 1010:
		speed_x=a_x;
		speed_y=a_y;
		temp1=15;//시간
		temp2=0;//각도
		temp3=1;//도는 방향
		break;
	case 1011:
		speed_x=a_x;
		speed_y=a_y;
		temp1=40;
		temp2=0;
		temp3=0;
		break;
	}

	if(type<100)
	{
		disappear=false;
	}
	else if(type==1006 || type==1007 || type==1008 || type==1009 || type==1010 || type==1011)
	{
		disappear=false;
	}
	else 
	{
		disappear=true;
	}
}
void CMissile::init_missile()
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
	type2=0x0;
	live_time=0;
	bounce=0;
}
