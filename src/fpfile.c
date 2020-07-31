#include<header.h>

void update_fpfile_info(void)
{

	char buff[35]={0x00};
	FILE *fp;
	int ret=0;
	fp=popen("dmesg | grep -A 1 'SAGEM SA' | tail -n 1 | sed 's/.*SerialNumber: //'","r");
	fread(buff,21,1,fp);
	fclose(fp);
	printf("scanner id = %s\n",buff);
	ret = fp_detect_type();

	if(ret == CAPACITIVE)
	{
		sprintf(module.FP_TYPE,"Capacitive");
		capacitive_scanner_id();	

	}
	else if(ret == OPTICAL)
	{
		sprintf(module.FP_TYPE,"Optical");
		optical_scanner_id();
	}
	else
	{
		strcpy(module.FPScanneridExists,"Error");
		fprintf(stderr,"Scanner Not Found\n");
		sprintf(module.FP_TYPE,"Not-Detected");
	}

	return;
}

int fp_detect_type(void)
{

	int ret,i=0;
	int usb_check=0;
	int flag_cp_op=0;


	for(i=0;i<3;i++)
	{
		ret=gl11_optcap_pwron();
		if(ret==0)
			break;
		msleep(100);

	}

	if(ret != 0)
	{
		printf("finger print poweron failed\n");
		return -1;
	}

	msleep(200);

	for ( i=0; i<28; i++)
	{

		usb_check = usb_device_presence("147e","2016");
		if (usb_check == 0)
		{
			flag_cp_op = 1;
			break;
		}
		else
		{
			usb_check=usb_device_presence("079b","0047");
			if ( usb_check == 0)
			{
				flag_cp_op=2;
				break;
			}
		}
		msleep(200);
	}


	if(usb_check == 0 && flag_cp_op == 1 )
	{
		fprintf(stdout,"Capactive Scanner Detected\n");
		return CAPACITIVE;
	}

	else  if(usb_check == 0 && flag_cp_op == 2 )
	{
		fprintf(stdout,"Optical Scanner Detected\n");
		return OPTICAL;
	}
	else
		return NO_DEVICE;

}
