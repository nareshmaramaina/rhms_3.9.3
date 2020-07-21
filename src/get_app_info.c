#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
int App_updates();
int main()
{
	App_updates();	
	return 0;
}

int App_updates()
{
	FILE *fp = NULL;

	char *line=NULL,*str=NULL;
	int Update_count,Update_flag;
	size_t len=20;
	int i,j,check=0,  Total_Device_Apps=0,  Total_Server_Apps=0;

	char DeviceApplicationType[50][128];
	char DeviceApplicationName[50][128];
	float DeviceApplicationVersion[50];


	memset(DeviceApplicationType,0,sizeof(DeviceApplicationType));
	memset(DeviceApplicationName,0,sizeof(DeviceApplicationName));
	memset(DeviceApplicationVersion,0,sizeof(DeviceApplicationVersion));

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
			strcpy(DeviceApplicationType[i],str+16);
			if(DeviceApplicationType[i][ strlen(DeviceApplicationType[i]) -1 ] == '\n')
				DeviceApplicationType[i][ strlen(DeviceApplicationType[i]) - 1 ]='\0';
			i++;
		}
		else if((str = (char *)strstr(line,"ApplicationName:")) != NULL)
		{
			strcpy(DeviceApplicationName[j],str+16);
			if(DeviceApplicationName[j][strlen(DeviceApplicationName[j])-1] == '\n')
				DeviceApplicationName[j][strlen(DeviceApplicationName[j])-1]='\0';
			j++;
		}
		else if((str = (char *)strstr(line,"Version:")) != NULL)
		{
			if( i > 0 && i == j )
				DeviceApplicationVersion[j-1]  = atof(str+8);

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

		fprintf(stdout,"ApplicationType =%s ,ApplicationName=%s,ApplicationVersion= %.1f \n",DeviceApplicationType[i],DeviceApplicationName[i],DeviceApplicationVersion[i]);


	return 0;
}
