#include<header.h>

int Device_work_records()
{
	struct Device
	{
		int Total_Solt1_secs;
		int Total_Solt2_secs;
		int Total_Solt3_secs;
		int Total_Solt4_secs;
		int Total_work_secs;
		int Total_adapter_secs;
		int Total_charging_secs;
		int Total_discharging_secs;
	}Day;
	int i;


	FILE *fp=NULL;

	char filename[248];
	char Date[14];

	memset(filename,0x00,sizeof(filename));
	memset(&Day,0x00,sizeof(Day));


	if( get_logname(filename) != 0 )
	{
		if( CONFIG.BatteryInfo )
			strcpy(module.BatteryInfo,"ERROR");
		strcpy(module.DOT,"ERROR");
		fprintf(stdout," DOT file not found\n");
		return -1;
	}

	fp = fopen(filename,"r");

	if ( fp == NULL )
	{
		if( CONFIG.BatteryInfo )
			strcpy(module.BatteryInfo,"ERROR");
		strcpy(module.DOT,"ERROR");

		fprintf(stderr,"Error in  opening  %s\n",filename);

		return -1;
	}

	fread(&Day,sizeof(struct Device),1,fp);

	fclose(fp);
	char *ptr=filename+14;
	for ( i =0; i<8; i++)
		Date[i]=ptr[i];
	Date[i]='\0';
	printf("DAte = %s\n",Date);
	strcpy(DOT_FILE,filename);	
	sprintf(module.DOT,"%s/%d/%d/%d/%d",Date,Day.Total_Solt1_secs/60,Day.Total_Solt2_secs/60,Day.Total_Solt3_secs/60,Day.Total_Solt4_secs/60);

	if( CONFIG.BatteryInfo )
		sprintf(module.BatteryInfo,"%s/%d/%d/%d/%d",Date,Day.Total_work_secs/60,Day.Total_adapter_secs/60,Day.Total_charging_secs/60,Day.Total_discharging_secs/60);

#if DEBUG
	fprintf(stdout,"module.DOT = %s \n",module.DOT);
	if( CONFIG.BatteryInfo )
		fprintf(stdout,"module.BatteryInfo= %s \n",module.BatteryInfo);
#endif
	return 0;

}
int get_logname(char *file)
{
	DIR *dp;
	struct dirent *dirp;


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
		while( (dirp = readdir(dp)) )
		{

			if ( strstr(dirp->d_name,"_work.log") != NULL)
			{
				if ( strstr(dirp->d_name,today) == NULL )
				{
					sprintf(file,"/var/log/DOT/%s",dirp->d_name);
					closedir(dp);
					puts(file);
					return 0;
				}
			}

		}
		closedir(dp);
	}
	return -1;
}
