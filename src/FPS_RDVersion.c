#include<header.h>
void FPS_RD_version()
{

	FILE *fp=NULL;
	char Buff[24]="";
	memset(module.FPSRDVer,0x00,sizeof(module.FPSRDVer));

	system("cat /home/rdservice/config/config.ini  | grep rd_ver | cut -d '=' -f2 > /tmp/.RHMSRDVersion.info");

	fp = fopen("/tmp/.RHMSRDVersion.info","r");
	if ( fp == NULL ) 
	{
		strcpy(module.FPSRDVer,"NotFound");
		fprintf(stderr,"/tmp/.RHMSRDVersion.info file not found\n");
		return;
	}

	fread(Buff,24,1,fp);

	sscanf(Buff,"%s",module.FPSRDVer);

	fclose(fp);

	remove("/tmp/.RHMSRDVersion.info");

	if(strlen(module.FPSRDVer) == 0)	
		strcpy(module.FPSRDVer,"NotFound");

	fprintf(stdout," FPSRDVer_Buff = %s\tmodule.FPSRDVer = %s\n",Buff,module.FPSRDVer);
	return;
}
/*int main()
{

	FPS_RD_version();

}*/
