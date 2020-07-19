#include<header.h>
extern int GPS_Success;
void Second_Time_Health_Info_sending_for_GPS()
{
	short int i,ret;

	for ( i = 0 ; i < 15 ; i++ )
	{

		ret = access("/var/.gps_data.txt",F_OK );
		if ( ret == 0 )
		{
			GPS_Success = 1;

			Location_info();

			fprintf(stdout,"GPS Success\n");

			break;	
		}

		fprintf(stderr,"/var/.gps_data.txt file not found, Waiting for GPS information ...\n");
		sleep(60);
	}

	return;
}
void Periodic_tags(void)
{
	short int ret;

	if ( CONFIG.geo_location || CONFIG.GPS )
		Location_info();
	
	if( CONFIG.Iris_or_Biomat )
		iris_status();
	
	
	ret = gl11_iodev_open();
	if ( ret != 0)
	{
		fprintf(stderr,"gl11_iodev_open failed\n");
		return;
	}

	else 
	{
	     if( CONFIG.Printer )
                paper_status();

	    // 	RTC_info();

		battery_status();

		// Comm SIM db signal 
		gl11_iodev_close();
	}

	update_internal_memory_info();
	update_ram_info();
	
	return;
}
