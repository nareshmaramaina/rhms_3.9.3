#include<header.h>
void Iris_version()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0;
	fp = fopen("/etc/iritech_rd_info.txt","r");
	if ( fp == NULL ) 
	{
		strcpy(module.IritechRDVer,"ERROR");
		fprintf(stderr,"/etc/iritech_rd_info.txt file not found\n");
		return;
	}
	memset(module.IritechRDVer,0x00,sizeof(module.IritechRDVer));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"IRITECH_RD V") != NULL)
		{

			sscanf(line+12,"%s",module.IritechRDVer);
		}
	}
	if(strlen(module.IritechRDVer) == 0)	
		strcpy(module.IritechRDVer,"ERROR");

	fprintf(stdout," RD_VERSION_BUFF = %s\tmodule.IritechRDVer = %s \n",line,module.IritechRDVer);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
/*int main()
  {

  Iris_version();

  }*/
