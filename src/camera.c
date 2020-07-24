#include<header.h>


int  verify_presence(int times)
{
	int cam_check=-1,i;

	for (i=0; i<times ;i++)
	{

		cam_check = usb_device_presence("090c","37d0");
		if( cam_check == 0)
		{
			printf("Cam found \n");
			strcpy(module.Camera,"Yes");
			printf("module.Camera is OK\n");
			return 0;
		}
		else
			printf("Camera not found usb_device_presence = %d\n",cam_check);	

			strcpy(module.Camera,"No");

	}	
	return -1;

}

int camera_status()
{
	int ret=0;
	memset(module.Camera,0,sizeof(module.Camera));

	ret = verify_presence(5);
	if(ret==0)
	{
		printf("camera found\n");
		return 0;
	}

	ret = gl11_cam_control(1);
	printf("Cam pwr_on = %d\n",ret);
	sleep(1);
	if(ret < 0)
	{
		fprintf(stderr,"Camera Poweron Failed\n");
		strcpy(module.Camera,"No");
		return -1;

	}

	ret = verify_presence(10);
	if(ret == 0)
	{
		printf("camera found\n");
		gl11_cam_control(0);
		return 0;

	}
	else
	{
		fprintf(stderr,"Camera not found After power on \n");
		return -1;
	}




}
