#include<header.h>

void reboot_device(char last_digit) 
{
	struct tm my_tm;

	struct tm *current;

	struct timeval tv;

	short int machine_secs;	

	int mid_sleep_secs,Total_sleep_secs;

	memset(&my_tm,0,sizeof(struct tm));

	current = &my_tm;

	gettimeofday (&tv,NULL);

	current = localtime (&tv.tv_sec) ;
	fprintf(stdout,"%02d:%02d:%02d\n",current->tm_hour,current->tm_min,current->tm_sec);
	if ( current->tm_year+1900 < 2020 )
	{
		fprintf(stderr,"Date Wrong set - Year Error, RHMS Exiting \n");
		return ;
	}


	mid_sleep_secs =  (  (23 - current->tm_hour) * 3600 ) + ( (59 - current->tm_min) * 60 ) + ( (59 - current->tm_sec) + 1 );

	machine_secs = (  atoi(&last_digit) ) * 20 * 60;

	Total_sleep_secs = mid_sleep_secs + machine_secs;

	printf( "\nRHMS: sleep %d secs to reboot\n",Total_sleep_secs);
	printf("midnight sleep secs   = %d\tmachine_secs = %d \nTotal Sleep secs = %d\n", mid_sleep_secs , machine_secs,Total_sleep_secs); 

	sleep( mid_sleep_secs + machine_secs );		

	printf("\n****** Rebooting the Device  for RHMS Daily Run ... ******\n\n"); 	

	system("reboot");

	return;
}

