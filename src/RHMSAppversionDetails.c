#include<header.h>
void RHMSAppVersionDetails()
{

	FILE *fp=NULL;
	char line[32]="";
	fp = fopen("/etc/vision/RHMS/RHMSClientversion.info","r");
	if ( fp == NULL )
	{
		strcpy(module.RHMSClientVersion,"NotFound");
		fprintf(stderr,"/etc/vision/RHMS/RHMSClientversion.info file not found\n");
		return;
	}
	memset(module.RHMSClientVersion,0x00,sizeof(module.RHMSClientVersion));

	fread(line,sizeof(line),1,fp);

	fclose(fp);

	if( strstr(line,"Version:") != NULL)
		sscanf(line+8,"%s",module.RHMSClientVersion);

	if(strlen(module.RHMSClientVersion) == 0)
		strcpy(module.RHMSClientVersion,"NotFound");

	fprintf(stdout,"line = %s\tmodule.RHMSClientVersion = %s \n",line,module.RHMSClientVersion);
	return;
}
