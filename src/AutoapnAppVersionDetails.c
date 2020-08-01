#include<header.h>
void AutoapnAppVersionDetails()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0;
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
			strcpy(module.AutoapnAppVersion,line+8);
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
