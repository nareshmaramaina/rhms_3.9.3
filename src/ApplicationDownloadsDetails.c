#include<header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

extern char *Standard_Apps_path;
extern char *Install_Applications_file;

int ApplicationDownloadsDetails(int TotalApplicationDownloads,xmlNodePtr childnode)
{
	char ApplicationDownloadCompletedFile[356];
	xmlNodePtr childofchildnode = NULL;
	char ApplicationPatchFileName[TotalApplicationDownloads][340];	
	struct Applications
	{
		char Type[128];
		char Name[128];
		char Version[12];
		char Downloaded_DateAndTime[34]; 
	}Application[TotalApplicationDownloads];
	FILE *fp = NULL;
	char *line=NULL;
	size_t len=0;
	int ret,i, DownloadCount=0,TotalApplicationCount=0;
	char ApplicationName[128];
	char ApplicationType[128];
	char Downloaded_DateAndTime[34]; 
	float Version,DownloadedVersion;

	memset(ApplicationPatchFileName,0,sizeof(ApplicationPatchFileName));
	memset(Application,0,sizeof(Application));




	fp = fopen(Install_Applications_file,"r");
	if ( fp == NULL )
	{
		fprintf(stdout," file not found %s\n",Install_Applications_file);
		return -1;
	}

	DownloadCount=0;	
	while( (getline(&line, &len, fp) > 0) )
	{
		if ( line[strlen(line)-1] == '\n' )
			line[strlen(line)-1] = '\0';

		if( (strstr(line,Standard_Apps_path) != NULL) )
		{
			if ( access(line,F_OK) != 0 )
			{
				fprintf(stderr,"%s file not found\n",line);
				continue;
			}
			strcpy(ApplicationPatchFileName[DownloadCount],line);
			DownloadCount++;
			break;
		}
	}
	free(line);
	line=NULL;
	fclose(fp);




	for(i=0,TotalApplicationCount=0;i < DownloadCount;i++)
	{
		memset(ApplicationName,0,sizeof(ApplicationName));
		memset(ApplicationType,0,sizeof(ApplicationType));
		Version=0;
		ret = Get_Tokens_of_ApplicationPatchfile(ApplicationPatchFileName[i],ApplicationType,ApplicationName,&Version);
		printf("S.No %d, ApplicationName = %s  Version= %.1f\n" ,i+1,ApplicationName,Version);
		if( ret  != 0 )
			continue;

		memset(ApplicationDownloadCompletedFile,0,sizeof(ApplicationDownloadCompletedFile));
		sprintf(ApplicationDownloadCompletedFile,"%s/%s/%s/DownloadCompleted",Standard_Apps_path,ApplicationType,ApplicationName);
		memset(Downloaded_DateAndTime,0,sizeof(Downloaded_DateAndTime));
		DownloadedVersion=0;
		ret =  Downloaded_DateAndTime_Version_Details(ApplicationDownloadCompletedFile,&DownloadedVersion, Downloaded_DateAndTime);
		if ( ret == 0 )
		{
			strcpy(Application[TotalApplicationCount].Type,ApplicationType);
			strcpy(Application[TotalApplicationCount].Name,ApplicationName);
			strcpy(Application[TotalApplicationCount].Downloaded_DateAndTime,Downloaded_DateAndTime);
			sprintf(Application[TotalApplicationCount].Version,"%.1f",DownloadedVersion);
			TotalApplicationCount++;
		}
		else
		{
			fprintf(stderr,"Application Downloaded Date and Time /Version Error, file %s\n",ApplicationDownloadCompletedFile);
		}
	}

	for(i=0;i< TotalApplicationCount ;i++)
	{
		fprintf(stdout,"Application[%d].Name = %s, Application[%d].Downloaded_DateAndTime = %s ,Application[%d].Version = %s",i,Application[i].Name,i,Application[i].Downloaded_DateAndTime,i,Application[i].Version);
		childofchildnode = xmlNewChild(childnode, NULL, BAD_CAST "Application",NULL);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationType ", BAD_CAST Application[i].Type);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationName", BAD_CAST Application[i].Name);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationVer", BAD_CAST Application[i].Version);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "Date_Time", BAD_CAST Application[i].Downloaded_DateAndTime);
	}

	return 0;
}
