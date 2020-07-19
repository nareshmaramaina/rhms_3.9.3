#include <header.h>

int pendrive_test(int);
int usb_details(void);
	//int main()
int update_usb_info()
{

	FILE *fp4;
	char str[100]="";
	int flag=0, ret = -1;

	memset(str,0x00,100);

	fp4=fopen("/proc/partitions","r");
	if ( fp4 == NULL )
		return -1;

	while((fgets(str,80,fp4))!=NULL)
	{
		if((strstr(str,"sda1")) != NULL)
		{
			fprintf(stdout,"USB sda1 Device file found\n");
			flag=2;
			break;
		}


		else if((strstr(str,"sda")) != NULL)
		{
			flag=1;
			fprintf(stdout,"USB sda Device file found\n");
		}	


	}

	fclose(fp4);

	if (flag == 0)
	{	
		strcpy(module.Usbdevice.Total,"Not Found");
		strcpy(module.Usbdevice.Use,"Not Found");
		strcpy(module.Usbdevice.Free,"Not Found");
	}
	else 
	{
		mkdir_p("/mnt/usb_test");	
		ret = pendrive_test(flag);


		if( ret != 0 )
		{	
			strcpy(module.Usbdevice.Total,"Not Mounting");
			strcpy(module.Usbdevice.Use,"Not Mounting");
			strcpy(module.Usbdevice.Free,"Not Mounting");
		}
	}

	fprintf(stdout,"USB Memory Total= %s Use= %s Free=%s\n",module.Usbdevice.Total,module.Usbdevice.Use,module.Usbdevice.Free);
	return 0;
}

int pendrive_test(int partition_flag)
{
	int ret=0;
	FILE *fp3;
	char str[100]="";
	int flag=0;

	memset(str,0x00,100);
	fp3=fopen("/etc/mtab","r");
	if (fp3==NULL)
		return -1;

	while((fgets(str,80,fp3))!=NULL)
	{
		if((strstr(str,"/mnt/usb_test")) != NULL)
		{
			flag=1;
			break;
		}
	}
	fclose(fp3);


	if(flag == 0)
	{
		fprintf(stdout," Checking ...\n");
		if(partition_flag == 1)
			ret=system("mount /dev/sda /mnt/usb_test");
		else if(partition_flag == 2)
			ret=system("mount /dev/sda1 /mnt/usb_test");

		if(ret!=0)
		{
			fprintf(stdout,"mount failed\n");
			return -2;
		} 

	}
	ret = update_pendrive_details();


	if(flag == 0)
		system("umount /mnt/usb_test");

	return ret;
}


int update_pendrive_details(void)
{

	char  *line=NULL;
	size_t len=0;
	FILE *fp=NULL;

	char Partition[24];
	int success_flag=0;


	system("df  -h | grep /dev/sda > /tmp/.USB_details");

	fp = fopen("/tmp/.USB_details","r");
	if ( fp == NULL )
		return -1;

	while(getline(&line, &len, fp)> 0)
	{
		if(strstr(line,"/mnt/usb_test") != NULL)
		{
			sscanf(line,"%s%s%s%s",Partition,module.Usbdevice.Total,module.Usbdevice.Use,module.Usbdevice.Free);
			success_flag=1;
			break;
		}
	}

	fclose(fp);
	free(line);
	line = NULL;
	remove("/tmp/.USB_details");

	if(success_flag)
		return 0;
	else
		return -1;
}

int usb_device_presence (char *vendor_id, char *product_id)
{
	FILE *fp=NULL;

	char tmp_buf[80]="";

	int ver_flag=0;

	char info[512]="";

	memset(tmp_buf,0x00,80);

	sprintf(tmp_buf,"Vendor=%s ProdID=%s",vendor_id,product_id);

	fp=fopen("/proc/bus/usb/devices","r");

	if (fp == NULL)
		return -1;


	while (fgets(info, sizeof(info), fp) != NULL )
	{

		if (strstr(info,"Vendor="))
		{
			if (strstr(info,tmp_buf))
			{
				ver_flag=1;
				break;
			}

		}
	}

	fclose(fp);

	if (ver_flag)
		return 0;
	else
		return -1;
}
