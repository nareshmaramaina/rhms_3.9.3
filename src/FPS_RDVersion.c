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
void FPS_RD_SDK_version()
{

	FILE *fp=NULL;
	char line[80]="",*str=NULL;
	size_t sizeofBuffer=0;
	fp = fopen("/etc/rd_info.txt","r");
	if ( fp == NULL ) 
	{
		strcpy(module.FPS_RD_SDK_Ver,"NotFound");
		fprintf(stderr,"/etc/rd_info.txt file not found\n");
		return;
	}
	memset(module.FPS_RD_SDK_Ver,0x00,sizeof(module.FPS_RD_SDK_Ver));
	while( fgets(line,sizeof(line),fp) != NULL )
	{
		if(  ( str =  strstr(line,"RD-SDK")  ) != NULL)
		{
			sizeofBuffer = sizeof(module.FPS_RD_SDK_Ver); 
			if( strlen(str+8) > sizeofBuffer ) 
				fprintf(stderr,"Invalid: FPS_RD_SDK_Ver Length More than %d bytes \n",sizeofBuffer);
			else 
				sscanf(str+8,"%s",module.FPS_RD_SDK_Ver);
			break;

		}
		memset(line,0,sizeof(line));
	}
	if(strlen(module.FPS_RD_SDK_Ver) == 0)	
		strcpy(module.FPS_RD_SDK_Ver,"NotFound");

	fprintf(stdout," FPS_RD_SDK_Ver_BUFF = %s\tmodule.FPS_RD_SDK_Ver = %s\n",line,module.FPS_RD_SDK_Ver);
	fclose(fp);
	return;
}
/*int main()
{
	FPS_RD_SDK_version();
}*/
