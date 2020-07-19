#include "header.h"

int PinpadSerialNo_info_by_dev_name(char *port, unsigned char *serialno)
{


	int resp = 0, ret = 0;


	ret = PINPAD_ModemOpen (port);

	if (ret != 0)
		return -1;

	resp = handshake ();

	ret = print_error_resp (resp);
	if (ret != 0)
	{
		PINPAD_Modemclose ();
		return -1;
	}

	Get_Pinpad_Serial_No(serialno);
	printf("Pinpad_SerialNo:%s\n",serialno);


	PINPAD_Modemclose ();

	return 0;

}
int main()
{
	unsigned char serialno[64];
	short int tries = 5, ret;

	while ( tries-- )
	{
		memset(serialno,0,sizeof(serialno));

		ret = PinpadSerialNo_info_by_dev_name("/dev/ttyACM0", serialno);
		if ( ret == 0  ) 
			break;

		ret = PinpadSerialNo_info_by_dev_name("/dev/ttyACM1", serialno);
		if ( ret == 0  ) 
			break;
		sleep(1);
	}
	if ( strlen((char*) serialno) != 0 ) 
		printf("Pinpad_SerialNo:%s\n",serialno);
	return 0;
}
