#include <header.h>
int Send_Periodic_Health_status_to_server (void)
{
	int ret = 0;
	int i=0;

	ret = create_Health_Status_xml_file();

	if ( ret != 0 )
		return ret;	

	for (i=0; i<8; i++)
	{
		check_net_connection(); //Blocking For autoapn details

		ret = Update_request(3); // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request 

		if(ret == 0)
		{
			fprintf(stderr,"Health Updation Success\n");
			update_Periodic_Health_status_date_file();
			break;
		}

		else if ( ret == -2 )
			break;

		else   
		{
			fprintf(stdout,"***** Health Updation Failure, retrying = %d, Waiting for 60secs ****\n",i+1);
			sleep(60);
		}
	}

	return ret;
}
