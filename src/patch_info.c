#include <header.h>
char ServerProjectName[128];

int FirmwareDetails()
{
	char *Server_Firmware_release_file="/etc/vision/RHMS/Firmware/ServerFirmwareRelease.info";
	FILE *fp = NULL;
	char *line=NULL,*str=NULL;
	size_t len=20,sizeofBuffer=0;
	char buff[128]="";
	char Device_Firmware_release_file[400];
	char ServerFirmwareName[128]="";

	fp = fopen(Server_Firmware_release_file,"r");
	if(fp == NULL)
	{
		fprintf(stdout," %s  file not found \n",Server_Firmware_release_file);
		strcpy(module.FirmwareVersion,"NotFound");
		strcpy(module.FirmwareName,"NotFound");
		return -1;
	}

	while (  ( getline(&line, &len, fp) ) > 0)
	{

		if((str = (char *)strstr(line,"ProjectName:")) != NULL)
		{
			memset(ServerProjectName,0,sizeof(ServerProjectName));
			sizeofBuffer = sizeof(ServerProjectName);
			if( strlen(str+12) > sizeofBuffer )
			{
				fprintf(stderr,"Invalid: ServerProjectName Length More than %d bytes \n",sizeofBuffer);
				continue;
			}
			strcpy(ServerProjectName,str+12);
			if(ServerProjectName[strlen(ServerProjectName)-1] == '\n')
				ServerProjectName[strlen(ServerProjectName)-1]='\0';

		}
		else if((str = (char *)strstr(line,"FirmwareName:")) != NULL)
		{
			sizeofBuffer = sizeof(ServerFirmwareName);
			if( strlen(str+13) > sizeofBuffer )
			{
				fprintf(stderr,"Invalid: ServerFirmwareName Length More than %d bytes \n",sizeofBuffer);
				continue;
			}

			strcpy(ServerFirmwareName,str+13);
			if(ServerFirmwareName[strlen(ServerFirmwareName)-1] == '\n')
				ServerFirmwareName[strlen(ServerFirmwareName)-1]='\0';

		}

	}

	free(line);
	line=NULL;
	str=NULL;
	fclose(fp);


	memset( Device_Firmware_release_file,0,sizeof(Device_Firmware_release_file) );
	sprintf(Device_Firmware_release_file,"/etc/vision/RHMS/Firmware/%s/%s/FirmwareUpdated.info",ServerProjectName,ServerFirmwareName);
	fp = fopen(Device_Firmware_release_file,"r");
	if(fp == NULL)
	{
		fprintf(stdout," %s  file not found \n",Device_Firmware_release_file);
		strcpy(module.FirmwareVersion,"NotFound");
		strcpy(module.FirmwareName,"NotFound");
		return -1;
	}
	while((getline(&line, &len, fp)) > 0)
	{
		if((str = (char *)strstr(line,"FirmwareName:")) != NULL)
		{
			sizeofBuffer = sizeof(module.FirmwareName); 
			if( strlen(str+13) > sizeofBuffer ) 
			{
				fprintf(stderr,"Invalid: FirmwareName Length More than %d bytes \n",sizeofBuffer);
				continue;
			}
			memset(buff,0,sizeof(buff));	
			strcpy(buff,str+13);
			if(buff[strlen(buff)-1] == '\n')
				buff[strlen(buff)-1]='\0';

			strcpy(module.FirmwareName,buff);
		}
		else if((str = (char *)strstr(line,"Version:")) != NULL)
		{
			sizeofBuffer = sizeof(module.FirmwareVersion); 
			if( strlen(str+8) > sizeofBuffer ) 
			{
				fprintf(stderr,"Invalid: Firmware Version Length More than %d bytes \n",sizeofBuffer);
				continue;
			}
			memset(buff,0,sizeof(buff));	
			strcpy(buff,str+8);
			if(buff[strlen(buff)-1] == '\n')
				buff[strlen(buff)-1]='\0';

			strcpy(module.FirmwareVersion,buff);
		}

	}
	free(line);
	line=NULL;
	str=NULL;
	fclose(fp);
	return 0;
}


