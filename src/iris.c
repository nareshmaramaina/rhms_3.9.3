#include<header.h>

int iris_status(void)
{
	int iris_check,i;
	memset(module.IRIS,0,sizeof(module.IRIS));

	for (i=0; i < 2  ;i++)
	{

		iris_check =  usb_device_presence("2863","3399"); //biomatic

		if( iris_check == 0)
		{
			strcpy(module.IRIS,"Biomatiques");
			printf("Biomatiques  FOUND\n");
			return 0;
		}
		else if( ( iris_check =  usb_device_presence("1f63","f001") ) == 0)  //iritek
		{
			strcpy(module.IRIS,"Iritech");
			printf("Iritech  FOUND\n");
			return 0;
		}

		else
		{ 
			fprintf(stderr,"%d Iritech/Biomatiques not found usb_device_presence = %d\n",i,iris_check);	
			strcpy(module.IRIS,"NotConnected");
		}
		sleep(1);
	}

	return -1;
}

