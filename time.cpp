struct st_rtc {                                         /* struct RTC   */
              unsigned char     R64CNT;                 /* R64CNT       */
              char              wk1;                    /*              */
              union {                                   /* RSECCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :1;         /*              */
                           unsigned char S10:3;         /*    10sec     */
                           unsigned char S1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RSECCNT;                /*              */
              char              wk2;                    /*              */
              union {                                   /* RMINCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :1;         /*              */
                           unsigned char M10:3;         /*    10min     */
                           unsigned char M1 :4;         /*     1min     */
                           }      BIT;                  /*              */
                    }           RMINCNT;                /*              */
              char              wk3;                    /*              */
              union {                                   /* RHRCNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :2;         /*              */
                           unsigned char H10:2;         /*    10sec     */
                           unsigned char H1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RHRCNT;                 /*              */
              char              wk4;                    /*              */
              union {                                   /* RWKCNT       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char   :5;          /*              */
                           unsigned char WK:3;          /*    week      */
                           }      BIT;                  /*              */
                    }           RWKCNT;                 /*              */
              char              wk5;                    /*              */
              union {                                   /* RDAYCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :2;         /*              */
                           unsigned char D10:2;         /*    10day     */
                           unsigned char D1 :4;         /*     1day     */
                           }      BIT;                  /*              */
                    }           RDAYCNT;                /*              */
              char              wk6;                    /*              */
              union {                                   /* RMONCNT      */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char    :3;         /*              */
                           unsigned char M10:1;         /*    10mon     */
                           unsigned char M1 :4;         /*     1mon     */
                           }      BIT;                  /*              */
                    }          RMONCNT;                 /*              */
              char             wk7;                     /*              */
              union {                                   /* RYRCNT       */
                    unsigned short WORD;                /*  Word Access */
                    struct {                            /*  Bit  Access */
                           unsigned short Y1000:4;      /*   1000year   */
                           unsigned short Y100 :4;      /*    100year   */
                           unsigned short Y10  :4;      /*     10year   */
                           unsigned short Y1   :4;      /*      1year   */
                           }       BIT;                 /*              */
                    }           RYRCNT;                 /*              */
              union {                                   /* RSECAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char S10:3;         /*    10sec     */
                           unsigned char S1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RSECAR;                 /*              */
              char              wk8;                    /*              */
              union {                                   /* RMINAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char M10:3;         /*    10min     */
                           unsigned char M1 :4;         /*     1min     */
                           }      BIT;                  /*              */
                    }           RMINAR;                 /*              */
              char              wk9;                    /*              */
              union {                                   /* RHRAR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :1;         /*              */
                           unsigned char H10:2;         /*    10sec     */
                           unsigned char H1 :4;         /*     1sec     */
                           }      BIT;                  /*              */
                    }           RHRAR;                  /*              */
              char              wk10;                   /*              */
              union {                                   /* RWKAR        */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :4;         /*              */
                           unsigned char WK :3;         /*    week      */
                           }      BIT;                  /*              */
                    }           RWKAR;                  /*              */
              char              wk11;                   /*              */
              union {                                   /* RDAYAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :1;         /*              */
                           unsigned char D10:2;         /*    10day     */
                           unsigned char D1 :4;         /*     1day     */
                           }      BIT;                  /*              */
                    }           RDAYAR;                 /*              */
              char              wk12;                   /*              */
              union {                                   /* RMONAR       */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char ENB:1;         /*    ENB       */
                           unsigned char    :2;         /*              */
                           unsigned char M10:1;         /*    10mon     */
                           unsigned char M1 :4;         /*     1mon     */
                           }      BIT;                  /*              */
                    }           RMONAR;                 /*              */
              char              wk13;                   /*              */
              union {                                   /* RCR1         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char CF :1;         /*    CF        */
                           unsigned char    :2;         /*              */
                           unsigned char CIE:1;         /*    CIE       */
                           unsigned char AIE:1;         /*    AIE       */
                           unsigned char    :2;         /*              */
                           unsigned char AF :1;         /*    AF        */
                           }      BIT;                  /*              */
                    }           RCR1;                   /*              */
              char              wk14;                   /*              */
              union {                                   /* RCR2         */
                    unsigned char BYTE;                 /*  Byte Access */
                    struct {                            /*  Bit  Access */
                           unsigned char PEF  :1;       /*    PEF       */
                           unsigned char PES  :3;       /*    PES       */
                           unsigned char RTCEN:1;       /*    RTCEN     */
                           unsigned char ADJ  :1;       /*    ADJ       */
                           unsigned char RESET:1;       /*    RESET     */
                           unsigned char START:1;       /*    START     */
                           }      BIT;                  /*              */
                    }           RCR2;                   /*              */
};

#define RTC   (*(volatile struct st_rtc   *)0xFFFFFEC0) /* RTC	 Address*/

int RTCReadHour()
{
	int hour;
	RTC.RCR1.BIT.CIE = 0;
	RTC.RCR1.BIT.CF = 0;
	hour = (RTC.RHRCNT.BIT.H10 * 10) + RTC.RHRCNT.BIT.H1;
	return hour;
}

int RTCReadMinute()
{
	int minute;
	RTC.RCR1.BIT.CIE = 0;
	RTC.RCR1.BIT.CF = 0;
	minute = (RTC.RMINCNT.BIT.M10 * 10) + RTC.RMINCNT.BIT.M1;
	return minute;
}

int RTCReadSecond()
{
	int second;
	RTC.RCR1.BIT.CIE = 0;
	RTC.RCR1.BIT.CF = 0;
	second = (RTC.RSECCNT.BIT.S10 * 10) + RTC.RSECCNT.BIT.S1;
	return second;
}

int time()
{
	return RTCReadHour()*3600 + RTCReadMinute()*60 + RTCReadSecond();
}
