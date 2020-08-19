#include<header.h>
void RHMSAppVersionDetails()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0,sizeofBuffer=0;
	fp = fopen("/etc/vision/RHMS/RHMSClientversion.info","r");
	if ( fp == NULL )
	{
		strcpy(module.RHMSClientVersion,"NotFound");
		fprintf(stderr,"/etc/vision/RHMS/RHMSClientversion.info file not found\n");
		return;
	}
	memset(module.RHMSClientVersion,0x00,sizeof(module.RHMSClientVersion));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"Version:") != NULL)
		{
			 sizeofBuffer = sizeof(module.RHMSClientVersion);
                        if( strlen(line+8) > sizeofBuffer )
                        {
                                fprintf(stderr,"Invalid: RHMSClientVersion Length More than %d bytes \n",sizeofBuffer);
                                continue;
                        }

			strcpy(module.RHMSClientVersion,line+8);
			if(module.RHMSClientVersion[strlen(module.RHMSClientVersion)-1] == '\n')
				module.RHMSClientVersion[strlen(module.RHMSClientVersion)-1]='\0';

			break;
		}
	}
	if(strlen(module.RHMSClientVersion) == 0)
		strcpy(module.RHMSClientVersion,"NotFound");

	fprintf(stdout," FPSRDVer_BUFF = %s\tmodule.RHMSClientVersion = %s \n",line,module.RHMSClientVersion);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
