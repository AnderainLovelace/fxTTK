extern "C"
{
#include <fxlib.h>
}
#include <stdio.h>
#include <string.h>
#include "dcconsole.h"
#include "def.h"
#include "ui.h"
typedef unsigned int 	uint;

#define PCUCHAR const unsigned char *

const char * HUASE_STRING[] 	= {"无色","黑桃","红桃","草花","方片"};
const char * DIANSHU_STRING[]	= {"无点数","A","2","3","4","5","6","7","8","9","10","J","Q","K"};

//101-103
static const char * LEIXING1_STRING[]	= {"杀","闪","桃"};
//201-210
static const char * LEIXING2_STRING[]	= {"过河拆桥","顺手牵羊","无中生有","决斗","借刀杀人","桃园结义","五谷丰登","南蛮入侵","万箭齐发","无懈可击"};
//251-252
static const char * LEIXING3_STRING[]	= {"乐不思蜀","闪电",};
//301-308
static const char * LEIXING4_STRING[]	= {"诸葛连弩1","雌雄双股剑2","青釭剑2","青龙偃月刀3","丈八蛇矛3","贯石斧3","方天画戟4","麒麟弓5"};
//331
static const char * LEIXING5_STRING[]	= {"八卦阵"};
//361-363
static const char * LEIXING6_STRING[]	= {"赤兔-1","大宛-1","紫辛-1"};
//381-383
static const char * LEIXING7_STRING[]	= {"爪黄飞电+1","的卢+1","绝影+1"};

#define IN_RANGE(l,a,b)		((l)>=(a) && (l)<=(b))

char card_info[128];

char * GetCardInfo(pai & p)
{
		const char 	*p1,*p2,*p3;
		int		paifu	= p.paifu;
		int		huase	= p.huase;
		int		dianshu	= p.dianshu;
		int		leixing	= p.leixing;

	  	if(paifu==0|| paifu==1);// do nothing
	 	else
		{
	   		strcpy(card_info,"牌副错误");
			return card_info;
		}
		if (huase>3 || huase<-1)
		{
			strcpy(card_info,"花色错误");
			return card_info;
		}
		p1 = (HUASE_STRING[huase+1]);
		if(dianshu<-1 || dianshu>12)
		{
			strcpy(card_info,"点数错误");
			return card_info;
		}
		p2 = DIANSHU_STRING[huase+1];
	
		if		(IN_RANGE(leixing,101,103))		p3 = (LEIXING1_STRING[leixing-101]);
		else if	(IN_RANGE(leixing,201,210))		p3 = (LEIXING2_STRING[leixing-201]);
		else if	(IN_RANGE(leixing,251,252))		p3 = (LEIXING3_STRING[leixing-251]);
		else if	(IN_RANGE(leixing,301,308))		p3 = (LEIXING4_STRING[leixing-301]);
		else if	(IN_RANGE(leixing,331,331))		p3 = (LEIXING5_STRING[leixing-331]);
		else if	(IN_RANGE(leixing,361,363))		p3 = (LEIXING6_STRING[leixing-361]);
		else if	(IN_RANGE(leixing,381,383))		p3 = (LEIXING7_STRING[leixing-381]);
		else
		{
			strcpy(card_info,"类型错误");
			return card_info;
		}
		sprintf(card_info,"%s%s-%s",p1,p2,p3);
		return card_info;
}

int select_shoupai (int type,pai * shoupai,int shoupaishu)
{
	uint			key;
	bool			redraw = true;
	int				i,top,bottom,index;
	const int		h_max = 4-1;
	const int		size = shoupaishu;

	index=0,top=0,bottom=h_max;

	while(true)
	{
		if(redraw)
		{
			int x=0,y=12;
			
			if (bottom-top>h_max)bottom = top + h_max;
			if(top>index)
			{
				top = index;
				bottom = index + h_max;
			}
			if (index>bottom)
			{
				bottom = index;
				top = bottom - h_max;
			}
			if(bottom>size - 1)bottom = size - 1;
			
			redraw = false;
			Bdisp_AllClr_VRAM();
			sprintf(card_info,"%s玩家有%d张牌",type ? "【查看】":"【选择】",size);
			ChsPrint(0,0,0,(PCUCHAR)card_info);
			if(shoupaishu>0)
			{
				for (i=top;i<=bottom;++i,y+=12)
				{
					//printf("%d %d %d",i,top,bottom);GetKey(&key);
					ChsPrint(x,y,index==i,(PCUCHAR)GetCardInfo(shoupai[i]));
				}
			}
			else
			{
				ChsPrint(x,y,0,"空城");
			}
		}
		GetKey(&key);
		
		if (key==KEY_CTRL_UP) 
			{if(--index<0) index = size - 1;redraw = true;}
		else if (key==KEY_CTRL_DOWN)
			{if(++index>size - 1) index = 0;redraw = true;}
		else if (key==KEY_CTRL_EXIT)	return -1;
		else if (key==KEY_CTRL_EXE) 	return index;
	}
}

void show_judgement (wujiang & w)
{
	const char * 	name;
	int 			x=0,y=0,sel=0;
	uint			key = 0;
	pai				*pandingpai = w.pandingpai;
	
	Bdisp_AllClr_VRAM();

	if(w.juese)
		name = "玩家";
	else
		name = "电脑";
		
	ChsPrint(x,y,sel,(PCUCHAR)name);ChsPrint(x+24,y,sel,(PCUCHAR)"当前判定区：");y+=12;
	
	if((pandingpai[0]).leixing==-1)ChsPrint(x,y,sel,(PCUCHAR)"空");
	else
	{
		x=0;
		ChsPrint(x,y,sel,(PCUCHAR)GetCardInfo(pandingpai[0]));y+=12;
		if((pandingpai[1]).leixing==-1);
		else
		{
			ChsPrint(x,y,sel,(PCUCHAR)GetCardInfo(pandingpai[1]));y+=12;
			if((pandingpai[2]).leixing==-1);
			else
			{
				ChsPrint(x,y,sel,(PCUCHAR)GetCardInfo(pandingpai[2]));
			}
		}
	}
	while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT)
	{
		GetKey(&key);
	}
}

static const char * EQUIPMENT_TYPE[] = {"武器　：","防具　：","进攻马：","防御马："};

void show_equipment (wujiang & w)
{
	const char * 	name;
	int 			x=0,y=0,sel=0,i=0;
	uint			key = 0;
	pai				*zhuangbei = w.zhuangbei;

	Bdisp_AllClr_VRAM();	

	if(w.juese)
		name = "玩家";
	else
		name = "电脑";
		
	ChsPrint(x,y,sel,(PCUCHAR)name);ChsPrint(x+24,y,sel,(PCUCHAR)"当前装备");y+=12;
	
	for(i=0;i<4;++i,y+=12)
	{
		x=0;
		ChsPrint(x,y,sel,(PCUCHAR)EQUIPMENT_TYPE[i]);x+=48;
		if(zhuangbei[0].leixing==-1)
			ChsPrint(x,y,sel,(PCUCHAR)"空");
		else
			ChsPrint(x,y,sel,(PCUCHAR)GetCardInfo(zhuangbei[i]));
		
	}
	while(key!=KEY_CTRL_EXE && key!=KEY_CTRL_EXIT)
	{
		GetKey(&key);
	}
}

