int		dGetLineBox (char * s,int max,int width,int x,int y);
void	dConsoleRedraw ();
void	dConsolePut(const char * str);
int		dGetLine (int max,char * s);
int		dPrintf (const char * format,...);
int 	GetLineBox (char * s,int max,int width,int x,int y);

int		get_int ();

int		ChsOpenHZK ();
void	ChsCloseHZK ();
void	ChsPrint (int x,int y,int sel,const unsigned char * str);

unsigned int WaitKey();

#define printf		dPrintf
