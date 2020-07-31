#include<header.h>
void FPS_Id_and_version()
{

	FILE *fp=NULL;
	char *line=NULL;
	size_t len=0;
	fp = fopen("/etc/scanner_type","r");
	if ( fp == NULL ) 
	{
		strcpy(module.FPScanneridExists,"Error");
		sprintf(module.FP_TYPE,"Not-Detected");
		fprintf(stderr,"/etc/scanner_type file not found\n");
		return;
	}
	memset(module.scanner_id,0x00,sizeof(module.scanner_id));
	while( getline(&line,&len,fp) != -1 )
	{
		if( strstr(line,"ScannerType:OPTICAL") != NULL)
			sprintf(module.FP_TYPE,"Optical");
		else if( strstr(line,"ScannerType:CAPACITIVE") != NULL)
			sprintf(module.FP_TYPE,"Capacitive");
		if( strstr(line,"ScannerID:") != NULL)
		{
			strcpy(module.FPScanneridExists,"Yes");
			sscanf(line+10,"%s",module.scanner_id);
			break;
		}
	}
	if(strlen(module.scanner_id) == 0)	
		strcpy(module.FPScanneridExists,"Error");
	if(strlen(module.FP_TYPE) == 0)	
		strcpy(module.FP_TYPE,"Not-Detected");

	fprintf(stdout," module.FP_TYPE= %s\tmodule.scanner_id = %s.. \n",module.FP_TYPE,module.scanner_id);
	free(line);
	fclose(fp);
	line=NULL;
	return;
}
/*int main()
  {

  FPS_Id_and_version();

  }*/
