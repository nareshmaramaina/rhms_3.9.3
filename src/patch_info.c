#include <header.h>

int FirmwareDetails()
{
	FILE *fp = NULL;

	char *line=NULL,*str=NULL;

	size_t len=20,sizeofBuffer=0;
	char buff[128]="";
	fp = fopen("/etc/vision/RHMS/Firmware/FirmwareUpdated.info","r");
	if(fp == NULL)
	{
		fprintf(stdout,"Firmware Details Unavailable\n");
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



