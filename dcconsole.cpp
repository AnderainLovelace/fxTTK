extern "C"
{
#include <fxlib.h>
}
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "dcconsole.h"
#include "file.h"

#define LINE_ROW_MAX	5
#define LINE_COL_MAX	10

#define SCR_LEFT		4
#define SCR_TOP			2

typedef unsigned int 	uint;
typedef unsigned char	uchar;

//-------------------------------------------------------------
// chinese

static int fh_HZK;

void ChsDraw(int x,int y,int width,int height,int mode,uchar * pGraph)
{
	DISPGRAPH dg;

	dg.x					= x;
	dg.y					= y;
	dg.GraphData.width		= width;
	dg.GraphData.height		= height;
	dg.GraphData.pBitmap	= pGraph;
	dg.WriteModify			= mode+1;
	dg.WriteKind			= IMB_WRITEKIND_OVER;

	Bdisp_WriteGraph_VRAM(&dg);
}

void ChsDrawChar (int x,int y,int sel,uchar c1,uchar c2)
{
	uchar mat[24];
	uint sec,pot;

	sec = c1-0xa1;
	pot = c2-0xa1;

	Bfile_ReadFile(fh_HZK,mat,24,(94*sec+pot)*24);

	ChsDraw(x,y,12,12,sel,mat);
}

int ChsOpenHZK ()
{
	fh_HZK = open_file("\\\\crd0\\HZK12.df",_OPENMODE_READ_SHARE);
	return fh_HZK<0;// TRUE if open fail
}

void ChsCloseHZK ()
{
	Bfile_CloseFile(fh_HZK);
}

void ChsPrint (int x,int y,int sel,const unsigned char * str)
{
	for(;*str;++str)
	{
		if ((*str) & 0x80) // GB ?
		{
			ChsDrawChar(x,y,sel,*str,*(str+1));
			++str;
		}
		else
		{
			ChsDrawChar(x,y,sel,0xA3,0x80+*str);
		}
		x+=12;
	}
}

//-------------------------------------------------------------
// console
uchar	line_buf[LINE_ROW_MAX][LINE_COL_MAX+1][2];
int		line_index	= 0;
int		line_x		= 0;
int		line_start	= 0;
int		line_count	= 0;

void dAreaClear (int left,int top,int right,int bottom,int sel) 
{ 
	DISPBOX box; 
	box.left = left;box.top = top;box.right = right;box.bottom = bottom; 
 	if (sel != 1) 
		Bdisp_AreaClr_VRAM (&box); 
	if (sel != 0){ 
 		Bdisp_DrawLineVRAM (box.left,box.top,box.right,box.top); 
		Bdisp_DrawLineVRAM (box.left,box.bottom,box.right,box.bottom); 
		Bdisp_DrawLineVRAM (box.left,box.top,box.left,box.bottom); 
		Bdisp_DrawLineVRAM (box.right,box.top,box.right,box.bottom); 
    } 
}

uint WaitKey ()
{
	uint key;GetKey(&key);return key;
}

char dGetKeyChar (uint key)
{
	if (key>=KEY_CHAR_A && key<=KEY_CHAR_Z)
		return key;
	else if (key==KEY_CHAR_PMINUS || key==KEY_CHAR_MINUS)
		return '-';
	else if (key>=KEY_CHAR_0 && key<= KEY_CHAR_9)
		return key;

	return 0;
}

int GetLineBox (char * s,int max,int width,int x,int y)
{
	int		pos = strlen(s);
	int		refresh = 1;
	uint	key;
	char	c;
	
	while(1)
	{
		if (refresh)
		{
			dAreaClear(x,y,x+width*6+2,y+10,2);

			if (pos<width-1)
			{
				PrintXY (x+1,y+2,(uchar*)s,0);
				PrintXY (x+1+pos*6,y+2,(uchar*)"_",0);
			}
			else
			{
				PrintXY (x+1,y+2,(uchar*)(s+pos-width+1),0);
				PrintXY (x+1+(width-1)*6,y+2,(uchar*)"_",0);
			}
			refresh = 0;
		}

		GetKey(&key);

		if ((c=dGetKeyChar(key))!=0)
		{
			if (pos>=max) continue;

			s[pos++] = c;s[pos] = '\0';
			refresh = 1;
		}
		else
		{
			if (key==KEY_CTRL_DEL)
			{
				if (pos<=0) continue;
				s[--pos] = '\0';
				refresh  = 1;
			}
			else if (key==KEY_CTRL_AC)
			{
				*s		= 0;
				pos		= 0;
				refresh	= 1;
			}
			else if (key==KEY_CTRL_EXE) return 1;
			else if (key==KEY_CTRL_EXIT) return 0;
			
		}
	}
}

int get_int ()
{
	char buf[128];
	GetLineBox (buf,128,12,0,0);
	return atol(buf);
}

void dConsoleRedraw ()
{
	int i,j,left = SCR_LEFT,top = SCR_TOP;
	Bdisp_AllClr_VRAM();
	for(i=0,j=line_start;i<line_count;++i,top+=12)
	{
		ChsPrint(left,top,0,(uchar*)line_buf[j]);
		if (++j>=LINE_ROW_MAX) j = 0;
	}
}
void dConsolePut(const char * str)
{
	if (line_count == 0) line_count = 1;
	for (;*str;++str)
	{
		if (*str != '\n')
		{
			uchar * s = line_buf[line_index][line_x++];
			if (*str & 0x80)
			{
				s[0] = *str;
				s[1] = *++str;
			}
			else
			{
				s[0] = 0xA3;
				s[1] = (*str+0x80);
			}
		}
		else
		{
			line_buf[line_index][line_x][0] = 0;
			line_x = LINE_COL_MAX;
		}
		if (line_x>=LINE_COL_MAX)
		{
			line_buf[line_index][line_x][0] = 0;

			line_x = 0;
			if (line_count<LINE_ROW_MAX)
			{
				++line_count;
			}
			else
			{
				line_start++;
				if (line_start>=LINE_ROW_MAX) line_start = 0;
			}
			line_index++;
			if (line_index>=LINE_ROW_MAX) line_index = 0;
		}
	}
	line_buf[line_index][line_x][0] = '\0';
	dConsoleRedraw();
}

int dPrintf (const char * format,...)
{
	char	buf[256];
	int		length;
	va_list	arg_list;

	va_start(arg_list,format);
	length = vsprintf(buf,format,arg_list);
	va_end(arg_list);

	dConsolePut (buf);
	WaitKey();
	return length;
}

