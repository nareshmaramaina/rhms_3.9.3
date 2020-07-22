#include<header.h>
void Biomatiques_RD_version()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0;
	fp = fopen("/etc/Biomatiques_rd_info.txt","r");
	if ( fp == NULL ) 
	{
		strcpy(module.BiomRDVer,"Not Found");
		fprintf(stderr,"/etc/Biomatiques_rd_info.txt file not found\n");
		return;
	}
	memset(module.BiomRDVer,0x00,sizeof(module.BiomRDVer));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"Biomatiques") != NULL)
		{

			sscanf(line+16,"%s",module.BiomRDVer);
		}
	}
	if(strlen(module.BiomRDVer) == 0)	
		strcpy(module.BiomRDVer,"Not Found");

	fprintf(stdout," BiomRDVer_BUFF = %s\tmodule.BiomRDVer = %s \n",line,module.BiomRDVer);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
/*int main()
{

	RD_version();

}*/
