#include<header.h>
int Downloaded_DateAndTime_Version_Details(char *DownloadCompletedFile,float *DownloadedVersion,char *Downloaded_DateAndTime)
{
	FILE *fp = NULL;
	char *line=NULL,*str=NULL;
	size_t len=0;
	int flag=0;
	fp = fopen(DownloadCompletedFile,"r");
	if(fp == NULL)
	{
		fprintf(stdout," %s  file not found \n",DownloadCompletedFile);
		return -1;
	}
	else
	{
		while( (getline(&line, &len, fp) > 0 ))
		{
			if((str = (char *)strstr(line,"Version:")) != NULL)
				*DownloadedVersion=atof(str+8);

			else if((str = (char *)strstr(line,"Downloaded_DateAndTime=")) != NULL)
			{
				strcpy(Downloaded_DateAndTime,str+23);
				if(Downloaded_DateAndTime[strlen(Downloaded_DateAndTime)-1] == '\n')
					Downloaded_DateAndTime[strlen(Downloaded_DateAndTime)-1]='\0';
				if ( strlen(Downloaded_DateAndTime) == 19 )
					flag=1;
				else fprintf(stderr,"Downloaded_DateAndTime = %s , Date and Time Error\n",Downloaded_DateAndTime);
				break;
			}


			else fprintf(stdout,"Line = %s \n",line);

		}
		free(line);
		line=NULL;
		fclose(fp);
	}
	fprintf(stdout,"DownloadedVersion = %.1f Downloaded_DateAndTime = %s\n",*DownloadedVersion,Downloaded_DateAndTime);
	if ( flag == 1  )
		return 0;
	else
		return -1;
}

