#include <header.h>
int GPS_Success;
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
	short int Server_ret=0,ret=0,Second_Time_For_GPS = 0,BootTimeSentSuccess=0;
	int run_time = -1;
	char machineid[15];
	int Hardware_run=0,BootTime_run=0,Periodic_run=0;
	ret = rhms_lock();

	if(ret < 0)    /* Case is Not To run Twice*/
	{
		fprintf(stderr,"RHMS Application is already Running\n");
		return -1;
	}


	fprintf(stdout,"\n****************************\n");
	fprintf(stdout,"Application	: %s\n", "RHMS Client");
	fprintf(stdout,"Version 	: %s\n", "3.9.1");
	fprintf(stdout,"***************************\n");

	mkdir_p("/opt/");

	memset(&module,0x00,sizeof(struct terminal_status));
	memset(&CONFIG,0x00,sizeof(struct rhms));
	memset(machineid, 0 ,sizeof(machineid));

	Get_Config_Settings(); // Get Settings for enble or disable each Tag 

	Update_Configured_Server_Addr();

	if ( CONFIG.DOT )
		system("/vision/DOT &> /dev/null &"); // If DOT tag enble, it should run all boot times


	get_machineid(machineid);

	ret = Check_RHMS_All_requests_run(&Hardware_run,&BootTime_run,&Periodic_run); // Check Today With Last RHMS Success Date 

	run_time = is_RHMS_multiple_run();

	if ( ret ==  0 && run_time == 100 ) // Updated for the day when 100 ( Run every day ince flag)
	{
		fprintf(stderr,"RHMS Details are Updated for the Day\n");
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
				Update_Current_Date_with_Time();
				create_Hardware_status_xml_file();
				Server_ret =  Send_Hardware_status_to_server(); 
				if ( Server_ret == -2 )
				{
					fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);
					return Server_ret;
				}

			}
			else 
				update_Hardware_status_date_file();
		}
		if ( ( BootTime_run != 0 || run_time != 100 ) && BootTimeSentSuccess == 0 )
		{
			Update_Current_Date_with_Time();
			ret = create_BootTime_Status_xml_file();
			if ( ret != 0 )
				return -1;

			Server_ret =  Send_BootTime_status_to_server();
			if ( Server_ret == -2 )
			{
				fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);	
				return Server_ret;
			}
			else if ( Server_ret == 0 )
				BootTimeSentSuccess = 1;

		}
		else fprintf(stdout," Boot Time request Already Successed \n");

		if ( Server_ret == -1 && (run_time == 100 || run_time == 200) ) // If network failure
		{
			sleep(3600); // Sleep 1hr
			continue;
		}
		if (  Periodic_run != 0 || Second_Time_For_GPS == 1 || run_time % 60 == 0 )
		{
			check_net_connection(); //Blocking For autoapn details

			Periodic_tags();

			ret = create_Health_Status_xml_file();
			if ( ret != 0 )
				return ret;	
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
		if ( Server_ret == -1 && (run_time == 100 || run_time == 200) ) // If network failure
		{
			sleep(3600); // Sleep 1hr
			continue;
		}


		run_time = is_RHMS_multiple_run();
		ret = Check_RHMS_All_requests_run(&Hardware_run,&BootTime_run,&Periodic_run); // Check Today With Last RHMS Success Date 

		if ( run_time == 100   ||  run_time == 200 )
		{
			if ( CONFIG.GPS && GPS_Success == 0 )
			{
				Second_Time_Health_Info_sending_for_GPS();
				if( GPS_Success == 1 )
				{
					Second_Time_For_GPS = 1;
					continue;
				}
			}

			if ( ret == 0)
				reboot_device(machineid[9]);

			return 0;
		}


		else	if ( ret == 0 && run_time % 60 == 0)
		{
			fprintf(stdout,"RHMS: Sleep run_time = %d\n",run_time);
			sleep(run_time);
			printf("Posting the Health updation details again\n");
		}

		else
		{
			fprintf(stdout,"Exiting, run_time = %d\n",run_time);
			break;

		}

	}

	return ret;

}
