#include <header.h>

int PinpadSerialNo_info_by_dev_name(char *port)
{

	int resp = 0, ret = 0;

	char serialno[64]="";

	ret = PINPAD_ModemOpen (port);

	if (ret < 0)
	{
		printf ("%s modem open failed \n",port);
		strcpy(module.PinpadSN,"ERROR");
		return -1;
	}

	resp = handshake ();

	ret = print_error_resp (resp);
	if (ret < 0)
	{
		strcpy(module.PinpadSN,"ERROR");
		printf ("%s modem open failed While handshake \n",port);
		PINPAD_Modemclose ();
		return -1;
	}

	Get_Pinpad_Serial_No((unsigned char *)serialno);
	
	if( strlen(serialno) == 0 )
		strcpy(module.PinpadSN,"ERROR");
	else 
		strcpy(module.PinpadSN,serialno);
	
	fprintf(stdout," module.PinpadSN = %s, serialno = %s\n",module.PinpadSN,serialno);

	PINPAD_Modemclose ();

	return 0;

}


/*int main()
{

 PinpadSerialNo_info_by_dev_name("/dev/ttyACM0");
 PinpadSerialNo_info_by_dev_name("/dev/ttyACM1");
return 0;
}*/
