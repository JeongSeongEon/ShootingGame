#include <stdlib.h>
#include <math.h>

#pragma once


#define A 0.15//중력가속
#define G 0.05//중력
#define AR 0.003//공기저항

#define MISSILE_MAX 2000
#define EFFECT_MAX 1000
#define ITEM_MAX 2
#define SUB_MAX 10

#define BOSS_TYPE_MAX 15
#define PLAYER_TYPE_MAX 32

#define SUB_TYPE_MAX 6

#define CLIENTWIDTH 600
#define CLIENTHEIGHT 800
static float c_wid=CLIENTWIDTH-16;
static float c_hei=CLIENTHEIGHT-38;
//static float c_wid=584;
//static float c_hei=742;


static int boss_path[BOSS_TYPE_MAX]={7,6,4,5,10, 1,8,13,3,12,2, 0,9,11,14};
//static int boss_path[BOSS_TYPE_MAX]={13,11,12,7,6, 4,5,10,1,8, 3,2,0,9};

static int boss_hp[BOSS_TYPE_MAX]={200,200,200,200,200,  200,200,200,200,200,  200,200,200,200,130};

static int boss_del1[BOSS_TYPE_MAX]={0,0,0,3,0, 4,0,0,0,0, 0,3,0,0,0};
static int boss_del1_angry[BOSS_TYPE_MAX]={0,0,0,3,0, 4,0,0,0,0, 0,3,0,0,0};////1발1발사이

static int boss_del2[BOSS_TYPE_MAX]={50,50,60,60,60, 60,100,140,100,9999, 9999,9999,50,9999,9999};
static int boss_del2_angry[BOSS_TYPE_MAX]={40,80,45,45,45, 50,180,130,100,9999, 9999,9999,40,9999,9999};////장전

static int boss_missile_mum[BOSS_TYPE_MAX]=           {240,1,60,720,1, 200,18,3,5,2, 5,4,49,1,5};
static int boss_missile_mum_angry[BOSS_TYPE_MAX]=     {330,2,90,720,1, 280,36,4,5,2, 5,4,49,1,5};///총 몇발 쏠껀지

static int boss_missile_mum_same[BOSS_TYPE_MAX]=      {3,1,60,36,1, 20,18,3,5,2, 5,4,49,1,5};
static int boss_missile_mum_same_angry[BOSS_TYPE_MAX]={3,2,90,36,1, 28,36,4,5,2, 5,4,49,1,5};////동시에 몇발

////////////////////////////////////////////////
static int player_missile_num_max[PLAYER_TYPE_MAX]={7,3,1,2,3,1,1,2,2,4, 7,7,1,2,6,6,1,2,2,1, 1,7,7,7,7,2,1,2,2,4, 5,5};
static int player_missile_del_max[PLAYER_TYPE_MAX]={1,2,1,1,2,1,2,2,3,1, 1,3,1,1,1,1,3,5,4,1, 1,1,3,1,3,1,3,4,1,4, 5,4};

///////////////////////////////////////////////
static int sub_missile_num_max[SUB_TYPE_MAX]={1,2,1,2,2,3};
static int sub_missile_del_max[SUB_TYPE_MAX]={15,25,50,70,30,40};

float rand_num(int num);
float get_angle(float x1,float y1,float x2,float y2);
float get_distance(float x1,float y1,float x2,float y2);
void get_crt(int xx,int yy);
