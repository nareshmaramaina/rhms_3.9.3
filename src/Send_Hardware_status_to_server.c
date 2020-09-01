#include <header.h>
extern char *Hardware_Status_file;
int Send_Hardware_status_to_server (void)
{
	int ret = 0;
	int i=0;

	Update_Current_Date_with_Time();
	create_Hardware_status_xml_file();

	for (i=0; i<5; i++)
	{
		check_net_connection(); //Blocking For autoapn details

		ret = Update_request(1); // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request 

		if(ret == 0)
		{
			fprintf(stderr,"Hardware Updation Success\n");
			mkdir_p("/var/log/Health/");
			copy_file("/var/log/Health/Last_Hardware_Status.xml",Hardware_Status_file);//des,src
			update_Hardware_status_date_file();
			break;
		}

		else if ( ret == -2 )
			break;

		else   
		{
			fprintf(stdout,"***** Hardware Updation Failure, retrying = %d, Waiting for 60secs ****\n",i+1);
			sleep(60);
		}
	}

	return ret;
}

