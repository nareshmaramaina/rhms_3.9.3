#include <header.h>
int Send_BootTime_status_to_server (void)
{
	int ret = 0;
	int i=0;

	for (i=0; i<5; i++)
	{
		check_net_connection(); //Blocking For autoapn details

		ret = Update_request(2); // arg 1 For Hardware request,arg 2 For BootTime request, arg 3 For Periodic Health request 

		if(ret == 0)
		{
			fprintf(stderr,"BootTime Updation Success\n");
			update_BootTime_status_date_file();
			if( CONFIG.DOT )
				remove(DOT_FILE);
			break;
		}

		else if ( ret == -2 )
			break;

		else   
		{
			fprintf(stdout,"***** BootTime Updation Failure, retrying = %d, Waiting for 60secs ****\n",i+1);
			sleep(60);
		}
	}

	return ret;
}

