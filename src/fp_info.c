#include <header.h>

void optical_scanner_id(void)
{
	char buffer[50]="";

	short int ret=0,i;
	for(i = 0 ; i< 3 ;i++)
	{
		ret = opt_scanner_id(buffer);
		if (ret == 0)
			break;
		msleep(500);
	}

	memset(module.scanner_id,0x00,sizeof(module.scanner_id));
	if(ret == 0)
		strcpy(module.scanner_id,buffer);
	else
	{
		fprintf(stderr,"optical_scanner_id (module.scanner_id ) is %s\n",module.scanner_id);
		strcpy(module.scanner_id,"ERROR");
	}
	return;
}

int opt_scanner_id(char *opt_id)
{
	char *str=NULL;
	FILE *fp=NULL;
	int flag=0;
	size_t len=0;

	fp=fopen("/proc/bus/usb/devices","r");
	if(fp==NULL)
	{
		fprintf(stderr,"error /proc/bus/usb/devices opening the log\n");
		return -1;
	}

	memset(opt_id,0x0,sizeof(opt_id));

	while((getline(&str,&len,fp))!=-1)
	{
		if ( (strstr(str,"Product=SAGEM MORPHOSMART") ) != NULL )
		{
			getline(&str,&len,fp);
			if ( strstr(str,"SerialNumber=") != NULL )
			{
				fprintf(stdout,"Optical Buff = %s\n",str);

				strncpy(opt_id,str+17,21);
				opt_id[22]='\0';
				flag=1;
			}
			break;
		}
	}
	free(str);
	str=NULL;
	fclose(fp);

	if(flag == 0)
		return -1;

	return 0;
}
void capacitive_scanner_id(void)
{
	char buffer[50]="";
	short int ret=0,i;
	
	memset(module.scanner_id,0x00,sizeof(module.scanner_id));

	for(i = 0 ; i< 3 ;i++)
	{
		ret = cap_scanner_id(buffer);
		if (ret == 0)
			break;
		msleep(500);
	}


	if(ret == 0)
		strcpy(module.scanner_id,buffer);
	else
	{
		fprintf(stderr,"optical_scanner_id (module.scanner_id ) is %s\n",module.scanner_id);
		strcpy(module.scanner_id,"ERROR");
	}
	return;
}

int cap_scanner_id(char *cap_id)
{
	int Status = 0, i = 0;
	PT_CHAR dsn[] = "usb,vid=0x147e,pid=0x2016";
	PT_CONNECTION   handle;
	PT_EXTENDED_INFO *pExtInfo = NULL ;
	Status = PTInitialize(NULL);
	if (0 != Status) {
		fprintf(stderr,"\n PTInitialize :Initialize the PTAPI library failed");
		fflush(stdout);
		return -1;
	}
	/*  Open a new connection to a FM connected to this host */
	Status = PTOpen(dsn, &handle);
	if (0 != Status) {
		fprintf(stderr,"\n PTOpen:Open a new connection to a FM connected to this host failed"); fflush(stdout);
		return -1;
	}
	Status = PTExtendedInfo (handle,&pExtInfo);
	if(Status != 0)
	{
		sprintf(module.scanner_id,"ERROR");
		fprintf(stderr,"ret of PTExtendedInfo : %d\n",Status);
		return -1;
	}
	for(i=0; i<16; i++)
	{
		printf("%02X",pExtInfo->GUID[i]);
		sprintf(cap_id+(2*i),"%02X",pExtInfo->GUID[i]);

	}
	printf("\n");


	/*Close a connection previously opened by PTOpen()*/
	Status = PTClose(handle);
	if (0 != Status)
		fprintf(stderr,"PTClose :Close a connection previously opened by PTOpen() failed");
	/* Unintialize the PTAPI library */
	Status = PTTerminate();
	if (0 != Status)
		fprintf(stderr,"PTTerminate : Uninitialize the PTAPI library failed");
	return 0;
}

int fp_type(void)
{
	FILE *fpr = NULL;
	struct stat sb;
	char *buf = NULL;
	int ret = 0;

	sleep(4);

	system ("cat /proc/bus/usb/devices > /mnt/jffs2/finger_print");

	msleep(500);

	fpr = fopen("/mnt/jffs2/finger_print","r");

	if(fpr==NULL)
	{
		perror("fopen");
		return -1;
	}
	stat("/mnt/jffs2/finger_print",&sb);

	buf=(char *)calloc(1,sb.st_size);
	if(buf==NULL) 
	{
		perror("calloc:");
		return -1;
	}

	fread(buf,1,sb.st_size,fpr);

	if ( strstr(buf,"SAGEM") != NULL )
	{
		remove("/usr/lib/libbiometric.so");
		symlink("/usr/lib/liboptical_wrappers.so","/usr/lib/libbiometric.so");
		ret = OPTICAL;
	}
	else if( strstr(buf,"UPEK") != NULL ) 
	{
		remove("/usr/lib/libbiometric.so");
		symlink("/usr/lib/libbiometric_INN.so","/usr/lib/libbiometric.so");
		ret = CAPACITIVE;
	}

	else
		ret = NO_DEVICE;

	free(buf);
	fclose(fpr);

	return ret;
}

int  update_fp_scanner_info(void)
{
	int ret = 0;

	memset(module.FP_TYPE,0,sizeof(module.FP_TYPE));
	memset(module.scanner_id,0x00,sizeof(module.scanner_id));

	ret = fp_type();

	if(ret == 1)
	{
		fprintf(stdout,"Optical Scanner Detected\n");

		sprintf(module.FP_TYPE,"OK/Optical");

		optical_scanner_id();

		return 0;
	}
	else if(ret == 2)
	{
		fprintf(stdout,"Capacitive Scanner detected\n");

		sprintf(module.FP_TYPE,"OK/Capacitive");

		capacitive_scanner_id();

		return 0;

	}

	else
	{
		fprintf(stdout,"Scanner Not Detected\n");
	
		sprintf(module.FP_TYPE,"ERROR/ERROR");
	
		return -1;
	}

}


