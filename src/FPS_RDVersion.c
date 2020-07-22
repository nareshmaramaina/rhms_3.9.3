#include<header.h>
void FPS_RD_version()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0;
	fp = fopen("/etc/rd_info.txt","r");
	if ( fp == NULL ) 
	{
		strcpy(module.FPSRDVer,"Not Found");
		fprintf(stderr,"/etc/rd_info.txt file not found\n");
		return;
	}
	memset(module.FPSRDVer,0x00,sizeof(module.FPSRDVer));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"RD-SDK") != NULL)
		{

			sscanf(line+8,"%s",module.FPSRDVer);
		}
	}
	if(strlen(module.FPSRDVer) == 0)	
		strcpy(module.FPSRDVer,"Not Found");

	fprintf(stdout," FPSRDVer_BUFF = %s\tmodule.FPSRDVer = %s \n",line,module.FPSRDVer);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
/*int main()
{

	RD_version();

}*/
