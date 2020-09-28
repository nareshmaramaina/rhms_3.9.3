#include<header.h>
extern char ServerProjectName[128];
int is_RHMS_multiple_run()
{
	FILE *fp = NULL;
	size_t len=0,sizeofBuffer=0;
	char *str=NULL; 
	int time = 0;


	fp = fopen("/etc/Health_response","r");

	if ( fp == NULL )
	{
		fprintf(stderr,"/etc/Health_response open error\n");
		return -1;	
	}	

	while((getline(&str,&len,fp)) != -1)
	{
		if ( strstr(str,"ProjectName:") != NULL )
		{

			if ( strlen(ServerProjectName) == 0 )
			{
				memset(ServerProjectName,0,sizeof(ServerProjectName));
				sizeofBuffer = sizeof(ServerProjectName);
				if( strlen(str+12) > sizeofBuffer )
				{
					fprintf(stderr,"Invalid: ServerProjectName Length More than %d bytes \n",sizeofBuffer);
					continue;
				}
				strcpy(ServerProjectName,str+12);
				if(ServerProjectName[strlen(ServerProjectName)-1] == '\n')
					ServerProjectName[strlen(ServerProjectName)-1]='\0';
			}


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

	if ( time < 60 || time  > 82800)
		time =-1;

	fprintf(stdout,"Final UpdateFrequency in secs = %d\n",time);

	return time;
}
