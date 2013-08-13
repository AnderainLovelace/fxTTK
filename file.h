extern "C"
{

typedef unsigned short fontc;

fontc * char_to_font		(const char * cfname,fontc * ffname);
char * font_to_char			(const fontc *ffname,char *cfname);
int	open_file 				(const char * cfname,int mode);

}