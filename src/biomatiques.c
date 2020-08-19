#include<header.h>
void Biomatiques_RD_version()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0,sizeofBuffer=0;
	fp = fopen("/etc/Biomatiques_rd_info.txt","r");
	if ( fp == NULL ) 
	{
		strcpy(module.BiomRDVer,"NotFound");
		fprintf(stderr,"/etc/Biomatiques_rd_info.txt file not found\n");
		return;
	}
	memset(module.BiomRDVer,0x00,sizeof(module.BiomRDVer));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"Biomatiques") != NULL)
		{
			sizeofBuffer = sizeof(module.BiomRDVer);
			if( strlen(line+16) > sizeofBuffer )
			{
				fprintf(stderr,"Invalid: BiomRDVer Length More than %d bytes \n",sizeofBuffer);
				continue;
			}
			 sscanf(line+16,"%s",module.BiomRDVer);
		}
	}
	if(strlen(module.BiomRDVer) == 0)	
		strcpy(module.BiomRDVer,"NotFound");

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
