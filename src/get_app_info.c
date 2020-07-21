#include<header.h>
int Total_Device_Apps=0;
int Applications_Details()
{
	FILE *fp = NULL;

	char *line=NULL,*str=NULL;
	size_t len=20;
	int i,j;

	fp = fopen("/etc/visiontek_Application_release","r");
	if(fp == NULL)
	{
		fprintf(stdout," /etc/visiontek_Application_release  file not found \n");
		return -1;
	}

	for(i=0,j=0;getline(&line, &len, fp) > 0;)
	{
		if((str = (char *)strstr(line,"ApplicationType:")) != NULL)
		{
			strcpy(module.Application[i].Type,str+16);
			if(module.Application[i].Type[ strlen(module.Application[i].Type) -1 ] == '\n')
				module.Application[i].Type[ strlen(module.Application[i].Type) - 1 ]='\0';
			i++;
		}
		else if((str = (char *)strstr(line,"ApplicationName:")) != NULL)
		{
			strcpy(module.Application[j].Name,str+16);
			if(module.Application[j].Name[strlen(module.Application[j].Name)-1] == '\n')
				module.Application[j].Name[strlen(module.Application[j].Name)-1]='\0';
			j++;
		}
		else if((str = (char *)strstr(line,"Version:")) != NULL)
		{
			if( i > 0 && i == j )
			{
				strcpy(module.Application[j-1].Version,str+8);
				if(module.Application[j-1].Version[strlen(module.Application[j-1].Version)-1] == '\n')
					module.Application[j-1].Version[strlen(module.Application[j-1].Version)-1]='\0';
			}
			else 
			{	
				fprintf(stdout," %d  %d \n", i,j);
				fprintf(stdout,"Wrong Application Response in /etc/visiontek_Application_release\n");
				return 0;
			}
		}


		else fprintf(stdout,"Line = %s \n",line);

		if ( i == 49  )
		{
			fprintf(stdout,"Caution: Maximum 50 applications are servered, skipping remains");
			break;
		}


	}
	Total_Device_Apps = i;
	fprintf(stdout," Total_Device_Apps = %d\n", Total_Device_Apps);
	fprintf(stdout," %d  %d \n", i,j);
	free(line);
	line=NULL;
	fclose(fp);

	for(i=0;i<Total_Device_Apps;i++)

		fprintf(stdout,"ApplicationType =%s ,ApplicationName=%s,ApplicationVersion= %s\n",module.Application[i].Type,module.Application[i].Name,module.Application[i].Version);


	return 0;
}
