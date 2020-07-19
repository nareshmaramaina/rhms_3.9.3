#include<header.h>
void  barcode_SerialNo()
{
	short int ret=-1, tries = 5;
	char serialno[32];

	//idVendor=2010, idProduct=7638
	while( tries-- )
	{
		memset(serialno,0,sizeof(serialno));

		ret = get_Usb_device_serialno("2010","7638",serialno);

		if( ret == 0)
		{
			strcpy(module.BarcodeSno,serialno);
			printf("Barcode Scanner found, Serial No %s \n",module.BarcodeSno);
			return;
		}

		strcpy(module.BarcodeSno,"ERROR");
	
		sleep(2);
		fprintf(stdout,"Barcode not found, retrying\n");

	}
	return;

}

