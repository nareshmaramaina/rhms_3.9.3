#include"header.h"
struct Device
{
	int Total_Solt1_secs;
	int Total_Solt2_secs;
	int Total_Solt3_secs;
	int Total_Solt4_secs;
	int Total_work_secs;
#if BTINFO
	int Total_adapter_secs;
	int Total_charging_secs;
	int Total_discharging_secs;
#endif
}Day;

int main(int argc,char *argv[])
{

	int pid_cnt;

	FILE *fp = popen("pidof DOT | wc -w","r");
	
        if( fp == NULL)
        {
                fprintf(stderr,"\npopen Failed\n");
                return -1;
        }

        else
        {
                fscanf(fp,"%d",&pid_cnt);

                pclose(fp);

                if( pid_cnt > 1)
                {
                        printf("Exiting App,  DOT App Already Running \n");
                        return 0;
                }

        }


	Device_working_secs();
	return 0;
}

int Device_working_secs()
{
	FILE *fp;

	int chameleon_secs = 0 ;

	int Uptime_secs=0,device_secs=0,ret=0;


	char file_name[34]="";

	char Chameleon_filename[34]="";

	int adapter = 0;

	int Charging = 0,Slot_mode=0; 

	int Discharging = 0;

	Calculate_time_diff(Chameleon_filename); 

	memset(&Day,0x00,sizeof(Day));
	if ( makedir_p("/var/log/DOT") != 0)
	{
		makedir_p("/var/");
		makedir_p("/var/log");
		makedir_p("/var/log/DOT");
	}

	fp = fopen(Chameleon_filename,"r");
	if ( fp == NULL )
		fprintf(stderr," First Boot in the Day %s\n",Chameleon_filename);

	else 
	{
		fread(&Day,sizeof(struct Device),1,fp);
		fclose(fp);
#if DEBUG
		printf("Previous Total_work_secs = %d\tDay.Total_Solt1_secs = %d\nDay.Total_Solt2_secs = %d\nDay.Total_Solt3_secs = %d\nDay.Total_Solt4_secs = %d\n",Day.Total_work_secs,Day.Total_Solt1_secs,Day.Total_Solt2_secs,Day.Total_Solt3_secs,Day.Total_Solt4_secs);
#if BTINFO
		printf("Previos Total_work_secs = %d\t Total_charging_secs = %d\n Day.Total_discharging_secs =%d\nDay.Total_adapter_secs = %d\n",Day.Total_work_secs,Day.Total_charging_secs,Day.Total_discharging_secs,Day.Total_adapter_secs);
#endif
#endif

	}

	while( 1 ) 
	{

		fp=fopen("/proc/uptime","r");

		fscanf(fp,"%d",&Uptime_secs);

		fclose(fp);

		memset(file_name,0,sizeof(file_name));

		Slot_mode =  Calculate_time_diff(file_name); 

		if (Slot_mode < 0 )
		{
			memset(&Day,0x00,sizeof(Day));
			fprintf(stderr,"DOT: Date error, Sleep 60\n");
			sleep(60);
			continue;
		}

		ret = strcmp(Chameleon_filename,file_name);

		if ( ret != 0 )
		{
			strcpy(Chameleon_filename,file_name);

			memset(&Day,0x00,sizeof(Day));

		}

		device_secs = Uptime_secs - chameleon_secs;

		Day.Total_work_secs =  Day.Total_work_secs + device_secs;


		if( Slot_mode == 1 )
			Day.Total_Solt1_secs = Day.Total_Solt1_secs + device_secs;
		else if( Slot_mode == 2 )
			Day.Total_Solt2_secs = Day.Total_Solt2_secs + device_secs;

		else if( Slot_mode == 3 )
			Day.Total_Solt3_secs = Day.Total_Solt3_secs + device_secs;

		else if( Slot_mode == 4 )
			Day.Total_Solt4_secs = Day.Total_Solt4_secs + device_secs;


#if BTINFO
		Adapter_status(&adapter, &Charging, &Discharging);

		if( adapter == 1 )
			Day.Total_adapter_secs = Day.Total_adapter_secs + device_secs ;
		else if( Charging == 1 )
			Day.Total_charging_secs = Day.Total_charging_secs + device_secs;
		else if( Discharging == 1 )
			Day.Total_discharging_secs = Day.Total_discharging_secs + device_secs;

		else printf(" Battery Information Failed\n");
#endif
		fp = fopen(file_name,"w");

		if ( fp == NULL )
		{

			fprintf(stderr," %s open error\n",file_name);

			return -1;

		}

		fwrite(&Day,sizeof(struct Device),1,fp);
		fclose(fp);

		chameleon_secs = Uptime_secs;	
#if DEBUG
		printf("Total_work_secs = %d\tDay.Total_Solt1_secs = %d\nDay.Total_Solt2_secs = %d\nDay.Total_Solt3_secs = %d\nDay.Total_Solt4_secs = %d\n",Day.Total_work_secs,Day.Total_Solt1_secs,Day.Total_Solt2_secs,Day.Total_Solt3_secs,Day.Total_Solt4_secs);
#if BTINFO
		printf("Total_work_secs = %d\t Total_charging_secs = %d\n Day.Total_discharging_secs =%d\nDay.Total_adapter_secs = %d\n",Day.Total_work_secs,Day.Total_charging_secs,Day.Total_discharging_secs,Day.Total_adapter_secs);
#endif
#endif
		sleep(60);

	}

	return 0;

}

