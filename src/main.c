#include <header.h>
short int GPS_Success,Second_Time_For_GPS;
int rhms_lock()
{
	int fd,ret=0;

	fd = open("/tmp/.rhms_lock",O_CREAT | O_CLOEXEC);

	ret = flock(fd,LOCK_EX|LOCK_NB);

	if (ret != 0)
	{
		close(fd);
		return -1;
	}
	return 0;

}

int main()
{
	short int Server_ret=0,ret=0,BootTimeSentSuccess=0,HardwareRequestFailure=0;
	int run_time = -1;
	char machineid[64];
	int Hardware_run=0,BootTime_run=0,Periodic_run=0;
	ret = rhms_lock();
	int RHMS_Current_Version=4;

	if(ret < 0)    /* Case is Not To run Twice*/
	{
		fprintf(stderr,"RHMS Application is already Running\n");
		return -1;
	}


	mkdir_p("/opt/");

	memset(&module,0x00,sizeof(struct terminal_status));
	memset(&CONFIG,0x00,sizeof(struct rhms));

	fprintf(stdout,"\n****************************\n");
	fprintf(stdout,"Application	: %s\n", "RHMS Client");
	fprintf(stdout,"Version 	: %d\n",RHMS_Current_Version);
	fprintf(stdout,"***************************\n");

	Write_Current_Version(RHMS_Current_Version); // Integer Version Only Have to write, because of Package version
	Get_Config_Settings(); // Get Settings for enble or disable each Tag 
	fprintf(stdout,"RHMS: Sleep 6 secs\n");
	sleep(6); // For Startx Purpose 
	Update_Configured_Server_Addr();

	if ( CONFIG.DOT )
		system("/vision/DOT &> /dev/null &"); // If DOT tag enble, it should run all boot times



	ret = Check_RHMS_All_requests_run(&Hardware_run,&BootTime_run,&Periodic_run); // Check Today With Last RHMS Success Date 

	run_time = is_RHMS_multiple_run();

	if ( ret ==  0 && run_time == 100 ) // Updated for the day when 100 ( Run every day ince flag)
	{
		fprintf(stderr,"RHMS Details are Updated for the Day\n");
		memset(machineid, 0 ,sizeof(machineid));
		get_machineid(machineid);
		reboot_device(machineid[9]);
		return 0;
	}

	POS_HEALTH_DETAILS();


	while(1)
	{
		fprintf(stdout," Hardware_run = %d, BootTime_run = %d, Periodic_run = %d\n",Hardware_run,BootTime_run,Periodic_run);
		if ( Hardware_run != 0 || run_time != 100 )
		{	
			ret = 	Is_Hardware_Status_changed();

			if ( ret != 0) // on return 0 No Change, return non zero  Changes happened
			{
				Server_ret =  Send_Hardware_status_to_server(); 
				if ( Server_ret == -2 )
				{
					fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);
					return Server_ret;
				}
				else if ( Server_ret == -1 )
					HardwareRequestFailure = 1;

				else HardwareRequestFailure = 0;
			}
			else 
				update_Hardware_status_date_file();
		}

		if ( ( BootTime_run != 0 || run_time != 100 ) && BootTimeSentSuccess == 0 )
		{

			Server_ret =  Send_BootTime_status_to_server();
			if ( Server_ret == -2 )
			{
				fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);	
				return Server_ret;
			}
			else if ( Server_ret == 0 )
				BootTimeSentSuccess = 1;

		}
		else 
		{
			BootTimeSentSuccess = 1;
			fprintf(stdout," Boot Time request Already Success \n");
		}

		if (  Periodic_run != 0 || Second_Time_For_GPS == 1 || run_time % 60 == 0 )
		{

			Server_ret =  Send_Periodic_Health_status_to_server();
			if ( Server_ret == -2 )
			{
				fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);	
				return Server_ret;
			}
			else if ( Server_ret == 0 )
			{
				if ( Periodic_run > 0 && Can_i_reboot() == 0 )
				{
					system("reboot");
					return 0;
				}
				Second_Time_For_GPS = 0;

			}
		}


		run_time = is_RHMS_multiple_run();
		ret = Check_RHMS_All_requests_run(&Hardware_run,&BootTime_run,&Periodic_run); // Check Today With Last RHMS Success Date 
		if (  ( Server_ret == -1 || ret != 0 || run_time < 0  || BootTimeSentSuccess == 0 || HardwareRequestFailure == 1) ) // If network failure
		{
			if (  ( run_time % 60 == 0 ) && run_time < 3600  ) 
			{
				fprintf(stdout,"Waiting For %d secs,  Due to Network issue or Hardware/BootTime/PeriodicHealth request Issue\n",run_time);
				sleep(run_time);
			}
			else
			{
				fprintf(stdout,"Waiting For 1Hr, Due to Network issue or Hardware/BootTime/PeriodicHealth request Issue\n");
				sleep(3600); // Sleep 1hr
			}	 
			continue;
		}

		ret = Run_Loop(ret,run_time);

		if ( ret != 1)
			break;
	}

	return ret;

}
