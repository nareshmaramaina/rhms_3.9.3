#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int PINPAD_ModemOpen(char * );
int  (*PINPAD_Modemclose) (void);
int (*handshake)(void);
int (*Get_Pinpad_Serial_No)(unsigned char *);
int (*print_error_resp) (int );
//int   PinpadSerialNo_info_by_dev_name(char *,unsigned char *serialno);
