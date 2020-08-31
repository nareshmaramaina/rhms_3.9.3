#include <header.h>
extern short int GPS_Success,Second_Time_For_GPS;
int Run_Loop(short int ret, int run_time)
{
	char machineid[64]="";
	
	if ( run_time == 100   ||  run_time == 200 )
	{
		if ( CONFIG.GPS && GPS_Success == 0 )
		{
			Second_Time_Health_Info_sending_for_GPS();
			if( GPS_Success == 1 )
			{
				check_net_connection(); //Blocking For autoapn details

				Periodic_Health_Status_Details();

				External_Devices_SerialNo_info();

				Second_Time_For_GPS = 1;
		
				printf("Second Time GPS Found, Send the Health updation details again\n");
				
				return 1;
			}
		}

		if ( ret == 0)
		{
			get_machineid(machineid);
			reboot_device(machineid[9]);
		}
		return 0;
	}


	else	if ( ret == 0 && run_time % 60 == 0)
	{
		fprintf(stdout,"RHMS: Next Health request run_time = %d\n",run_time);
		sleep(run_time);

		check_net_connection(); //Blocking For autoapn details

		Periodic_Health_Status_Details();

		External_Devices_SerialNo_info();

		printf("Health Configuration Run Time Finished, Send the Health updation details again\n");
		
		return 1;
	}

	else
	{
		fprintf(stderr,"Exiting, Some thing Went wrong ( Unknown Case ) , run_time = %d\n",run_time);
		return -1;
	}
}
