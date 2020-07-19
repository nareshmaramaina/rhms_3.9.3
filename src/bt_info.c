#include<header.h>
int bluetooth_status()
{
	int ret;
	memset(module.Bluetooth,0,sizeof(module.Bluetooth));

	ret = gl11_bluetooth_control_dlopen(1); 
	sleep(1);
	if(ret < 0)
	{
		fprintf(stderr,"Bluetooth Poweron Failed\n");
		strcpy(module.Bluetooth,"ERROR");
		return -1;
	}


	ret = check_presence(3);
	if(ret == 0)
	{
		strcpy(module.Bluetooth,"OK");
		printf("module.Bluetooth = %s\n",module.Bluetooth);
		return 0;
	}

	else
	{
		fprintf(stderr,"Bluetooth not found After power on \n");
		strcpy(module.Bluetooth,"ERROR");
		return -1;
	}


}

int  check_presence(int times)
{
	int bt_check=-1,i;

	for (i=0; i < times ;i++)
	{

		bt_check = usb_device_presence("0a12","0001");
		if( bt_check == 0)
			return 0;
		else
			printf("Bluetooth not found usb_device_presence = %d\n",bt_check);	

		sleep(1);
	}	
	return -1;
}

