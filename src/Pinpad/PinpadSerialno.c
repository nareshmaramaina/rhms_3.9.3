#include "header.h"

int PinpadSerialNo_info_by_dev_name(char *port)
{

	int resp = 0, ret = 0;

	char serialno[64]="";

	ret = PINPAD_ModemOpen (port);

	if (ret < 0)
		return -1;

	resp = handshake ();

	ret = print_error_resp (resp);
	if (ret < 0)
	{
		PINPAD_Modemclose ();
		return -1;
	}

	Get_Pinpad_Serial_No((unsigned char *)serialno);
	
	if ( strlen(serialno) != 0 )
	fprintf(stdout,"Pinpad_SerialNo:%s\n",serialno);

	PINPAD_Modemclose ();

	return 0;

}


int main()
{
	short int ret= -1,tries = 5;

	while(--tries )
	{
		ret = PinpadSerialNo_info_by_dev_name("/dev/ttyACM0");
		if ( ret == 0 )
			return 0;

		PinpadSerialNo_info_by_dev_name("/dev/ttyACM1");
		if ( ret == 0 )
			return 0;

		sleep(1);

	}
	return -1;
}
