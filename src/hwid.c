#include<header.h>
void HardwareID_Details()
{

	short int ret=0,i;
	FILE *fp=NULL;

	for ( i=0; i< 5;i++)
	{
		ret = system("fw_printenv  hwid | cut -d '=' -f2 > /tmp/.RHMSHardwareID");

		if ( ret == 0)
			break;

		sleep(1);
	}

	fp = fopen("/tmp/.RHMSHardwareID", "r");

	if(fp ==NULL)
	{
		strcpy(module.HardwareIDExists,"No");
		fprintf(stderr,"LIB#Unable To Open The /tmp/.RHMSHardwareID\n");
		return;

	}

	fscanf(fp,"%s",module.HardwareID);
	fclose(fp);
	remove("/tmp/.RHMSHardwareID");
	if( strlen(module.HardwareID) == 0 )
		strcpy(module.HardwareIDExists,"No");
	else strcpy(module.HardwareIDExists,"Yes");
	fprintf(stdout," module.HardwareIDExists %s module.HardwareID %s \n",module.HardwareIDExists,module.HardwareID);
	return;
}

