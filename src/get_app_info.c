#include<header.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


/*int main()
  {
  int Total_Current_Server_Apps=0;
  Total_Current_Server_Apps = Get_Total_Server_Apps();
  fprintf(stdout,"Total_Current_Server_Apps = %d\n", Total_Current_Server_Apps);
  if( Total_Current_Server_Apps > 0 )
  App_updates(Total_Current_Server_Apps);
  else fprintf(stdout," No Server Apps Found, Apps request/response not happened    \n");	
  return 0;
  }*/
extern char ServerProjectName[128];
char *Server_Application_release_file="/etc/vision/RHMS/Apps/ServerApplicationsRelease.info";
int Applications_Details(int Total_Current_Server_Apps,xmlNodePtr childnode)
{
	xmlNodePtr childofchildnode = NULL;
	struct RHMSApplication
	{
		char Type[128];
		char Name[128];
		float Version;
	}ServerApplication[Total_Current_Server_Apps];

	struct POSApplication
	{
		char Type[128];
		char Name[128];
		float Version;
	}DeviceApplication;
	struct Device
	{
		char Version[12];
		char Type[128];
		char Name[128];
	};
	struct Device RunningApplication[Total_Current_Server_Apps];
	struct Device Application[Total_Current_Server_Apps];
	char Device_Application_release_file[456];
	FILE *fp = NULL;
	char *line=NULL,*str=NULL;
	size_t len=20,sizeofBuffer=0;
	int ret, i,j,check=0,  Total_Server_Apps=0;
	memset(ServerApplication,0,sizeof(ServerApplication));
	memset(Application,0,sizeof(Application));
	memset(RunningApplication,0,sizeof(RunningApplication));
	fp = fopen(Server_Application_release_file,"r");
	if(fp == NULL)
	{
		fprintf(stdout," %s  file not found \n",Server_Application_release_file);
		return -1;
	}

	for(i=0,j=0,check=0;getline(&line, &len, fp) > 0;)
	{
		if((str = (char *)strstr(line,"ProjectName:")) != NULL)
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

		else if((str = (char *)strstr(line,"ApplicationType:")) != NULL)
		{
			if( check == 0 || check == 2 || check == 4 )
			{

				sizeofBuffer = sizeof(ServerApplication[i].Type);
				if( strlen(str+16) > sizeofBuffer )
				{
					fprintf(stderr,"Invalid: ServerApplication[%d].Type Length More than %d bytes \n",i,sizeofBuffer);
					continue;
				}

				strcpy(ServerApplication[i].Type,str+16);
				if(ServerApplication[i].Type[ strlen(ServerApplication[i].Type) -1 ] == '\n')
					ServerApplication[i].Type[ strlen(ServerApplication[i].Type) - 1 ]='\0';
				i++;
				check=1;
			}
			else 
			{
				fprintf(stdout,"ApplicationType Error: Wrong Application Response in %s\n",Server_Application_release_file);
				return -1;
			}
		}
		else if((str = (char *)strstr(line,"ApplicationName:")) != NULL)
		{
			if ( check == 1 )
			{
				sizeofBuffer = sizeof(ServerApplication[j].Name);
				if( strlen(str+16) > sizeofBuffer )
				{
					fprintf(stderr,"Invalid: ServerApplication[%d].Name Length More than %d bytes \n",j,sizeofBuffer);
					continue;
				}
				strcpy(ServerApplication[j].Name,str+16);
				if(ServerApplication[j].Name[strlen(ServerApplication[j].Name)-1] == '\n')
					ServerApplication[j].Name[strlen(ServerApplication[j].Name)-1]='\0';
				j++;
				check = 2;
			}
			else 
			{
				fprintf(stdout,"ApplicationName Error: Wrong Application Response in %s\n",Server_Application_release_file);
				return -1;
			}

		}
		else if((str = (char *)strstr(line,"Version:")) != NULL)
		{
			if( check == 2  && i == j )
			{
				ServerApplication[j-1].Version  = atof(str+8);
				check=3;
			}
			else 
			{	
				fprintf(stdout,"Version Error: Wrong Application Response in %s\n",Server_Application_release_file);
				return 0;
			}
		}

		else if((str = (char *)strstr(line,"ApplicationURL:")) != NULL)
		{
			if( check == 3  && i == j )
				check=4;
			else
			{
				fprintf(stdout,"ApplicationURL Error: Wrong Application Response in %s\n",Server_Application_release_file);
				return 0;
			}
		}

		else fprintf(stdout," Line = %s",line);


	}

	Total_Server_Apps = i;
	free(line);
	line=NULL;
	fclose(fp);

	if ( check == 3 )
	{
		fprintf(stdout,"ApplicationURL Error: Wrong Application Response in %s\n",Server_Application_release_file);
		return -1;
	}
	//	for(i=0;i<j;i++)
	//		fprintf(stdout,"ApplicationType =%s ,ApplicationName=%s,ApplicationVersion= %.1f ApplicationURL = %s\n",ServerApplication[i].Type,ServerApplication[i].Name,ServerApplication[i].Version,ServerApplication[i].URL);

	int DeviceApps=0;
	for(i=0,DeviceApps=0;i<Total_Server_Apps;i++)
	{

		memset(Device_Application_release_file,0,sizeof(Device_Application_release_file));
		sprintf(Device_Application_release_file,"/etc/vision/RHMS/Apps/%s/%s/%s/AppUpdated.info",ServerProjectName,ServerApplication[i].Type,ServerApplication[i].Name);
		memset(&DeviceApplication,0,sizeof(struct POSApplication));
		ret = Device_App_info_Details(Device_Application_release_file,DeviceApplication.Type,DeviceApplication.Name,&DeviceApplication.Version );
		if ( ret == 0 )
		{
			strcpy(Application[DeviceApps].Type,DeviceApplication.Type);
			strcpy(Application[DeviceApps].Name,DeviceApplication.Name);
			sprintf(Application[DeviceApps].Version,"%.1f",DeviceApplication.Version);
			DeviceApps++;
		}
		else
		{

			fprintf(stdout,"\033[1;31m Application Management Not installed / No intial Patch Found,  ApplicationType = %s, ApplicationName = %s ServerApplicationVersion = %f \n\033[0m",ServerApplication[i].Type,ServerApplication[i].Name,ServerApplication[i].Version );
		}
	}

	for(i=0;i<DeviceApps;i++)
	{
		fprintf(stdout,"App Management ApplicationType =%s ,ApplicationName=%s,ApplicationVersion= %s\n",Application[i].Type,Application[i].Name,Application[i].Version);
		childofchildnode = xmlNewChild(childnode, NULL, BAD_CAST "Application",NULL);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationType", BAD_CAST Application[i].Type);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationName", BAD_CAST Application[i].Name);
		xmlNewChild(childofchildnode, NULL, BAD_CAST "ApplicationVer", BAD_CAST Application[i].Version);
	}

	return 0;
}
int Get_Total_Server_Apps()
{
	int Total_Server_apps= 0;
	FILE *fp = NULL;
	char *line=NULL;
	int i,j;
	size_t len;
	fp = fopen(Server_Application_release_file,"r");
	if(fp == NULL)
		fprintf(stdout," %s  file not found \n",Server_Application_release_file);
	else 
	{
		for(i=0,j=0;getline(&line, &len, fp) > 0;)
		{
			if(	strstr(line,"ApplicationType:") != NULL)
				i++;	
			else if(	strstr(line,"ApplicationName:")  != NULL)
				j++;

		}
		if( i == j )
			Total_Server_apps=i;
		else 
			fprintf(stdout,"Wrong Response in %s, We Can't Continue \n",Server_Application_release_file); 
		fclose(fp);

	}
	return Total_Server_apps;
}

int Device_App_info_Details(char *Device_Application_release_file,char *DeviceApplicationType,char *DeviceApplicationName,float *DeviceApplicationVersion )
{
	FILE *fp = NULL;
	char *line=NULL,*str=NULL;
	size_t len=0;
	int flag=0;
	fp = fopen(Device_Application_release_file,"r");
	if(fp == NULL)
	{
		fprintf(stdout," %s  file not found \n",Device_Application_release_file);
		return -1;
	}
	else 
	{
		while( (getline(&line, &len, fp) > 0 ))
		{
			if((str = (char *)strstr(line,"ApplicationType:")) != NULL)
			{
				if( strlen(str+16) > 128 )
				{
					fprintf(stderr,"Invalid: DeviceApplicationType Length More than 128 bytes \n");
					continue;
				}

				strcpy(DeviceApplicationType,str+16);
				if(DeviceApplicationType[ strlen(DeviceApplicationType) -1 ] == '\n')
					DeviceApplicationType[ strlen(DeviceApplicationType) - 1 ]='\0';
			}
			else if((str = (char *)strstr(line,"ApplicationName:")) != NULL)
			{
				if( strlen(str+16) > 128 )
				{
					fprintf(stderr,"Invalid: DeviceApplicationName Length More than 128 bytes \n");
					continue;
				}

				strcpy(DeviceApplicationName,str+16);
				if(DeviceApplicationName[strlen(DeviceApplicationName)-1] == '\n')
					DeviceApplicationName[strlen(DeviceApplicationName)-1]='\0';
			}
			else if((str = (char *)strstr(line,"Version:")) != NULL)
			{
				flag=1;
				*DeviceApplicationVersion  = atof(str+8);
				break;
			}


			else fprintf(stdout,"Line = %s \n",line);

		}
		free(line);
		line=NULL;
		fclose(fp);
	}
	if ( flag == 1)
		return 0;
	else 
		return -1;
}
