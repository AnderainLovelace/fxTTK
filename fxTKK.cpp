extern "C"
{
#include <fxlib.h>
}
#include <stdio.h>
#include "dcconsole.h"

extern int start_game();

extern "C"
{
int AddIn_main(int isAppli, unsigned short OptionNum)
{
	Bdisp_AllClr_DDVRAM();

	if(ChsOpenHZK())
	{
		PrintMini(0,0,"can not open HZK file",MINI_OVER);
		WaitKey();
		return 0;
	}

	start_game();

    return 1;
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section

#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section
}
