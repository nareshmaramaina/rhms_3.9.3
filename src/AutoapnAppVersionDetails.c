#include<header.h>
void AutoapnAppVersionDetails()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0,sizeofBuffer=0;
	fp = fopen("/etc/vision/autoapn/ver.info","r");
	if ( fp == NULL )
	{
		strcpy(module.AutoapnAppVersion,"NotFound");
		fprintf(stderr,"/etc/vision/autoapn/ver.info file not found\n");
		return;
	}
	memset(module.AutoapnAppVersion,0x00,sizeof(module.AutoapnAppVersion));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"Version:") != NULL)
		{
		 sizeofBuffer = sizeof(module.AutoapnAppVersion);
                        if( strlen(line+8) > sizeofBuffer )
                        {
                                fprintf(stderr,"Invalid: AutoapnAppVersion Length More than %d bytes \n",sizeofBuffer);
                                continue;
                        }
		
			strcpy(module.AutoapnAppVersion,line+8);
			if(module.AutoapnAppVersion[strlen(module.AutoapnAppVersion)-1] == '\n')
				module.AutoapnAppVersion[strlen(module.AutoapnAppVersion)-1]='\0';

			break;
		}
	}
	if(strlen(module.AutoapnAppVersion) == 0)
		strcpy(module.AutoapnAppVersion,"NotFound");

	fprintf(stdout," FPSRDVer_BUFF = %s\tmodule.AutoapnAppVersion = %s \n",line,module.AutoapnAppVersion);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
