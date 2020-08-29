#include<header.h>
void HardwareID_Details()
{

	FILE *fp=NULL;
	char Buff[30]="";

	system("fw_printenv  hwid | cut -d '=' -f2 > /tmp/.RHMSHardwareID");


	fp = fopen("/tmp/.RHMSHardwareID", "r");

	if(fp ==NULL)
	{
		strcpy(module.HardwareIDExists,"No");
		fprintf(stderr,"LIB#Unable To Open The /tmp/.RHMSHardwareID\n");
		return;

	}
	fread(Buff,30,1,fp);
	sscanf(Buff,"%s",module.HardwareID);

	fclose(fp);
	remove("/tmp/.RHMSHardwareID");

	if( strlen(module.HardwareID) == 0 )
		strcpy(module.HardwareIDExists,"No");
	else strcpy(module.HardwareIDExists,"Yes");

	fprintf(stdout," module.HardwareIDExists %s module.HardwareID %s \n",module.HardwareIDExists,module.HardwareID);
	return;
}

