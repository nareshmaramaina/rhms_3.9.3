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


	FILE *fp=NULL;

	char filename[248];
	//	char Date[14];
	int File_day=0,File_month=0,File_year=0;

	memset(filename,0x00,sizeof(filename));
	memset(&Day,0x00,sizeof(Day));


	if( get_logname(filename) != 0 )
	{
		fprintf(stdout," DOT file not found\n");
		return -1;
	}

	fp = fopen(filename,"r");

	if ( fp == NULL )
	{
		fprintf(stderr,"Error in  opening  %s\n",filename);

		return -1;
	}

	fread(&Day,sizeof(struct Device),1,fp);

	fclose(fp);
	sscanf(filename+14,"%02d%02d%04d",&File_day,&File_month,&File_year);


	/*	char *ptr=filename+14;
		for ( i =0; i<8; i++)
		Date[i]=ptr[i];
		Date[i]='\0'; */

	sprintf(module.DOT.Date,"%04d-%02d-%02d",File_year,File_month,File_day);
	printf("module.DOT.Date = %s\n",module.DOT.Date);
	strcpy(DOT_FILE,filename);

	//	strcpy(module.DOT.Date,Date);
	sprintf(module.DOT.Slot1,"%d",Day.Total_Solt1_secs/60);
	sprintf(module.DOT.Slot2,"%d",Day.Total_Solt2_secs/60);
	sprintf(module.DOT.Slot3,"%d",Day.Total_Solt3_secs/60);
	sprintf(module.DOT.Slot4,"%d",Day.Total_Solt4_secs/60);

	if( CONFIG.BatteryInfo )
	{
		sprintf(module.BatteryInfo.Date,"%04d-%02d-%02d",File_year,File_month,File_day);
		printf("module.BatteryInfo.Date = %s\n",module.BatteryInfo.Date);
		//		strcpy(module.BatteryInfo.Date,Date);
		sprintf(module.BatteryInfo.Day_worked_mins,"%d",Day.Total_work_secs/60);
		sprintf(module.BatteryInfo.Day_adapter_mins,"%d",Day.Total_adapter_secs/60);
		sprintf(module.BatteryInfo.Day_charged_mins,"%d",Day.Total_charging_secs/60);
		sprintf(module.BatteryInfo.Day_discharged_mins,"%d",Day.Total_discharging_secs/60);
	}
	return 0;

}
int get_logname(char *file)
{
	DIR *dp;
	struct dirent *dirp;


	char today[14];

	memset(today,0,sizeof(today));

	Get_Current_Date(today);

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
