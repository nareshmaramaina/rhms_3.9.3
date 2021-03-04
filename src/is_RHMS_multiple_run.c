#include<header.h>
//char LatestProjectName[128];
int Get_RHMS_runtime_and_Delete_Hw_Info_On_ProjectChange()
{
	FILE *fp = NULL;
	size_t len=0;
	char *str=NULL; 
	int time = 0;
	char LatestProjectName[128];
	static char LastProjectName[128];
	int sizeofBuffer;

	fp = fopen("/etc/Health_response","r");

	if ( fp == NULL )
	{
		fprintf(stderr,"/etc/Health_response open error\n");
		return -1;	
	}	

	while((getline(&str,&len,fp)) != -1)
	{

		if((strstr(str,"ProjectName:")) != NULL)
		{
			memset(LatestProjectName,0,sizeof(LatestProjectName));
			sizeofBuffer = sizeof(LatestProjectName);
			if( strlen(str+12) > sizeofBuffer )
			{
				fprintf(stderr,"Invalid: LatestProjectName Length More than %d bytes \n",sizeofBuffer);
				continue;
			}
			strcpy(LatestProjectName,str+12);
			if(LatestProjectName[strlen(LatestProjectName)-1] == '\n')
				LatestProjectName[strlen(LatestProjectName)-1]='\0';

		}

		else if  (strstr(str,"UpdateFrequency:") != NULL )
			time = atoi(str+16);
		else if (      strstr(str,"Units:DailyOnce") != NULL )
			time = 100;
		else if (      strstr(str,"Units:EveryBoot") != NULL )
			time = 200;
		else if (      strstr(str,"Units:Minutes") != NULL )
			time = time*60;
		else if (      strstr(str,"Units:Hours") != NULL )
			time = time*60*60;

		//		fprintf(stdout,"%s\n",str);
	}
	free(str);
	str=NULL;	
	fclose(fp);

	if ( strlen(LastProjectName) > 0  && strcmp(LastProjectName,LatestProjectName) != 0 )
	{
		fprintf(stdout," Project Changed LastProjectName = %s ,LatestProjectName = %s\n So Deleting Last Hardware Info Details\n",LastProjectName,LatestProjectName);
		remove("/opt/.rhms_Hardware_status_date_update");	
		remove("/var/log/Health/Last_Hardware_Status.xml");
	}


	if ( time < 60 || time  > 82800)
		time =-1;

	memset(LastProjectName,0,sizeof(LastProjectName));
	strcpy(LastProjectName,LatestProjectName);
	fprintf(stdout,"Final UpdateFrequency in secs = %d, Project Name = %s \n",time,LastProjectName);

	return time;
}
