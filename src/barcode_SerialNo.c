#include<header.h>
void  barcode_SerialNo()
{
	short int ret=-1, tries = 3;
	char serialno[32];

	//idVendor=2010, idProduct=7638

	memset(module.BarcodeSno,0,sizeof(module.BarcodeSno));
	memset(module.BarcodeSnoExists,0,sizeof(module.BarcodeSnoExists));

	while( tries-- )
	{
		memset(serialno,0,sizeof(serialno));

		ret = get_Usb_device_serialno("2010","7638",serialno);

		if( ret == 0)
		{
			strcpy(module.BarcodeSnoExists,"Found");
			strcpy(module.BarcodeSno,serialno);
			printf("Barcode Scanner found, Serial No %s \n",module.BarcodeSno);
			return;
		}


		sleep(1);
		fprintf(stdout,"Barcode not found, retrying\n");

	}
	strcpy(module.BarcodeSnoExists,"NotFound");
	return;

}

