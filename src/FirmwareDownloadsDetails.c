#include<header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

extern char *Install_Firmwares_file;
extern char *Standard_Firmwares_path;

int FirmwareDownloadsDetails(int TotalFirmwareDownloads,xmlNodePtr childnode)
{
	char FirmwareDownloadCompletedFile[356];
	xmlNodePtr childofchildnode = NULL;
	char FirmwarePatchFileName[TotalFirmwareDownloads][340];	
	struct Firmwares
	{
		char Name[128];
		char Version[12];
		char Downloaded_DateAndTime[34]; 
	}Firmware[TotalFirmwareDownloads];
	FILE *fp = NULL;
	char *line=NULL;
	size_t len=0,sizeofBuffer=0;
	int ret,i, DownloadCount=0,TotalFirmwareCount=0;
	char FirmwareName[128];
	char Downloaded_DateAndTime[34]; 
	float Version,DownloadedVersion;

	memset(FirmwarePatchFileName,0,sizeof(FirmwarePatchFileName));
	memset(Firmware,0,sizeof(Firmware));




	fp = fopen(Install_Firmwares_file,"r");
	if ( fp == NULL )
	{
		fprintf(stdout," file not found %s\n",Install_Firmwares_file);
		return -1;
	}

	DownloadCount=0;	
	while( (getline(&line, &len, fp) > 0) )
	{
		if ( line[strlen(line)-1] == '\n' )
			line[strlen(line)-1] = '\0';

		if( (strstr(line,Standard_Firmwares_path) != NULL) )
		{
			if ( access(line,F_OK) != 0 )
			{
				fprintf(stderr,"%s file not found\n",line);
				continue;
			}
			sizeofBuffer = sizeof(FirmwarePatchFileName[DownloadCount]);
			if( strlen(line) > sizeofBuffer )
			{
				fprintf(stderr,"Invalid: FirmwarePatchFileName[%d] Length More than %d bytes \n",DownloadCount,sizeofBuffer);
				continue;
			}

			strcpy(FirmwarePatchFileName[DownloadCount],line);
			DownloadCount++;
		}
	}
	free(line);
	line=NULL;
	fclose(fp);




	for(i=0,TotalFirmwareCount=0;i < DownloadCount;i++)
	{
		memset(FirmwareName,0,sizeof(FirmwareName));
		Version=0;
		ret = Get_Tokens_of_FirmwarePatchfile(FirmwarePatchFileName[i],FirmwareName,&Version);
		printf("S.No %d, FirmwareName = %s  Version= %.1f\n" ,i+1,FirmwareName,Version);
		if( ret  != 0 )
			continue;

		memset(FirmwareDownloadCompletedFile,0,sizeof(FirmwareDownloadCompletedFile));
		sprintf(FirmwareDownloadCompletedFile,"%s/%s/%.1f_DownloadCompleted", Standard_Firmwares_path,FirmwareName,Version);
		memset(Downloaded_DateAndTime,0,sizeof(Downloaded_DateAndTime));
		DownloadedVersion=0;
		ret =  Downloaded_DateAndTime_Version_Details(FirmwareDownloadCompletedFile,&DownloadedVersion, Downloaded_DateAndTime);
		if ( ret == 0 )
		{
			strcpy(Firmware[TotalFirmwareCount].Name,FirmwareName);
			strcpy(Firmware[TotalFirmwareCount].Downloaded_DateAndTime,Downloaded_DateAndTime);
			sprintf(Firmware[TotalFirmwareCount].Version,"%.1f",DownloadedVersion);
			TotalFirmwareCount++;
		}
		else
		{
			fprintf(stderr,"Firmware Downloaded Date and Time /Version Error, file %s\n",FirmwareDownloadCompletedFile);
		}
	}
	fprintf(stdout,"Download Complete TotalFirmwaresCount = %d\n",TotalFirmwareCount);

	for(i=0;i< TotalFirmwareCount ;i++)
	{
		fprintf(stdout,"Firmware[%d].Name = %s, Firmware[%d].Downloaded_DateAndTime = %s ,Firmware[%d].Version = %s\n",i,Firmware[i].Name,i,Firmware[i].Downloaded_DateAndTime,i,Firmware[i].Version);
		childofchildnode = xmlNewChild(childnode, NULL, BAD_CAST "FirmwareDownload",NULL);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "FirmwareName", BAD_CAST Firmware[i].Name);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "FirmwareVer", BAD_CAST Firmware[i].Version);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "Date_Time", BAD_CAST Firmware[i].Downloaded_DateAndTime);
	}

	return 0;
}
