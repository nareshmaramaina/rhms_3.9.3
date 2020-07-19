#include<header.h>
//int get_date_to_send(char *file);
int main()
{
	char file[512];

	DIR *dp;
	struct dirent *dirp;

	FILE *fp = NULL;

	char today[14];

	memset(today,0,sizeof(today));
	memset(file,0,sizeof(file));

	struct tm *intim;
	struct tm my_tm;
	struct timeval tv;

	intim = &my_tm;

	memset(intim,0,sizeof(struct tm));

	gettimeofday (&tv,NULL);

	intim = localtime (&tv.tv_sec) ;

	sprintf(today,"%02d%02d%04d",intim->tm_mday,intim->tm_mon+1,intim->tm_year+1900);

	dp = opendir("/var/log/DOT");

	if ( dp == NULL )
	{
		return -1;
	}

	else 
	{
		while( dirp = readdir(dp) )
		{

			if ( strstr(dirp->d_name,"_work.log") != NULL)
			{
				if ( strstr(dirp->d_name,today) == NULL )
				{
					sprintf(file,"/var/log/%s",dirp->d_name);
					closedir(dp);
					puts(file);
					return 0;
				}
			}

		}
		closedir(dp);
	}
	fprintf(stdout,"file not found\n");
	return -1;
}
