// g_1.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "g_60.h"

#include <stdlib.h>

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.


HBITMAP hBit;
static RECT crt;
SYSTEMTIME st;

XFORM XForm={1,0,0,1,0,0};

CPlayer *player;
CMissile *missile[MISSILE_MAX];
CEffect *effect[EFFECT_MAX];
CItem *item[ITEM_MAX];
CBoss *boss;
CSub *sub[SUB_MAX];

bool test = false;

static TCHAR log_text[255];

long time_1;
long time_2;
long time_temp;

int i;

int state;
int stage_select;
int die_time;
int item_time;
int item_rand;

int ending_scroll=0;
bool scroll_speed=false;
bool push_q=false;

void game_init();

void game_2();
void draw_0();
void boss_hit(int ii);
void boss_missile_create(int id);
void player_hit(int ii);
void create_item(int xxx,int yyy,int ttt);
void change_type(int idd);

void create_missile(int ttt,int temp1,int temp2);
void create_missile(int ttt,int temp1,int temp2,float temp3);

void ending();

void draw_player();
void draw_boss();

void angle_start();
void angle_end();


unsigned seed;

HDC hdc,hMemDC;
// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

HBITMAP OldBit;
HPEN hPen,OldPen,boss_Pen;
HBRUSH hBrush,OldBrush,boss_Brush;


HBITMAP loadBitmap;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_G_60, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_G_60));

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
void create_item(int xxx,int yyy,int ttt)
{
	int ii;
	for(ii=0;ii<ITEM_MAX;ii++)
	{
		if(!item[ii]->live)
		{
			item[ii]->create_item(xxx,yyy,ttt);
			ii=ITEM_MAX+1;
		}
	}
}
/////create_missile
void create_missile(int ttt,int temp1,int temp2)
{
	create_missile(ttt,temp1,temp2,0);
}
void create_missile(int ttt,int temp1,int temp2,float temp3)
{
	int ii=0;
	int count=1;
	int xxx,yyy;
	float temp_0;
	boss->shot_count=0;

	if(ttt<90)
	{
		count=player_missile_num_max[ttt-1];
	}
	else if(ttt<100)
	{
		count=sub_missile_num_max[ttt-90];
		xxx=temp1;
		yyy=temp2;
	}
	else
	{
		switch(ttt)
		{
		case 101:
		case 102:
			count=72;
			xxx=temp1;
			yyy=temp2;
			break;
		case 130:
			if(boss->angry)
			{
				count=36;
			}
			else
			{
				count=36;
			}
			xxx=temp1;
			yyy=temp2;
			break;
		case 141:
		case 142:	
			if(boss->angry)
			{
				count=boss_missile_mum_same_angry[boss_path[boss->lv]];
			}
			else
			{
				count=boss_missile_mum_same[boss_path[boss->lv]];
			}
			temp_0=count;
			break;
		case 151:
			if(boss->angry)
			{
				count=3+rand_num(3);
			}
			else
			{
				count=2+rand_num(2);
			}
			xxx=temp1;
			yyy=temp2;
			break;
		case 152:
			temp_0=10+rand_num(70);
			count=2;
			xxx=temp1;
			yyy=temp2;
			break;
		case 153:
		case 154:
			count=3;
			xxx=temp1;
			yyy=temp2;
			break;
		case 155:
			count=3;
			xxx=temp1;
			yyy=temp2;			
			break;
		case 156:
		case 157:
			count=36;
			xxx=temp1;
			yyy=temp2;			
			break;
		case 159:
			count=16;
			xxx=temp1;
			yyy=temp2;		
			break;
		case 160:
			count=6;//3������ 20��
			xxx=temp1;
			yyy=temp2;	
			break;
		case 161:			
			count=10;//����1�� ���׶��
			xxx=temp1;
			yyy=temp2;	
			break;
		default:
			if(boss->angry)
			{
				count=boss_missile_mum_same_angry[boss_path[boss->lv]];
			}
			else
			{
				count=boss_missile_mum_same[boss_path[boss->lv]];
			}
			break;
		}
	}

	for(ii=0;ii<MISSILE_MAX;ii++)
	{
		if(!missile[ii]->live)
		{
			switch(ttt)
			{
			case 1:
				missile[ii]->create_missile(1,player->x,player->y-3,270-15+((count-1)*5),20,0x1);
				break;
			case 2:
				missile[ii]->create_missile(1,player->x,player->y-3,270-5+((count-1)*5),20,0x1);
				break;
			case 3:
				missile[ii]->create_missile(1,player->x,player->y-3,270,20,0x1);
				break;
			case 4:
				missile[ii]->create_missile(1,player->x-7+((count-1)*14),player->y-3,270,20,0x1);
				break;
			case 5:
				missile[ii]->create_missile(1,player->x-8+((count-1)*8),player->y-3,270,20,0x1);
				break;
			case 6:
			case 7:
				missile[ii]->create_missile(1,player->x,player->y-3,255+rand_num(31),10+rand_num(10),0x1);
				break;
			case 8:
			case 9:
				missile[ii]->create_missile(1,player->x,player->y-3,230+rand_num(81),10+rand_num(10),0x1);
				break;
			case 10:
				missile[ii]->create_missile(1,player->x,player->y-3,258+((count-1)*8),20,0x1);
				break;
			case 11:
			case 12:
				missile[ii]->create_missile(1,player->x,player->y-3,270-24+((count-1)*8),20,0x1);
				break;
			case 13:
				missile[ii]->create_missile(1,player->x,player->y-3,240+player->shot_angle,15,0x1);
				if(player->shot_angle_p)
				{
					player->shot_angle+=3;
					if(player->shot_angle>=player->shot_angle_max)
					{
						player->shot_angle_p=false;
					}
				}
				else
				{
					player->shot_angle-=3;
					if(player->shot_angle<=0)
					{
						player->shot_angle_p=true;
					}
				}
				break;
			case 14:
				if(count==2)
				{
					missile[ii]->create_missile(1,player->x,player->y-3,310-player->shot_angle,15,0x1);
				}
				else
				{
					missile[ii]->create_missile(1,player->x,player->y-3,230+player->shot_angle,15,0x1);
				}
				if(player->shot_angle_p)
				{
					player->shot_angle+=3;
					if(player->shot_angle>=player->shot_angle_max)
					{
						player->shot_angle_p=false;
					}
				}
				else
				{
					player->shot_angle-=3;
					if(player->shot_angle<=0)
					{
						player->shot_angle_p=true;
					}
				}
				break;
			case 15:
				missile[ii]->create_missile(1,player->x,player->y-3,(60*(count-1))+player->shot_angle,10,0x1);
				player->shot_angle+=0.7;
				if(player->shot_angle>360)
				{
					player->shot_angle=(int)player->shot_angle%360;
				}
				break;
			case 16:
				missile[ii]->create_missile(1,player->x,player->y-3,(60*(count-1))-player->shot_angle,10,0x1);
				player->shot_angle+=0.7;				
				if(player->shot_angle>360)
				{
					player->shot_angle=(int)player->shot_angle%360;
				}
				break;
			case 17:
				missile[ii]->create_missile(1,player->x,player->y-3,270,5,0x1001);
				break;
			case 18:
				missile[ii]->create_missile(1,player->x,player->y-3,270-90+((count-1)*180),5,0x1001);
				break;
			case 19:
				missile[ii]->create_missile(2+(count-1),temp1,temp2,270-50+((count-1)*100),6,0x1);
				break;
			case 20:
				missile[ii]->create_missile(1,temp1,temp2,320,6,0x1);
				break;
			case 21:
				missile[ii]->create_missile(1,temp1,temp2,220,6,0x1);
				break;
			case 22:
			case 23:
				missile[ii]->create_missile(1,player->x,player->y-3,270+((count-1)*7),20,0x1);
				break;
			case 24:
			case 25:
				missile[ii]->create_missile(1,player->x,player->y-3,270-((count-1)*7),20,0x1);
				break;
			case 26:
				missile[ii]->create_missile(4,player->x,player->y-3,190+((count-1)*160),20,0x1);
				break;
			case 27:
				missile[ii]->create_missile(1,player->x,player->y-3,(get_angle(player->x,player->y,boss->x,boss->y)),11,0x1);
				break;
			case 28:
				missile[ii]->create_missile(1,player->x-10+((count-1)*20),player->y-3,(get_angle(player->x,player->y,boss->x,boss->y)),11,0x1);
				break;
			case 29:
				missile[ii]->create_missile(1,player->x-10+((count-1)*20),player->y-3,270,15,0x10000000);
				break;
			case 30://////�������ӵ�
				missile[ii]->create_missile(1,player->x-12+((count-1)*8),player->y-3,270,0,0x200);
				break;
			case 31:
				missile[ii]->create_missile(1,player->x,player->y-3,270,20,0x1);
				break;
			case 32:
				switch(count)
				{
				case 1:
					missile[ii]->create_missile(1,player->x-20,player->y-4,270,18,0x1);
					break;
				case 2:
					missile[ii]->create_missile(1,player->x-10,player->y-8-4,270,18,0x1);
					break;
				case 3:
					missile[ii]->create_missile(1,player->x,player->y-16-4,270,18,0x1);
					break;
				case 4:
					missile[ii]->create_missile(1,player->x+10,player->y-8-4,270,18,0x1);
					break;
				case 5:
					missile[ii]->create_missile(1,player->x+20,player->y-4,270,18,0x1);
					break;
				}
				break;

			case 90:
				missile[ii]->create_missile(1,xxx,yyy-2,270,20,0x1);
				break;
			case 91:
				missile[ii]->create_missile(1,xxx-4+(count*8),yyy-2,270,20,0x1);
				break;
			case 92:
				missile[ii]->create_missile(1,xxx,yyy-3,270,5,0x1001);
				break;
			case 93:
				missile[ii]->create_missile(1,xxx,yyy-3,270-90+((count-1)*180),5,0x1001);
				break;
			case 94:
				missile[ii]->create_missile(1,xxx,yyy-3,255+rand_num(31),10+rand_num(10),0x1);
				break;
			case 95:
				missile[ii]->create_missile(1,xxx,yyy-3,255+rand_num(31),10+rand_num(10),0x1);
				break;
			case 96:
				break;
			case 97:
				break;
			case 98:
				break;
			case 99:
				break;




			case 101:////������ ���ư��°�
				missile[ii]->create_missile(ttt,xxx,yyy,count*5,4.5,0x11);
				break;
			case 102:
				missile[ii]->create_missile(ttt,xxx,yyy,count*5,4.5,0x21);
				break;

			case 110: //��ź
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(get_angle(boss->x,boss->y,player->x,player->y))-50+(50*(boss->shot_num%3))+(rand_num(210)/10.0-10),2+(rand_num(600)/100.0),0x1);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(get_angle(boss->x,boss->y,player->x,player->y))-50+(50*(boss->shot_num%3))+(rand_num(250)/10.0-12),2+(rand_num(600)/100.0),0x1);
				}
				boss->shot_num--;
				break;
			case 120: 
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,boss->shot_num%36*10+((int)boss->shot_num/120)*3.3,6,0x1);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,boss->shot_num%36*10+((int)boss->shot_num/180)*4,7,0x1);
				}
				boss->shot_num--;
				break;
			case 130:		
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,xxx,yyy,count*10-3+(rand_num(600)/100.0),3+(rand_num(700)/100.0),0x100000);
				}
				else
				{
					missile[ii]->create_missile(ttt,xxx,yyy,count*10-3+(rand_num(600)/100.0),3+(rand_num(700)/100.0),0x100000);
				}
				break;
			case 141:			
				if(count<=(temp_0/2))
				{					
					missile[ii]->create_missile(ttt,boss->x,boss->y,190+count*5,5,0x1000000);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,10+(count-10)*5,5,0x1000000);
				}
				boss->shot_num--;
				break;
			case 142:						
				if(count<=temp_0/2)
				{					
					missile[ii]->create_missile(ttt,boss->x,boss->y,350-count*5,5,0x1000000);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,170-(count-10)*5,5,0x1000000);
				}
				boss->shot_num--;
				break;
			case 150:					
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,0,boss->shot_num,0x10000,boss->x+cos((boss->shot_num*10)*3.14/180)*150,boss->y+sin((boss->shot_num*10)*3.14/180)*150);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,0,boss->shot_num,0x10000,boss->x+cos((boss->shot_num*20)*3.14/180)*150,boss->y+sin((boss->shot_num*20)*3.14/180)*150);
				}
				boss->shot_num--;
				break;
			case 151:
				temp_0=rand_num(35900)/100.0;
				missile[ii]->create_missile(151,xxx+cos(temp_0*3.14/180)*10,yyy+sin(temp_0*3.14/180)*10,temp_0,0,0x1);
				break;
			case 152:
				if(count==2)
				{
					missile[ii]->create_missile(152,xxx,yyy,temp3-105,4,0x1);
				}
				else
				{
					missile[ii]->create_missile(152,xxx,yyy,temp3+105,4,0x1);
				}
				
				break;
			case 153:				
				missile[ii]->create_missile(ttt,xxx,yyy,(120*count)+(temp3)*3,4,0x1);				
				break;
			case 154:				
				missile[ii]->create_missile(ttt,xxx,yyy,(120*count)-(temp3)*3,4,0x1);			
				break;
			case 155:
				if(count==2)
				{
					missile[ii]->create_missile(ttt,xxx,yyy,temp3-60+(count*30),7.5,0x1);
				}
				else
				{
					missile[ii]->create_missile(ttt,xxx,yyy,temp3-60+(count*30),4,0x1);
				}
				break;
			case 156:
				missile[ii]->create_missile(ttt,xxx,yyy,(count*10),4,0x11);
				break;
			case 157:
				missile[ii]->create_missile(ttt,xxx,yyy,(count*10),4,0x21);
				break;
			case 158:
				if(player->y>100)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,90,5,0x10000,count*12-7,100);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,90,5,0x10000,count*12-7,player->y-80);
				}
				boss->shot_num--;
				break;
			case 159:
				missile[ii]->create_missile(ttt,xxx,yyy,((360.0/16.0)*count)+(temp3)*3,4,0x1);
				break;
			case 160:
				missile[ii]->create_missile(160,xxx,yyy,get_angle(xxx,yyy,player->x,player->y)+(60*count),5,0x1);
				break;
			case 161:
				missile[ii]->create_missile(161,xxx,yyy,(36*count),2.7,0x1);
				break;

			case 201://////3���� sin��
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(120*boss->shot_num)+(boss->shot_num/3)*3.1,5,0x101);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(120*boss->shot_num)+(boss->shot_num/3)*4.7,5,0x101);
				}
				boss->shot_num--;
				break;
			case 202:
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(120*boss->shot_num)-(boss->shot_num/3)*3.1,5,0x101);
				} 
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(120*boss->shot_num)-(boss->shot_num/3)*4.7,5,0x101);
				}
				boss->shot_num--;
				break;

			case 1001://///������
			case 1002:
				missile[ii]->create_missile(ttt,boss->x,boss->y,0,1,0x10000,(c_wid*(2.0/3.0))/2+rand_num(c_wid*(2.0/3.0)),rand_num(300));
				boss->shot_num--;
				break;
			case 1003://///������
				missile[ii]->create_missile(ttt,boss->x,boss->y,0,1,0x10000,player->x+(rand_num(401)-200),player->y-380-(rand_num(170)));
				boss->shot_num--;
				break;
			case 1004:
				if(boss->angry)
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(get_angle(boss->x,boss->y,player->x,player->y))-100+(40*(boss->shot_num)),5,0x1);
				}
				else
				{
					missile[ii]->create_missile(ttt,boss->x,boss->y,(get_angle(boss->x,boss->y,player->x,player->y))-100+(50*(boss->shot_num)),5,0x1);
				}
				boss->shot_num--;
				break;
			case 1005:
				missile[ii]->create_missile(ttt,boss->x,boss->y,temp1+(get_angle(boss->x,boss->y,player->x,player->y)+(72*count)),4.5,0x1);
				boss->shot_num--;
				break;
			case 1006:
				if(count==2)
				{
					missile[ii]->create_missile(1006,boss->x,boss->y,0,1,0x10000,292-100,250);
				}
				else if(count==1)
				{
					missile[ii]->create_missile(1007,boss->x,boss->y,0,1,0x10000,292+100,250);
				}
				boss->shot_num--;
				break;
			case 1008:///��� ��
				switch(count)
				{
				case 1:
					missile[ii]->create_missile(1008,boss->x,boss->y,0,1,0x10000,50,692);
					break;
				case 2:
					missile[ii]->create_missile(1008,boss->x,boss->y,0,1,0x10000,50,100);
					break;
				case 3:
					missile[ii]->create_missile(1008,boss->x,boss->y,0,1,0x10000,534,692);
					break;
				case 4:
					missile[ii]->create_missile(1008,boss->x,boss->y,0,1,0x10000,534,100);
					break;
				case 5:
					missile[ii]->create_missile(1008,boss->x,boss->y,0,1,0x10000,292,296);
					break;
				}
				boss->shot_num--;
				break;
			case 1009:
				switch(count)
				{
				case 1:
					missile[ii]->create_missile(1009,boss->x,boss->y,0,1,0x10000,50,692);
					break;
				case 2:
					missile[ii]->create_missile(1009,boss->x,boss->y,0,1,0x10000,50,100);
					break;
				case 3:
					missile[ii]->create_missile(1009,boss->x,boss->y,0,1,0x10000,534,692);
					break;
				case 4:
					missile[ii]->create_missile(1009,boss->x,boss->y,0,1,0x10000,534,100);
					break;
				}
				boss->shot_num--;
				break;
			case 1010:
				missile[ii]->create_missile(1010,boss->x,boss->y,0,1,0x10000,292,296);
				boss->shot_num--;
				break;
			case 1011:///
				missile[ii]->create_missile(1011,boss->x,boss->y,0,1,0x10000,boss->x,boss->y);
				missile[ii]->live_time=72*boss->shot_num;
				boss->shot_num--;
				break;
			}
			count--;
			if(count<1)
			{
				ii=MISSILE_MAX+1;
			}
		}
	}
}
void create_effect(int ttt,int xx,int yy)
{
	int count=1;
	int ii;
	switch(ttt)
	{
	case 1:
		count=20;
		break;
	case 2:
		count=5;
		break;
	case 100:
		count=20;
		break;
	}
	for(ii=0;ii<EFFECT_MAX;ii++)
	{
		if(!effect[ii]->live)
		{
			switch(ttt)
			{
			case 1:
				effect[ii]->create_effect(1,xx,yy,count*18+(rand_num(30)-15),2+(rand_num(200)/100.0),15);
				break;
			case 2:
				effect[ii]->create_effect(1,xx,yy,count*72+(rand_num(8)-4),2+(rand_num(200)/100.0),15);
				break;
			case 100:
				effect[ii]->create_effect(100,xx,yy,count*18+(rand_num(30)-15),2+(rand_num(200)/100.0),15);
				break;
			}
			count--;
			if(count<1)
			{
				ii=EFFECT_MAX+1;
			}
		}
	}
}

void OnTimer(HWND hWnd)
{

	int i;

	GetClientRect(hWnd,&crt);
	hdc=GetDC(hWnd);

	if(hBit==NULL)
	{
		hBit=CreateCompatibleBitmap(hdc,crt.right,crt.bottom);
	}
	hMemDC=CreateCompatibleDC(hdc);
	OldBit=(HBITMAP)SelectObject(hMemDC,hBit);

	FillRect(hMemDC,&crt,GetSysColorBrush(COLOR_WINDOW));
	
	///////game
	switch(state)
	{
	case 99:			
		break;
	case 0://����ȭ��
		if(player->down)
		{			
			stage_select++;
			if(stage_select>(BOSS_TYPE_MAX))
			{
				stage_select=0;
			}
			player->down=false;
		}
		else if(player->up)
		{			
			stage_select--;
			if(stage_select<0)
			{
				stage_select=BOSS_TYPE_MAX;
			}
			player->up=false;
		}
		break;
	case 1://�����ʱ�ȭ
		game_init();
		state=2;
		die_time=0;
		item_time=100+rand_num(110);
		break;
	case 2://����
		game_2();
		break;
	case 3:///���� ��
		break;
	case 4:
		break;
	}
	



	draw_player();

	////////draw
	switch(state) 
	{
	case 0://����ȭ��
		if(push_q)
		{			
			wsprintf(log_text,TEXT("���Ӱ����ϴ� ����� ����ͼ� �������"),crt.right,crt.bottom);
			TextOut(hMemDC,50,120,log_text,lstrlen(log_text));		
			wsprintf(log_text,TEXT("������� ���� ����Ŷ� ������ �͵� ���� ������ ���׵� ���� ����"));
			TextOut(hMemDC,50,170,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("�׷��� �׳� �ð� ����� ������ ����ֱ� �ٶ�"));
			TextOut(hMemDC,50,220,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("�� %d���� ���������� �����Ǿ� �ְ� "),BOSS_TYPE_MAX);
			TextOut(hMemDC,50,270,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("�� %d���� �̻��� ������ ����"),PLAYER_TYPE_MAX);
			TextOut(hMemDC,50,320,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("�������� ������ �������� ȿ������ ��Ÿ�� "));
			TextOut(hMemDC,50,370,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("������ ���� ������??"));
			TextOut(hMemDC,50,470,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("-2016.07.08-"));
			TextOut(hMemDC,50,570,log_text,lstrlen(log_text));
		}
		else
		{
			wsprintf(log_text,TEXT("���ӽ����� S��ư"),crt.right,crt.bottom);
			TextOut(hMemDC,200,60,log_text,lstrlen(log_text));		
			wsprintf(log_text,TEXT("�߽�:X    �ӵ� ����:Z"));
			TextOut(hMemDC,200,100,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("�Ͻ����� SPACE"));
			TextOut(hMemDC,200,140,log_text,lstrlen(log_text));
			wsprintf(log_text,TEXT("���� Q"));
			TextOut(hMemDC,200,180,log_text,lstrlen(log_text));

			for(i=0;i<BOSS_TYPE_MAX+1;i++)
			{				
				if(i==0)
				{
					wsprintf(log_text,TEXT("stage���"));
				}
				else
				{
					wsprintf(log_text,TEXT("stage%d"),i);
				}
				TextOut(hMemDC,180,230+(i*20),log_text,lstrlen(log_text));
				if(stage_select==i)
				{	
					wsprintf(log_text,TEXT(">>"));
					TextOut(hMemDC,160,230+(i*20),log_text,lstrlen(log_text));
				}
			}
		}
		break;
	case 1:
		break;
	case 2:
		draw_0();		
		//wsprintf(log_text,TEXT("id %d  top"),(int)(get_angle(boss->x,boss->y,player->x,player->y)*180/3.14));
		//TextOut(hMemDC,100,100,log_text,lstrlen(log_text));
		break;
	case 3:
		wsprintf(log_text,TEXT("%d / %d ������������ ����"),boss->lv+1,BOSS_TYPE_MAX);
		TextOut(hMemDC,200,220,log_text,lstrlen(log_text));	
		wsprintf(log_text,TEXT("���ӿ��� �����:S"));
		TextOut(hMemDC,200,270,log_text,lstrlen(log_text));	
		break;
	case 4:
		draw_0();
		wsprintf(log_text,TEXT("�Ͻ�����"));
		TextOut(hMemDC,200,300,log_text,lstrlen(log_text));
		TextOut(hMemDC,400,300,log_text,lstrlen(log_text));
		break;
	case 999:
		ending();
		break;
	}


	SelectObject(hMemDC,OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd,hdc);
	
	InvalidateRect(hWnd,NULL,FALSE);

	//wsprintf(log_text,TEXT("%d"),gametime);
	//TextOut(hMemDC,10,10,log_text,lstrlen(log_text));

}


//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
//  ����:
//
//    Windows 95���� �߰��� 'RegisterClassEx' �Լ����� ����
//    �ش� �ڵ尡 Win32 �ý��۰� ȣȯ�ǵ���
//    �Ϸ��� ��쿡�� �� �Լ��� ����մϴ�. �� �Լ��� ȣ���ؾ�
//    �ش� ���� ���α׷��� �����
//    '�ùٸ� ������' ���� �������� ������ �� �ֽ��ϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_G_60));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_G_60);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, CLIENTWIDTH, CLIENTHEIGHT, NULL, NULL, hInstance, NULL);

   srand(seed);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		GetSystemTime(&st);
		time_1=st.wMilliseconds;
		time_2=st.wMilliseconds;
		time_temp=0;
		player = new CPlayer();
		player->init();
		for(i=0;i<MISSILE_MAX;i++)
		{
			missile[i]=new CMissile();
		}
		for(i=0;i<EFFECT_MAX;i++)
		{
			effect[i]=new CEffect();
		}
		for(i=0;i<ITEM_MAX;i++)
		{
			item[i]=new CItem();
		}
		boss = new CBoss();
		boss->init(0);

		for(i=0;i<SUB_MAX;i++)
		{
			sub[i]=new CSub();
		}


		SetTimer(hWnd,1,25,NULL);

		stage_select=0;
		state=0;

		
		boss_Pen=CreatePen(PS_INSIDEFRAME,2,RGB(0,0,255));
		boss_Brush=CreateSolidBrush(RGB(0,255,0));

		hPen=CreatePen(PS_INSIDEFRAME,2,RGB(255,0,0));
		hBrush=CreateSolidBrush(RGB(0,0,255));


		return 0;
	case WM_TIMER:
		GetSystemTime(&st);
		time_1=st.wMilliseconds;
		time_temp=time_2-time_1;
		time_2=st.wMilliseconds;
		OnTimer(hWnd);
		break;
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_RIGHT:
				player->right=true;		
				break;
			case VK_LEFT:
				player->left=true;		
				break;
			case VK_UP:
				player->up=true;	
				break;
			case VK_DOWN:
				player->down=true;		
				break;
			case VK_SHIFT:
				if(state==2)
				{
					player->sh=true;
				}
				break;
			case '1':
				if(state==2)
				{
					player->num[0]=true;
					if(player->sh && player->num[0])
					{
						player->super=true;
						player->num[0]=false;
						player->sh=false;
					}
				}
			case '2':
				if(state==2)
				{
					player->num[1]=true;
					if(player->sh && player->num[1])
					{
						player->super=false;
						player->num[1]=false;
						player->sh=false;
					}
				}
			case '3':
				if(state==2)
				{
					player->num[2]=true;
					if(player->sh && player->num[2])
					{
						player->hp++;
						player->num[2]=false;
						player->sh=false;
					}
				}
			case '4':
				if(state==2)
				{
					player->num[3]=true;
					if(player->sh && player->num[3])
					{
						for(int ii2=0;ii2<MISSILE_MAX;ii2++)
						{
							if(missile[ii2]->live)
							{
								if(missile[ii2]->disappear)
								{
									create_effect(2,missile[ii2]->x,missile[ii2]->y);
									missile[ii2]->init_missile();
								}
							}
						}
						player->num[3]=false;
						player->sh=false;
					}
				}
			case '5':
				if(state==2)
				{
					player->num[4]=true;
					if(player->sh && player->num[4])
					{
						if(!sub[player->sub_count]->live)
						{
							sub[player->sub_count]->init(player->sub_count,rand_num(SUB_TYPE_MAX));
							player->sub_count++;
						}
						player->num[4]=false;
						player->sh=false;
					}
				}
				break;
			case 'X':
				if(state==999)
				{
					scroll_speed=true;
				}
				else
				{
					player->shot=true;	
				}
				break;
			case 'Q':
				push_q=true;
				break;
			case 'Z':
				player->slow=true;
				break;
			case 'S':
				if(state==0)
				{
					state=1;
				}
				else if(state==3)
				{
					stage_select=0;
					state=0;
				}
				break;
			case VK_SPACE:
				if(state==2)
				{
					state=4;
				}
				else if(state==4)
				{
					state=2;
				}
				break;
			}
		}
		break;
	case WM_KEYUP:
		{
			switch(wParam)
			{
			case VK_RIGHT:
				player->right=false;
				break;
			case VK_LEFT:
				player->left=false;
				break;
			case VK_UP:
				player->up=false;
				break;
			case VK_DOWN:
				player->down=false;
				break;				
			case VK_LSHIFT:
				if(state==2)
				{
					player->sh=false;
				}
				break;
			case VK_NUMPAD1:
				if(state==2)
				{
					player->num[0]=false;
				}
			case '2':
				if(state==2)
				{
					player->num[1]=false;
				}
			case '3':
				if(state==2)
				{
					player->num[2]=false;
				}
			case '4':
				if(state==2)
				{
					player->num[3]=false;
				}
			case '5':
				if(state==2)
				{
					player->num[4]=false;
				}
				break;
			case 'X':
				if(state==999)
				{
					scroll_speed=false;
				}
				else
				{
					player->shot=false;	
				}
				break;
			case 'Q':
				push_q=false;
				break;
			case 'Z':
				player->slow=false;
				break;
			}
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �޴��� ���� ������ ���� �м��մϴ�.
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

		if(hBit)
		{
			hMemDC = CreateCompatibleDC(hdc);

			SelectObject(hMemDC, hBit);

			BitBlt(hdc, 0, 0, c_wid, c_hei, hMemDC, 0, 0, SRCCOPY);

			DeleteObject(hMemDC);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		
	DeleteObject(SelectObject(hMemDC,boss_Pen));
	DeleteObject(SelectObject(hMemDC,boss_Brush));
	DeleteObject(SelectObject(hMemDC,OldPen));
	DeleteObject(SelectObject(hMemDC,OldBrush));

	DeleteObject(SelectObject(hMemDC,hPen));
	DeleteObject(SelectObject(hMemDC,hBrush));


		if(hBit)DeleteObject(hBit);
		PostQuitMessage(0);
		KillTimer(hWnd,1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void game_init()
{
	int ii;	
	player->init();
	if(stage_select==0)
	{
		boss->init(0);
	}
	else
	{
		boss->init(stage_select-1);
		player->hp=3;
	}
	for(ii=0;ii<EFFECT_MAX;ii++)
	{ 
		effect[ii]->init_effect();
	}
	for(ii=0;ii<MISSILE_MAX;ii++)
	{
		missile[ii]->init_missile();
	}
	for(ii=0;ii<ITEM_MAX;ii++)
	{
		item[ii]->init_item();
	}
}

void game_2()
{
	int ii;
	////////////////////player
	player->move();
	player->sub_angle++;
	if(player->sub_angle>360)
	{
		player->sub_angle=player->sub_angle-360;
	}
	if(test)
	{
		player->x+=((boss->x-player->x)*0.3);
		player->y+=((boss->y+150-player->y)*0.08);
		player->shot=true;
	}

	if(!player->live)
	{
		die_time++;
		if(die_time>100)
		{
			if(stage_select==0)
			{
				state=3;
			}
			else
			{
				stage_select=0;
				state=0;
			}
		}
	}
	if(player->hit_time>0)
	{
		player->hit_time--;
	}
	if(player->del>0)
	{
		player->del--;
	}
	if(player->del<1 && player->shot && player->live)
	{
		player->del=player->del_max;
		if(player->type==19)
		{
			create_missile(player->type,player->x,player->y-3);
		}
		else
		{
			create_missile(player->type,0,0);
		}
	}
	//////////////sub
	for(ii=0;ii<SUB_MAX;ii++)
	{
		if(sub[ii]->live)
		{
			sub[ii]->move(player->x,player->y,player->sub_count,player->sub_angle);

			sub[ii]->shot_del--;
			if(sub[ii]->shot_del<1)
			{
				sub[ii]->shot_del=sub_missile_del_max[sub[ii]->type];
				create_missile(90+sub[ii]->type,sub[ii]->x,sub[ii]->y);
			}
		}
	}
	/////////////////item
	item_time--;
	if(item_time<1)
	{
		item_time=200+rand_num(100);
		create_item((c_wid*(2.0/3.0))/2+rand_num(c_wid*(2.0/3.0)),450+rand_num(280),200+rand_num(150));
	}
	
	for(ii=0;ii<ITEM_MAX;ii++)
	{
		if(item[ii]->live)
		{
			item[ii]->move();
			if(get_distance(player->x,player->y,item[ii]->x,item[ii]->y)<12)
			{
				item_rand=rand_num(1000);
				//item_rand=355;
				if(item_rand<70)
				{
					for(int ii2=0;ii2<MISSILE_MAX;ii2++)
					{
						if(missile[ii2]->live)
						{
							if(missile[ii2]->type<100)
							{
								missile[ii2]->type2 =  missile[ii2]->type2 | 0x1000;
							}
						}
					}
				}
				else if(item_rand<140)
				{
					for(int ii2=0;ii2<MISSILE_MAX;ii2++)
					{
						if(missile[ii2]->live)
						{
							if(missile[ii2]->disappear)
							{
								create_effect(2,missile[ii2]->x,missile[ii2]->y);
								missile[ii2]->init_missile();
							}
						}
					}
				}
				else if(item_rand<340)
				{
					player->hp++;
				}
				else if(item_rand<440)
				{	////create_sub
					if(!sub[player->sub_count]->live)
					{
						sub[player->sub_count]->init(player->sub_count,rand_num(SUB_TYPE_MAX));
						//sub[player->sub_count]->init(player->sub_count,4);
						player->sub_count++;
					}
				}
				else
				{
					change_type(0);
				}
				create_effect(1,item[ii]->x,item[ii]->y);
				item[ii]->init_item();						
			}
		}
	}

	////////////////////missile
	for(ii=0;ii<MISSILE_MAX;ii++)
	{
		if(missile[ii]->live)
		{			
			missile[ii]->live_time++;

			if(missile[ii]->type<100)
			{
				missile[ii]->move(boss->x,boss->y);
			}
			else
			{
				missile[ii]->move(player->x,player->y);
			}

			switch(missile[ii]->type)
			{
			case 1:
			case 4:
				if(get_distance(boss->x,boss->y,missile[ii]->x,missile[ii]->y)<17)
				{
					boss_hit(ii);
				}
				break;
			case 2:
				if(get_distance(boss->x,boss->y,missile[ii]->x,missile[ii]->y)<17)
				{
					boss_hit(ii);
				}
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					missile[ii]->temp1=missile[ii]->temp2;
					create_missile(20,(int)missile[ii]->x,(int)missile[ii]->y);
				}
				break;
			case 3:
				if(get_distance(boss->x,boss->y,missile[ii]->x,missile[ii]->y)<17)
				{
					boss_hit(ii);
				}
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					missile[ii]->temp1=missile[ii]->temp2;
					create_missile(21,(int)missile[ii]->x,(int)missile[ii]->y);
				}
				break;
			case 101:
			case 102:
			case 110:
			case 120:
			case 130:
			case 141:
			case 142:
			case 151:
			case 152:
			case 153:
			case 154:
			case 155:
			case 156:
			case 157:
			case 159:
			case 160:
			case 161:
			case 201:
			case 202:
				if(player->hit_time<1 && player->live)
				{
					if(get_distance(player->x,player->y,missile[ii]->x,missile[ii]->y)<7)
					{
						player_hit(ii);						
					}
				}
				break;
			case 150:
				if(missile[ii]->temp1>0)
				{
					missile[ii]->temp1--;
					if(missile[ii]->temp1<1)
					{
						missile[ii]->angle=get_angle(missile[ii]->x,missile[ii]->y,player->x,player->y);
						missile[ii]->type2=0x1;
						missile[ii]->distance=10;						
					}
				}
				if(player->hit_time<1 && player->live)
				{
					if(get_distance(player->x,player->y,missile[ii]->x,missile[ii]->y)<7)
					{
						player_hit(ii);						
					}
				}
				break;
			case 158:
				if(missile[ii]->temp1<1)
				{
					missile[ii]->type2=0x1;
					missile[ii]->angle=90;
				}
				else
				{
					missile[ii]->temp1--;
				}
				if(player->hit_time<1 && player->live)
				{
					if(get_distance(player->x,player->y,missile[ii]->x,missile[ii]->y)<7)
					{
						player_hit(ii);						
					}
				}
				break;
			case 1001:
			case 1002:
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					create_missile(100+missile[ii]->type%10,(int)missile[ii]->x,(int)missile[ii]->y);
					missile[ii]->init_missile();
				}
				break;
			case 1003:
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					create_missile(130,(int)missile[ii]->x,(int)missile[ii]->y);
					missile[ii]->init_missile();
				}
				break;
			case 1004:
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					missile[ii]->temp1=13;
					create_missile(151,missile[ii]->x,missile[ii]->y);
				}
				break;
			case 1005:
				missile[ii]->temp1--;
				if(missile[ii]->temp1<1)
				{
					if(boss->angry)
					{
						missile[ii]->temp1=6;
					}
					else
					{
						missile[ii]->temp1=8;
					}
					create_missile(152,missile[ii]->x,missile[ii]->y,missile[ii]->angle);
				}
				break;
			case 1006:
				if(missile[ii]->temp1<1)
				{
					missile[ii]->temp1=2;
					missile[ii]->temp2+=1.5;
					create_missile(153,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);
				}
				else
				{
					missile[ii]->temp1--;
				}
				break;
			case 1007:				
				if(missile[ii]->temp1<1)
				{
					missile[ii]->temp1=2;
					missile[ii]->temp2+=1.5;
					create_missile(154,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);
				}
				else
				{
					missile[ii]->temp1--;
				}
				break;
			case 1008:
				if(missile[ii]->temp1<1)
				{
					if(missile[ii]->temp3<1)
					{
						missile[ii]->temp1=40+rand_num(80);
						missile[ii]->temp3=21;
					}
					else
					{
						missile[ii]->temp3-=1;
						if((int)missile[ii]->temp3%2==0)
						{
							create_missile(155,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);
						}
					}
				}
				else
				{
					missile[ii]->temp1--;
					missile[ii]->temp2=get_angle(missile[ii]->x,missile[ii]->y,player->x,player->y);
				}
				break;
			case 1009:
				if(missile[ii]->temp1<1)
				{
					if(boss->angry)
					{
						missile[ii]->temp1=60;
					}
					else
					{
						missile[ii]->temp1=80;
					}
					switch((int)missile[ii]->temp2)
					{
					case 0:
						create_missile(156,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);
						break;
					case 1:
						create_missile(157,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);
						break;
					}
					if(missile[ii]->temp2==0)
					{
						missile[ii]->temp2=1;
					}
					else
					{
						missile[ii]->temp2=0;
					}
				}
				else
				{
					missile[ii]->temp1--;					
				}
				break;
			case 1010:
				if(missile[ii]->temp1<1)
				{
					create_missile(159,missile[ii]->x,missile[ii]->y,missile[ii]->temp2);					
					missile[ii]->temp2+=(0.8*missile[ii]->temp3);
					if(missile[ii]->live_time>20)
					{
						if(missile[ii]->live_time%10==0)
						{
							if(rand_num(10)<5)
							{
								missile[ii]->temp3*=-1;
							}
						}
					}
					missile[ii]->temp1=2;
				}		
				else
				{
					missile[ii]->temp1--;					
				}
				break;
			case 1011:
				missile[ii]->speed_x=player->x+cos((missile[ii]->live_time)*3.14/180)*130;
				missile[ii]->speed_y=player->y+sin((missile[ii]->live_time)*3.14/180)*130;
				if(missile[ii]->temp1<1)
				{
					if(missile[ii]->temp3<1)
					{						
						missile[ii]->temp2++;
						if(missile[ii]->temp2>2)
						{
							missile[ii]->temp2=0;
						}
						switch((int)missile[ii]->temp2)
						{
						case 0:			
							missile[ii]->temp1=140;
						case 1:			
							missile[ii]->temp1=60;
							break;
						}
					}
					else
					{
						missile[ii]->temp3--;
						switch((int)missile[ii]->temp2)
						{
						case 0:							
							if((int)(missile[ii]->temp3)%5==0)
							{
								create_missile(160,missile[ii]->x,missile[ii]->y,missile[ii]->temp3);
							}	
							break;
						case 1:							
							if((int)(missile[ii]->temp3)%40==0)
							{
								create_missile(161,missile[ii]->x,missile[ii]->y,missile[ii]->temp3);
							}	
							break;
						}
					}
				}		
				else
				{
					missile[ii]->temp1--;	
					if(missile[ii]->temp1<1)
					{
						switch((int)missile[ii]->temp2)
						{
						case 0:
							missile[ii]->temp3=90;
							break;
						case 1:
							missile[ii]->temp3=100;
							break;
						case 2:
							break;
						}
					}
				}
				break;
			}
		}
	}
	
	//////////////////////effect
	for(ii=0;ii<EFFECT_MAX;ii++)
	{
		if(effect[ii]->live)
		{
			effect[ii]->move();
		}
	}


	////////////////boss
	if(boss->live)
	{
		if(boss->shot_num>0)
		{
			boss->del1--;
			if(boss->del1<1)
			{
				boss_missile_create(boss_path[boss->lv]);
			}
		}
		else 
		{	
			boss->move();	
			if(boss->del2!=9999)
			{
				boss->del2--;
			}
			if(boss->del2<1)
			{
				if(boss->angry)
				{
					boss->del2=boss_del2_angry[boss_path[boss->lv]];
					boss->shot_num=boss_missile_mum_angry[boss_path[boss->lv]];
				}
				else
				{
					boss->del2=boss_del2[boss_path[boss->lv]];
					boss->shot_num=boss_missile_mum[boss_path[boss->lv]];
				}			
				if(boss->type==1)
				{
					boss->type=2;
				}
				else if(boss->type==2)
				{
					boss->type=1;
				}
			}
		}
		if(boss->hit_time>0)
		{
			boss->hit_time--;
		}
	}
	else
	{
		die_time++;
		if(die_time>100)
		{
			if(stage_select==0)
			{
				state=999;
				ending_scroll=0;
				scroll_speed=false;
			}
			else
			{
				stage_select=0;
				state=0;
			}
		}
	}
}
void draw_0()
{
	int ii;

	for(ii=0;ii<SUB_MAX;ii++)
	{
		if(sub[ii]->live)
		{
			Ellipse(hMemDC,sub[ii]->x-7,sub[ii]->y-7,sub[ii]->x+7,sub[ii]->y+7);
		}
	}

	draw_player();
	if(player->live)
	{
		if(player->hit_time>0 && player->hit_time%2==0)
		{			
			
		}
		else
		{
			Ellipse(hMemDC,player->x-10,player->y-10,player->x+10,player->y+10);
		}
		for(i=0;i<player->hp;i++)
		{
			Rectangle(hMemDC,0,c_hei-10-(i*12),10,c_hei-(i*12));
		}
	}
	
	
	draw_boss();
	if(boss->live)
	{
		if(boss->hit_time>0 && boss->hit_time%2==0)
		{			
			//hBrush=CreateSolidBrush(RGB(255,0,0));
			//OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
			Ellipse(hMemDC,boss->x-20,boss->y-20,boss->x+20,boss->y+20);	
			//hBrush=CreateSolidBrush(RGB(0,0,255));
			//OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
		}
		else
		{
			Ellipse(hMemDC,boss->x-20,boss->y-20,boss->x+20,boss->y+20);
		}
		Rectangle(hMemDC,boss->x-10,c_hei-3,boss->x+10,c_hei);
	}

	draw_player();
	for(ii=0;ii<ITEM_MAX;ii++)
	{
		if(item[ii]->live)
		{
			Rectangle(hMemDC,item[ii]->x-7,item[ii]->y-7,item[ii]->x+7,item[ii]->y+7);
		}
	}

	
	float aangle=10;
	///XFORM XForm={1,0,0,1,0,0};	
	for(ii=0;ii<MISSILE_MAX;ii++)
	{
		if(missile[ii]->live)
		{
			//hBrush=CreateSolidBrush(RGB(0,255,0));
			//OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
			switch(missile[ii]->type)
			{
			case 1001:
			case 1002:
			case 1003:
			case 1004:
			case 1005:
			case 1006:
			case 1007:
			case 1008:
			case 1009:
			case 1010:
			case 1011:
				draw_boss();
				Ellipse(hMemDC,missile[ii]->x-10,missile[ii]->y-10,missile[ii]->x+10,missile[ii]->y+10);
				break;
			case 1:case 2:case 3:case 4:
				draw_player();
				SetGraphicsMode(hMemDC,GM_ADVANCED);
				XForm.eM11=(float)cos(missile[ii]->angle*3.14/180);
				XForm.eM12=(float)sin(missile[ii]->angle*3.14/180);
				XForm.eM21=(float)-sin(missile[ii]->angle*3.14/180);
				XForm.eM22=(float)cos(missile[ii]->angle*3.14/180);
				XForm.eDx=missile[ii]->x;
				XForm.eDy=missile[ii]->y;
				SetWorldTransform(hMemDC,&XForm); 
				//Ellipse(hMemDC,missile[ii]->x-5,missile[ii]->y-7,missile[ii]->x+5,missile[ii]->y+7);
				Ellipse(hMemDC,-7,-5,7,5);
				
				XForm.eM11=1;
				XForm.eM12=0; 
				XForm.eM21=0;
				XForm.eM22=1;				
				XForm.eDx=0;
				XForm.eDy=0;
				SetWorldTransform(hMemDC,&XForm);
				break;
			default:		
				draw_boss();
				SetGraphicsMode(hMemDC,GM_ADVANCED);
				if(missile[ii]->type2 & 0x100000)
				{
					XForm.eM11=(float)cos(missile[ii]->temp1*3.14/180);
					XForm.eM12=(float)sin(missile[ii]->temp1*3.14/180);
					XForm.eM21=(float)-sin(missile[ii]->temp1*3.14/180);
					XForm.eM22=(float)cos(missile[ii]->temp1*3.14/180);
				}
				else
				{
					XForm.eM11=(float)cos(missile[ii]->angle*3.14/180);
					XForm.eM12=(float)sin(missile[ii]->angle*3.14/180);
					XForm.eM21=(float)-sin(missile[ii]->angle*3.14/180);
					XForm.eM22=(float)cos(missile[ii]->angle*3.14/180);
				}
				XForm.eDx=missile[ii]->x;
				XForm.eDy=missile[ii]->y;
				SetWorldTransform(hMemDC,&XForm); 
				//Ellipse(hMemDC,missile[ii]->x-5,missile[ii]->y-7,missile[ii]->x+5,missile[ii]->y+7);
				Ellipse(hMemDC,-7,-5,7,5);
				
				XForm.eM11=1;
				XForm.eM12=0; 
				XForm.eM21=0;
				XForm.eM22=1;				
				XForm.eDx=0;
				XForm.eDy=0;
				SetWorldTransform(hMemDC,&XForm);
				break;
			}
			//hBrush=CreateSolidBrush(RGB(0,0,255));
			//OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
		}
	}
	draw_boss();
	if(boss->live)
	{		
		//hBrush=CreateSolidBrush(RGB(0,0,255));
		//OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
		Rectangle(hMemDC,10,5,10+((c_wid-20)*(boss->hp/boss->hp_max)),15);
		//Rectangle(hMemDC,10,5,c_wid-20,15);
	}
	


	for(ii=0;ii<EFFECT_MAX;ii++)
	{
		if(effect[ii]->live)
		{
			switch(effect[ii]->type)
			{
			case 1:	
				draw_player();
				Ellipse(hMemDC,effect[ii]->x-3,effect[ii]->y-3,effect[ii]->x+3,effect[ii]->y+3);
				break;
			case 100:		
				draw_boss();		
				Ellipse(hMemDC,effect[ii]->x-3,effect[ii]->y-3,effect[ii]->x+3,effect[ii]->y+3);
				break;
			}
		}
	}
}
void boss_hit(int ii)
{
	if(boss->hp>0)
	{
		boss->hp--;
		if(boss->hp<1)
		{
			if(boss_path[boss->lv]==9)
			{
				for(int ii2=0;ii2<MISSILE_MAX;ii2++)
				{
					if(missile[ii2]->live)
					{
						if(missile[ii2]->type==1006 || missile[ii2]->type==1007) 
						{
							missile[ii2]->init_missile();
						}
					}
				}
			}
			else if(boss_path[boss->lv]==10)
			{
				for(int ii2=0;ii2<MISSILE_MAX;ii2++)
				{
					if(missile[ii2]->live)
					{
						if(missile[ii2]->type==1008)
						{
							create_effect(2,missile[ii2]->x,missile[ii2]->y);
							missile[ii2]->init_missile();
						}
					}
				}
			}
			else if(boss_path[boss->lv]==11)
			{
				for(int ii2=0;ii2<MISSILE_MAX;ii2++)
				{
					if(missile[ii2]->live)
					{
						if(missile[ii2]->type==1009)
						{
							create_effect(2,missile[ii2]->x,missile[ii2]->y);
							missile[ii2]->init_missile();
						}
					}
				}
			}
			else if(boss_path[boss->lv]==13)
			{
				for(int ii2=0;ii2<MISSILE_MAX;ii2++)
				{
					if(missile[ii2]->live)
					{
						if(missile[ii2]->type==1010)
						{
							create_effect(2,missile[ii2]->x,missile[ii2]->y);
							missile[ii2]->init_missile();
						}
					}
				}
			}
			else if(boss_path[boss->lv]==14)
			{
				for(int ii2=0;ii2<MISSILE_MAX;ii2++)
				{
					if(missile[ii2]->live)
					{
						if(missile[ii2]->type==1011)
						{
							create_effect(2,missile[ii2]->x,missile[ii2]->y);
							missile[ii2]->init_missile();
						}
					}
				}
			}
			boss->lv++;
			//boss->lv+=99;
			if(boss->lv>=BOSS_TYPE_MAX)
			{
				boss->die();
			}
			else if(stage_select!=0)
			{
				boss->die();
			}
			else
			{
				boss->init(boss->lv%BOSS_TYPE_MAX);
			}
		}
		if(boss->hp/boss->hp_max<0.3)
		{
			boss->angry=true;
		}
	}
	boss->hit_time=10;
	create_effect(1,missile[ii]->x,missile[ii]->y);
	missile[ii]->init_missile();
}
void player_hit(int ii)
{
	if(!player->super)
	{
		if(player->hp>0)
		{
			////player
			
			if(player->sub_count>0)
			{
				for(int ii2=0;ii2<SUB_MAX;ii2++)
				{
					if(sub[ii2]->live)
					{
						if(sub[ii2]->num==0)
						{
							sub[ii2]->die();
							player->sub_count--;
						}
					}
				}					
				for(int ii3=0;ii3<SUB_MAX;ii3++)
				{
					if(sub[ii3]->live)
					{
						sub[ii3]->num--;
					}
				}	
			}
			else
			{
				player->hp--;
			}

			if(player->hp==0)
			{
				player->die();
			}
			else
			{
				change_type(0);
			}
		}
	}
	player->hit_time=20;
	create_effect(100,missile[ii]->x,missile[ii]->y);
	missile[ii]->init_missile();
}

void boss_missile_create(int id)
{
	if(boss->angry)
	{
		boss->del1=boss_del1_angry[boss_path[boss->lv]];
	}
	else
	{
		boss->del1=boss_del1[boss_path[boss->lv]];
	}
	switch(id)//{7,6,4,5,10,1,8,13,3,12,2,0,9,11};
	{
	case 7:
		create_missile(1004,0,0); // ���ư��鼭 �̻��� ����3 ���ڸ��� � 
		break;
	case 6:
		create_missile(150,0,0); /// �ֺ��� �̻��� -> �÷��̾� ������ 
		break;
	case 4:
		create_missile(1003,player->x,player->y);//�÷��̾� �ֺ� ���� �߷�
		break;
	case 5:
		create_missile(140+boss->type,0,0);  //��ƨ�� 
		break;
	case 10:
		create_missile(1008,0,0); /// �ͷ�5�� 3���� -10,0,10
		break;
	case 1:
		create_missile(1000+boss->type,0,0); /// ���� ȸ��
		break;
	case 8:
		create_missile(1005,rand_num(360),0); /// ���ư��鼭 �̻��� ����2 2������ 
		break;
	case 13:
		create_missile(1010,0,0); /// �ͷ� 1�� 6���� �͸�����
		break;
	case 3:		
		create_missile(120,player->x,player->y);//�عٶ�� 
		break;
	case 12:
		create_missile(158,0,0); /// ��
		break;
	case 2:
		create_missile(110,player->x,player->y);//3���� ��ź
		break;
	case 0:		
		create_missile(200+boss->type,110,110);//3���� ���°�
		break;
	case 9:
		create_missile(1006,0,0); /// �ͷ� 2�� 3���� 120�� ���ۺ���
		break;
	case 11:
		create_missile(1009,0,0); /// �ͷ�4�� 36�� ��ȭ��
		break;
	case 14:
		create_missile(1011,player->x,player->y); /// 
		break;
	}
}						
void change_type(int idd)
{	
	if(idd==0)
	{
		while(true)
		{
			player->type_temp=rand_num(PLAYER_TYPE_MAX)+1;
			if(player->type_temp==20 || player->type_temp==21)
			{
			}
			else
			{
				if(player->type!=player->type_temp)
				{
					break;
				}
			}
		}
		player->type_change(player->type_temp);
	}
	else
	{
		player->type_change(idd);
	}
}

void draw_player()
{
	OldPen=(HPEN)SelectObject(hMemDC,boss_Pen);
	OldBrush=(HBRUSH)SelectObject(hMemDC,boss_Brush);
}
void draw_boss()
{
	OldPen=(HPEN)SelectObject(hMemDC,hPen);
	OldBrush=(HBRUSH)SelectObject(hMemDC,hBrush);
}

void ending()
{	
	if(scroll_speed)
	{
		ending_scroll+=5;
	}
	else
	{
		ending_scroll+=2;
	}
	if(ending_scroll>1100)
	{
		stage_select=0;
		state=0;
	}
	wsprintf(log_text,TEXT("�̰� ���� ����� ���� ���̾�.."));
	TextOut(hMemDC,150,742-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("�������� �ܻ����ִ� ����̰ڱ���"));
	TextOut(hMemDC,150,742+(35*1)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("��¶�� ... �����մϴ�!"));
	TextOut(hMemDC,150,742+(35*2)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("����� �� ���� ���� ������ ���̸�"));
	TextOut(hMemDC,150,742+(35*3)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("�����ڴ� �̹� ������ �߰��� "));
	TextOut(hMemDC,150,742+(35*4)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("������ �����ؼ��� ������ ���� ����������"));
	TextOut(hMemDC,150,742+(35*5)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("�̷��� ���� ���� �𸣴� ���̴�"));
	TextOut(hMemDC,150,742+(35*6)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("���� �� ���������� �ۿ��� ������ ����� �ִٸ�"));
	TextOut(hMemDC,150,742+(35*7)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("���� ���� ������ �����ε� ����ֱ� �ٷ�"));
	TextOut(hMemDC,150,742+(35*8)-ending_scroll,log_text,lstrlen(log_text));
	wsprintf(log_text,TEXT("�÷��� ���༭ ����"));
	TextOut(hMemDC,150,742+(35*9)-ending_scroll,log_text,lstrlen(log_text));
}
