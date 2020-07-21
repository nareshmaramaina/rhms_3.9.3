#include <header.h>
int GPS_Success;

int main()
{
	short int run_time = 0,ret=0;	
	char machineid[15];

	fprintf(stdout,"\n****************************\n");
	fprintf(stdout,"Application	: %s\n", "RHMS Client");
	fprintf(stdout,"Version 	: %s\n", "3.9.1");
	fprintf(stdout,"***************************\n");

	mkdir_p("/opt/");

	memset(&module,0x00,sizeof(struct terminal_status));
	memset(&CONFIG,0x00,sizeof(struct rhms));
	memset(machineid, 0 ,sizeof(machineid));

	Get_Config_Settings(); // Get Settings for enble or disable each Tag 


	if ( CONFIG.DOT )
		system("/vision/DOT &> /dev/null &"); // If DOT tag enble, it should run all boot times


	get_machineid(machineid);

	ret = RTC_info_and_Check_RHMS_run(); // Check Today With Last RHMS Success Date 


	run_time = is_RHMS_multiple_run();

	if ( ret ==  0 && run_time == 100 ) // Updated for the day when 100 ( Run every day ince flag)
	{
		fprintf(stderr,"RHMS Details are Updated for the Day\n");
		reboot_device(machineid[9]);
		return 0;
	}

	POS_HEALTH_DETAILS();

	ret = 	Is_Hardware_Status_changed();

	if ( ret != 0) // on return 0 No Change, return non zero  Changes happened
	{
		create_Hardware_status_xml_file();
		ret =  Send_Hardware_status_to_server(); 
		if ( ret == -2 )
		{
			fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);
			return ret;
		}

	}


	create_BootTime_Status_xml_file();


	while(1)
	{
		ret = create_Health_Status_xml_file();
		if ( ret != 0 )
			return ret;	

		ret =  Send_Hardware_status_to_server(); 

		if ( ret == -2 )
		{
			fprintf(stderr," Please Do Register Serial Number = %s, Macid = %s in RHMS\n",module.SerialNo,module.macid);	
			return ret;
		}
		else if ( ret == -1 && (run_time == 100 || run_time == 200) ) // If network failure
		{
			sleep(3600); // Sleep 1hr
			continue;
		}


		run_time = is_RHMS_multiple_run();


		if ( run_time == 100   ||  run_time == 200 )
		{
			if ( CONFIG.GPS && GPS_Success == 0 )
			{
				Second_Time_Health_Info_sending_for_GPS();
				if( GPS_Success == 1 )
					continue;
			}
			reboot_device(machineid[9]);
			return 0;
		}


		else	if ( run_time >= 60 && run_time <= 86400)
		{

			fprintf(stdout,"RHMS: Sleep run_time = %d\n",run_time);

			sleep(run_time);
			printf("Posting the Health updation details again\n");

			if( ( RTC_info_and_Check_RHMS_run() > 0 ) && ( ret == 0 ) ) // Check Today With Last RHMS Success Date 
				system("reboot");

			Periodic_tags();
		}

		else break;

	}

	return ret;

}
