#include<header.h>
char *path="/etc/vision/RHMS/RunningApps/";
int Get_Total_Device_Apps()
{
	int ret,count=0;
	DIR *dp;
	struct dirent *dirp;
	
//	sprintf(path,"/etc/vision/RHMS/Apps/%s/",ServerProjectName);
	dp = opendir(path);
	if( dp == NULL )
		fprintf(stdout,"%s directory not found\n",path);
	else 
	{
		while ( (dirp = readdir(dp)) )
		{
			if (	strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
				continue;


			ret = Check_apps(dirp->d_name);
			if ( ret > 0 )
			{
				count = count+ret;
				fprintf(stdout,"Application Count %d, ApplicatinType = %s \n",ret,dirp->d_name );
			}
		}
		closedir(dp);
	}
	return count;
}
/*int main()
{

	xmlNodePtr Runningchildnode;
	int Total_Running_apps = Get_Total_Device_Apps();

	fprintf(stdout," Total_Running_apps = %d\n",Total_Running_apps);

	if ( Total_Running_apps > 0 )
		Running_Apps_Details(Total_Running_apps,Runningchildnode);

	return 0;
}*/
int Check_apps(const char *file)
{
	int count=0;
	char Extend_path[440];
	DIR *dp;
	struct dirent *dirp;
	memset(Extend_path,0,sizeof(Extend_path));
	sprintf(Extend_path,"%s/%s",path,file);
	dp = opendir(Extend_path);
	if( dp == NULL)
		return -1;
	else
	{
		while ( ( dirp = readdir(dp) ) )
		{
			if (    strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
				continue;
			memset(Extend_path,0,sizeof(Extend_path));
			sprintf(Extend_path,"%s/%s/%s/app.info",path,file,dirp->d_name);

			if ( access(Extend_path,F_OK) == 0 )
			{
				count++;
				fprintf(stdout," %s \n",Extend_path );
			}
			else 
				fprintf(stdout," file %s not found \n",Extend_path );


		}
		closedir(dp);
	}
	return count;
}
void Running_Apps_Details(int Total_Device_Running_Apps, xmlNodePtr Runningchildnode)
{
	char Device_Application_release_file[488];
	xmlNodePtr Runningchildofchildnode = NULL;/* node pointers */
	struct Device
	{
		char Version[24];
		char Type[128];
		char Name[128];
	};
	struct Device RunningApplication[Total_Device_Running_Apps];
	struct POSApplication
	{
		char Type[128];
		char Name[128];
		char Version[24];
	}DeviceApplication;
	int i,ret,Running_apps=0;
	char Extend_path[400];
	DIR *dp,*Inner_dp;
	struct dirent *dirp,*Inner_dirp;
	dp = opendir(path);
	if( dp == NULL )
	{
		fprintf(stdout,"%s directory not found\n",path);
		return;
	}
	while ( (dirp = readdir(dp)) )
	{
		if (    strcmp(dirp->d_name,".") == 0 || strcmp(dirp->d_name,"..") == 0 )
			continue;


		memset(Extend_path,0,sizeof(Extend_path));
		sprintf(Extend_path,"%s/%s",path,dirp->d_name);
		Inner_dp = opendir(Extend_path);
		if( Inner_dp == NULL)
		{
			continue;
		}
		else
		{
			while ( ( Inner_dirp = readdir(Inner_dp) ) )
			{
				if (    strcmp(Inner_dirp->d_name,".") == 0 || strcmp(Inner_dirp->d_name,"..") == 0 )
					continue;
				memset(Device_Application_release_file,0,sizeof(Device_Application_release_file));
				sprintf(Device_Application_release_file,"%s/%s/app.info",Extend_path,Inner_dirp->d_name);
				if ( access(Device_Application_release_file,F_OK) == 0 )
				{
					memset(&DeviceApplication,0,sizeof(struct POSApplication));
					ret = Device_App_info_Details(Device_Application_release_file,DeviceApplication.Type,DeviceApplication.Name,DeviceApplication.Version );
					if ( ret == 0 )
					{
						if ( strlen(DeviceApplication.Type) == 0 && strlen(DeviceApplication.Name) )
						{
							fprintf(stderr,"Wrong application Details in %s file\n",Device_Application_release_file);	
							continue;
						}
						strcpy(RunningApplication[Running_apps].Type,DeviceApplication.Type);
						strcpy(RunningApplication[Running_apps].Name,DeviceApplication.Name);
						strcpy(RunningApplication[Running_apps].Version,DeviceApplication.Version);
						Running_apps++;
					}

				}
				else fprintf(stdout,"%s file not found\n",Device_Application_release_file);

			}
			closedir(Inner_dp);
		}

	}
	closedir(dp);


	for(i=0;i<Running_apps;i++)
	{       
		fprintf(stdout,"Running ApplicationType =%s ,ApplicationName=%s,ApplicationVersion= %s\n",RunningApplication[i].Type,RunningApplication[i].Name,RunningApplication[i].Version);
		Runningchildofchildnode = xmlNewChild(Runningchildnode, NULL, BAD_CAST "Application",NULL);
		xmlNewChild(Runningchildofchildnode, NULL, BAD_CAST "ApplicationType", BAD_CAST RunningApplication[i].Type);
		xmlNewChild(Runningchildofchildnode, NULL, BAD_CAST "ApplicationName", BAD_CAST RunningApplication[i].Name);
		xmlNewChild(Runningchildofchildnode, NULL, BAD_CAST "ApplicationVer", BAD_CAST RunningApplication[i].Version);
	} 

	return;
}
